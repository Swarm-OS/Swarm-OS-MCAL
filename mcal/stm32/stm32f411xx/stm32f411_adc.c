/**
 * @file stm32f411_adc.c
 * @author Christoph Lehr
 * @date 21 Jan 2020
 * @brief STM32F411 implentation of API for accessing the ADC
 *
 * This file implements the generic API which shall be used to 
 * interact with the ADC of different Microcontrollers.
 */

#include <mcus.h>
#if IS_MCU(STM32F411)

#include <ADC.h>
#include <datatypes.h>
#include <stm32f411_adc.h>

uint16_t* ADC_Bufffer[ADC_CHANNELS];

std_return_type_t MCAL_ADC_init(uint8_t ADC_no)
{
    MCAL_ADC1_PCLK_EN();
    return E_OK;
}

std_return_type_t AMCAL_DC_deinit(uint8_t ADC_no)
{
    MCAL_ADC1_PCLK_DI() 
    return E_OK;

std_return_type_t MCAL_ADC_config(ADC_config_t ADC_cfg)
{
    return E_NOT_IMPLEMENTED;
}

std_return_type_t MCAL_ADC_channel_read(ADC_Channel_t ADC_no, uint16_t* buffer)
{
    return E_NOT_IMPLEMENTED;
}


std_return_type_t MCAL_ADC_channel_iread(ADC_Channel_t ADC_no, uint16_t* buffer, void (*callback)(void))
{
    return E_NOT_IMPLEMENTED;
}


#endif