/**
 * @file stm32f4xx_interrupt.h
 * @author Christoph Lehr
 * @date 12 Apr 2020
 * @brief File containing interrupt API for STM32F4 series
 *
 * This file specifies the API to configure the STM32F4
 * interrupts
 */

#ifndef MCAL_INTERRUPT_STM32F411XX_H
#define MCAL_INTERRUPT_STM32F411XX_H

#include "datatypes.h"

// Interrup vectors, stack pointer etc.
typedef struct _DeviceVectors
{
    /* Stack pointer */
    void* StackPointer;                   //  0x00 Stackpointer

    /* Cortex-M handlers */
    void* fp_Reset_Handler;               //  0x0004 Reset Handler
    void* fp_NMI_Handler;                 //  0x0008 Non maskable interrupt, Clock Security System
    void* fp_HardFault_Handler;           //  0x000C All class of fault
    void* fp_MemManage_Handler;           //  0x0010 Memory Management
    void* fp_BusFault_Handler;            //  0x0014 Pre-fetch fault, memory access fault
    void* fp_UsageFault_Handler;          //  0x0018 Undefined instruction or illegal state
    void* fp_Reserved_0x1C;               //  0x001C Reserved
    void* fp_Reserved_0x20;               //  0x0020 Reserved
    void* fp_Reserved_0x24;               //  0x0024 Reserved
    void* fp_Reserved_0x28;               //  0x0028 Reserved
    void* fp_SVCall_Handler;              //  0x002C System Service call via SWI instruction
    void* fp_DebugMonitor_Handler;        //  0x0030 Debug Monitor
    void* fp_Reserved_0x34;               //  0x0034 Reserved
    void* fp_PendSV_Handler;              //  0x0038 Pendable request for system service
    void* fp_SysTick_Handler;             //  0x003C System tick timer

    /* Peripheral handlers */
    void* fp_WWDG_Handler;                //  0x0040 Window Watchdog interrupt
    void* fp_EXTI16_PVD_Handler;          //  0x0044 EXTI Line 16 interrupt / PVD through EXTI  line detection interrupt
    void* fp_EXTI21_TAMP_STAMP_Handler;   //  0x0048 EXTI Line 21 interrupt / Tamper and TimeStamp interrupts through the EXTI line
    void* fp_EXTI22_RTC_WKUP_Handler;     //  0x004C EXTI Line 22 interrupt / RTC Wakeup interrupt through the EXTI line
    void* fp_FLASH_Handler;               //  0x0050 Flash global interrupt
    void* fp_RCC_Handler;                 //  0x0054 RCC global interrupt
    void* fp_EXTI0_Handler;               //  0x0058 EXTI Line 0 interrupt
    void* fp_EXTI1_Handler;               //  0x005C EXTI Line 1 interrupt
    void* fp_EXTI2_Handler;               //  0x0060 EXTI Line 2 interrupt
    void* fp_EXTI3_Handler;               //  0x0064 EXTI Line 3 interrupt
    void* fp_EXTI4_Handler;               //  0x0068 EXTI Line 4 interrupt
    void* fp_DMA1_STREAM0_Handler;        //  0x006C DMA1 Stream 0 global interrupt
    void* fp_DMA1_STREAM1_Handler;        //  0x0070 DMA1 Stream 1 global interrupt
    void* fp_DMA1_STREAM2_Handler;        //  0x0074 DMA1 Stream 2 global interrupt
    void* fp_DMA1_STREAM3_Handler;        //  0x0078 DMA1 Stream 3 global interrupt
    void* fp_DMA1_STREAM4_Handler;        //  0x007C DMA1 Stream 4 global interrupt
    void* fp_DMA1_STREAM5_Handler;        //  0x0080 DMA1 Stream 5 global interrupt
    void* fp_DMA1_STREAM6_Handler;        //  0x0084 DMA1 Stream 6 global interrupt
    void* fp_ADC_Handler;                 //  0x0088 ADC1 global interrupts
    void* fp_Unused_0x008C;               //  0x008C Unused
    void* fp_Unused_0x0090;               //  0x0090 Unused
    void* fp_Unused_0x0094;               //  0x0094 Unused
    void* fp_Unused_0x0098;               //  0x0098 Unused
    void* fp_EXTI9_5_Handler;             //  0x009C EXTI Line[9:5] interrupts
    void* fp_TIM1_BRK_TIM9_Handler;       //  0x00A0 TIM1 Break interrupt and TIM9 global interrupt
    void* fp_TIM1_UP_TIM10_Handler;       //  0x00A4 TIM1 Update interrupt and TIM10 global interrupt
    void* fp_TIM1_TRG_COM_TIM11_Handler;  //  0x00A8 TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
    void* fp_TIM1_CC_Handler;             //  0x00AC TIM1 Capture Compare interrupt
    void* fp_TIM2_Handler;                //  0x00B0 TIM2 global interrupt
    void* fp_TIM3_Handler;                //  0x00B4 TIM3 global interrupt
    void* fp_TIM4_Handler;                //  0x00B8 TIM4 global interrupt
    void* fp_I2C1_EV_Handler;             //  0x00BC I2C1 event interrupt
    void* fp_I2C1_ER_Handler;             //  0x00C0 I2C1 error interrupt
    void* fp_I2C2_EV_Handler;             //  0x00C4 I2C2 event interrupt
    void* fp_I2C2_ER_Handler;             //  0x00C8 I2C1 error interrupt
    void* fp_SPI1_Handler;                //  0x00CC SPI1 global interrupt
    void* fp_SPI2_Handler;                //  0x00D0 SPI2 global interrupt
    void* fp_USART1_Handler;              //  0x00D4 USART1 global interrupt
    void* fp_USART2_Handler;              //  0x00D8 USART2 global interrupt
    void* fp_Unused_0x00DC;               //  0x00DC Unused
    void* fp_EXTI15_10_Handler;           //  0x00E0 EXTI Line[15:10] interrupts
    void* fp_EXTI17_RTC_ALARM_Handler;    //  0x00E4 EXTI Line 17 interrupt / RTC Alarms (A and B) through EXTI line interrupt
    void* fp_EXTI18_OTG_FS_WKUP_Handler;  //  0x00E8 EXTI Line 18 interrupt / USB On-The-Go  FS Wakeup through EXTI line interrupt
    void* fp_Unused_0x00EC;               //  0x00EC Unused
    void* fp_Unused_0x00F0;               //  0x00F0 Unused
    void* fp_Unused_0x00F4;               //  0x00F4 Unused
    void* fp_Unused_0x00F8;               //  0x00F8 Unused
    void* fp_DMA1_STREAM7_Handler;        //  0x00FC DMA1 Stream 7 global interrupt
    void* fp_Unused_0x0100;               //  0x0100 Unused
    void* fp_SDIO_Handler;                //  0x0104 SDIO global interrupt
    void* fp_TIM5_Handler;                //  0x0108 TIM5 global interrupt
    void* fp_SPI3_Handler;                //  0x010C SPI3 global interrupt
    void* fp_Unused_0x0110;               //  0x0110 Unused
    void* fp_Unused_0x0114;               //  0x0114 Unused
    void* fp_Unused_0x0118;               //  0x0118 Unused
    void* fp_Unused_0x011C;               //  0x011C Unused
    void* fp_DMA2_STREAM0_Handler;        //  0x0120 DMA2 Stream 0 global interrupt
    void* fp_DMA2_STREAM1_Handler;        //  0x0124 DMA2 Stream 1 global interrupt
    void* fp_DMA2_STREAM2_Handler;        //  0x0128 DMA2 Stream 2 global interrupt
    void* fp_DMA2_STREAM3_Handler;        //  0x012C DMA2 Stream 3 global interrupt
    void* fp_DMA2_STREAM4_Handler;        //  0x0130 DMA2 Stream 4 global interrupt
    void* fp_Unused_0x0134;               //  0x0134 Unused
    void* fp_Unused_0x0138;               //  0x0138 Unused
    void* fp_Unused_0x013C;               //  0x013C Unused
    void* fp_Unused_0x0140;               //  0x0140 Unused
    void* fp_Unused_0x0144;               //  0x0144 Unused
    void* fp_Unused_0x0148;               //  0x0148 Unused
    void* fp_OTG_FS_Handler;              //  0x014C USB On The Go FS global interrupt
    void* fp_DMA2_STREAM5_Handler;        //  0x0150 DMA2 Stream 5 global interrupt
    void* fp_DMA2_STREAM6_Handler;        //  0x0154 DMA2 Stream 6 global interrupt
    void* fp_DMA2_STREAM7_Handler;        //  0x0158 DMA2 Stream 7 global interrupt
    void* fp_USART6_Handler;              //  0x015C USART6 global interrupt
    void* fp_I2C3_EV_Handler;             //  0x0160 I2C1 event interrupt
    void* fp_I2C3_ER_Handler;             //  0x0164 I2C1 error interrupt
    void* fp_Unused_0x0168;               //  0x0168 Unused
    void* fp_Unused_0x016C;               //  0x016C Unused
    void* fp_Unused_0x0170;               //  0x0170 Unused
    void* fp_Unused_0x0174;               //  0x0174 Unused
    void* fp_Unused_0x0178;               //  0x0178 Unused
    void* fp_Unused_0x017C;               //  0x017C Unused
    void* fp_Unused_0x0180;               //  0x0180 Unused
    void* fp_FPU_Handler;                 //  0x0184 FPU global interrupt
    void* fp_Unused_0x0188;               //  0x0188 Unused
    void* fp_Unused_0x018C;               //  0x018C Unused
    void* fp_SPI4_Handler;                //  0x0190 SPI4 global interrupt
    void* fp_SPI5_Handler;                //  0x0194 SPI5 global interrupt
} DeviceVectors;

void __attribute__((weak)) Reset_Handler(void);        
void __attribute__((weak)) NMI_Handler(void);
void __attribute__((weak)) HardFault_Handler(void);
void __attribute__((weak)) MemManage_Handler(void);
void __attribute__((weak)) BusFault_Handler(void);
void __attribute__((weak)) UsageFault_Handler(void);
void __attribute__((weak)) SVCall_Handler(void);
void __attribute__((weak)) DebugMonitor_Handler(void);
void __attribute__((weak)) PendSV_Handler(void);
void __attribute__((weak)) SysTick_Handler(void);
void __attribute__((weak)) WWDG_Handler(void);
void __attribute__((weak)) EXTI16_PVD_Handler(void);
void __attribute__((weak)) EXTI21_TAMP_STAMP_Handler(void);
void __attribute__((weak)) EXTI22_RTC_WKUP_Handler(void);
void __attribute__((weak)) FLASH_Handler(void);
void __attribute__((weak)) RCC_Handler(void);
void __attribute__((weak)) EXTI0_Handler(void);
void __attribute__((weak)) EXTI1_Handler(void);
void __attribute__((weak)) EXTI2_Handler(void);
void __attribute__((weak)) EXTI3_Handler(void);
void __attribute__((weak)) EXTI4_Handler(void);
void __attribute__((weak)) DMA1_STREAM0_Handler(void);
void __attribute__((weak)) DMA1_STREAM1_Handler(void);
void __attribute__((weak)) DMA1_STREAM2_Handler(void);
void __attribute__((weak)) DMA1_STREAM3_Handler(void);
void __attribute__((weak)) DMA1_STREAM4_Handler(void);
void __attribute__((weak)) DMA1_STREAM5_Handler(void);
void __attribute__((weak)) DMA1_STREAM6_Handler(void);
void __attribute__((weak)) ADC_Handler(void);
void __attribute__((weak)) EXTI9_5_Handler(void);
void __attribute__((weak)) TIM1_BRK_TIM9_Handler(void);
void __attribute__((weak)) TIM1_UP_TIM10_Handler(void);
void __attribute__((weak)) TIM1_TRG_COM_TIM11_Handler(void);
void __attribute__((weak)) TIM1_CC_Handler(void);
void __attribute__((weak)) TIM2_Handler(void);
void __attribute__((weak)) TIM3_Handler(void);
void __attribute__((weak)) TIM4_Handler(void);
void __attribute__((weak)) I2C1_EV_Handler(void);
void __attribute__((weak)) I2C1_ER_Handler(void);
void __attribute__((weak)) I2C2_EV_Handler(void);
void __attribute__((weak)) I2C2_ER_Handler(void);
void __attribute__((weak)) SPI1_Handler(void);
void __attribute__((weak)) SPI2_Handler(void);
void __attribute__((weak)) USART1_Handler(void);
void __attribute__((weak)) USART2_Handler(void);
void __attribute__((weak)) EXTI15_10_Handler(void);
void __attribute__((weak)) EXTI17_RTC_ALARM_Handler(void);
void __attribute__((weak)) EXTI18_OTG_FS_WKUP_Handler(void);
void __attribute__((weak)) DMA1_STREAM7_Handler(void);
void __attribute__((weak)) SDIO_Handler(void);
void __attribute__((weak)) TIM5_Handler(void);
void __attribute__((weak)) SPI3_Handler(void);
void __attribute__((weak)) DMA2_STREAM0_Handler(void);
void __attribute__((weak)) DMA2_STREAM1_Handler(void);
void __attribute__((weak)) DMA2_STREAM2_Handler(void);
void __attribute__((weak)) DMA2_STREAM3_Handler(void);
void __attribute__((weak)) DMA2_STREAM4_Handler(void);
void __attribute__((weak)) OTG_FS_Handler(void);
void __attribute__((weak)) DMA2_STREAM5_Handler(void);
void __attribute__((weak)) DMA2_STREAM6_Handler(void);
void __attribute__((weak)) DMA2_STREAM7_Handler(void);
void __attribute__((weak)) USART6_Handler(void);
void __attribute__((weak)) I2C3_EV_Handler(void);
void __attribute__((weak)) I2C3_ER_Handler(void);
void __attribute__((weak)) FPU_Handler(void);
void __attribute__((weak)) SPI4_Handler(void);
void __attribute__((weak)) SPI5_Handler(void);

// IRQ Numbers
typedef enum
{
    MCAL_WWDG_IRQ               =    0,
    MCAL_EXTI16_PVD_IRQ         =    1,
    MCAL_EXTI21_TAMP_STAMP_IRQ  =    2,
    MCAL_EXTI22_RTC_WKUP_IRQ    =    3,
    MCAL_FLASH_IRQ              =    4,
    MCAL_RCC_IRQ                =    5,
    MCAL_EXTI0_IRQ              =    6,
    MCAL_EXTI1_IRQ              =    7,
    MCAL_EXTI2_IRQ              =    8,
    MCAL_EXTI3_IRQ              =    9,
    MCAL_EXTI4_IRQ              =   10,
    MCAL_DMA1_STREAM0_IRQ       =   11,
    MCAL_DMA1_STREAM1_IRQ       =   12,
    MCAL_DMA1_STREAM2_IRQ       =   13,
    MCAL_DMA1_STREAM3_IRQ       =   14,
    MCAL_DMA1_STREAM4_IRQ       =   15,
    MCAL_DMA1_STREAM5_IRQ       =   16,
    MCAL_DMA1_STREAM6_IRQ       =   17,
    MCAL_ADC_IRQ                =   18,
    // 19 - 22 unused
    MCAL_EXTI9_5_IRQ            =   23,
    MCAL_TIM1_BRK_TIM9_IRQ      =   24,
    MCAL_TIM1_UP_TIM10_IRQ      =   25,
    MCAL_TIM1_TRG_COM_TIM11_IRQ =   26, 
    MCAL_TIM1_CC_IRQ            =   27,
    MCAL_TIM2_IRQ               =   28,
    MCAL_TIM3_IRQ               =   29,
    MCAL_TIM4_IRQ               =   30,
    MCAL_I2C1_EV_IRQ            =   31,
    MCAL_I2C1_ER_IRQ            =   32,
    MCAL_I2C2_EV_IRQ            =   33,
    MCAL_I2C2_ER_IRQ            =   34,
    MCAL_SPI1_IRQ               =   35,
    MCAL_SPI2_IRQ               =   36,
    MCAL_USART1_IRQ             =   37,
    MCAL_USART2_IRQ             =   38,
    // 39 unused
    MCAL_EXTI15_10_IRQ          =   40,
    MCAL_EXTI17_RTC_ALARM_IRQ   =   41,
    MCAL_EXTI18_OTG_FS_WKUP_IRQ =   42,
    // 42 - 46 unused
    MCAL_DMA1_STREAM7_IRQ       =   47,
    // 48 unused
    MCAL_SDIO_IRQ               =   49,
    MCAL_TIM5_IRQ               =   50,
    MCAL_SPI3_IRQ               =   51,
    // 52 - 55 unused
    MCAL_DMA2_STREAM0_IRQ       =   56,
    MCAL_DMA2_STREAM1_IRQ       =   57,
    MCAL_DMA2_STREAM2_IRQ       =   58,
    MCAL_DMA2_STREAM3_IRQ       =   59,
    MCAL_DMA2_STREAM4_IRQ       =   60,
    // 61 - 66 unused
    MCAL_OTG_FS_IRQ             =   67,
    MCAL_DMA2_STREAM5_IRQ       =   68,
    MCAL_DMA2_STREAM6_IRQ       =   69,
    MCAL_DMA2_STREAM7_IRQ       =   70,
    MCAL_USART6_IRQ             =   71,
    MCAL_I2C3_EV_IRQ            =   72,
    MCAL_I2C3_ER_IRQ            =   73,
    // 74 - 80 unused
    MCAL_FPU_IRQ                =   81,
    MCAL_SPI4_IRQ               =   84,
    MCAL_SPI5_IRQ               =   85,
} MCAL_IRQ_t;

#define MCAL_STM32F4XX_MAX_IRQ  85

std_return_type_t stm32f4xx_enable_interrupt(MCAL_IRQ_t irq);

std_return_type_t stm32f4xx_disable_interrupt(MCAL_IRQ_t irq);

std_return_type_t stm32f4xx_set_interrupt_priority(MCAL_IRQ_t irq, uint8_t priority);



#endif