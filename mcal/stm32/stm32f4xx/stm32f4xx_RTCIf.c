/**
 * @file stm32f4xx_RTCIf.c
 * @author Christoph Lehr
 * @date  9 May 2020
 * @brief File containing STM32F4xx RTC API
 *
 * This file implements the generic RTC interface 
 * API for the STM32F4xx series.
 */

#include <datatypes.h>
#include <RTCIf.h>
#include "stm32f4xx.h"
#include "stm32f4xx_interrupt.h"
#include <SysClockIf.h>


typedef enum __date_time_flags
{
    STM32F4XX_RTCIF_TIME            = 0x01, // use time
    STM32F4XX_RTCIF_DATE            = 0x02, // use date
} date_time_flags_t;

void (*alarm_a_callback)(RTCIf_date_time_t*);   
RTCIf_date_time_t *alarm_a_buffer;
void (*alarm_b_callback)(RTCIf_date_time_t*);   
RTCIf_date_time_t *alarm_b_buffer;

static void disable_write_protection(void);
static void enable_write_protection(void);
static std_return_type_t enter_init_mode(void);
static void leave_init_mode(void);

static std_return_type_t check_bin(RTCIf_bin_date_time_t *time, date_time_flags_t flags);
static std_return_type_t check_bcd(RTCIf_bcd_date_time_t *time, date_time_flags_t flags);
static void bin2bcd(RTCIf_date_time_t *original, RTCIf_date_time_t *converted);
static void bcd2bin(RTCIf_date_time_t *original, RTCIf_date_time_t *converted);

static void set_date_time(RTCIf_date_time_t *date_time, date_time_flags_t flags);
static void get_date_time(RTCIf_date_time_t *date_time);

static void set_alarm(RTCIf_date_time_t *date_time, volatile STM32F4xx_RTC_ARLMxR_Regdef_t *alarm_reg);

std_return_type_t RTCIf_init()
{
    // enable PWR peripheral clock to disable write protection of RTC
    STM32F4xx_PWR_PCLK_EN();
    STM32F4xx_PWR->PWR_CR.DBP = 1;

    // enable LSI
    STM32F4xx_RCC->RCC_CSR.LSION=1;
    while(STM32F4xx_RCC->RCC_CSR.LSIRDY ==0)
    {

    }
    // enable RTC 
    // reset backup domain
    STM32F4xx_RCC->RCC_BDCR.BDRST = 1;
    STM32F4xx_RCC->RCC_BDCR.BDRST = 0;
    // select LSI as RTC source
    STM32F4xx_RCC->RCC_BDCR.RTCSEL = 2;
    // enable RTC clock
    STM32F4xx_RCC->RCC_BDCR.RTCEN = 1;

    disable_write_protection();
    std_return_type_t status = enter_init_mode();

    if(status == E_OK)
    {
        // calculate asynchronous and synchronous prescaler values
        char * input_clock = "RTC Clock Source";
        identifier_t rtc_clock = SysClockIf_get_clock_id(input_clock);
        uint32_t rtc_input_frequency = SysClockIf_get_clock_frequency(rtc_clock);
        
        // asynchronous shall be as large as possible
        uint8_t prescaler_async=0;
        // maximum asynch divisor is 128, therfore start at this value
        for(prescaler_async = 128; prescaler_async >1;prescaler_async--)
        {
            if(rtc_input_frequency % prescaler_async ==0)
            {
                break;
            }
        }
        // prescaler is +1 register
        prescaler_async--;
        // calculate synchronous prescaler
        uint32_t prescaler_synch = rtc_input_frequency/prescaler_async;
        // prescaler is +1 register
        prescaler_synch--;

        // set prescaler values
        STM32F4XX_RTC_REG->RTC_PRER.PREDIV_S = prescaler_synch;
        STM32F4XX_RTC_REG->RTC_PRER.PREDIV_A = prescaler_async;

        
        leave_init_mode();
    }
    enable_write_protection();
    return E_OK;
}

std_return_type_t RTCIf_deinit()
{
    return E_OK;
}

static void disable_write_protection(void)
{
    STM32F4XX_RTC_REG->RTC_WPR.KEY = 0xCA;
    STM32F4XX_RTC_REG->RTC_WPR.KEY = 0x53;
    return;
}

static void enable_write_protection(void)
{
    STM32F4XX_RTC_REG->RTC_WPR.KEY = 0xFF;
    return;
}

static std_return_type_t enter_init_mode(void)
{
    STM32F4XX_RTC_REG->RTC_ISR.INIT = 1;
    for(uint32_t i=0; i<1000000;i++)
    {
        for(uint16_t j=0; j<1000;j++);
        if(STM32F4XX_RTC_REG->RTC_ISR.INITF)
        {
            return E_OK;
        }
    }
    return E_STATE_TIMEOUT;
}

static void 
leave_init_mode(void)
{
    STM32F4XX_RTC_REG->RTC_ISR.INIT = 0;
}

static std_return_type_t check_bin(RTCIf_bin_date_time_t *time, date_time_flags_t flags)
{
    if(flags & STM32F4XX_RTCIF_TIME)
    {
        if(time->minutes >= 60 || time->seconds >= 60 ||
           (time->uses_24h_format != FALSE && time->hour >= 24 ) ||
           (time->uses_24h_format == FALSE && time->hour >  12 ))
        {
            return E_VALUE_OUT_OF_RANGE;
        }
    }

    if(flags & STM32F4XX_RTCIF_DATE)
    {
        // week has 7 days, year has 12 months and max length of a month is 31 days
        if(time->day_of_week >7 || time->month > 12 || time->day_of_month > 31)
        {
            return E_VALUE_OUT_OF_RANGE;
        }
        // february has max 29 days
        if(time->month == 2 && time->day_of_month > 29)
        {
            return E_VALUE_OUT_OF_RANGE;
        }
        // April, June, September and November have only 30 days
        if( (time->month == 4 || time->month == 6 || 
             time->month == 9 || time->month == 11) &&
            time->day_of_month > 30)   
        {
            return E_VALUE_OUT_OF_RANGE;
        }
    }

    return E_OK;
}

static std_return_type_t check_bcd(RTCIf_bcd_date_time_t *time, date_time_flags_t flags)
{
    if(flags & STM32F4XX_RTCIF_TIME)
    {
        if(time->second_tens >= 6 || time->minute_tens >= 6)
        {
            return E_VALUE_OUT_OF_RANGE;
        }

        if(time->uses_24h_format != FALSE)
        {
            if(time->hour_tens > 2 || (time->hour_tens == 2 && time->hour_units >= 4))
            {
                return E_VALUE_OUT_OF_RANGE;
            }
        }
        else
        {
            if(time->hour_tens > 1 || (time->hour_tens == 1 && time->hour_units > 2))
            {
                return E_VALUE_OUT_OF_RANGE;
            }
        }
    }

    if(flags & STM32F4XX_RTCIF_DATE)
    {
        // week has 7 days, max 12 months and max 31 days
        if( time->day_of_week >7 || time->month_tens > 1 || 
            (time->month_tens == 1 && time->month_units > 2) ||
            (time->day_tens == 3 && time->month_units > 1))
        {
            return E_VALUE_OUT_OF_RANGE;
        }
        // febraury has max 29 days
        if(time->month_tens == 0 && time->month_units == 2 && time->day_tens >= 3)
        {
            return E_VALUE_OUT_OF_RANGE;
        }        

        // check if month is April, June, September of November
        if((time->month_tens == 0 && 
            (time->month_units == 4 || time->month_units == 6|| time->month_units == 9)) ||
           (time->month_tens == 1 && time->month_units == 1)
        )
        {
            // check if day of month is the 31st
            if(time->month_units == 3 && time->month_units == 1)
            {
                return E_VALUE_OUT_OF_RANGE;
            }
        } 
    }

    return E_OK;
}

static void bin2bcd(RTCIf_date_time_t *original, RTCIf_date_time_t *converted)
{
    uint8_t unit=0;
    uint8_t tens=0;

    // convert seconds
    unit = original->bin.seconds % 10;
    tens = original->bin.seconds / 10;
    converted->bcd.second_tens = tens;
    converted->bcd.second_units = unit;

    // convert minutes
    unit = original->bin.minutes % 10;
    tens = original->bin.minutes / 10;
    converted->bcd.minute_tens = tens;
    converted->bcd.minute_units = unit;

    // convert hours
    unit = original->bin.hour % 10;
    tens = original->bin.hour / 10;
    converted->bcd.hour_tens = tens;
    converted->bcd.hour_units = unit;

    // set am/pm 
    converted->bcd.is_PM = original->bin.is_PM;
    converted->bcd.uses_24h_format = original->bin.uses_24h_format;

    // copy day of week bcd == bin in this case
    converted->bcd.day_of_week = original->bin.day_of_week;

    // convert day of month
    unit = original->bin.day_of_month % 10;
    tens = original->bin.day_of_month / 10;
    converted->bcd.day_tens = tens;
    converted->bcd.day_units = unit;

    // convert month
    unit = original->bin.month % 10;
    tens = original->bin.month / 10;
    converted->bcd.month_tens = tens;
    converted->bcd.month_units = unit;

    // convert year
    unit = original->bin.year % 10;
    tens = original->bin.year / 10;
    converted->bcd.year_tens = tens;
    converted->bcd.year_units = unit;
    
}

static void bcd2bin(RTCIf_date_time_t *original, RTCIf_date_time_t *converted)
{
    uint8_t temp=0;

    // convert seconds
    temp = original->bcd.second_tens * 10;
    temp +=original->bcd.second_units;
    converted->bin.seconds = temp;

    // convert minute
    temp = original->bcd.minute_tens * 10;
    temp +=original->bcd.minute_units;
    converted->bin.minutes = temp;

    // convert hours
    temp = original->bcd.hour_tens * 10;
    temp +=original->bcd.hour_units;
    converted->bin.hour = temp;

    // convert day of month
    temp = original->bcd.day_tens * 10;
    temp +=original->bcd.day_units;
    converted->bin.day_of_month = temp;

    // convert month
    temp = original->bcd.month_tens * 10;
    temp +=original->bcd.month_units;
    converted->bin.month = temp;

    // convert year
    temp = original->bcd.year_tens * 10;
    temp +=original->bcd.year_units;
    converted->bin.year = temp;

    // copy 1:1 mappings
    converted->bin.day_of_week = original->bcd.day_of_week;
    converted->bin.uses_24h_format = original->bcd.uses_24h_format;
    converted->bin.is_PM = original->bcd.is_PM;
}

static void set_date_time(RTCIf_date_time_t *date_time, date_time_flags_t flags)
{
    RTCIf_date_time_t local_date_time;
    if(date_time->input_format == RTCIF_FORMAT_BIN)
    {
        bin2bcd(date_time, &local_date_time);
        date_time = &local_date_time;
    }

    if(flags & STM32F4XX_RTCIF_TIME)
    {
        if(date_time->bcd.uses_24h_format == FALSE)
        {
            if(date_time->bcd.is_PM != FALSE)
            {
                STM32F4XX_RTC_REG->RTC_TR.PM = 1;
            }
            else
            {
                STM32F4XX_RTC_REG->RTC_TR.PM = 0;
            }
        }
        // read register data
        STM32F4xx_RTC_TR_Regdef_t time_reg;
        time_reg.raw = STM32F4XX_RTC_REG->RTC_TR.raw;

        // set seconds
        time_reg.ST = date_time->bcd.second_tens;
        time_reg.SU = date_time->bcd.second_units;

        // set minuts
        time_reg.MNT = date_time->bcd.minute_tens;
        time_reg.MNU = date_time->bcd.minute_units;

        // set hours
        time_reg.HT = date_time->bcd.hour_tens;
        time_reg.HU = date_time->bcd.hour_units;

        // write data back
        STM32F4XX_RTC_REG->RTC_TR.raw = time_reg.raw ;
    }
    
    if(flags & STM32F4XX_RTCIF_DATE)
    {
        // read register data
        STM32F4xx_RTC_DR_Regdef_t date_reg;
        date_reg.raw = STM32F4XX_RTC_REG->RTC_DR.raw;

        // set day of month
        date_reg.DT = date_time->bcd.day_tens;
        date_reg.DU = date_time->bcd.day_units;

        // set month
        date_reg.MT = date_time->bcd.month_tens;
        date_reg.MU = date_time->bcd.month_units;

        // set year
        date_reg.YT = date_time->bcd.year_tens;
        date_reg.YU = date_time->bcd.year_units;

        // set day of week
        date_reg.WDU = date_time->bcd.day_of_week;

        // write data back
        STM32F4XX_RTC_REG->RTC_DR.raw = date_reg.raw;
    }
}
static void get_date_time(RTCIf_date_time_t *date_time)
{
    if(STM32F4XX_RTC_REG->RTC_CR.FMT == 1)
    {
        date_time->bcd.uses_24h_format = FALSE;
        if(STM32F4XX_RTC_REG->RTC_TR.PM == 1)
        {
            date_time->bcd.is_PM = TRUE;
        }
        else
        {
            date_time->bcd.is_PM = FALSE;
        }
    }
    else
    {
        date_time->bcd.uses_24h_format = TRUE;
    }
    // get seconds
    date_time->bcd.second_tens=STM32F4XX_RTC_REG->RTC_TR.ST;
    date_time->bcd.second_units=STM32F4XX_RTC_REG->RTC_TR.SU;

    // get minuts
    date_time->bcd.minute_tens = STM32F4XX_RTC_REG->RTC_TR.MNT;
    date_time->bcd.minute_units = STM32F4XX_RTC_REG->RTC_TR.MNU;

    // get hours
    date_time->bcd.hour_tens = STM32F4XX_RTC_REG->RTC_TR.HT;
    date_time->bcd.hour_units = STM32F4XX_RTC_REG->RTC_TR.HU;

    // get day of month
    date_time->bcd.day_tens = STM32F4XX_RTC_REG->RTC_DR.DT;
    date_time->bcd.day_units = STM32F4XX_RTC_REG->RTC_DR.DU;

    // get month
    date_time->bcd.month_tens = STM32F4XX_RTC_REG->RTC_DR.MT;
    date_time->bcd.month_units = STM32F4XX_RTC_REG->RTC_DR.MU;

    // get year
    date_time->bcd.year_tens = STM32F4XX_RTC_REG->RTC_DR.YT;
    date_time->bcd.year_units = STM32F4XX_RTC_REG->RTC_DR.YU;

    // get day of week
    date_time->bcd.day_of_week = STM32F4XX_RTC_REG->RTC_DR.WDU;
}

std_return_type_t RTCIf_config(RTCIf_handle_t *cfg)
{

    if(cfg->time->input_format == RTCIF_FORMAT_BCD)
    {
        std_return_type_t status = check_bcd(&cfg->time->bcd,STM32F4XX_RTCIF_TIME |STM32F4XX_RTCIF_DATE);
        if(status != E_OK)
        {
            return status;
        }
    }
    else
    {
        std_return_type_t status = check_bin(&cfg->time->bin, STM32F4XX_RTCIF_TIME |STM32F4XX_RTCIF_DATE);
        if(status != E_OK)
        {
            return status;
        }
    }

    disable_write_protection();
    std_return_type_t status = enter_init_mode();

    if(status == E_OK)
    {
        if(cfg->use_24h_mode != FALSE)
        {
            // use 24 hour mode
            STM32F4XX_RTC_REG->RTC_CR.FMT = 0;
        } 
        else
        {
            // use AM/PM mode
            STM32F4XX_RTC_REG->RTC_CR.FMT = 1;
        }

        // set time and day
        set_date_time(cfg->time, STM32F4XX_RTCIF_TIME |STM32F4XX_RTCIF_DATE);

        
        leave_init_mode();
    }
    enable_write_protection();

    return status;
}

std_return_type_t RTCIf_set_time(RTCIf_date_time_t *time)
{
    if(time->input_format == RTCIF_FORMAT_BCD)
    {
        std_return_type_t status = check_bcd(&time->bcd,STM32F4XX_RTCIF_TIME);
        if(status != E_OK)
        {
            return status;
        }
    }
    else
    {
        std_return_type_t status = check_bin(&time->bin, STM32F4XX_RTCIF_TIME);
        if(status != E_OK)
        {
            return status;
        }
    }

    disable_write_protection();
    std_return_type_t status = enter_init_mode();

    if(status == E_OK)
    {
        // set time and day
        set_date_time(time, STM32F4XX_RTCIF_TIME);
        
        leave_init_mode();
    }
    enable_write_protection();
    return status;
}

std_return_type_t RTCIf_set_date(RTCIf_date_time_t *date)
{
    if(date->input_format == RTCIF_FORMAT_BCD)
    {
        std_return_type_t status = check_bcd(&date->bcd,STM32F4XX_RTCIF_DATE);
        if(status != E_OK)
        {
            return status;
        }
    }
    else
    {
        std_return_type_t status = check_bin(&date->bin, STM32F4XX_RTCIF_DATE);
        if(status != E_OK)
        {
            return status;
        }
    }

    disable_write_protection();
    std_return_type_t status = enter_init_mode();

    if(status == E_OK)
    {
        // set time and day
        set_date_time(date, STM32F4XX_RTCIF_DATE);
        
        leave_init_mode();
    }
    enable_write_protection();
    return status;
}

std_return_type_t RTCIf_set_date_time(RTCIf_date_time_t *date_time)
{
    if(date_time->input_format == RTCIF_FORMAT_BCD)
    {
        std_return_type_t status = check_bcd(&date_time->bcd,STM32F4XX_RTCIF_TIME |STM32F4XX_RTCIF_DATE);
        if(status != E_OK)
        {
            return status;
        }
    }
    else
    {
        std_return_type_t status = check_bin(&date_time->bin, STM32F4XX_RTCIF_TIME |STM32F4XX_RTCIF_DATE);
        if(status != E_OK)
        {
            return status;
        }
    }

    disable_write_protection();
    std_return_type_t status = enter_init_mode();

    if(status == E_OK)
    {
        // set time and day
        set_date_time(date_time, STM32F4XX_RTCIF_TIME |STM32F4XX_RTCIF_DATE);
        
        leave_init_mode();
    }
    enable_write_protection();
    return status;
}

std_return_type_t RTCIf_get_date_time(RTCIf_date_time_t *date_time)
{
    if(date_time->input_format == RTCIF_FORMAT_BCD)
    {
        // RTC stores date time alreay in BCD format
        get_date_time(date_time);
    }
    else
    {
        // use temporare variable before converting bcd to binary 
        RTCIf_date_time_t temp_date_time;
        get_date_time(&temp_date_time);
        bcd2bin(&temp_date_time, date_time);
    }
    
    return E_OK;
}

static void set_alarm(RTCIf_date_time_t *date_time, volatile STM32F4xx_RTC_ARLMxR_Regdef_t *alarm_reg)
{
    RTCIf_date_time_t local_date_time;
    if(date_time->input_format == RTCIF_FORMAT_BIN)
    {
        bin2bcd(date_time, &local_date_time);
        date_time = &local_date_time;
    }

    // read register data
    STM32F4xx_RTC_ARLMxR_Regdef_t time_reg;
    time_reg.raw = alarm_reg->raw;

    if(date_time->bcd.uses_24h_format == FALSE)
    {
        if(date_time->bcd.is_PM != FALSE)
        {
            time_reg.PM = 1;
        }
        else
        {
            time_reg.PM = 0;
        }

    }
    // set seconds
    time_reg.ST = date_time->bcd.second_tens;
    time_reg.SU = date_time->bcd.second_units;

    // set minuts
    time_reg.MNT = date_time->bcd.minute_tens;
    time_reg.MNU = date_time->bcd.minute_units;

    // set hours
    time_reg.HT = date_time->bcd.hour_tens;
    time_reg.HU = date_time->bcd.hour_units;

    // write data back
    alarm_reg->raw = time_reg.raw ;

}

std_return_type_t RTCIf_set_alarm(identifier_t alarm_id, RTCIf_alarm_handle_t *alarm_handle)
{


    if(alarm_handle->alarm->input_format == RTCIF_FORMAT_BCD)
    {
        std_return_type_t status = check_bcd(&alarm_handle->alarm->bcd,STM32F4XX_RTCIF_TIME);
        if(status != E_OK)
        {
            return status;
        }        
        // check_bcd does not support simply checking day
        if(alarm_handle->alarm->bcd.day_of_week>7 || alarm_handle->alarm->bcd.day_tens > 3 ||
           (alarm_handle->alarm->bcd.day_tens == 3 && alarm_handle->alarm->bcd.day_units >1 ))
        {
            return E_VALUE_OUT_OF_RANGE;
        }
    }
    else
    {
        std_return_type_t status = check_bin(&alarm_handle->alarm->bin, STM32F4XX_RTCIF_TIME);
        if(status != E_OK)
        {
            return status;
        }
        // check_bin does not support simply checking day
        if(alarm_handle->alarm->bin.day_of_month > 31 || alarm_handle->alarm->bin.day_of_week>7)
        {
            return E_VALUE_OUT_OF_RANGE;
        }
    }

    if(alarm_id <= 0 || alarm_id > 2 )
    {
        return E_NOT_EXISTING;
    }

    disable_write_protection();
    std_return_type_t status = enter_init_mode();
    if(status == E_OK)
    {
        volatile STM32F4xx_RTC_ARLMxR_Regdef_t *alarm_reg;
        if(alarm_id == 1)
        {
            STM32F4XX_RTC_REG->RTC_CR.ALRAE = 0;
            STM32F4XX_RTC_REG->RTC_CR.ALRAIE = 0;
            alarm_reg = &STM32F4XX_RTC_REG->RTC_ALRMAR;
            alarm_a_callback = alarm_handle->callback;
            alarm_a_buffer = alarm_handle->buffer;
        }
        else
        {
            STM32F4XX_RTC_REG->RTC_CR.ALRBE = 0;
            STM32F4XX_RTC_REG->RTC_CR.ALRBIE = 0;
            alarm_reg = &STM32F4XX_RTC_REG->RTC_ALRMBR;
            alarm_b_callback = alarm_handle->callback;
            alarm_b_buffer = alarm_handle->buffer;
        }
        
        set_alarm(alarm_handle->alarm, alarm_reg);
        alarm_reg->MSK1  = alarm_handle->flags.mask_seconds;
        alarm_reg->MSK2  = alarm_handle->flags.mask_minutes;
        alarm_reg->MSK3  = alarm_handle->flags.mask_hours;
        alarm_reg->MSK4  = alarm_handle->flags.mask_date;
        alarm_reg->WDSEL = alarm_handle->flags.use_day_of_week;

        if(alarm_id == 1)
        {
            STM32F4XX_RTC_REG->RTC_CR.ALRAE  = 1;
            STM32F4XX_RTC_REG->RTC_CR.ALRAIE = 1;
        }
        else
        {
            STM32F4XX_RTC_REG->RTC_CR.ALRBE  = 1;
            STM32F4XX_RTC_REG->RTC_CR.ALRBIE = 1;
        }

        // enable interrupt flags
        STM32F4xx_EXTI->EXTI_IMR    |=  (0x1 << 17);
        STM32F4xx_EXTI->EXTI_RTSR   |=  (0x1 << 17);
        stm32f4xx_enable_interrupt(STM32F4xx_EXTI17_RTC_ALARM_IRQ);

        leave_init_mode();
    }   
    enable_write_protection();
        
    return status;
}


std_return_type_t RTCIf_clear_alarm(identifier_t alarm_id)
{
    if(alarm_id == 1)
    {
        STM32F4XX_RTC_REG->RTC_CR.ALRAE = 0;
        STM32F4XX_RTC_REG->RTC_CR.ALRAIE = 0;

        if(STM32F4XX_RTC_REG->RTC_CR.ALRBE == 0)
        {
            stm32f4xx_disable_interrupt(STM32F4xx_EXTI17_RTC_ALARM_IRQ);
        }
    }
    else if(alarm_id == 2)
    {
        STM32F4XX_RTC_REG->RTC_CR.ALRBE = 0;
        STM32F4XX_RTC_REG->RTC_CR.ALRBIE = 0;

        if(STM32F4XX_RTC_REG->RTC_CR.ALRAE == 0)
        {
            stm32f4xx_disable_interrupt(STM32F4xx_EXTI17_RTC_ALARM_IRQ);
        }
    }
    else
    {
        return E_NOT_EXISTING;
    }
    return E_OK;
}


void EXTI17_RTC_ALARM_Handler()
{
    STM32F4xx_EXTI->EXTI_PR |= (1 << 17) ;
    if(STM32F4XX_RTC_REG->RTC_ISR.ALRAF == 1)
    {
        STM32F4XX_RTC_REG->RTC_ISR.ALRAF = 0; 
        if(alarm_a_buffer != NULL)
        {
            (void) RTCIf_get_date_time(alarm_a_buffer);
        }
        alarm_a_callback(alarm_a_buffer);
    }
    else if(STM32F4XX_RTC_REG->RTC_ISR.ALRBF == 1)
    {
        STM32F4XX_RTC_REG->RTC_ISR.ALRBF = 0; 
        if(alarm_b_buffer != NULL)
        {
            (void) RTCIf_get_date_time(alarm_b_buffer);
        }
        alarm_b_callback(alarm_a_buffer);
    }
}