#ifndef MCAL_STM32F411XX_H
#define MCAL_STM32F411XX_H

#include <stdint.h>

#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _MMIO_HWORD(mem_addr) (*(volatile uint16_t *)(mem_addr))
#define _MMIO_WORD(mem_addr) (*(volatile uint32_t *)(mem_addr))

#define _MMIO_ADDR_CRC      0x40023000U
#define _MMIO_ADDR_PWR      0x40007000U
#define _MMIO_ADDR_BKP      0x40002800U
#define _MMIO_ADDR_RCC      0x40023800U  
typedef struct
{
    volatile uint32_t RCC_CR;           //  MCAL_RCC clock control register 
    volatile uint32_t RCC_PLLCFGR;      //  MCAL_RCC PLL configuration register
    volatile uint32_t RCC_CFGR;         //  MCAL_RCC clock configuration register 
    volatile uint32_t RCC_CIR;          //  MCAL_RCC clock interrupt register
    volatile uint32_t RCC_AHB1RSTR;     //  MCAL_RCC AHB1 peripheral reset register
    volatile uint32_t RCC_AHB2RSTR;     //  MCAL_RCC AHB2 peripheral reset register
    const    uint32_t _reserved_0;      //  Reserved register space
    const    uint32_t _reserved_1;      //  Reserved register space
    volatile uint32_t RCC_APB1RSTR;     //  MCAL_RCC APB1 peripheral reset register
    volatile uint32_t RCC_APB2RSTR;     //  MCAL_RCC APB2 peripheral reset register
    const    uint32_t _reserved_2;      //  Reserved register space
    const    uint32_t _reserved_3;      //  Reserved register space
    volatile uint32_t RCC_AHB1ENR;      //  MCAL_RCC AHB1 peripheral clock enable register
    volatile uint32_t RCC_AHB2ENR;      //  MCAL_RCC AHB2 peripheral clock enable register
    const    uint32_t _reserved_4;      //  Reserved register space
    const    uint32_t _reserved_5;      //  Reserved register space
    volatile uint32_t RCC_APB1ENR;      //  MCAL_RCC APB1 peripheral clock enable register
    volatile uint32_t RCC_APB2ENR;      //  MCAL_RCC APB2 peripheral clock enable register
    const    uint32_t _reserved_6;      //  Reserved register space
    const    uint32_t _reserved_7;      //  Reserved register space
    volatile uint32_t RCC_AHB1LPENR;    //  MCAL_RCC AHB1 peripheral clock enable in low power mode register
    volatile uint32_t RCC_AHB2LPENR;    //  MCAL_RCC AHB2 peripheral clock enable in low power mode register
    const    uint32_t _reserved_8;      //  Reserved register space
    const    uint32_t _reserved_9;      //  Reserved register space
    volatile uint32_t RCC_APB1LPENR;    //  MCAL_RCC APB1 peripheral clock enable in low power mode register
    volatile uint32_t RCC_APB2LPENR;    //  MCAL_RCC APB2 peripheral clock enabled in low power mode register
    const    uint32_t _reserved_10;     //  Reserved register space
    const    uint32_t _reserved_11;     //  Reserved register space
    volatile uint32_t RCC_BDCR;         //  MCAL_RCC Backup domain control register
    volatile uint32_t RCC_CSR;          //  MCAL_RCC clock control & status register
    const    uint32_t _reserved_12;     //  Reserved register space
    const    uint32_t _reserved_13;     //  Reserved register space
    volatile uint32_t RCC_SSCGR;        //  MCAL_RCC spread spectrum clock generation register
    volatile uint32_t RCC_PLLI2SCFGR;   //  MCAL_RCC PLLI2S configuration register
    const    uint32_t _reserved_14;     //  Reserved register space
    volatile uint32_t RCC_DCKCFGR;      //  MCAL_RCC Dedicated Clocks Configuration Register
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
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} MCAL_GPIO_RegDef_t;


#define _MMIO_ADDR_GPIOA    0x40020000U  
#define MCAL_GPIOA          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOA)

#define _MMIO_ADDR_GPIOB    0x40020400U
#define MCAL_GPIOB          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOB)

#define _MMIO_ADDR_GPIOC    0x40020800U
#define MCAL_GPIOC          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOC)

#define _MMIO_ADDR_GPIOD    0x40020C00U
#define MCAL_GPIOD          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOD)

#define _MMIO_ADDR_GPIOE    0x40021000U
#define MCAL_GPIOE          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOE)

#define _MMIO_ADDR_GPIOH    0x40021C00U
#define MCAL_GPIOH          ((MCAL_GPIO_RegDef_t* ) _MMIO_ADDR_GPIOH)


#define _MMIO_ADDR_EXTI     0x40013C00U

#define _MMIO_ADDR_ADC1     0x40012000U
#define _MMIO_ADDR_ADC2     0x40012800U
#define _MMIO_ADDR_ADC3     0x40013C00U

#define _MMIO_ADDR_DMA1     0x40026000U
#define _MMIO_ADDR_DMA2     0x40026400U

#define _MMIO_ADDR_TIM1     0x40010000U
#define _MMIO_ADDR_TIM8     0x40013400U

#define _MMIO_ADDR_TIM2     0x40000000U 
#define _MMIO_ADDR_TIM3     0x40000400U
#define _MMIO_ADDR_TIM4     0x40000800U 
#define _MMIO_ADDR_TIM5     0x40000C00U 

#define _MMIO_ADDR_TIM6     0x40001000U
#define _MMIO_ADDR_TIM7     0x40001400U

#define _MMIO_ADDR_TIM9     0x40014000U
#define _MMIO_ADDR_TIM10    0x40014400U  
#define _MMIO_ADDR_TIM11    0x40014800U
#define _MMIO_ADDR_TIM12    0x40001800U
#define _MMIO_ADDR_TIM13    0x40001C00U
#define _MMIO_ADDR_TIM14    0x40002000U

#define _MMIO_ADDR_RTC      0x40002800U 

#define _MMIO_ADDR_IWDG     0x40003000U 
#define _MMIO_ADDR_WWDG     0x40002C00U

#define _MMIO_ADDR_SDIO     0x40012C00U 

#define _MMIO_ADDR_USB_FS   0x50000000U 

#define _MMIO_ADDR_SPI1     0x40013000U
#define _MMIO_ADDR_SPI2     0x40003800U 
#define _MMIO_ADDR_SPI3     0x40003C00U 
#define _MMIO_ADDR_SPI4     0x40013400U  
#define _MMIO_ADDR_SPI5     0x40015000U 

#define _MMIO_ADDR_I2S1     _MMIO_ADDR_SPI1
#define _MMIO_ADDR_I2S2     _MMIO_ADDR_SPI2
#define _MMIO_ADDR_I2S3     _MMIO_ADDR_SPI3
#define _MMIO_ADDR_I2S4     _MMIO_ADDR_SPI4 
#define _MMIO_ADDR_I2S5     _MMIO_ADDR_SPI5 

#define _MMIO_ADDR_I2S2_ext 0x40003400U  
#define _MMIO_ADDR_I2S3_ext 0x40004000U 

#define _MMIO_ADDR_I2C1     0x40005400U
#define _MMIO_ADDR_I2C2     0x40005800U 
#define _MMIO_ADDR_I2C3     0x40005C00U  

#define _MMIO_ADDR_USART1   0x40011000U
#define _MMIO_ADDR_USART2   0x40004400U
#define _MMIO_ADDR_USART3   0x40004800U
#define _MMIO_ADDR_USART4   0x40004C00U
#define _MMIO_ADDR_USART5   0x40005000U
#define _MMIO_ADDR_USART6   0x40011400U 

#define _MMIO_ADDR_USB_OTG  0x50000000

#define _MMIO_ADDR_FLASH    0x40023C00 

#define _MMIO_ADDR_SYSCFG   0x40013800 


#endif