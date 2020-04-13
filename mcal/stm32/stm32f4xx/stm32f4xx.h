#ifndef MCAL_STM32F411XX_H
#define MCAL_STM32F411XX_H

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
} MCAL_NVIC_RegDef_t;

#define MCAL_NVIC           ((MCAL_NVIC_RegDef_t* ) _MMIO_ADDR_NVIC)


// STM32F4xx peripheral registers

#define _MMIO_ADDR_CRC      0x40023000UL
#define _MMIO_ADDR_PWR      0x40007000UL

typedef struct
{
    volatile uint32_t PWR_CR;           //  0x00 PWR power control register 
    volatile uint32_t PWR_CSR;          //  0x04 PWR power control/status register
} MCAL_PWR_RegDef_t;

#define MCAL_PWR            ((MCAL_PWR_RegDef_t* ) _MMIO_ADDR_PWR)

#define _MMIO_ADDR_BKP      0x40002800UL
#define _MMIO_ADDR_RCC      0x40023800UL  
typedef struct
{
    volatile uint32_t RCC_CR;           //  0x00 MCAL_RCC clock control register 
    volatile uint32_t RCC_PLLCFGR;      //  0x04 MCAL_RCC PLL configuration register
    volatile uint32_t RCC_CFGR;         //  0x08 MCAL_RCC clock configuration register 
    volatile uint32_t RCC_CIR;          //  0x0C MCAL_RCC clock interrupt register
    volatile uint32_t RCC_AHB1RSTR;     //  0x10 MCAL_RCC AHB1 peripheral reset register
    volatile uint32_t RCC_AHB2RSTR;     //  0x14 MCAL_RCC AHB2 peripheral reset register
    const    uint32_t _reserved_0;      //  0x18 Reserved register space
    const    uint32_t _reserved_1;      //  0x1C Reserved register space
    volatile uint32_t RCC_APB1RSTR;     //  0x20 MCAL_RCC APB1 peripheral reset register
    volatile uint32_t RCC_APB2RSTR;     //  0x24 MCAL_RCC APB2 peripheral reset register
    const    uint32_t _reserved_2;      //  0x28 Reserved register space
    const    uint32_t _reserved_3;      //  0x2C Reserved register space
    volatile uint32_t RCC_AHB1ENR;      //  0x30 MCAL_RCC AHB1 peripheral clock enable register
    volatile uint32_t RCC_AHB2ENR;      //  0x34 MCAL_RCC AHB2 peripheral clock enable register
    const    uint32_t _reserved_4;      //  0x38 Reserved register space
    const    uint32_t _reserved_5;      //  0x3C Reserved register space
    volatile uint32_t RCC_APB1ENR;      //  0x40 MCAL_RCC APB1 peripheral clock enable register
    volatile uint32_t RCC_APB2ENR;      //  0x44 MCAL_RCC APB2 peripheral clock enable register
    const    uint32_t _reserved_6;      //  0x48 Reserved register space
    const    uint32_t _reserved_7;      //  0x4C Reserved register space
    volatile uint32_t RCC_AHB1LPENR;    //  0x50 MCAL_RCC AHB1 peripheral clock enable in low power mode register
    volatile uint32_t RCC_AHB2LPENR;    //  0x54 MCAL_RCC AHB2 peripheral clock enable in low power mode register
    const    uint32_t _reserved_8;      //  0x58 Reserved register space
    const    uint32_t _reserved_9;      //  0x5C Reserved register space
    volatile uint32_t RCC_APB1LPENR;    //  0x60 MCAL_RCC APB1 peripheral clock enable in low power mode register
    volatile uint32_t RCC_APB2LPENR;    //  0x64 MCAL_RCC APB2 peripheral clock enabled in low power mode register
    const    uint32_t _reserved_10;     //  0x68 Reserved register space
    const    uint32_t _reserved_11;     //  0x6C Reserved register space
    volatile uint32_t RCC_BDCR;         //  0x70 MCAL_RCC Backup domain control register
    volatile uint32_t RCC_CSR;          //  0x74 MCAL_RCC clock control & status register
    const    uint32_t _reserved_12;     //  0x78 Reserved register space
    const    uint32_t _reserved_13;     //  0x7C Reserved register space
    volatile uint32_t RCC_SSCGR;        //  0x80 MCAL_RCC spread spectrum clock generation register
    volatile uint32_t RCC_PLLI2SCFGR;   //  0x84 MCAL_RCC PLLI2S configuration register
    const    uint32_t _reserved_14;     //  0x88 Reserved register space
    volatile uint32_t RCC_DCKCFGR;      //  0x8C MCAL_RCC Dedicated Clocks Configuration Register
} MCAL_RCC_RegDef_t;

#define MCAL_RCC                ((MCAL_RCC_RegDef_t* ) _MMIO_ADDR_RCC)

#define MCAL_GPIOA_PCLK_EN()    (MCAL_RCC->RCC_AHB1ENR |= (1<<0))
#define MCAL_GPIOA_PCLK_DI()    (MCAL_RCC->RCC_AHB1ENR &= ~(1<<0))
#define MCAL_GPIOB_PCLK_EN()    (MCAL_RCC->RCC_AHB1ENR |= (1<<1))
#define MCAL_GPIOB_PCLK_DI()    (MCAL_RCC->RCC_AHB1ENR &= ~(1<<1))
#define MCAL_GPIOC_PCLK_EN()    (MCAL_RCC->RCC_AHB1ENR |= (1<<2))
#define MCAL_GPIOC_PCLK_DI()    (MCAL_RCC->RCC_AHB1ENR &= ~(1<<2))
#define MCAL_GPIOD_PCLK_EN()    (MCAL_RCC->RCC_AHB1ENR |= (1<<3))
#define MCAL_GPIOD_PCLK_DI()    (MCAL_RCC->RCC_AHB1ENR &= ~(1<<3))
#define MCAL_GPIOE_PCLK_EN()    (MCAL_RCC->RCC_AHB1ENR |= (1<<4))
#define MCAL_GPIOE_PCLK_DI()    (MCAL_RCC->RCC_AHB1ENR &= ~(1<<4))
#define MCAL_GPIOH_PCLK_EN()    (MCAL_RCC->RCC_AHB1ENR |= (1<<7))
#define MCAL_GPIOH_PCLK_DI()    (MCAL_RCC->RCC_AHB1ENR &= ~(1<<7))

#define MCAL_CRC_PCLK_EN()      (MCAL_RCC->RCC_AHB1ENR |= (1<<12))
#define MCAL_CRC_PCLK_DI()      (MCAL_RCC->RCC_AHB1ENR &= ~(1<<12))

#define MCAL_DMA1_PCLK_EN()     (MCAL_RCC->RCC_AHB1ENR |= (1<<21))
#define MCAL_DMA1_PCLK_DI()     (MCAL_RCC->RCC_AHB1ENR &= ~(1<<21))
#define MCAL_DMA2_PCLK_EN()     (MCAL_RCC->RCC_AHB1ENR |= (1<<22))
#define MCAL_DMA2_PCLK_DI()     (MCAL_RCC->RCC_AHB1ENR &= ~(1<<22))

#define MCAL_USB_FS_PCLK_EN()   (MCAL_RCC->RCC_AHB2ENR |= (1<<7))
#define MCAL_USB_FS_PCLK_DI()   (MCAL_RCC->RCC_AHB2ENR &= ~(1<<7))

#define MCAL_TIM1_PCLK_EN()     (MCAL_RCC->RCC_APB2ENR |= (1<<0))
#define MCAL_TIM1_PCLK_DI()     (MCAL_RCC->RCC_APB2ENR &= ~(1<<0))
#define MCAL_TIM2_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<0))
#define MCAL_TIM2_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<0))
#define MCAL_TIM3_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<1))
#define MCAL_TIM3_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<1))
#define MCAL_TIM4_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<2))
#define MCAL_TIM4_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<2))
#define MCAL_TIM5_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<3))
#define MCAL_TIM5_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<3))

#define MCAL_TIM9_PCLK_EN()     (MCAL_RCC->RCC_APB2ENR |= (1<<16))
#define MCAL_TIM9_PCLK_DI()     (MCAL_RCC->RCC_APB2ENR &= ~(1<<16))
#define MCAL_TIM10_PCLK_EN()    (MCAL_RCC->RCC_APB2ENR |= (1<<17))
#define MCAL_TIM10_PCLK_DI()    (MCAL_RCC->RCC_APB2ENR &= ~(1<<17))
#define MCAL_TIM11_PCLK_EN()    (MCAL_RCC->RCC_APB2ENR |= (1<<18))
#define MCAL_TIM11_PCLK_DI()    (MCAL_RCC->RCC_APB2ENR &= ~(1<<18))

#define MCAL_WWDG_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<11))
#define MCAL_WWDG_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<11))

#define MCAL_PWR_PCLK_EN()      (MCAL_RCC->RCC_APB1ENR |= (1<<28))
#define MCAL_PWR_PCLK_DI()      (MCAL_RCC->RCC_APB1ENR &= ~(1<<28))

#define MCAL_I2C1_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<21))
#define MCAL_I2C1_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<21))
#define MCAL_I2C2_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<22))
#define MCAL_I2C2_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<22))
#define MCAL_I2C3_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<23))
#define MCAL_I2C3_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<23))

#define MCAL_SPI1_PCLK_EN()     (MCAL_RCC->RCC_APB2ENR |= (1<<12))
#define MCAL_SPI1_PCLK_DI()     (MCAL_RCC->RCC_APB2ENR &= ~(1<<12))
#define MCAL_SPI2_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<14))
#define MCAL_SPI2_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<14))
#define MCAL_SPI3_PCLK_EN()     (MCAL_RCC->RCC_APB1ENR |= (1<<15))
#define MCAL_SPI3_PCLK_DI()     (MCAL_RCC->RCC_APB1ENR &= ~(1<<15))
#define MCAL_SPI4_PCLK_EN()     (MCAL_RCC->RCC_APB2ENR |= (1<<13))
#define MCAL_SPI4_PCLK_DI()     (MCAL_RCC->RCC_APB2ENR &= ~(1<<13))
#define MCAL_SPI5_PCLK_EN()     (MCAL_RCC->RCC_APB2ENR |= (1<<20))
#define MCAL_SPI5_PCLK_DI()     (MCAL_RCC->RCC_APB2ENR &= ~(1<<20))

#define MCAL_USART1_PCLK_EN()   (MCAL_RCC->RCC_APB2ENR |= (1<<4))
#define MCAL_USART1_PCLK_DI()   (MCAL_RCC->RCC_APB2ENR &= ~(1<<4))
#define MCAL_USART2_PCLK_EN()   (MCAL_RCC->RCC_APB1ENR |= (1<<17))
#define MCAL_USART2_PCLK_DI()   (MCAL_RCC->RCC_APB1ENR &= ~(1<<17))
#define MCAL_USART6_PCLK_EN()   (MCAL_RCC->RCC_APB2ENR |= (1<<5))
#define MCAL_USART6_PCLK_DI()   (MCAL_RCC->RCC_APB2ENR &= ~(1<<5))

#define MCAL_ADC1_PCLK_EN()     (MCAL_RCC->RCC_APB2ENR |= (1<<8))
#define MCAL_ADC1_PCLK_DI()     (MCAL_RCC->RCC_APB2ENR &= ~(1<<8))

#define MCAL_SDIO_PCLK_EN()     (MCAL_RCC->RCC_APB2ENR |= (1<<11))
#define MCAL_SDIO_PCLK_DI()     (MCAL_RCC->RCC_APB2ENR &= ~(1<<11))

#define MCAL_SYSCFG_PCLK_EN()   (MCAL_RCC->RCC_APB2ENR |= (1<<14))
#define MCAL_SYSCFG_PCLK_DI()   (MCAL_RCC->RCC_APB2ENR &= ~(1<<14))

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
} MCAL_GPIO_RegDef_t;


#define _MMIO_ADDR_GPIOA    0x40020000UL  
#define MCAL_GPIOA          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOA)

#define _MMIO_ADDR_GPIOB    0x40020400UL
#define MCAL_GPIOB          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOB)

#define _MMIO_ADDR_GPIOC    0x40020800UL
#define MCAL_GPIOC          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOC)

#define _MMIO_ADDR_GPIOD    0x40020C00UL
#define MCAL_GPIOD          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOD)

#define _MMIO_ADDR_GPIOE    0x40021000UL
#define MCAL_GPIOE          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOE)

#define _MMIO_ADDR_GPIOH    0x40021C00UL
#define MCAL_GPIOH          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOH)


#define _MMIO_ADDR_EXTI     0x40013C00UL

typedef struct
{
    volatile uint32_t EXTI_IMR;     // 0x00 Interrupt mask register
    volatile uint32_t EXTI_EMR;     // 0x04 Event mask register
    volatile uint32_t EXTI_RTSR;    // 0x08 Rising trigger selection register
    volatile uint32_t EXTI_FTSR;    // 0x0C Falling trigger selection register
    volatile uint32_t EXTI_SWIER;   // 0x10 Software interrupt event register 
    volatile uint32_t EXTI_PR;      // 0x14 Pending register
} MCAL_EXTI_RegDef_t;

#define MCAL_EXTI          ((MCAL_EXTI_RegDef_t* ) _MMIO_ADDR_EXTI)

#define _MMIO_ADDR_ADC1     0x40012000UL
#define _MMIO_ADDR_ADC2     0x40012800UL
#define _MMIO_ADDR_ADC3     0x40013C00UL

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

#define _MMIO_ADDR_I2C1     0x40005400UL
#define _MMIO_ADDR_I2C2     0x40005800UL 
#define _MMIO_ADDR_I2C3     0x40005C00UL  

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
} MCAL_SYSCFG_RegDef_t;

#define MCAL_SYSCFG              ((MCAL_SYSCFG_RegDef_t* ) _MMIO_ADDR_SYSCFG)

#endif