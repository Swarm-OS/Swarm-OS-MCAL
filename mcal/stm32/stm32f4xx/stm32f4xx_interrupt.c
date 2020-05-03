/**
 * @file stm32f4xx_interrupt.c
 * @author Christoph Lehr
 * @date 12 Apr 2020
 * @brief Tmplementation of interrupt API for STM32F4 series
 *
 * This file provides the implementation for the STM32F4 
 * interrupt configuration
 */

#include "datatypes.h"
#include "stm32f4xx_interrupt.h"
#include "stm32f4xx.h"

boolean stm32f4xx_irq_exists(STM32F4xx_IRQ_t irq);

// unused IRQ IDs
uint8_t unused_IRQs[] = {19, 20, 21,22, 39, 42, 43, 44, 45, 46, 48, 61, 62, 63, 64, 65, 66, 74,75,76,77,78,79,80};

// stack pointer location
extern uint32_t _estack;

/* Exception Table */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
        /* Configure Initial Stack Pointer, using linker-generated symbols */
        .StackPointer                   = (void*) (&_estack),
        .fp_Reset_Handler               = (void*) Reset_Handler,
        .fp_NMI_Handler                 = (void*) NMI_Handler,
        .fp_HardFault_Handler           = (void*) HardFault_Handler,
        .fp_MemManage_Handler           = (void*) MemManage_Handler,
        .fp_BusFault_Handler            = (void*) BusFault_Handler,
        .fp_UsageFault_Handler          = (void*) UsageFault_Handler,
        .fp_SVCall_Handler              = (void*) SVCall_Handler,
        .fp_DebugMonitor_Handler        = (void*) DebugMonitor_Handler,
        .fp_PendSV_Handler              = (void*) PendSV_Handler,
        .fp_SysTick_Handler             = (void*) SysTick_Handler,
        .fp_WWDG_Handler                = (void*) WWDG_Handler,
        .fp_EXTI16_PVD_Handler          = (void*) EXTI16_PVD_Handler,
        .fp_EXTI21_TAMP_STAMP_Handler   = (void*) EXTI21_TAMP_STAMP_Handler,
        .fp_EXTI22_RTC_WKUP_Handler     = (void*) EXTI22_RTC_WKUP_Handler,
        .fp_FLASH_Handler               = (void*) FLASH_Handler,
        .fp_RCC_Handler                 = (void*) RCC_Handler,
        .fp_EXTI0_Handler               = (void*) EXTI0_Handler,
        .fp_EXTI1_Handler               = (void*) EXTI1_Handler,
        .fp_EXTI2_Handler               = (void*) EXTI2_Handler,
        .fp_EXTI3_Handler               = (void*) EXTI3_Handler,
        .fp_EXTI4_Handler               = (void*) EXTI4_Handler,
        .fp_DMA1_STREAM0_Handler        = (void*) DMA1_STREAM0_Handler,
        .fp_DMA1_STREAM1_Handler        = (void*) DMA1_STREAM1_Handler,
        .fp_DMA1_STREAM2_Handler        = (void*) DMA1_STREAM2_Handler,
        .fp_DMA1_STREAM3_Handler        = (void*) DMA1_STREAM3_Handler,
        .fp_DMA1_STREAM4_Handler        = (void*) DMA1_STREAM4_Handler,
        .fp_DMA1_STREAM5_Handler        = (void*) DMA1_STREAM5_Handler,
        .fp_DMA1_STREAM6_Handler        = (void*) DMA1_STREAM6_Handler,
        .fp_ADC_Handler                 = (void*) ADC_Handler,
        .fp_EXTI9_5_Handler             = (void*) EXTI9_5_Handler,
        .fp_TIM1_BRK_TIM9_Handler       = (void*) TIM1_BRK_TIM9_Handler,
        .fp_TIM1_UP_TIM10_Handler       = (void*) TIM1_UP_TIM10_Handler,
        .fp_TIM1_TRG_COM_TIM11_Handler  = (void*) TIM1_TRG_COM_TIM11_Handler,
        .fp_TIM1_CC_Handler             = (void*) TIM1_CC_Handler,
        .fp_TIM2_Handler                = (void*) TIM2_Handler,
        .fp_TIM3_Handler                = (void*) TIM3_Handler,
        .fp_TIM4_Handler                = (void*) TIM4_Handler,
        .fp_I2C1_EV_Handler             = (void*) I2C1_EV_Handler,
        .fp_I2C1_ER_Handler             = (void*) I2C1_ER_Handler,
        .fp_I2C2_EV_Handler             = (void*) I2C2_EV_Handler,
        .fp_I2C2_ER_Handler             = (void*) I2C2_ER_Handler,
        .fp_SPI1_Handler                = (void*) SPI1_Handler,
        .fp_SPI2_Handler                = (void*) SPI2_Handler,
        .fp_USART1_Handler              = (void*) USART1_Handler,
        .fp_USART2_Handler              = (void*) USART2_Handler,
        .fp_EXTI15_10_Handler           = (void*) EXTI15_10_Handler,
        .fp_EXTI17_RTC_ALARM_Handler    = (void*) EXTI17_RTC_ALARM_Handler,
        .fp_EXTI18_OTG_FS_WKUP_Handler  = (void*) EXTI18_OTG_FS_WKUP_Handler,
        .fp_DMA1_STREAM7_Handler        = (void*) DMA1_STREAM7_Handler,
        .fp_SDIO_Handler                = (void*) SDIO_Handler,
        .fp_TIM5_Handler                = (void*) TIM5_Handler,
        .fp_SPI3_Handler                = (void*) SPI3_Handler,
        .fp_DMA2_STREAM0_Handler        = (void*) DMA2_STREAM0_Handler,
        .fp_DMA2_STREAM1_Handler        = (void*) DMA2_STREAM1_Handler,
        .fp_DMA2_STREAM2_Handler        = (void*) DMA2_STREAM2_Handler,
        .fp_DMA2_STREAM3_Handler        = (void*) DMA2_STREAM3_Handler,
        .fp_DMA2_STREAM4_Handler        = (void*) DMA2_STREAM4_Handler,
        .fp_OTG_FS_Handler              = (void*) OTG_FS_Handler,
        .fp_DMA2_STREAM5_Handler        = (void*) DMA2_STREAM5_Handler,
        .fp_DMA2_STREAM6_Handler        = (void*) DMA2_STREAM6_Handler,
        .fp_DMA2_STREAM7_Handler        = (void*) DMA2_STREAM7_Handler,
        .fp_USART6_Handler              = (void*) USART6_Handler,
        .fp_I2C3_EV_Handler             = (void*) I2C3_EV_Handler,
        .fp_I2C3_ER_Handler             = (void*) I2C3_ER_Handler,
        .fp_FPU_Handler                 = (void*) FPU_Handler,
        .fp_SPI4_Handler                = (void*) SPI4_Handler,
        .fp_SPI5_Handler                = (void*) SPI5_Handler,

};


std_return_type_t stm32f4xx_enable_interrupt(STM32F4xx_IRQ_t irq)
{
    if(stm32f4xx_irq_exists(irq) == FALSE)
    {
        return E_VALUE_ERR;
    }

    uint8_t reg_no = irq >> 5;      // devide by 32 to get NVIC register number 
    uint8_t reg_pos = irq & 0x1F;   // 32-1, mask out last 5 bits to get position inside register

    STM32F4xx_NVIC->NVIC_ISER[reg_no] |= (1 << reg_pos);

    return E_OK;
}

std_return_type_t stm32f4xx_disable_interrupt(STM32F4xx_IRQ_t irq)
{
    if(stm32f4xx_irq_exists(irq) == FALSE)
    {
        return E_VALUE_ERR;
    }

    uint8_t reg_no = irq >> 5;      // devide by 32 to get NVIC register number 
    uint8_t reg_pos = irq & 0x1F;   // 32-1, mask out last 5 bits to get position inside register

    STM32F4xx_NVIC->NVIC_ICER[reg_no] |= (1 << reg_pos);

    return E_OK;
}

boolean stm32f4xx_irq_exists(STM32F4xx_IRQ_t irq)
{
    if(irq > STM32F4xx_STM32F4XX_MAX_IRQ)
    {
        return FALSE;
    }

    uint8_t len = sizeof(unused_IRQs);
    for(uint8_t i =0; i < len; i++)
    {
        if(unused_IRQs[i] == irq)
        {
            return FALSE;
        }
    }
    return TRUE;
}