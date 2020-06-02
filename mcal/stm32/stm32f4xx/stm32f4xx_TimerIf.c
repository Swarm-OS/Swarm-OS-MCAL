/**
 * @file stm32f411_TimerIf.c
 * @author Christoph Lehr
 * @date 30 May 2020
 * @brief STM32F4 implentation of API for configuring Timers
 *
 * This file implements the generic API which shall be used to 
 * interact with the MCUs timer and their functionality
 */

#include <TimerIf.h>
#include <mcus.h>
#include <datatypes.h>
#include <stddef.h>
#include "stm32f4xx.h"

#if IS_MCU(STM32F411)
#   define MAX_TIMER 11
#else if IS_MCU(STM32F407)
#   define MAX_TIMER 14
#endif

typedef struct timer_config
{
    TimerIf_timer_mode_t mode;
    union 
    {
        void (*oc_callback)(void);
        void (*ic_callback)(uint32_t);
        void (*ctc_callback)(void); 
    };
} timer_config_t;

static volatile timer_config_t global_cfg[MAX_TIMER][4];

static boolean timer_exists(identifier_t timer_id);

static std_return_type_t config_16bit_timer(TimerIf_config_t *cfg);
static std_return_type_t config_32bit_timer(TimerIf_config_t *cfg);
static std_return_type_t config_cnt_mode( identifier_t timer_id, STM32F4xx_TIM_CR1_Regdef_t *cr1_reg, TimerIf_counting_mode_t cnt_mode);

static std_return_type_t config_advanced_timer(TimerIf_channel_config_t *cfg);
static std_return_type_t config_general_purpose_timer(TimerIf_channel_config_t *cfg);
static std_return_type_t config_basic_timer(TimerIf_channel_config_t *cfg);

static std_return_type_t config_pwm_output(TimerIf_channel_config_t *cfg);
static std_return_type_t config_output_compare(TimerIf_channel_config_t *cfg);


std_return_type_t TimerIf_init(uint8_t timer_id)
{
    std_return_type_t status = E_OK;
    switch (timer_id)
    {
    case 1:
        STM32F4xx_TIM1_PCLK_EN();
        break;
    case 2:
        STM32F4xx_TIM2_PCLK_EN();
        break;
    case 3:
        STM32F4xx_TIM3_PCLK_EN();
        break;
    case 4:
        STM32F4xx_TIM4_PCLK_EN();
        break;
    case 5:
        STM32F4xx_TIM5_PCLK_EN();
        break;
#if IS_MCU(MCU_STM32F407)
    case 6:
        STM32F4xx_TIM6_PCLK_EN();
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 7:
        STM32F4xx_TIM7_PCLK_EN();
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 8:
        STM32F4xx_TIM8_PCLK_EN();
        break;
#endif
    case 9:
        STM32F4xx_TIM9_PCLK_EN();
        break;
    case 10:
        STM32F4xx_TIM10_PCLK_EN();
        break;
    case 11:
        STM32F4xx_TIM11_PCLK_EN();
        break;
#if IS_MCU(MCU_STM32F407)
    case 12:
        STM32F4xx_TIM12_PCLK_EN();
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
        STM32F4xx_TIM13_PCLK_EN();
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
        STM32F4xx_TIM14_PCLK_EN();
        break;    
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }
    return status;
}

std_return_type_t TimerIf_deinit(uint8_t timer_id)
{
    std_return_type_t status = E_OK;
    switch (timer_id)
    {
    case 1:
        STM32F4xx_TIM1_PCLK_DI();
        break;
    case 2:
        STM32F4xx_TIM2_PCLK_DI();
        break;
    case 3:
        STM32F4xx_TIM3_PCLK_DI();
        break;
    case 4:
        STM32F4xx_TIM4_PCLK_DI();
        break;
    case 5:
        STM32F4xx_TIM5_PCLK_DI();
        break;
#if IS_MCU(MCU_STM32F407)
    case 6:
        STM32F4xx_TIM6_PCLK_DI();
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 7:
        STM32F4xx_TIM7_PCLK_DI();
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 8:
        STM32F4xx_TIM8_PCLK_DI();
        break;
#endif
    case 9:
        STM32F4xx_TIM9_PCLK_DI();
        break;
    case 10:
        STM32F4xx_TIM10_PCLK_DI();
        break;
    case 11:
        STM32F4xx_TIM11_PCLK_DI();
        break;
#if IS_MCU(MCU_STM32F407)
    case 12:
        STM32F4xx_TIM12_PCLK_DI();
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
        STM32F4xx_TIM13_PCLK_DI();
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
        STM32F4xx_TIM14_PCLK_DI();
        break;    
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }
    return status;
}

std_return_type_t TimerIf_Timer_start(uint8_t timer_id)
{
    std_return_type_t status = E_OK;
    switch (timer_id)
    {
    case 1:
        STM32F4XX_TIM1_REG->TIM_CR1.CEN = 1;
        break;
    case 2:
        STM32F4XX_TIM2_REG->TIM_CR1.CEN = 1;
        break;
    case 3:
        STM32F4XX_TIM3_REG->TIM_CR1.CEN = 1;
        break;
    case 4:
        STM32F4XX_TIM4_REG->TIM_CR1.CEN = 1;
        break;
    case 5:
        STM32F4XX_TIM5_REG->TIM_CR1.CEN = 1;
        break;
#if IS_MCU(MCU_STM32F407)
    case 6:
        STM32F4XX_TIM6_REG->TIM_CR1.CEN = 1;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 7:
        STM32F4XX_TIM7_REG->TIM_CR1.CEN = 1;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 8:
        STM32F4XX_TIM8_REG->TIM_CR1.CEN = 1;
        break;
#endif
    case 9:
        STM32F4XX_TIM9_REG->TIM_CR1.CEN = 1;
        break;
    case 10:
        STM32F4XX_TIM10_REG->TIM_CR1.CEN = 1;
        break;
    case 11:
        STM32F4XX_TIM11_REG->TIM_CR1.CEN = 1;
        break;
#if IS_MCU(MCU_STM32F407)
    case 12:
        STM32F4XX_TIM12_REG->TIM_CR1.CEN = 1;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
        STM32F4XX_TIM13_REG->TIM_CR1.CEN = 1;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
        STM32F4XX_TIM14_REG->TIM_CR1.CEN = 1;
        break;    
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }
    return status;
}

std_return_type_t TimerIf_Timer_stop(uint8_t timer_id)
{
    std_return_type_t status = E_OK;
    switch (timer_id)
    {
    case 1:
        STM32F4XX_TIM1_REG->TIM_CR1.CEN = 0;
        break;
    case 2:
        STM32F4XX_TIM2_REG->TIM_CR1.CEN = 0;
        break;
    case 3:
        STM32F4XX_TIM3_REG->TIM_CR1.CEN = 0;
        break;
    case 4:
        STM32F4XX_TIM4_REG->TIM_CR1.CEN = 0;
        break;
    case 5:
        STM32F4XX_TIM5_REG->TIM_CR1.CEN = 0;
        break;
#if IS_MCU(MCU_STM32F407)
    case 6:
        STM32F4XX_TIM6_REG->TIM_CR1.CEN = 0;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 7:
        STM32F4XX_TIM7_REG->TIM_CR1.CEN = 0;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 8:
        STM32F4XX_TIM8_REG->TIM_CR1.CEN = 0;
        break;
#endif
    case 9:
        STM32F4XX_TIM9_REG->TIM_CR1.CEN = 0;
        break;
    case 10:
        STM32F4XX_TIM10_REG->TIM_CR1.CEN = 0;
        break;
    case 11:
        STM32F4XX_TIM11_REG->TIM_CR1.CEN = 0;
        break;
#if IS_MCU(MCU_STM32F407)
    case 12:
        STM32F4XX_TIM12_REG->TIM_CR1.CEN = 0;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
        STM32F4XX_TIM13_REG->TIM_CR1.CEN = 0;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
        STM32F4XX_TIM14_REG->TIM_CR1.CEN = 0;
        break;    
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }
    return status;
}

std_return_type_t TimerIf_config(TimerIf_config_t *cfg)
{

    std_return_type_t status = E_OK;

    if(timer_exists(cfg->timer_id) != FALSE)
    {
        if(cfg->timer_id == 2 || cfg->timer_id == 5)
        {
            status = config_32bit_timer(cfg);
        }
        else if(cfg->timer_id >= 1 && cfg->timer_id <=14)
        {
            status = config_16bit_timer(cfg);
        }
    }
    else
    {
        status = E_NOT_EXISTING;
    }
    return status;
}

static std_return_type_t config_16bit_timer(TimerIf_config_t *cfg)
{
    STM32F4xx_TIM_CR1_Regdef_t *cr1_reg;
    STM32F4xx_TIM_ARR_16bit_Regdef_t *arr_reg;
    STM32F4xx_TIM_PSC_16bit_Regdef_t *psc_reg;
    std_return_type_t status = E_OK;

    switch (cfg->timer_id)
    {
    case 1:
        cr1_reg = &STM32F4XX_TIM1_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM1_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM1_REG->TIM_PSC;
        break;
    case 3:
        cr1_reg = &STM32F4XX_TIM3_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM3_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM3_REG->TIM_PSC;
        break;
    case 4:
        cr1_reg = &STM32F4XX_TIM4_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM4_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM4_REG->TIM_PSC;
        break;
#if IS_MCU(MCU_STM32F407)
    case 6:
        cr1_reg = &STM32F4XX_TIM6_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM6_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM6_REG->TIM_PSC;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 7:
        cr1_reg = &STM32F4XX_TIM7_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM7_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM7_REG->TIM_PSC;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 8:
        cr1_reg = &STM32F4XX_TIM8_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM8_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM8_REG->TIM_PSC;
        break;
#endif
    case 9:
        cr1_reg = &STM32F4XX_TIM9_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM9_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM9_REG->TIM_PSC;
        break;
    case 10:
        cr1_reg = &STM32F4XX_TIM10_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM10_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM10_REG->TIM_PSC;
        break;
    case 11:
        cr1_reg = &STM32F4XX_TIM11_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM11_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM11_REG->TIM_PSC;
        break;
#if IS_MCU(MCU_STM32F407)
    case 12:
        cr1_reg = &STM32F4XX_TIM12_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM12_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM12_REG->TIM_PSC;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
        cr1_reg = &STM32F4XX_TIM13_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM13_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM13_REG->TIM_PSC;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
        cr1_reg = &STM32F4XX_TIM14_REG->TIM_CR1;
        arr_reg = &STM32F4XX_TIM14_REG->TIM_ARR;
        psc_reg = &STM32F4XX_TIM14_REG->TIM_PSC;
        break;    
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }

    if(cfg->period > 0xFFFF || cfg->prescaler > 0xFFFF)
    {
        status = E_VALUE_OUT_OF_RANGE;
    }
    else
    {
        arr_reg->ARR = cfg->period;
        psc_reg->PSC = cfg->prescaler;
    }

    status = config_cnt_mode(cfg->timer_id, cr1_reg, cfg->cnt_mode);

    if(cfg->clk_source != TIMERIF_INTERNAL_CLK)
    {
        status = E_NOT_IMPLEMENTED;
    }

    return status;
}

static std_return_type_t config_32bit_timer(TimerIf_config_t *cfg)
{
    STM32F4xx_TIM_2_5_RegDef_t *timer_reg;
    std_return_type_t status = E_OK;

    if(cfg->timer_id == 2)
    {
        timer_reg = STM32F4XX_TIM2_REG;
    }
    else if(cfg->timer_id == 5)
    {
        timer_reg = STM32F4XX_TIM5_REG;
    }

    timer_reg->TIM_ARR.ARR = cfg->period;
    timer_reg->TIM_PSC.PSC = cfg->prescaler;

    // set counting mode
    status = config_cnt_mode(cfg->timer_id, &timer_reg->TIM_CR1, cfg->cnt_mode);

    if(cfg->clk_source != TIMERIF_INTERNAL_CLK)
    {
        status = E_NOT_IMPLEMENTED;
    }

    return status;
}

static std_return_type_t config_cnt_mode( identifier_t timer_id, STM32F4xx_TIM_CR1_Regdef_t *cr1_reg, TimerIf_counting_mode_t cnt_mode)
{
    std_return_type_t status = E_OK;
    
    if(timer_id == 6 || timer_id == 7 || timer_id >8)
    {
        if(cnt_mode == TimerIf_COUNTING_UP )
        {
            cr1_reg->DIR = 0;
        }
        else if (cnt_mode == TimerIf_COUNTING_DOWN)
        {
            cr1_reg->DIR = 1;
        }
        else
        {
            status = E_NOT_SUPPORTED;
        }
    }
    else
    {
        // change of CMS from center to edge aligned and vice versa is only allowed when CEN == 0
        switch (cnt_mode)
        {
        case TimerIf_COUNTING_UP:
            if(cr1_reg->CEN == 1 && cr1_reg->CMS != 0)
            {
                status = E_STATE_ERR;
            }
            else
            {
                cr1_reg->DIR = 0;
                cr1_reg->CMS = 0;
            }
            break;
        case TimerIf_COUNTING_DOWN:
            if(cr1_reg->CEN == 1 && cr1_reg->CMS != 0)
            {
                status = E_STATE_ERR;
            }
            else
            {
                cr1_reg->DIR = 1;
                cr1_reg->CMS = 0;
            }
            break;
        
        case TimerIf_COUNTING_CENTER_UP:
            if(cr1_reg->CEN == 1 && cr1_reg->CMS == 0)
            {
                status = E_STATE_ERR;
            }
            else
            {
                cr1_reg->CMS = 1;
            }
            break;
        case TimerIf_COUNTING_CENTER_DOWN:
            if(cr1_reg->CEN == 1 && cr1_reg->CMS == 0)
            {
                status = E_STATE_ERR;
            }
            else
            {
                cr1_reg->CMS = 2;
            }
            break;
        case TimerIf_COUNTING_CENTER_UP_DOWN:

            if(cr1_reg->CEN == 1 && cr1_reg->CMS == 0)
            {
                status = E_STATE_ERR;
            }
            else
            {
                cr1_reg->CMS = 3;
            }
            break;
        default:
            status = E_NOT_SUPPORTED;
            break;
        }
    }   
}

std_return_type_t TimerIf_channel_config(TimerIf_channel_config_t *cfg)
{
    std_return_type_t status = E_OK;
    if(cfg->timer_id == 1 || cfg->timer_id == 8)
    {
        status = config_advanced_timer(cfg);
    }
#if IS_MCU(STM32F407)
    else if(cfg->timer_id == 6 || cfg->timer_id == 7)
    {
        status = config_basic_timer(cfg);
    }
#endif
    else if (cfg->timer_id >=2 && cfg->timer_id <= 5)
    {
        status = config_general_purpose_timer(cfg);
    }
    else if (cfg->timer_id >=9 && cfg->timer_id <= 11)
    {
        status = config_general_purpose_timer(cfg);
    }
#if IS_MCU(STM32F407)
    else if (cfg->timer_id >=12 && cfg->timer_id <= 14)
    {
        status = config_general_purpose_timer(cfg);
    }
#endif
    else
    {
        status = E_NOT_EXISTING;
    }
    
    return status;
}

static std_return_type_t config_advanced_timer(TimerIf_channel_config_t *cfg)
{
    std_return_type_t status = E_OK;
    if (cfg->channel_id >4)
    {
        return E_NOT_EXISTING;
    }

    switch (cfg->mode)
    {
    case TIMERIF_MODE_OUTPUT_PWM:
        status = config_pwm_output(cfg);
        break;

    case TIMERIF_MODE_DISABLED:
    case TIMERIF_MODE_NORMAL:
    case TIMERIF_MODE_OUTPUT_COMPARE:
    case TIMERIF_MODE_INPUT_COMPTURE:
    case TIMERIF_MODE_INPUT_PWM_COMPTURE:
    case TIMERIF_MODE_OUTPUT_SINGLE_SHOT:
        status = E_NOT_IMPLEMENTED;
        break;
    
    default:
        status = E_NOT_SUPPORTED;
        break;
    }

    return status;
}

static std_return_type_t config_general_purpose_timer(TimerIf_channel_config_t *cfg)
{
    std_return_type_t status = E_OK;
    if ((cfg->timer_id >= 9 && cfg->channel_id >2) ||
        (cfg->timer_id <= 5 && cfg->channel_id >4))
    {
        return E_NOT_EXISTING;
    }

    switch (cfg->mode)
    {
    case TIMERIF_MODE_OUTPUT_COMPARE:

        break;
    case TIMERIF_MODE_OUTPUT_PWM:
        status = config_pwm_output(cfg);
        break;
    case TIMERIF_MODE_DISABLED:
    case TIMERIF_MODE_NORMAL:
    case TIMERIF_MODE_INPUT_COMPTURE:
    case TIMERIF_MODE_INPUT_PWM_COMPTURE:
    case TIMERIF_MODE_OUTPUT_SINGLE_SHOT:
        status = E_NOT_IMPLEMENTED;
        break;
    
    default:
        status = E_NOT_SUPPORTED;
        break;
    }

    return status;
}

static std_return_type_t config_basic_timer(TimerIf_channel_config_t *cfg)
{
    std_return_type_t status = E_OK;
    switch (cfg->mode)
    {
    case TIMERIF_MODE_DISABLED:
    case TIMERIF_MODE_NORMAL:
        status = E_NOT_IMPLEMENTED;
        break;    
    default:
        status = E_NOT_SUPPORTED;
        break;
    }

    return status;
}

static std_return_type_t config_outputs(TimerIf_channel_config_t *cfg)
{
    STM32F4xx_TIM_CCER_Regdef_t *ccer_reg;

    switch (cfg->timer_id)
    {
    case 1:
        ccer_reg = &STM32F4XX_TIM1_REG->TIM_CCER;
        break;
    case 2:
        ccer_reg = &STM32F4XX_TIM2_REG->TIM_CCER;
        break;
    case 3:
        ccer_reg = &STM32F4XX_TIM3_REG->TIM_CCER;
        break;
    case 4:
        ccer_reg = &STM32F4XX_TIM4_REG->TIM_CCER;
        break;
    case 5:
        ccer_reg = &STM32F4XX_TIM5_REG->TIM_CCER;
        break;
#if IS_MCU(MCU_STM32F407)
    case 8:
        ccer_reg = &STM32F4XX_TIM8_REG->TIM_CCER;
        break;
#endif
    case 9:
        ccer_reg = &STM32F4XX_TIM9_REG->TIM_CCER;
        break;
    case 10:
        ccer_reg = &STM32F4XX_TIM10_REG->TIM_CCER;
        break;
    case 11:
        ccer_reg = &STM32F4XX_TIM11_REG->TIM_CCER;
        break;
#if IS_MCU(MCU_STM32F407)
    case 12:
        ccer_reg = &STM32F4XX_TIM12_REG->TIM_CCER;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
        ccer_reg = &STM32F4XX_TIM13_REG->TIM_CCER;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
        ccer_reg = &STM32F4XX_TIM14_REG->TIM_CCER;
        break;
#endif
    default:
        return E_NOT_EXISTING;
    }

    uint8_t flags = 0;

    if(cfg->output.output & TIMERIF_OUTPUT_NORMAL)
    {
        flags |= 1;
    }

    if(cfg->output.output & TIMERIF_OUTPUT_COMPLEMTARY)
    {
        flags |= 2;
    }

    if(cfg->output.invert_polarity_channel == TRUE)
    {
        flags |= 4;
    }

    if(cfg->output.invert_polarity_compchannel == TRUE)
    {
        flags |= 8;
    }


    uint32_t ccer_raw = ccer_reg->raw;
    uint8_t shift = cfg->channel_id * 4;
    ccer_raw &= ~(0xF << shift);
    ccer_raw |=  (flags << shift);
    ccer_reg->raw = ccer_raw;

    return E_OK;
}

static std_return_type_t config_pwm_output(TimerIf_channel_config_t *cfg)
{
    STM32F4xx_TIM_CCMR1_Regdef_t *ccmr1_reg;
    STM32F4xx_TIM_CCMR2_Regdef_t *ccmr2_reg;

    switch (cfg->timer_id)
    {
    case 1:
        ccmr1_reg = &STM32F4XX_TIM1_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM1_REG->TIM_CCMR2;
        STM32F4XX_TIM1_REG->TIM_CR1.ARPE = 1;
        break;
    case 2:
        ccmr1_reg = &STM32F4XX_TIM2_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM2_REG->TIM_CCMR2;
        STM32F4XX_TIM2_REG->TIM_CR1.ARPE = 1;
        break;
    case 3:
        ccmr1_reg = &STM32F4XX_TIM3_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM3_REG->TIM_CCMR2;
        STM32F4XX_TIM3_REG->TIM_CR1.ARPE = 1;
        break;
    case 4:
        ccmr1_reg = &STM32F4XX_TIM4_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM4_REG->TIM_CCMR2;
        STM32F4XX_TIM4_REG->TIM_CR1.ARPE = 1;
        break;
    case 5:
        ccmr1_reg = &STM32F4XX_TIM5_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM5_REG->TIM_CCMR2;
        STM32F4XX_TIM5_REG->TIM_CR1.ARPE = 1;
        break;
#if IS_MCU(MCU_STM32F407)
    case 8:
        ccmr1_reg = &STM32F4XX_TIM8_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM8_REG->TIM_CCMR2;
        STM32F4XX_TIM8_REG->TIM_CR1.ARPE = 1;
        break;
#endif
    case 9:
        ccmr1_reg = &STM32F4XX_TIM9_REG->TIM_CCMR1;
        STM32F4XX_TIM9_REG->TIM_CR1.ARPE = 1;
        break;
    case 10:
        ccmr1_reg = &STM32F4XX_TIM10_REG->TIM_CCMR1;
        STM32F4XX_TIM10_REG->TIM_CR1.ARPE = 1;
        break;
    case 11:
        ccmr1_reg = &STM32F4XX_TIM11_REG->TIM_CCMR1;
        STM32F4XX_TIM11_REG->TIM_CR1.ARPE = 1;
        break;
#if IS_MCU(MCU_STM32F407)
    case 12:
        ccmr1_reg = &STM32F4XX_TIM12_REG->TIM_CCMR1;
        STM32F4XX_TIM12_REG->TIM_CR1.ARPE = 1;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
        ccmr1_reg = &STM32F4XX_TIM13_REG->TIM_CCMR1;
        STM32F4XX_TIM13_REG->TIM_CR1.ARPE = 1;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
        ccmr1_reg = &STM32F4XX_TIM14_REG->TIM_CCMR1;
        STM32F4XX_TIM14_REG->TIM_CR1.ARPE = 1;
        break;
#endif
    default:
        return E_NOT_EXISTING;
    }

    uint8_t flags = 0x06;

    if (cfg->pwm.polarity_pwm == TIMERIF_POLARITY_ACTIVE_LOW)
    {
        flags |= 1;
    }
    
    uint8_t use_fast_pwm =0;
    if(cfg->pwm.pwm_mode == TIMERIF_FAST_PWM)
    {
        use_fast_pwm = 1;
    }

    if(cfg->channel_id == 1)
    {
        ccmr1_reg->oc.CC1S = 0;
        ccmr1_reg->oc.OC1M = flags;
        ccmr1_reg->oc.OC1PE = 1;
        ccmr1_reg->oc.OC1FE = use_fast_pwm;
    }
    else if(cfg->channel_id == 2)
    {
        ccmr1_reg->oc.CC2S = 0;
        ccmr1_reg->oc.OC2M = flags;
        ccmr1_reg->oc.OC2PE = 1;
        ccmr1_reg->oc.OC2FE = use_fast_pwm;
    }
    else if(cfg->channel_id == 3)
    {
        ccmr2_reg->oc.CC3S = 0;
        ccmr2_reg->oc.OC3M = flags;
        ccmr2_reg->oc.OC3PE = 1;
        ccmr2_reg->oc.OC3FE = use_fast_pwm;
    }
    else if(cfg->channel_id == 4)
    {
        ccmr2_reg->oc.CC4S = 0;
        ccmr2_reg->oc.OC4M = flags;
        ccmr2_reg->oc.OC4PE = 1;
        ccmr2_reg->oc.OC4FE = use_fast_pwm;
    }

    return E_OK;
}

static std_return_type_t config_output_compare(TimerIf_channel_config_t *cfg)
{
    STM32F4xx_TIM_CCMR1_Regdef_t *ccmr1_reg;
    STM32F4xx_TIM_CCMR2_Regdef_t *ccmr2_reg;

    switch (cfg->timer_id)
    {
    case 1:
        ccmr1_reg = &STM32F4XX_TIM1_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM1_REG->TIM_CCMR2;
        break;
    case 2:
        ccmr1_reg = &STM32F4XX_TIM2_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM2_REG->TIM_CCMR2;
        break;
    case 3:
        ccmr1_reg = &STM32F4XX_TIM3_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM3_REG->TIM_CCMR2;
        break;
    case 4:
        ccmr1_reg = &STM32F4XX_TIM4_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM4_REG->TIM_CCMR2;
        break;
    case 5:
        ccmr1_reg = &STM32F4XX_TIM5_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM5_REG->TIM_CCMR2;
        break;
#if IS_MCU(MCU_STM32F407)
    case 8:
        ccmr1_reg = &STM32F4XX_TIM8_REG->TIM_CCMR1;
        ccmr2_reg = &STM32F4XX_TIM8_REG->TIM_CCMR2;
        break;
#endif
    case 9:
        ccmr1_reg = &STM32F4XX_TIM9_REG->TIM_CCMR1;
        break;
    case 10:
        ccmr1_reg = &STM32F4XX_TIM10_REG->TIM_CCMR1;
        break;
    case 11:
        ccmr1_reg = &STM32F4XX_TIM11_REG->TIM_CCMR1;
        break;
#if IS_MCU(MCU_STM32F407)
    case 12:
        ccmr1_reg = &STM32F4XX_TIM12_REG->TIM_CCMR1;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
        ccmr1_reg = &STM32F4XX_TIM13_REG->TIM_CCMR1;
        break;
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
        ccmr1_reg = &STM32F4XX_TIM14_REG->TIM_CCMR1;
        break;
#endif
    default:
        return E_NOT_EXISTING;
    }

    if(cfg->output_compare.callback != NULL)
    {
        return E_NOT_IMPLEMENTED;
    }

    uint8_t flags = 0;

    if(cfg->output_compare.edge & TIMERIF_RISING_EDGE)
    {
        flags |= 1;
    }

    if(cfg->output_compare.edge & TIMERIF_FALLING_EDGE)
    {
        flags |= 2;
    }

    if(cfg->channel_id == 1)
    {
        ccmr1_reg->oc.OC1M = flags;
        ccmr1_reg->oc.CC1S = 0;
        ccmr1_reg->oc.OC1PE = 0;
        ccmr1_reg->oc.OC1FE = 0;
    }
    else if(cfg->channel_id == 2)
    {
        ccmr1_reg->oc.OC2M = flags;
        ccmr1_reg->oc.CC2S = 0;
        ccmr1_reg->oc.OC2PE = 0;
        ccmr1_reg->oc.OC2FE = 0;
    }
    else if(cfg->channel_id == 3)
    {
        ccmr2_reg->oc.OC3M = flags;
        ccmr2_reg->oc.CC3S = 0;
        ccmr2_reg->oc.OC3PE = 0;
        ccmr2_reg->oc.OC3FE = 0;
    }
    else if(cfg->channel_id == 4)
    {
        ccmr2_reg->oc.OC4M = flags;
        ccmr2_reg->oc.CC4S = 0;
        ccmr2_reg->oc.OC4PE = 0;
        ccmr2_reg->oc.OC4FE = 0;
    }
    

    return E_OK;
}

static boolean timer_exists(identifier_t timer_id)
{
    boolean exists = FALSE;
    switch (timer_id)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
#if IS_MCU(MCU_STM32F407)
    case 6:
#endif
#if IS_MCU(MCU_STM32F407)
    case 7:
#endif
#if IS_MCU(MCU_STM32F407)
    case 8:
#endif
    case 9:
    case 10:
    case 11:
#if IS_MCU(MCU_STM32F407)
    case 12:
#endif
#if IS_MCU(MCU_STM32F407)
    case 13:
#endif
#if IS_MCU(MCU_STM32F407)
    case 14:
#endif
        exists = TRUE;
        break;    
    default:
        exists = FALSE;
        break;
    }

    return exists;
}

std_return_type_t TimerIf_get_counter(identifier_t timer_id, uint32_t *buffer)
{
    *buffer =0;
    return E_NOT_IMPLEMENTED;    
}
