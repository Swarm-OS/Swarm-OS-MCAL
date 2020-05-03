#ifndef STM32F4xx_STM32F411XX_H
#define STM32F4xx_STM32F411XX_H

#include <stdint.h>

#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _MMIO_HWORD(mem_addr) (*(volatile uint16_t *)(mem_addr))
#define _MMIO_WORD(mem_addr) (*(volatile uint32_t *)(mem_addr))

// Cortex M4 general registers

#define _MMIO_ADDR_NVIC     0xE000E100UL

typedef struct 
{
    volatile uint32_t NVIC_ISER[8];     //  0x0000 - 0x001C Interrupt Set-enable Registers 0xE000E100
    const uint32_t reserved_1[24];      //  0x0020 - 0x007C reserved  
    volatile uint32_t NVIC_ICER[8];     //  0x0080 - 0x009C Interrupt Clear-enable Registers 0XE000E180
    const uint32_t reserved_2[24];      //  0x00A0 - 0x00FC reserved  
    volatile uint32_t NVIC_ISPR[8];     //  0x0100 - 0x011C Interrupt Set-pending Registers 0XE000E200
    const uint32_t reserved_3[24];      //  0x0120 - 0x017C reserved 
    volatile uint32_t NVIC_ICPR[8];     //  0x0180 - 0x019C Interrupt Clear-pending Registers 0XE000E280
    const uint32_t reserved_4[24];      //  0x01A0 - 0x01FC reserved 
    volatile uint32_t NVIC_IABR[8];     //  0x0200 - 0x021C Interrupt Active Bit Registers 0xE000E300
    const uint32_t reserved_5[56];      //  0x0220 - 0x02FC reserved 
    volatile uint32_t NVIC_IPR0[60];    //  0x0300 - 0x03EC Interrupt Priority Registers 0xE000E400
    const uint32_t reserved_6[644];     //  0x03F0 - 0x0DFC reserved 
    volatile uint32_t STIR;             //  0x0E00 Software Trigger Interrupt Register 0xE000EF00
} STM32F4xx_NVIC_RegDef_t;

#define STM32F4xx_NVIC           ((STM32F4xx_NVIC_RegDef_t* ) _MMIO_ADDR_NVIC)


// STM32F4xx peripheral registers

#define _MMIO_ADDR_CRC      0x40023000UL
#define _MMIO_ADDR_PWR      0x40007000UL

typedef struct
{
    volatile uint32_t PWR_CR;           //  0x00 PWR power control register 
    volatile uint32_t PWR_CSR;          //  0x04 PWR power control/status register
} STM32F4xx_PWR_RegDef_t;

#define STM32F4xx_PWR            ((STM32F4xx_PWR_RegDef_t* ) _MMIO_ADDR_PWR)

#define _MMIO_ADDR_BKP      0x40002800UL
#define _MMIO_ADDR_RCC      0x40023800UL  
typedef struct
{
    volatile uint32_t RCC_CR;           //  0x00 STM32F4xx_RCC clock control register 
    volatile uint32_t RCC_PLLCFGR;      //  0x04 STM32F4xx_RCC PLL configuration register
    volatile uint32_t RCC_CFGR;         //  0x08 STM32F4xx_RCC clock configuration register 
    volatile uint32_t RCC_CIR;          //  0x0C STM32F4xx_RCC clock interrupt register
    volatile uint32_t RCC_AHB1RSTR;     //  0x10 STM32F4xx_RCC AHB1 peripheral reset register
    volatile uint32_t RCC_AHB2RSTR;     //  0x14 STM32F4xx_RCC AHB2 peripheral reset register
    const    uint32_t _reserved_0;      //  0x18 Reserved register space
    const    uint32_t _reserved_1;      //  0x1C Reserved register space
    volatile uint32_t RCC_APB1RSTR;     //  0x20 STM32F4xx_RCC APB1 peripheral reset register
    volatile uint32_t RCC_APB2RSTR;     //  0x24 STM32F4xx_RCC APB2 peripheral reset register
    const    uint32_t _reserved_2;      //  0x28 Reserved register space
    const    uint32_t _reserved_3;      //  0x2C Reserved register space
    volatile uint32_t RCC_AHB1ENR;      //  0x30 STM32F4xx_RCC AHB1 peripheral clock enable register
    volatile uint32_t RCC_AHB2ENR;      //  0x34 STM32F4xx_RCC AHB2 peripheral clock enable register
    const    uint32_t _reserved_4;      //  0x38 Reserved register space
    const    uint32_t _reserved_5;      //  0x3C Reserved register space
    volatile uint32_t RCC_APB1ENR;      //  0x40 STM32F4xx_RCC APB1 peripheral clock enable register
    volatile uint32_t RCC_APB2ENR;      //  0x44 STM32F4xx_RCC APB2 peripheral clock enable register
    const    uint32_t _reserved_6;      //  0x48 Reserved register space
    const    uint32_t _reserved_7;      //  0x4C Reserved register space
    volatile uint32_t RCC_AHB1LPENR;    //  0x50 STM32F4xx_RCC AHB1 peripheral clock enable in low power mode register
    volatile uint32_t RCC_AHB2LPENR;    //  0x54 STM32F4xx_RCC AHB2 peripheral clock enable in low power mode register
    const    uint32_t _reserved_8;      //  0x58 Reserved register space
    const    uint32_t _reserved_9;      //  0x5C Reserved register space
    volatile uint32_t RCC_APB1LPENR;    //  0x60 STM32F4xx_RCC APB1 peripheral clock enable in low power mode register
    volatile uint32_t RCC_APB2LPENR;    //  0x64 STM32F4xx_RCC APB2 peripheral clock enabled in low power mode register
    const    uint32_t _reserved_10;     //  0x68 Reserved register space
    const    uint32_t _reserved_11;     //  0x6C Reserved register space
    volatile uint32_t RCC_BDCR;         //  0x70 STM32F4xx_RCC Backup domain control register
    volatile uint32_t RCC_CSR;          //  0x74 STM32F4xx_RCC clock control & status register
    const    uint32_t _reserved_12;     //  0x78 Reserved register space
    const    uint32_t _reserved_13;     //  0x7C Reserved register space
    volatile uint32_t RCC_SSCGR;        //  0x80 STM32F4xx_RCC spread spectrum clock generation register
    volatile uint32_t RCC_PLLI2SCFGR;   //  0x84 STM32F4xx_RCC PLLI2S configuration register
    const    uint32_t _reserved_14;     //  0x88 Reserved register space
    volatile uint32_t RCC_DCKCFGR;      //  0x8C STM32F4xx_RCC Dedicated Clocks Configuration Register
} STM32F4xx_RCC_RegDef_t;

#define STM32F4xx_RCC                ((STM32F4xx_RCC_RegDef_t* ) _MMIO_ADDR_RCC)

#define STM32F4xx_GPIOA_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<0))
#define STM32F4xx_GPIOA_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<0))
#define STM32F4xx_GPIOB_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<1))
#define STM32F4xx_GPIOB_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<1))
#define STM32F4xx_GPIOC_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<2))
#define STM32F4xx_GPIOC_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<2))
#define STM32F4xx_GPIOD_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<3))
#define STM32F4xx_GPIOD_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<3))
#define STM32F4xx_GPIOE_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<4))
#define STM32F4xx_GPIOE_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<4))
#define STM32F4xx_GPIOH_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<7))
#define STM32F4xx_GPIOH_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<7))

#define STM32F4xx_CRC_PCLK_EN()      (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<12))
#define STM32F4xx_CRC_PCLK_DI()      (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<12))

#define STM32F4xx_DMA1_PCLK_EN()     (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<21))
#define STM32F4xx_DMA1_PCLK_DI()     (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<21))
#define STM32F4xx_DMA2_PCLK_EN()     (STM32F4xx_RCC->RCC_AHB1ENR |= (1<<22))
#define STM32F4xx_DMA2_PCLK_DI()     (STM32F4xx_RCC->RCC_AHB1ENR &= ~(1<<22))

#define STM32F4xx_USB_FS_PCLK_EN()   (STM32F4xx_RCC->RCC_AHB2ENR |= (1<<7))
#define STM32F4xx_USB_FS_PCLK_DI()   (STM32F4xx_RCC->RCC_AHB2ENR &= ~(1<<7))

#define STM32F4xx_TIM1_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR |= (1<<0))
#define STM32F4xx_TIM1_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<0))
#define STM32F4xx_TIM2_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<0))
#define STM32F4xx_TIM2_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<0))
#define STM32F4xx_TIM3_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<1))
#define STM32F4xx_TIM3_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<1))
#define STM32F4xx_TIM4_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<2))
#define STM32F4xx_TIM4_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<2))
#define STM32F4xx_TIM5_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<3))
#define STM32F4xx_TIM5_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<3))

#define STM32F4xx_TIM9_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR |= (1<<16))
#define STM32F4xx_TIM9_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<16))
#define STM32F4xx_TIM10_PCLK_EN()    (STM32F4xx_RCC->RCC_APB2ENR |= (1<<17))
#define STM32F4xx_TIM10_PCLK_DI()    (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<17))
#define STM32F4xx_TIM11_PCLK_EN()    (STM32F4xx_RCC->RCC_APB2ENR |= (1<<18))
#define STM32F4xx_TIM11_PCLK_DI()    (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<18))

#define STM32F4xx_WWDG_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<11))
#define STM32F4xx_WWDG_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<11))

#define STM32F4xx_PWR_PCLK_EN()      (STM32F4xx_RCC->RCC_APB1ENR |= (1<<28))
#define STM32F4xx_PWR_PCLK_DI()      (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<28))

#define STM32F4xx_I2C1_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<21))
#define STM32F4xx_I2C1_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<21))
#define STM32F4xx_I2C2_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<22))
#define STM32F4xx_I2C2_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<22))
#define STM32F4xx_I2C3_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<23))
#define STM32F4xx_I2C3_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<23))

#define STM32F4xx_SPI1_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR |= (1<<12))
#define STM32F4xx_SPI1_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<12))
#define STM32F4xx_SPI2_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<14))
#define STM32F4xx_SPI2_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<14))
#define STM32F4xx_SPI3_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR |= (1<<15))
#define STM32F4xx_SPI3_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<15))
#define STM32F4xx_SPI4_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR |= (1<<13))
#define STM32F4xx_SPI4_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<13))
#define STM32F4xx_SPI5_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR |= (1<<20))
#define STM32F4xx_SPI5_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<20))

#define STM32F4xx_USART1_PCLK_EN()   (STM32F4xx_RCC->RCC_APB2ENR |= (1<<4))
#define STM32F4xx_USART1_PCLK_DI()   (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<4))
#define STM32F4xx_USART2_PCLK_EN()   (STM32F4xx_RCC->RCC_APB1ENR |= (1<<17))
#define STM32F4xx_USART2_PCLK_DI()   (STM32F4xx_RCC->RCC_APB1ENR &= ~(1<<17))
#define STM32F4xx_USART6_PCLK_EN()   (STM32F4xx_RCC->RCC_APB2ENR |= (1<<5))
#define STM32F4xx_USART6_PCLK_DI()   (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<5))

#define STM32F4xx_ADC1_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR |= (1<<8))
#define STM32F4xx_ADC1_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<8))

#define STM32F4xx_SDIO_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR |= (1<<11))
#define STM32F4xx_SDIO_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<11))

#define STM32F4xx_SYSCFG_PCLK_EN()   (STM32F4xx_RCC->RCC_APB2ENR |= (1<<14))
#define STM32F4xx_SYSCFG_PCLK_DI()   (STM32F4xx_RCC->RCC_APB2ENR &= ~(1<<14))

typedef struct
{
    volatile uint32_t MODER;    // 0x00
    volatile uint32_t OTYPER;   // 0x04
    volatile uint32_t OSPEEDR;  // 0x08
    volatile uint32_t PUPDR;    // 0x0C
    volatile uint32_t IDR;      // 0x10
    volatile uint32_t ODR;      // 0x14
    volatile uint32_t BSRR;     // 0x18
    volatile uint32_t LCKR;     // 0x1C
    volatile uint32_t AFRL;     // 0x20
    volatile uint32_t AFRH;     // 0x24
} STM32F4xx_GPIO_RegDef_t;


#define _MMIO_ADDR_GPIOA    0x40020000UL  
#define STM32F4xx_GPIOA          ((STM32F4xx_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOA)

#define _MMIO_ADDR_GPIOB    0x40020400UL
#define STM32F4xx_GPIOB          ((STM32F4xx_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOB)

#define _MMIO_ADDR_GPIOC    0x40020800UL
#define STM32F4xx_GPIOC          ((STM32F4xx_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOC)

#define _MMIO_ADDR_GPIOD    0x40020C00UL
#define STM32F4xx_GPIOD          ((STM32F4xx_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOD)

#define _MMIO_ADDR_GPIOE    0x40021000UL
#define STM32F4xx_GPIOE          ((STM32F4xx_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOE)

#define _MMIO_ADDR_GPIOH    0x40021C00UL
#define STM32F4xx_GPIOH          ((STM32F4xx_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOH)


#define _MMIO_ADDR_EXTI     0x40013C00UL

typedef struct
{
    volatile uint32_t EXTI_IMR;     // 0x00 Interrupt mask register
    volatile uint32_t EXTI_EMR;     // 0x04 Event mask register
    volatile uint32_t EXTI_RTSR;    // 0x08 Rising trigger selection register
    volatile uint32_t EXTI_FTSR;    // 0x0C Falling trigger selection register
    volatile uint32_t EXTI_SWIER;   // 0x10 Software interrupt event register 
    volatile uint32_t EXTI_PR;      // 0x14 Pending register
} STM32F4xx_EXTI_RegDef_t;

#define STM32F4xx_EXTI          ((STM32F4xx_EXTI_RegDef_t* ) _MMIO_ADDR_EXTI)

#define _MMIO_ADDR_ADC      0x40012000UL

#define _MMIO_ADDR_DMA1     0x40026000UL
#define _MMIO_ADDR_DMA2     0x40026400UL

#define _MMIO_ADDR_TIM1     0x40010000UL
#define _MMIO_ADDR_TIM8     0x40013400UL

#define _MMIO_ADDR_TIM2     0x40000000UL 
#define _MMIO_ADDR_TIM3     0x40000400UL
#define _MMIO_ADDR_TIM4     0x40000800UL 
#define _MMIO_ADDR_TIM5     0x40000C00UL 

#define _MMIO_ADDR_TIM6     0x40001000UL
#define _MMIO_ADDR_TIM7     0x40001400UL

#define _MMIO_ADDR_TIM9     0x40014000UL
#define _MMIO_ADDR_TIM10    0x40014400UL  
#define _MMIO_ADDR_TIM11    0x40014800UL
#define _MMIO_ADDR_TIM12    0x40001800UL
#define _MMIO_ADDR_TIM13    0x40001C00UL
#define _MMIO_ADDR_TIM14    0x40002000UL

#define _MMIO_ADDR_RTC      0x40002800UL 

typedef struct
{
    volatile uint32_t RTC_TR;       // 0x00 RTC time register
    volatile uint32_t RTC_DR;       // 0x04 RTC date register
    volatile uint32_t RTC_CR;       // 0x08 RTC control register
    volatile uint32_t RTC_ISR;      // 0x0C RTC initialization and status register
    volatile uint32_t RTC_PRER;     // 0x10 RTC prescaler register 
    volatile uint32_t RTC_WUTR;     // 0x14 RTC wakeup timer register 
    volatile uint32_t RTC_CALIBR;   // 0x18 RTC calibration register
    volatile uint32_t RTC_ALRMAR;   // 0x1C RTC alarm A register
    volatile uint32_t RTC_ALRMBR;   // 0x20 RTC alarm B register
    volatile uint32_t RTC_WPR;      // 0x24 RTC write protection register
    volatile uint32_t RTC_SSR;      // 0x28 RTC sub second register
    volatile uint32_t RTC_SHIFTR;   // 0x2C RTC shift control register
    volatile uint32_t RTC_TSTR;     // 0x30 RTC time stamp time register
    volatile uint32_t RTC_TSSSR;    // 0x34 RTC time stamp date register 
    volatile uint32_t RTC_CALR;     // 0x38 RTC timestamp sub second register 
    volatile uint32_t RTC_TAFCR;    // 0x3C RTC tamper and alternate function configuration register
    volatile uint32_t RTC_ALRMASSR; // 0x40 RTC alarm A sub second register
    volatile uint32_t RTC_ALRMBSSR; // 0x44 RTC alarm B sub second register 
    volatile uint32_t RTC_BKPR[20]; // 0x48 RTC backup registers
} STM32F4xx_RTC_RegDef_t;

#define STM32F4XX_RTC_REG   ((STM32F4xx_RTC_RegDef_t* ) _MMIO_ADDR_RTC)

#define _MMIO_ADDR_IWDG     0x40003000UL 
#define _MMIO_ADDR_WWDG     0x40002C00UL

#define _MMIO_ADDR_SDIO     0x40012C00UL 

#define _MMIO_ADDR_USB_FS   0x50000000UL 

#define _MMIO_ADDR_SPI1     0x40013000UL
#define _MMIO_ADDR_SPI2     0x40003800UL 
#define _MMIO_ADDR_SPI3     0x40003C00UL 
#define _MMIO_ADDR_SPI4     0x40013400UL  
#define _MMIO_ADDR_SPI5     0x40015000UL 

#define _MMIO_ADDR_I2S1     _MMIO_ADDR_SPI1
#define _MMIO_ADDR_I2S2     _MMIO_ADDR_SPI2
#define _MMIO_ADDR_I2S3     _MMIO_ADDR_SPI3
#define _MMIO_ADDR_I2S4     _MMIO_ADDR_SPI4 
#define _MMIO_ADDR_I2S5     _MMIO_ADDR_SPI5 

#define _MMIO_ADDR_I2S2_ext 0x40003400UL  
#define _MMIO_ADDR_I2S3_ext 0x40004000UL 

typedef union __STM32F4xx_I2C_CR1_Regdef
{
    struct
    {
        volatile uint16_t START         :   1;  // Byte 1, Bit 0 |  8
        volatile uint16_t STOP          :   1;  // Byte 1, Bit 1 |  9
        volatile uint16_t ACK           :   1;  // Byte 1, Bit 2 | 10
        volatile uint16_t POS           :   1;  // Byte 1, Bit 3 | 11
        volatile uint16_t PEC           :   1;  // Byte 1, Bit 4 | 12
        volatile uint16_t ALERT         :   1;  // Byte 1, Bit 5 | 13
        const uint16_t _reserved_1      :   1;  // Byte 1, Bit 6 | 14
        volatile uint16_t SWRST         :   1;  // Byte 1, Bit 7 | 15
        volatile uint16_t PE            :   1;  // Byte 0, Bit 0 |  0
        volatile uint16_t SMBUS         :   1;  // Byte 0, Bit 1 |  1
        const uint16_t _reserved_2      :   1;  // Byte 0, Bit 2 |  2
        volatile uint16_t SMBTYPE       :   1;  // Byte 0, Bit 3 |  3
        volatile uint16_t ENARP         :   1;  // Byte 0, Bit 4 |  4
        volatile uint16_t ENPEC         :   1;  // Byte 0, Bit 5 |  5
        volatile uint16_t ENGC          :   1;  // Byte 0, Bit 6 |  6
        volatile uint16_t NOSTRETCH     :   1;  // Byte 0, Bit 7 |  7
    };
    uint16_t raw;
} STM32F4xx_I2C_CR1_Regdef_t;

typedef union __STM32F4xx_I2C_CR2_Regdef
{
    struct
    {
        volatile uint16_t ITERREN       :   1;  // Byte 1, Bit 0   |  8
        volatile uint16_t ITEVTEN       :   1;  // Byte 1, Bit 1   |  9
        volatile uint16_t ITBUFEN       :   1;  // Byte 1, Bit 2   | 10
        volatile uint16_t DMAEN         :   1;  // Byte 1, Bit 3   | 11
        volatile uint16_t LAST          :   1;  // Byte 1, Bit 4   | 12
        const uint16_t _reserved_1      :   3;  // Byte 1, Bit 5-7 | 13-15
        volatile uint16_t FREQ          :   6;  // Byte 0, Bit 0-5 |  0-5
        const uint16_t _reserved_1      :   2;  // Byte 0, Bit 6-7 |  6-7
    };
    uint16_t raw;
} STM32F4xx_I2C_CR2_Regdef_t;

typedef union __STM32F4xx_I2C_OAR1_Regdef
{
    struct
    {
        volatile uint16_t ADD2          :   1;  // Byte 1, Bit 0-1 |  8-9
        const uint16_t _reserved_1      :   5;  // Byte 1, Bit 2-6 | 10-14
        volatile uint16_t ADDMODE       :   1;  // Byte 1, Bit 7   | 15
        volatile uint16_t ADD0          :   1;  // Byte 0, Bit 0   |  0
        volatile uint16_t ADD1          :   7;  // Byte 0, Bit 1-7 |  1-7

    };
    uint16_t raw;
} STM32F4xx_I2C_OAR1_Regdef_t;

typedef union __STM32F4xx_I2C_OAR2_Regdef
{
    struct
    {
        const uint16_t _reserved_1      :   8;  // Byte 1, Bit 0-7 |  8-15
        volatile uint16_t ENDUAL        :   1;  // Byte 0, Bit 0   |  0
        volatile uint16_t ADD2          :   7;  // Byte 0, Bit 1-7 |  1-7

    };
    uint16_t raw;
} STM32F4xx_I2C_OAR2_Regdef_t;

typedef union __STM32F4xx_I2C_DR_Regdef
{
    struct
    {
        const uint16_t _reserved_1      :   8;  // Byte 1, Bit 0-7 |  8-15
        volatile uint16_t DR            :   8;  // Byte 0, Bit 0-7 |  0-7

    };
    uint16_t raw;
} STM32F4xx_I2C_DR_Regdef_t;

typedef union __STM32F4xx_I2C_SR1_Regdef
{
    struct
    {
        volatile uint16_t BERR          :   1;  // Byte 1, Bit 0 |  8
        volatile uint16_t ARLO          :   1;  // Byte 1, Bit 1 |  9
        volatile uint16_t AF            :   1;  // Byte 1, Bit 2 | 10
        volatile uint16_t OVR           :   1;  // Byte 1, Bit 3 | 11
        volatile uint16_t PEC_ERR       :   1;  // Byte 1, Bit 4 | 12
        const uint16_t _reserved_1      :   1;  // Byte 1, Bit 5 | 13
        volatile uint16_t TIMEOUT       :   1;  // Byte 1, Bit 6 | 14
        volatile uint16_t SMBALER       :   1;  // Byte 1, Bit 7 | 15
        volatile uint16_t SB            :   1;  // Byte 0, Bit 0 |  0
        volatile uint16_t ADDR          :   1;  // Byte 0, Bit 1 |  1
        volatile uint16_t BTF           :   1;  // Byte 0, Bit 2 |  2
        volatile uint16_t ADD10         :   1;  // Byte 0, Bit 3 |  3
        volatile uint16_t STOPF         :   1;  // Byte 0, Bit 4 |  4
        const uint16_t __reserved_2     :   1;  // Byte 0, Bit 5 |  5
        volatile uint16_t RxNE          :   1;  // Byte 0, Bit 6 |  6
        volatile uint16_t TxE           :   1;  // Byte 0, Bit 7 |  7
    };
    uint16_t raw;
} STM32F4xx_I2C_SR1_Regdef_t;

typedef union __STM32F4xx_I2C_SR2_Regdef
{
    struct
    {
        volatile uint16_t PEC           :   8;  // Byte 1, Bit 0-7 |  8-15
        volatile uint16_t MSL           :   1;  // Byte 0, Bit 0   |  0
        volatile uint16_t BUSY          :   1;  // Byte 0, Bit 1   |  1
        volatile uint16_t TRA           :   1;  // Byte 0, Bit 2   |  2
        const uint16_t __reserved       :   1;  // Byte 0, Bit 3   |  3
        volatile uint16_t GENCALL       :   1;  // Byte 0, Bit 4   |  4
        volatile uint16_t SMBDEFAULT    :   1;  // Byte 0, Bit 5   |  5
        volatile uint16_t SMBHOST       :   1;  // Byte 0, Bit 6   |  6
        volatile uint16_t DAUALF        :   1;  // Byte 0, Bit 7   |  7
    };
    uint16_t raw;
} STM32F4xx_I2C_SR2_Regdef_t;

typedef union __STM32F4xx_I2C_CCR_Regdef
{
    struct
    {
        volatile uint16_t CCR_H         :   4;  // Byte 1, Bit 0-3 |  8-11
        const uint16_t __reserved       :   2;  // Byte 1, Bit 4-5 |  12-13
        volatile uint16_t CDUTY         :   1;  // Byte 1, Bit 6   |  14
        volatile uint16_t FS            :   1;  // Byte 1, Bit 7   |  15
        volatile uint16_t CCR_L         :   8;  // Byte 0, Bit 0-7 |  0-7
    };
    uint16_t raw;
} STM32F4xx_I2C_CCR_Regdef_t;

typedef union __STM32F4xx_I2C_TRISE_Regdef
{
    struct
    {
        const uint16_t __reserved_1     :   8;  // Byte 1, Bit 0-7 |   8-15
        volatile uint16_t TRISE         :   6;  // Byte 0, Bit 0-5 |  0-5
        const uint16_t __reserved_2     :   2;  // Byte 0, Bit 6-7 |  6-7
    };
    uint16_t raw;
} STM32F4xx_I2C_TRISE_Regdef_t;

typedef union __STM32F4xx_I2C_FLTR_Regdef
{
    struct
    {
        const uint16_t __reserved_1     :   8;  // Byte 1, Bit 0-7 |  8-15
        volatile uint16_t DNF           :   4;  // Byte 0, Bit 0-3 |  0-3
        volatile uint16_t ANOFF         :   4;  // Byte 0, Bit 4   |  4
        const uint16_t __reserved_2     :   3;  // Byte 0, Bit 5-7 |  5-7
    };
    uint16_t raw;
} STM32F4xx_I2C_FLTR_Regdef_t;


typedef struct
{
    volatile STM32F4xx_I2C_CR1_Regdef_t I2C_CR1;    // 0x00 I2C Control register 1
    volatile STM32F4xx_I2C_CR2_Regdef_t I2C_CR2;    // 0x04 I2C Control register 2
    volatile STM32F4xx_I2C_OAR1_Regdef_t I2C_OAR1;  // 0x08 I2C Own address register 1 
    volatile STM32F4xx_I2C_OAR2_Regdef_t I2C_OAR2;  // 0x0C I2C Own address register 2
    volatile STM32F4xx_I2C_DR_Regdef_t I2C_DR;      // 0x10 I2C Data register 
    volatile STM32F4xx_I2C_SR1_Regdef_t I2C_SR1;    // 0x14 I2C Status register 1
    volatile STM32F4xx_I2C_SR2_Regdef_t I2C_SR2;    // 0x18 I2C Status register 2 
    volatile STM32F4xx_I2C_CCR_Regdef_t I2C_CCR;    // 0x1C I2C Clock control register 
    volatile STM32F4xx_I2C_TRISE_Regdef_t I2C_TRISE;// 0x20 I2C TRISE register 
    volatile STM32F4xx_I2C_FLTR_Regdef_t I2C_FLTR;  // 0x24 I2C FLTR register
} STM32F4xx_I2C_RegDef_t;

#define _MMIO_ADDR_I2C1     0x40005400UL
#define STM32F4XX_RTC_REG   ((STM32F4xx_I2C_RegDef_t* ) _MMIO_ADDR_I2C1)
#define _MMIO_ADDR_I2C2     0x40005800UL 
#define STM32F4XX_RTC_REG   ((STM32F4xx_I2C_RegDef_t* ) _MMIO_ADDR_I2C2)
#define _MMIO_ADDR_I2C3     0x40005C00UL  
#define STM32F4XX_RTC_REG   ((STM32F4xx_I2C_RegDef_t* ) _MMIO_ADDR_I2C3)

#define _MMIO_ADDR_USART1   0x40011000UL
#define _MMIO_ADDR_USART2   0x40004400UL
#define _MMIO_ADDR_USART3   0x40004800UL
#define _MMIO_ADDR_USART4   0x40004C00UL
#define _MMIO_ADDR_USART5   0x40005000UL
#define _MMIO_ADDR_USART6   0x40011400UL 

#define _MMIO_ADDR_USB_OTG  0x50000000

#define _MMIO_ADDR_FLASH    0x40023C00 

#define _MMIO_ADDR_SYSCFG   0x40013800 

typedef struct
{
    volatile uint32_t SYSCFG_MEMRMP;    //  0x00 SYSCFG memory remap register
    volatile uint32_t SYSCFG_PMC;       //  0x04 SYSCFG peripheral mode configuration register 
    volatile uint32_t SYSCFG_EXTICR1;   //  0x08 SYSCFG external interrupt configuration register 1
    volatile uint32_t SYSCFG_EXTICR2;   //  0x0C SYSCFG external interrupt configuration register 2
    volatile uint32_t SYSCFG_EXTICR3;   //  0x10 SYSCFG external interrupt configuration register 3
    volatile uint32_t SYSCFG_EXTICR4;   //  0x14 SYSCFG external interrupt configuration register 4
    const    uint32_t _reserved_1;      //  0x18 reserved
    const    uint32_t _reserved_2;      //  0x1C reserved
    volatile uint32_t SYSCFG_CMPCR;     //  0x20 Compensation cell control register
} STM32F4xx_SYSCFG_RegDef_t;

#define STM32F4xx_SYSCFG              ((STM32F4xx_SYSCFG_RegDef_t* ) _MMIO_ADDR_SYSCFG)

#endif