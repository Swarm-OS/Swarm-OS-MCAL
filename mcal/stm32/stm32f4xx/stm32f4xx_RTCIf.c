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
#include <SysClockIf.h>


typedef enum __stm32f4xx_RTCIf_date_time_format
{
    STM32F4XX_RTCIF_SET_TIME            = 0x01, // time shall be set
    STM32F4XX_RTCIF_SET_DATE            = 0x02, // date shall be set
} stm32f4xx_RTCIf_date_time_format_t;



static void stm32f4xx_RTCIf_disable_write_protection(void);
static void stm32f4xx_RTCIf_enable_write_protection(void);
static std_return_type_t stm32f4xx_RTCIf_enter_init_mode(void);
static void stm32f4xx_RTCIf_leave_init_mode(void);
static void stm32f4xx_RTCIf_bin2bcd(RTCIf_date_time_t *original, RTCIf_date_time_t *converted);
static void stm32f4xx_RTCIf_bcd2bin(RTCIf_date_time_t *original, RTCIf_date_time_t *converted);
static void stm32f4xx_RTCIf_set_date_time(RTCIf_date_time_t *date_time, stm32f4xx_RTCIf_date_time_format_t flags);
static void stm32f4xx_RTCIf_get_date_time(RTCIf_date_time_t *date_time);

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

    stm32f4xx_RTCIf_disable_write_protection();
    std_return_type_t status = stm32f4xx_RTCIf_enter_init_mode();

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

        stm32f4xx_RTCIf_leave_init_mode();
    }
    stm32f4xx_RTCIf_enable_write_protection();
    return E_OK;
}

std_return_type_t RTCIf_deinit()
{
    return E_OK;
}

static void stm32f4xx_RTCIf_disable_write_protection(void)
{
    STM32F4XX_RTC_REG->RTC_WPR.KEY = 0xCA;
    STM32F4XX_RTC_REG->RTC_WPR.KEY = 0x53;
    return;
}

static void stm32f4xx_RTCIf_enable_write_protection(void)
{
    STM32F4XX_RTC_REG->RTC_WPR.KEY = 0xFF;
    return;
}

static std_return_type_t stm32f4xx_RTCIf_enter_init_mode(void)
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

static void stm32f4xx_RTCIf_leave_init_mode(void)
{
    STM32F4XX_RTC_REG->RTC_ISR.INIT = 0;
}

static void stm32f4xx_RTCIf_bin2bcd(RTCIf_date_time_t *original, RTCIf_date_time_t *converted)
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

static void stm32f4xx_RTCIf_bcd2bin(RTCIf_date_time_t *original, RTCIf_date_time_t *converted)
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

    // copy day of week bcd == bin in this case
    converted->bin.day_of_week = original->bcd.day_of_week;
}

static void stm32f4xx_RTCIf_set_date_time(RTCIf_date_time_t *date_time, stm32f4xx_RTCIf_date_time_format_t flags)
{
    RTCIf_date_time_t local_date_time;
    if(date_time->input_format == RTCIF_FORMAT_BIN)
    {
        stm32f4xx_RTCIf_bin2bcd(date_time, &local_date_time);
        date_time = &local_date_time;
    }

    if(flags & STM32F4XX_RTCIF_SET_TIME)
    {
        if(STM32F4XX_RTC_REG->RTC_CR.FMT == 1)
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
    
    if(flags & STM32F4XX_RTCIF_SET_DATE)
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
static void stm32f4xx_RTCIf_get_date_time(RTCIf_date_time_t *date_time)
{
    if(STM32F4XX_RTC_REG->RTC_CR.FMT == 1)
    {
        if(STM32F4XX_RTC_REG->RTC_TR.PM == 1)
        {
            date_time->bcd.is_PM = TRUE;
        }
        else
        {
            date_time->bcd.is_PM = FALSE;
        }
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
    stm32f4xx_RTCIf_disable_write_protection();
    std_return_type_t status = stm32f4xx_RTCIf_enter_init_mode();

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
        stm32f4xx_RTCIf_set_date_time(cfg->time, STM32F4XX_RTCIF_SET_TIME |STM32F4XX_RTCIF_SET_DATE);

        stm32f4xx_RTCIf_leave_init_mode();
    }
    stm32f4xx_RTCIf_enable_write_protection();

    return status;
}

std_return_type_t RTCIf_set_time(RTCIf_date_time_t *time)
{
    stm32f4xx_RTCIf_disable_write_protection();
    std_return_type_t status = stm32f4xx_RTCIf_enter_init_mode();

    if(status == E_OK)
    {
        // set time and day
        stm32f4xx_RTCIf_set_date_time(time, STM32F4XX_RTCIF_SET_TIME);
        stm32f4xx_RTCIf_leave_init_mode();
    }
    stm32f4xx_RTCIf_enable_write_protection();
    return status;
}

std_return_type_t RTCIf_set_date(RTCIf_date_time_t *date)
{
    stm32f4xx_RTCIf_disable_write_protection();
    std_return_type_t status = stm32f4xx_RTCIf_enter_init_mode();

    if(status == E_OK)
    {
        // set time and day
        stm32f4xx_RTCIf_set_date_time(date, STM32F4XX_RTCIF_SET_DATE);
        stm32f4xx_RTCIf_leave_init_mode();
    }
    stm32f4xx_RTCIf_enable_write_protection();
    return status;
}

std_return_type_t RTCIf_set_date_time(RTCIf_date_time_t *date_time)
{
    stm32f4xx_RTCIf_disable_write_protection();
    std_return_type_t status = stm32f4xx_RTCIf_enter_init_mode();

    if(status == E_OK)
    {
        // set time and day
        stm32f4xx_RTCIf_set_date_time(date_time, STM32F4XX_RTCIF_SET_TIME |STM32F4XX_RTCIF_SET_DATE);
        stm32f4xx_RTCIf_leave_init_mode();
    }
    stm32f4xx_RTCIf_enable_write_protection();
    return status;
}

std_return_type_t RTCIf_get_date_time(RTCIf_date_time_t *date_time)
{
    if(date_time->input_format == RTCIF_FORMAT_BCD)
    {
        // RTC stores date time alreay in BCD format
        stm32f4xx_RTCIf_get_date_time(date_time);
    }
    else
    {
        // use temporare variable before converting bcd to binary 
        RTCIf_date_time_t temp_date_time;
        stm32f4xx_RTCIf_get_date_time(&temp_date_time);
        stm32f4xx_RTCIf_bcd2bin(&temp_date_time, date_time);
    }
    
    return E_OK;
}


std_return_type_t RTCIf_set_alarm(identifier_t alarm_id, RTCIf_alarm_handle_t *alarm)
{
    return E_NOT_IMPLEMENTED;
}


std_return_type_t RTCIf_clear_alarm(identifier_t alarm_id)
{
    return E_NOT_IMPLEMENTED;
}


