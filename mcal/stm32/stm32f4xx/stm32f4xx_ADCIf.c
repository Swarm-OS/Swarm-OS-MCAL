/**
 * @file stm32f4xx_ADCIf.c
 * @author Christoph Lehr
 * @date 25 May 2020
 * @brief File containing STM32F4xx ADC API
 *
 * This file implements the generic ADC interface 
 * API for the STM32F4xx series.
 */

#include <stdint.h>
#include "datatypes.h"
#include "stm32f4xx.h"
#include "ADCIf.h"
#include "stm32f4xx_interrupt.h"
#include "mcus.h"

static std_return_type_t set_ADC_resolution(STM32F4xx_ADCx_RegDef_t* adc_reg, uint8_t resolution);
static std_return_type_t set_ADC_prescaler(uint16_t prescaler);
static std_return_type_t set_ADC_channel_sampling_rate(uint8_t channel, uint16_t sampling_duration, STM32F4xx_ADCx_RegDef_t* adc_reg);

std_return_type_t ADCIf_init(identifier_t adc_id)
{
    std_return_type_t status = E_OK;
    switch (adc_id)
    {
    case 1:
        STM32F4xx_ADC1_PCLK_EN();
        STM32F4xx_ADC1->ADC_CR2.ADON = 1;
        break;
#if IS_MCU(STM32F407)
    case 2:
        STM32F4xx_ADC2_PCLK_EN();
        STM32F4xx_ADC2->ADC_CR2.ADON = 1;
        break;
#endif
#if IS_MCU(STM32F407)
    case 3:
        STM32F4xx_ADC3_PCLK_EN();
        STM32F4xx_ADC3->ADC_CR2.ADON = 1;
        break;
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }

    return status;
}

std_return_type_t ADCIf_deinit(identifier_t adc_id)
{
    std_return_type_t status = E_OK;
    switch (adc_id)
    {
    case 1:
        STM32F4xx_ADC1_PCLK_DI();
        STM32F4xx_ADC1->ADC_CR2.ADON = 0;
        break;
#if IS_MCU(STM32F407)
    case 2:
        STM32F4xx_ADC2_PCLK_DI();
        STM32F4xx_ADC2->ADC_CR2.ADON = 0;
        break;
#endif
#if IS_MCU(STM32F407)
    case 3:
        STM32F4xx_ADC3_PCLK_DI();
        STM32F4xx_ADC3->ADC_CR2.ADON = 0;
        break;
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }

    return status;
}

ADCIf_supported_features_t ADCIf_get_supported_features(identifier_t adc_id)
{
    ADCIf_supported_features_t features;
    
    features.general.resolution_configuration=TRUE;
    features.general.sampling_duration_configuration = FALSE;
    features.general.sample_accumulation = FALSE;
    features.general.differential_measurement = FALSE;
    features.general.conversion_chains = TRUE;
    features.general.multiple_channel_groups = TRUE;
    features.general.DMA_trigger = TRUE;
    features.general.analog_value_monitor = TRUE;

    features.per_channel.configuration = TRUE;
    features.per_channel.resolution = FALSE;
    features.per_channel.sampling_duration = TRUE;

    features.triggers.analog_comperator = FALSE;
    features.triggers.external_event = TRUE;
    features.triggers.timer = TRUE;
    features.triggers.timer_capture = TRUE;
    features.triggers.timer_compare = TRUE;
    features.triggers.timer_capture_compare = TRUE;
    features.triggers.timer_overflow = TRUE;
    
    return features;
}

std_return_type_t ADCIf_config(ADCIf_config_t *adc_cfg)
{
    STM32F4xx_ADCx_RegDef_t* adc_reg;
    std_return_type_t status;

    if(adc_cfg->adc_id == 1)
    {
        adc_reg = STM32F4xx_ADC1;
    }
#if IS_MCU(STM32F407)
    else if(adc_cfg->adc_id == 2)
    {
        adc_reg = STM32F4xx_ADC2;
    } 
#endif
#if IS_MCU(STM32F407)
    else if(adc_cfg->adc_id == 3)
    {
        adc_reg = STM32F4xx_ADC3;
    } 
#endif
    else
    {
        return E_NOT_EXISTING;
    }

    status = set_ADC_resolution(adc_reg, adc_cfg->resolution);
    if(status != E_OK)
    {
        return status;
    }

    status = set_ADC_prescaler(adc_cfg->prescaler);
    if(status != E_OK)
    {
        return status;
    }

    if(adc_cfg->alignment == ADCIf_ALIGNMENT_LEFT)
    {
        adc_reg->ADC_CR2.ALIGN = 1;
    }
    else
    {
        adc_reg->ADC_CR2.ALIGN = 0;
    }

    if(adc_cfg->continous_conversion != FALSE)
    {
        adc_reg->ADC_CR2.CONT = 1;
    }
    else
    {
        adc_reg->ADC_CR2.CONT = 0;
    }

    return E_OK;
}

static std_return_type_t set_ADC_resolution(STM32F4xx_ADCx_RegDef_t* adc_reg, uint8_t resolution)
{
    if(resolution == 12 || resolution == 0)
    {
        adc_reg->ADC_CR1.RES = 0;
    }
    else if(resolution == 10)
    {
        adc_reg->ADC_CR1.RES = 1;
    }
    else if(resolution == 8)
    {
        adc_reg->ADC_CR1.RES = 2;
    }
    else if(resolution == 6)
    {
        adc_reg->ADC_CR1.RES = 3;
    }
    else
    {
        return E_NOT_SUPPORTED;
    }
    return E_OK;
}

static std_return_type_t set_ADC_prescaler(uint16_t prescaler)
{
    if(prescaler == 0 || prescaler == 2)
    {
        STM32F4xx_ADC_COMMON->ADC_CCR.ADCPRE = 0;
    }
    else if(prescaler == 4)
    {
        STM32F4xx_ADC_COMMON->ADC_CCR.ADCPRE = 1;
    }
    else if(prescaler == 6)
    {
        STM32F4xx_ADC_COMMON->ADC_CCR.ADCPRE = 2;
    }
    else if(prescaler == 8)
    {
        STM32F4xx_ADC_COMMON->ADC_CCR.ADCPRE = 3;
    }
    else
    {
        return E_NOT_SUPPORTED;
    }
    return E_OK;
}

std_return_type_t ADCIf_config_channel(ADCIf_channel_config_t *channel_cfg)
{
    STM32F4xx_ADCx_RegDef_t* adc_reg;

    if(channel_cfg->adc_id == 1)
    {
        adc_reg = STM32F4xx_ADC1;
    }
#if IS_MCU(STM32F407)
    else if(channel_cfg->adc_id == 2)
    {
        adc_reg = STM32F4xx_ADC2;
    } 
#endif
#if IS_MCU(STM32F407)
    else if(channel_cfg->adc_id == 3)
    {
        adc_reg = STM32F4xx_ADC3;
    } 
#endif
    else
    {
        return E_NOT_EXISTING;
    }
    
    if(channel_cfg->channel.channel > 15)
    {
        return E_NOT_EXISTING;
    }

    if(channel_cfg->channel.conv_mode != ADCIf_CONVERSION_MODE_SINGLE_ENDED)
    {
        return E_NOT_SUPPORTED;
    }

    return set_ADC_channel_sampling_rate(channel_cfg->channel.channel, channel_cfg->sampling_duration, adc_reg);
}

static std_return_type_t set_ADC_channel_sampling_rate(uint8_t channel, uint16_t sampling_duration, STM32F4xx_ADCx_RegDef_t* adc_reg)
{   
    uint8_t register_value = 0;
    switch (sampling_duration)
    {
    case 3:
        register_value = 0;
        break;
    case 15:
        register_value = 1;
        break;
    case 28:
        register_value = 2;
        break;
    case 56:
        register_value = 3;
        break;
    case 84:
        register_value = 4;
        break;
    case 112:
        register_value = 5;
        break;
    case 144:
        register_value = 6;
        break;
    case 480:
        register_value = 7;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    if(channel <= 9)
    {
        uint32_t reg_val = adc_reg->ADC_SMPR2.raw;
        uint8_t shift = channel *3;
        reg_val &= ~(0x7 << shift);
        reg_val |=  (register_value << shift);
        adc_reg->ADC_SMPR2.raw = reg_val;
    }
    else
    {
        uint32_t reg_val = adc_reg->ADC_SMPR1.raw;
        uint8_t shift = (channel-10) *3;
        reg_val &= ~(0x7 << shift);
        reg_val |=  (register_value << shift);
        adc_reg->ADC_SMPR2.raw = reg_val;
    }

    return E_OK;
}

std_return_type_t ADCIf_config_valid_window(identifier_t adc_id, ADCIf_value_window_t window)
{
    return E_NOT_IMPLEMENTED;
}

std_return_type_t ADCIf_config_conversion(ADCIf_conversion_config_t *conv_conf)
{
    std_return_type_t status = E_OK;
    STM32F4xx_ADCx_RegDef_t* adc_reg;

    switch (conv_conf->adc_id)
    {
    case 1:
        adc_reg = STM32F4xx_ADC1;
        break;
#if IS_MCU(STM32F407)
    case 2:
        adc_reg = STM32F4xx_ADC2;
        break;
#endif
#if IS_MCU(STM32F407)
    case 3:
        adc_reg = STM32F4xx_ADC3;
        break;
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }

    if(conv_conf->conv_mode == ADCIF_SINGLE_CHANNEL)
    {
        adc_reg->ADC_CR2.EOCS = 1;
        adc_reg->ADC_CR1.EOCIE = 0;
        adc_reg->ADC_SQR1.L = 1;
        adc_reg->ADC_SQR3.SQ1 = conv_conf->channel->channel;
    }
    else if (conv_conf->conv_mode == ADCIF_CHANNEL_GROUP)
    {
        adc_reg->ADC_CR2.EOCS = 1;
        adc_reg->ADC_CR1.EOCIE = 0;
        adc_reg->ADC_SQR1.L = conv_conf->group_config->group_size;
        
        ADCIf_channel_identifier_t *member;
        for(uint8_t i=0; i< conv_conf->group_config->group_size; i++)
        {
            member = &conv_conf->group_config->members[i];
            if(i <= 6)
            {
                uint8_t shift = i * 5;   
                adc_reg->ADC_SQR3.raw &= ~(0x1F << shift);
                adc_reg->ADC_SQR3.raw |=  (member->channel << shift);
                
            }
            else if( i<=12)
            {
                uint8_t shift = (i-7) * 5;   
                adc_reg->ADC_SQR2.raw &= ~(0x1F << shift);
                adc_reg->ADC_SQR2.raw |=  (member->channel << shift);
            }
            else
            {
                uint8_t shift = (i-13) * 5;   
                adc_reg->ADC_SQR1.raw &= ~(0x1F << shift);
                adc_reg->ADC_SQR1.raw |=  (member->channel << shift);
            }
        }
    }
    else
    {
        status = E_NOT_SUPPORTED;
    }

    if(conv_conf->enable_trigger != FALSE)
    {
        status = E_NOT_IMPLEMENTED;
    }

    return status;
}

std_return_type_t ADCIf_start_conversion(identifier_t adc_id, uint16_t* buffer)
{
    std_return_type_t status = E_OK;
    STM32F4xx_ADCx_RegDef_t* adc_reg;

    switch (adc_id)
    {
    case 1:
        adc_reg = STM32F4xx_ADC1;
        break;
#if IS_MCU(STM32F407)
    case 2:
        adc_reg = STM32F4xx_ADC2;
        break;
#endif
#if IS_MCU(STM32F407)
    case 3:
        adc_reg = STM32F4xx_ADC3;
        break;
#endif
    default:
        status = E_NOT_EXISTING;
        break;
    }
    
    adc_reg->ADC_CR2.SWSTART = 1;
    for(uint8_t i=0; i< adc_reg->ADC_SQR1.L; i++)
    {
        while(adc_reg->ADC_SR.EOC == 0 );
        adc_reg->ADC_SR.STRT = 0;
        buffer[i] = adc_reg->ADC_DR.DATA;
    }

    return status;
}



std_return_type_t ADCIf_start_conversion_i(identifier_t ADCIf_no, uint16_t* buffer)
{
    return E_NOT_IMPLEMENTED;
}


