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

typedef union __STM32F4xx_PWR_CR_Regdef
{
    struct
    {
        volatile uint32_t LDPS          :   1;  // Byte 0, Bit   0 |     0
        volatile uint32_t PDDS          :   1;  // Byte 0, Bit   1 |     1
        volatile uint32_t CWUF          :   1;  // Byte 0, Bit   2 |     2
        volatile uint32_t CSBF          :   1;  // Byte 0, Bit   3 |     3
        volatile uint32_t PVDE          :   1;  // Byte 0, Bit   4 |     4
        volatile uint32_t PLS           :   3;  // Byte 0, Bit 5-7 |  5- 7 

        volatile uint32_t DBP           :   1;  // Byte 1, Bit   0 |     8
        volatile uint32_t FPDS          :   1;  // Byte 1, Bit   1 |     9
        volatile uint32_t LPLVDS        :   1;  // Byte 1, Bit   2 |    10
        volatile uint32_t MRLVDS        :   1;  // Byte 1, Bit   3 |    11
        const uint32_t __reserved_1     :   1;  // Byte 1, Bit   4 |    12
        volatile uint32_t ADCDC1        :   1;  // Byte 1, Bit   5 |    13
        volatile uint32_t VOS           :   2;  // Byte 1, Bit 6-7 | 14-15

        const uint32_t __reserved_2     :   4;  // Byte 2, Bit 0-3 | 16-19
        volatile uint32_t FMSSR         :   1;  // Byte 2, Bit 0-3 |    20
        volatile uint32_t FISSR         :   1;  // Byte 2, Bit 0-3 |    21
        const uint32_t __reserved_3     :   2;  // Byte 2, Bit 0-3 | 22-23
        const uint32_t __reserved_4     :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_PWR_CR_Regdef_t;

typedef union __STM32F4xx_PWR_CSR_Regdef
{
    struct
    {
        volatile uint32_t WUF           :   1;  // Byte 0, Bit   0 |     0
        volatile uint32_t SBF           :   1;  // Byte 0, Bit   1 |     1
        volatile uint32_t PVDO          :   1;  // Byte 0, Bit   2 |     2
        volatile uint32_t BRR           :   1;  // Byte 0, Bit   3 |     3
        const uint32_t __reserved_1     :   4;  // Byte 0, Bit 4-7 |  4- 7 

        volatile uint32_t EWUP          :   1;  // Byte 1, Bit   0 |     8
        volatile uint32_t BE            :   1;  // Byte 1, Bit   1 |     9
        const uint32_t __reserved_2     :   4;  // Byte 1, Bit 2-5 | 10-13
        volatile uint32_t VOSRY         :   1;  // Byte 1, Bit   6 |    14
        const uint32_t __reserved_3     :   1;  // Byte 1, Bit   7 |    15

        const uint32_t __reserved_4     :   8;  // Byte 2, Bit 0-3 | 16-23
        const uint32_t __reserved_5     :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_PWR_CSR_Regdef_t;

typedef struct
{
    volatile STM32F4xx_PWR_CR_Regdef_t PWR_CR;      //  0x00 PWR power control register 
    volatile STM32F4xx_PWR_CSR_Regdef_t PWR_CSR;    //  0x04 PWR power control/status register
} STM32F4xx_PWR_RegDef_t;

#define STM32F4xx_PWR            ((STM32F4xx_PWR_RegDef_t* ) _MMIO_ADDR_PWR)

#define _MMIO_ADDR_BKP      0x40002800UL
#define _MMIO_ADDR_RCC      0x40023800UL  

typedef union __STM32F4xx_RCC_CR_Regdef
{
    struct
    {
        volatile uint32_t HSION         :   1;  // Byte 0, Bit   0 |     0
        volatile uint32_t HSRDY         :   1;  // Byte 0, Bit   1 |     1
        const uint32_t __reserved_1     :   1;  // Byte 0, Bit   2 |     2
        volatile uint32_t HSITRIM       :   5;  // Byte 0, Bit 3-7 |  3- 7
        volatile uint32_t HSICAL        :   8;  // Byte 1, Bit 0-7 |  8-15
        volatile uint32_t HSEON         :   1;  // Byte 2, Bit   0 |    16
        volatile uint32_t HSERDY        :   1;  // Byte 2, Bit   1 |    17
        volatile uint32_t HSEBYP        :   1;  // Byte 2, Bit   2 |    18
        volatile uint32_t CSSON         :   1;  // Byte 2, Bit   3 |    19
        const uint32_t __reserved_2     :   4;  // Byte 2, Bit 4-7 | 20-23
        volatile uint32_t PLLON         :   1;  // Byte 3, Bit   0 |    24
        volatile uint32_t PLLRDY        :   1;  // Byte 3, Bit   1 |    25
        volatile uint32_t PLLI2SON      :   1;  // Byte 3, Bit   2 |    26
        volatile uint32_t PLLI2SRDY     :   1;  // Byte 3, Bit   3 |    27
        const uint32_t __reserved_3     :   4;  // Byte 3, Bit 4-7 | 28-31
    };
    uint32_t raw;
} STM32F4xx_RCC_CR_Regdef_t;

typedef union __STM32F4xx_RCC_PLLCFGR_Regdef
{
    struct
    {
        volatile uint32_t PLLM          :   6;  // Byte   0, Bit    0 |  0- 5
        volatile uint32_t PLLN          :   9;  // Byte 0-1, Bit 6-14 |  8-14
        const uint32_t __reserved_1     :   1;  // Byte   1, Bit   15 |    15

        volatile uint32_t PLLP          :   2;  // Byte   2, Bit    0 | 16-17
        const uint32_t __reserved_2     :   4;  // Byte   2, Bit  2-5 | 18-21
        volatile uint32_t PLLSRC        :   1;  // Byte   2, Bit    6 |    22
        const uint32_t __reserved_3     :   1;  // Byte   2, Bit    7 |    23

        volatile uint32_t PLLQ          :   4;  // Byte   3, Bit  0-3 | 24-27
        const uint32_t __reserved_4     :   4;  // Byte   3, Bit  4-7 | 28-31
    };
    uint32_t raw;
} STM32F4xx_RCC_PLLCFGR_Regdef_t;

typedef union __STM32F4xx_RCC_CFGR_Regdef
{
    struct
    {
        volatile uint32_t SW            :   2;  // Bit  0- 1
        volatile uint32_t SWS           :   2;  // Bit  2- 3
        volatile uint32_t HPRE          :   4;  // Bit  4- 7
        const uint32_t __reserved_1     :   2;  // Bit  8- 9
        volatile uint32_t PPRE1         :   3;  // Bit 10-12
        volatile uint32_t PPRE2         :   3;  // Bit 13-15
        volatile uint32_t RTCPRE        :   5;  // Bit 16-20
        volatile uint32_t MCO1          :   2;  // Bit 21-22
        volatile uint32_t I2SSRC        :   1;  // Bit    23
        volatile uint32_t MCO1PRE       :   3;  // Bit 24-26
        volatile uint32_t MCO2PRE       :   3;  // Bit 27-29
        volatile uint32_t MCO2          :   2;  // Bit 30-31
    };
    uint32_t raw;
} STM32F4xx_RCC_CFGR_Regdef_t;

typedef union __STM32F4xx_RCC_CIR_Regdef
{
    struct
    {
        volatile uint32_t LSIRDYF       :   1;  // Bit     0
        volatile uint32_t LSERDYF       :   1;  // Bit     1
        volatile uint32_t HSIRDYF       :   1;  // Bit     2
        volatile uint32_t HSERDYF       :   1;  // Bit     3
        volatile uint32_t PLLRDYF       :   1;  // Bit     4
        volatile uint32_t PLLI2SRDYF    :   1;  // Bit     5
        const uint32_t __reserved_1     :   1;  // Bit     6
        volatile uint32_t CSSF          :   1;  // Bit     7
        volatile uint32_t LSIRDYIE      :   1;  // Bit     8
        volatile uint32_t LSERDYIE      :   1;  // Bit     9
        volatile uint32_t HSIRDYIE      :   1;  // Bit    10
        volatile uint32_t HSERDYIE      :   1;  // Bit    11
        volatile uint32_t PLLRDYIE      :   1;  // Bit    12
        volatile uint32_t PLLI2SRDYIE   :   1;  // Bit    13
        const uint32_t __reserved_2     :   2;  // Bit 14-15
        volatile uint32_t LSIRDYC       :   1;  // Bit    16
        volatile uint32_t LSERDYC       :   1;  // Bit    17
        volatile uint32_t HSIRDYC       :   1;  // Bit    18
        volatile uint32_t HSERDYC       :   1;  // Bit    19
        volatile uint32_t PLLRDYC       :   1;  // Bit    20
        volatile uint32_t PLLI2SRDYC    :   1;  // Bit    21
        const uint32_t __reserved_3     :   1;  // Bit    22
        volatile uint32_t CSSC          :   1;  // Bit    23
        const uint32_t __reserved_4     :   8;  // Bit 24-31
    };
    uint32_t raw;
} STM32F4xx_RCC_CIR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB1RSTR_Regdef
{
    struct
    {
        volatile uint32_t GPIOARST      :   1;  // Bit     0
        volatile uint32_t GPIOBRST      :   1;  // Bit     1
        volatile uint32_t GPIOCRST      :   1;  // Bit     2
        volatile uint32_t GPIODRST      :   1;  // Bit     3
        volatile uint32_t GPIOERST      :   1;  // Bit     4
        volatile uint32_t GPIOFRST      :   1;  // Bit     5
        volatile uint32_t GPIOGRST      :   1;  // Bit     6
        volatile uint32_t GPIOHRST      :   1;  // Bit     7
        volatile uint32_t GPIOIRST      :   1;  // Bit     8
        const uint32_t __reserved_1     :   3;  // Bit  9-11
        volatile uint32_t CRCRST        :   1;  // Bit    12
        const uint32_t __reserved_2     :   3;  // Bit 13-15
        const uint32_t __reserved_3     :   5;  // Bit 16-20
        volatile uint32_t DMA1RST       :   1;  // Bit    21
        volatile uint32_t DMA2RST       :   1;  // Bit    22
        const uint32_t __reserved_4     :   1;  // Bit 23-24
        volatile uint32_t ETHMACRST     :   1;  // Bit    25
        const uint32_t __reserved_5     :   3;  // Bit 26-28
        volatile uint32_t OTGHSRST      :   1;  // Bit    29
        const uint32_t __reserved_6     :   2;  // Bit 30-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB1RSTR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB2RSTR_Regdef
{
    struct
    {
        volatile uint32_t DCMIRST       :   1;  // Bit     0
        const uint32_t __reserved_1     :   3;  // Bit  1- 3
        volatile uint32_t CRYPRST       :   1;  // Bit     4
        volatile uint32_t HASHRST       :   1;  // Bit     5
        volatile uint32_t RNGRST        :   1;  // Bit     6
        volatile uint32_t OTGFSRST      :   1;  // Bit     7
        const uint32_t __reserved_2     :  24;  // Bit  8-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB2RSTR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB3RSTR_Regdef
{
    struct
    {
        volatile uint32_t FSMCRST       :   1;  // Bit     0
        const uint32_t __reserved_1     :  31;  // Bit  1-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB3RSTR_Regdef_t;

typedef union __STM32F4xx_RCC_APB1RSTR_Regdef
{
    struct
    {
        volatile uint32_t TIM2RST       :   1;  // Bit     0
        volatile uint32_t TIM3RST       :   1;  // Bit     1
        volatile uint32_t TIM4RST       :   1;  // Bit     2
        volatile uint32_t TIM5RST       :   1;  // Bit     3
        volatile uint32_t TIM6RST       :   1;  // Bit     4
        volatile uint32_t TIM7RST       :   1;  // Bit     5
        volatile uint32_t TIM12RST      :   1;  // Bit     6
        volatile uint32_t TIM13RST      :   1;  // Bit     7
        volatile uint32_t TIM14RST      :   1;  // Bit     8
        const uint32_t __reserved_1     :   2;  // Bit  9-10
        volatile uint32_t WWDGRST       :   1;  // Bit    11
        const uint32_t __reserved_2     :   2;  // Bit 12-13
        volatile uint32_t SPI2RST       :   1;  // Bit    14
        volatile uint32_t SPI3RST       :   1;  // Bit    15
        const uint32_t __reserved_3     :   1;  // Bit    16
        volatile uint32_t UART2RST      :   1;  // Bit    17
        volatile uint32_t UART3RST      :   1;  // Bit    18
        volatile uint32_t UART4RST      :   1;  // Bit    19
        volatile uint32_t UART5RST      :   1;  // Bit    20
        volatile uint32_t I2C1RST       :   1;  // Bit    21
        volatile uint32_t I2C2RST       :   1;  // Bit    22
        volatile uint32_t I2C3RST       :   1;  // Bit    23
        const uint32_t __reserved_4     :   1;  // Bit    24
        volatile uint32_t CAN1RST       :   1;  // Bit    25
        volatile uint32_t CAN2RST       :   1;  // Bit    26
        const uint32_t __reserved_5     :   1;  // Bit    27
        volatile uint32_t PWRRST        :   1;  // Bit    28
        volatile uint32_t DACRST        :   1;  // Bit    29
        const uint32_t __reserved_6     :   2;  // Bit 30-31
    };
    uint32_t raw;
} STM32F4xx_RCC_APB1RSTR_Regdef_t;

typedef union __STM32F4xx_RCC_APB2RSTR_Regdef
{
    struct
    {
        volatile uint32_t TIM1RST       :   1;  // Bit     0
        volatile uint32_t TIM8RST       :   1;  // Bit     1
        const uint32_t __reserved_1     :   2;  // Bit  2- 3
        volatile uint32_t USART1RST     :   1;  // Bit     4
        volatile uint32_t USART6RST     :   1;  // Bit     5
        const uint32_t __reserved_2     :   2;  // Bit  6- 7
        volatile uint32_t ADCRST        :   1;  // Bit     8
        const uint32_t __reserved_3     :   2;  // Bit  9-10
        volatile uint32_t SDIORST       :   1;  // Bit    11
        volatile uint32_t SPI1RST       :   1;  // Bit    12
        const uint32_t __reserved_4     :   1;  // Bit    13
        volatile uint32_t SYSCFGRST     :   1;  // Bit    14
        const uint32_t __reserved_5     :   1;  // Bit    15
        volatile uint32_t TIM9RST       :   1;  // Bit    16
        volatile uint32_t TIM10RST      :   1;  // Bit    17
        volatile uint32_t TIM11RST      :   1;  // Bit    18
        const uint32_t __reserved_6     :  13;  // Bit 19-31
    };
    uint32_t raw;
} STM32F4xx_RCC_APB2RSTR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB1ENR_Regdef
{
    struct
    {
        volatile uint32_t GPIOAEN       :   1;  // Bit     0
        volatile uint32_t GPIOBEN       :   1;  // Bit     1
        volatile uint32_t GPIOCEN       :   1;  // Bit     2
        volatile uint32_t GPIODEN       :   1;  // Bit     3
        volatile uint32_t GPIOEEN       :   1;  // Bit     4
        volatile uint32_t GPIOFEN       :   1;  // Bit     5
        volatile uint32_t GPIOGEN       :   1;  // Bit     6
        volatile uint32_t GPIOHEN       :   1;  // Bit     7
        volatile uint32_t GPIOIEN       :   1;  // Bit     8
        const uint32_t __reserved_1     :   3;  // Bit  9-11
        volatile uint32_t CRCEN         :   1;  // Bit    12
        const uint32_t __reserved_2     :   3;  // Bit 13-15
        const uint32_t __reserved_3     :   2;  // Bit 16-17
        volatile uint32_t BKPSRAMEN     :   1;  // Bit    18
        const uint32_t __reserved_4     :   1;  // Bit    19
        volatile uint32_t CCMDATARAMEN  :   1;  // Bit    20
        volatile uint32_t DMA1EN        :   1;  // Bit    21
        volatile uint32_t DMA2EN        :   1;  // Bit    22
        const uint32_t __reserved_5     :   1;  // Bit 23-24
        volatile uint32_t ETHMACEN      :   1;  // Bit    25
        volatile uint32_t ETHMACTXEN    :   1;  // Bit    26
        volatile uint32_t ETHMACRXEN    :   1;  // Bit    27
        volatile uint32_t ETHMACPTPEN   :   1;  // Bit    28
        volatile uint32_t OTGHSEN       :   1;  // Bit    29
        volatile uint32_t OTGHSULPIEN   :   1;  // Bit    29
        const uint32_t __reserved_6     :   1;  // Bit 30-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB1ENR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB2ENR_Regdef
{
    struct
    {
        volatile uint32_t DCMIEN        :   1;  // Bit     0
        const uint32_t __reserved_1     :   3;  // Bit  1- 3
        volatile uint32_t CRYPEN        :   1;  // Bit     4
        volatile uint32_t HASHEN        :   1;  // Bit     5
        volatile uint32_t RNGEN         :   1;  // Bit     6
        volatile uint32_t OTGFSEN       :   1;  // Bit     7
        const uint32_t __reserved_2     :  24;  // Bit  8-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB2ENR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB3ENR_Regdef
{
    struct
    {
        volatile uint32_t FSMCEN        :   1;  // Bit     0
        const uint32_t __reserved_1     :  31;  // Bit  1-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB3ENR_Regdef_t;

typedef union __STM32F4xx_RCC_APB1ENR_Regdef
{
    struct
    {
        volatile uint32_t TIM2EN        :   1;  // Bit     0
        volatile uint32_t TIM3EN        :   1;  // Bit     1
        volatile uint32_t TIM4EN        :   1;  // Bit     2
        volatile uint32_t TIM5EN        :   1;  // Bit     3
        volatile uint32_t TIM6EN        :   1;  // Bit     4
        volatile uint32_t TIM7EN        :   1;  // Bit     5
        volatile uint32_t TIM12EN       :   1;  // Bit     6
        volatile uint32_t TIM13EN       :   1;  // Bit     7
        volatile uint32_t TIM14EN       :   1;  // Bit     8
        const uint32_t __reserved_1     :   2;  // Bit  9-10
        volatile uint32_t WWDGEN        :   1;  // Bit    11
        const uint32_t __reserved_2     :   2;  // Bit 12-13
        volatile uint32_t SPI2EN        :   1;  // Bit    14
        volatile uint32_t SPI3EN        :   1;  // Bit    15
        const uint32_t __reserved_3     :   1;  // Bit    16
        volatile uint32_t UART2EN       :   1;  // Bit    17
        volatile uint32_t UART3EN       :   1;  // Bit    18
        volatile uint32_t UART4EN       :   1;  // Bit    19
        volatile uint32_t UART5EN       :   1;  // Bit    20
        volatile uint32_t I2C1EN        :   1;  // Bit    21
        volatile uint32_t I2C2EN        :   1;  // Bit    22
        volatile uint32_t I2C3EN        :   1;  // Bit    23
        const uint32_t __reserved_4     :   1;  // Bit    24
        volatile uint32_t CAN1EN        :   1;  // Bit    25
        volatile uint32_t CAN2EN        :   1;  // Bit    26
        const uint32_t __reserved_5     :   1;  // Bit    27
        volatile uint32_t PWREN         :   1;  // Bit    28
        volatile uint32_t DACEN         :   1;  // Bit    29
        const uint32_t __reserved_6     :   2;  // Bit 30-31
    };
    uint32_t raw;
} STM32F4xx_RCC_APB1ENR_Regdef_t;

typedef union __STM32F4xx_RCC_APB2ENR_Regdef
{
    struct
    {
        volatile uint32_t TIM1EN        :   1;  // Bit     0
        volatile uint32_t TIM8EN        :   1;  // Bit     1
        const uint32_t __reserved_1     :   2;  // Bit  2- 3
        volatile uint32_t USART1EN      :   1;  // Bit     4
        volatile uint32_t USART6EN      :   1;  // Bit     5
        const uint32_t __reserved_2     :   2;  // Bit  6- 7
        volatile uint32_t ADCEN         :   1;  // Bit     8
        const uint32_t __reserved_3     :   2;  // Bit  9-10
        volatile uint32_t SDIOEN        :   1;  // Bit    11
        volatile uint32_t SPI1EN        :   1;  // Bit    12
        const uint32_t __reserved_4     :   1;  // Bit    13
        volatile uint32_t SYSCFGEN      :   1;  // Bit    14
        const uint32_t __reserved_5     :   1;  // Bit    15
        volatile uint32_t TIM9EN        :   1;  // Bit    16
        volatile uint32_t TIM10EN       :   1;  // Bit    17
        volatile uint32_t TIM11EN       :   1;  // Bit    18
        const uint32_t __reserved_6     :  13;  // Bit 19-31
    };
    uint32_t raw;
} STM32F4xx_RCC_APB2ENR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB1LPENR_Regdef
{
    struct
    {
        volatile uint32_t GPIOALPEN     :   1;  // Bit     0
        volatile uint32_t GPIOBLPEN     :   1;  // Bit     1
        volatile uint32_t GPIOCLPEN     :   1;  // Bit     2
        volatile uint32_t GPIODLPEN     :   1;  // Bit     3
        volatile uint32_t GPIOELPEN     :   1;  // Bit     4
        volatile uint32_t GPIOFLPEN     :   1;  // Bit     5
        volatile uint32_t GPIOGLPEN     :   1;  // Bit     6
        volatile uint32_t GPIOHLPEN     :   1;  // Bit     7
        volatile uint32_t GPIOILPEN     :   1;  // Bit     8
        const uint32_t __reserved_1     :   3;  // Bit  9-11
        volatile uint32_t CRCLPEN       :   1;  // Bit    12
        const uint32_t __reserved_2     :   3;  // Bit 13-15
        const uint32_t __reserved_3     :   2;  // Bit 16-17
        volatile uint32_t BKPSRAMLPEN   :   1;  // Bit    18
        const uint32_t __reserved_4     :   1;  // Bit    19
        volatile uint32_t CCMDATARAMLPEN:   1;  // Bit    20
        volatile uint32_t DMA1LPEN      :   1;  // Bit    21
        volatile uint32_t DMA2LPEN      :   1;  // Bit    22
        const uint32_t __reserved_5     :   1;  // Bit 23-24
        volatile uint32_t ETHMACLPEN    :   1;  // Bit    25
        volatile uint32_t ETHMACTXLPEN  :   1;  // Bit    26
        volatile uint32_t ETHMACRXLPEN  :   1;  // Bit    27
        volatile uint32_t ETHMACPTPLPEN :   1;  // Bit    28
        volatile uint32_t OTGHSLPEN     :   1;  // Bit    29
        volatile uint32_t OTGHSULPILPEN :   1;  // Bit    29
        const uint32_t __reserved_6     :   1;  // Bit 30-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB1LPENR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB2LPENR_Regdef
{
    struct
    {
        volatile uint32_t DCMILPEN      :   1;  // Bit     0
        const uint32_t __reserved_1     :   3;  // Bit  1- 3
        volatile uint32_t CRYPLPEN      :   1;  // Bit     4
        volatile uint32_t HASHLPEN      :   1;  // Bit     5
        volatile uint32_t RNGLPEN       :   1;  // Bit     6
        volatile uint32_t OTGFSLPEN     :   1;  // Bit     7
        const uint32_t __reserved_2     :  24;  // Bit  8-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB2LPENR_Regdef_t;

typedef union __STM32F4xx_RCC_AHB3LPENR_Regdef
{
    struct
    {
        volatile uint32_t FSMCLPEN      :   1;  // Bit     0
        const uint32_t __reserved_1     :  31;  // Bit  1-31
    };
    uint32_t raw;
} STM32F4xx_RCC_AHB3LPENR_Regdef_t;

typedef union __STM32F4xx_RCC_APB1LPENR_Regdef
{
    struct
    {
        volatile uint32_t TIM2LPEN      :   1;  // Bit     0
        volatile uint32_t TIM3LPEN      :   1;  // Bit     1
        volatile uint32_t TIM4LPEN      :   1;  // Bit     2
        volatile uint32_t TIM5LPEN      :   1;  // Bit     3
        volatile uint32_t TIM6LPEN      :   1;  // Bit     4
        volatile uint32_t TIM7LPEN      :   1;  // Bit     5
        volatile uint32_t TIM12LPEN     :   1;  // Bit     6
        volatile uint32_t TIM13LPEN     :   1;  // Bit     7
        volatile uint32_t TIM14LPEN     :   1;  // Bit     8
        const uint32_t __reserved_1     :   2;  // Bit  9-10
        volatile uint32_t WWDGLPEN      :   1;  // Bit    11
        const uint32_t __reserved_2     :   2;  // Bit 12-13
        volatile uint32_t SPI2LPEN      :   1;  // Bit    14
        volatile uint32_t SPI3LPEN      :   1;  // Bit    15
        const uint32_t __reserved_3     :   1;  // Bit    16
        volatile uint32_t UART2LPEN     :   1;  // Bit    17
        volatile uint32_t UART3LPEN     :   1;  // Bit    18
        volatile uint32_t UART4LPEN     :   1;  // Bit    19
        volatile uint32_t UART5LPEN     :   1;  // Bit    20
        volatile uint32_t I2C1LPEN      :   1;  // Bit    21
        volatile uint32_t I2C2LPEN      :   1;  // Bit    22
        volatile uint32_t I2C3LPEN      :   1;  // Bit    23
        const uint32_t __reserved_4     :   1;  // Bit    24
        volatile uint32_t CAN1LPEN      :   1;  // Bit    25
        volatile uint32_t CAN2LPEN      :   1;  // Bit    26
        const uint32_t __reserved_5     :   1;  // Bit    27
        volatile uint32_t PWRLPEN       :   1;  // Bit    28
        volatile uint32_t DACLPEN       :   1;  // Bit    29
        const uint32_t __reserved_6     :   2;  // Bit 30-31
    };
    uint32_t raw;
} STM32F4xx_RCC_APB1LPENR_Regdef_t;

typedef union __STM32F4xx_RCC_APB2LPENR_Regdef
{
    struct
    {
        volatile uint32_t TIM1LPEN      :   1;  // Bit     0
        volatile uint32_t TIM8LPEN      :   1;  // Bit     1
        const uint32_t __reserved_1     :   2;  // Bit  2- 3
        volatile uint32_t USART1LPEN    :   1;  // Bit     4
        volatile uint32_t USART6LPEN    :   1;  // Bit     5
        const uint32_t __reserved_2     :   2;  // Bit  6- 7
        volatile uint32_t ADCLPEN       :   1;  // Bit     8
        const uint32_t __reserved_3     :   2;  // Bit  9-10
        volatile uint32_t SDIOLPEN      :   1;  // Bit    11
        volatile uint32_t SPI1LPEN      :   1;  // Bit    12
        const uint32_t __reserved_4     :   1;  // Bit    13
        volatile uint32_t SYSCFGLPEN    :   1;  // Bit    14
        const uint32_t __reserved_5     :   1;  // Bit    15
        volatile uint32_t TIM9LPEN      :   1;  // Bit    16
        volatile uint32_t TIM10LPEN     :   1;  // Bit    17
        volatile uint32_t TIM11LPEN     :   1;  // Bit    18
        const uint32_t __reserved_6     :  13;  // Bit 19-31
    };
    uint32_t raw;
} STM32F4xx_RCC_APB2LPENR_Regdef_t;

typedef union __STM32F4xx_RCC_BDCR_Regdef
{
    struct
    {
        volatile uint32_t LSEON         :   1;  // Bit     0
        volatile uint32_t LSERDY        :   1;  // Bit     1
        volatile uint32_t LSEBYP        :   1;  // Bit     2
        const uint32_t __reserved_1     :   5;  // Bit  3- 7
        volatile uint32_t RTCSEL        :   2;  // Bit  8- 9
        const uint32_t __reserved_2     :   5;  // Bit 10-14
        volatile uint32_t RTCEN         :   1;  // Bit    15
        volatile uint32_t BDRST         :   1;  // Bit    16
        const uint32_t __reserved_3     :  15;  // Bit 17-31
    };
    uint32_t raw;
} STM32F4xx_RCC_BDCR_Regdef_t;

typedef union __STM32F4xx_RCC_CSR_Regdef
{
    struct
    {
        volatile uint32_t LSION         :   1;  // Bit     0
        volatile uint32_t LSIRDY        :   1;  // Bit     1
        const uint32_t __reserved_1     :  22;  // Bit  2-23
        volatile uint32_t RMVF          :   1;  // Bit    24
        volatile uint32_t BORRSTF       :   1;  // Bit    25
        volatile uint32_t PINRSTF       :   1;  // Bit    26
        volatile uint32_t PORRSTF       :   1;  // Bit    27
        volatile uint32_t SFTRSTF       :   1;  // Bit    28
        volatile uint32_t IWDGRSTF      :   1;  // Bit    29
        volatile uint32_t WWDGRSTF      :   1;  // Bit    30
        volatile uint32_t LPWRRSTF      :   1;  // Bit    31
    };
    uint32_t raw;
} STM32F4xx_RCC_CSR_Regdef_t;

typedef union __STM32F4xx_RCC_SSCGR_Regdef
{
    struct
    {
        volatile uint32_t MODPER        :  13;  // Bit  0-12
        volatile uint32_t INCSTEP       :  15;  // Bit 13-27
        const uint32_t __reserved_1     :   2;  // Bit 28-29
        volatile uint32_t SPREADSEL     :   1;  // Bit    30
        volatile uint32_t SSCGEN        :   1;  // Bit    31
    };
    uint32_t raw;
} STM32F4xx_RCC_SSCGR_Regdef_t;

typedef union __STM32F4xx_RCC_PLLI2SCFGR_Regdef
{
    struct
    {
        const uint32_t __reserved_1     :   6;  // Bit  0- 5
        volatile uint32_t PLLI2SN       :   9;  // Bit  6-14
        const uint32_t __reserved_2     :  13;  // Bit 15-27
        volatile uint32_t PLLI2SR       :   3;  // Bit 28-30
        const uint32_t __reserved_3     :   1;  // Bit    31
    };
    uint32_t raw;
} STM32F4xx_RCC_PLLI2SCFGR_Regdef_t;

typedef union __STM32F4xx_RCC_DCKCFGR_Regdef
{
    struct
    {
        const uint32_t __reserved_1     :  24;  // Bit  0-23
        volatile uint32_t TIMPRE        :   1;  // Bit    24
        const uint32_t __reserved_2     :   7;  // Bit 25-31
    };
    uint32_t raw;
} STM32F4xx_RCC_DCKCFGR_Regdef_t;

typedef struct
{
    volatile STM32F4xx_RCC_CR_Regdef_t RCC_CR;                  //  0x00 STM32F4xx_RCC clock control register 
    volatile STM32F4xx_RCC_PLLCFGR_Regdef_t RCC_PLLCFGR;        //  0x04 STM32F4xx_RCC PLL configuration register
    volatile STM32F4xx_RCC_CFGR_Regdef_t RCC_CFGR;              //  0x08 STM32F4xx_RCC clock configuration register 
    volatile STM32F4xx_RCC_CIR_Regdef_t RCC_CIR;                //  0x0C STM32F4xx_RCC clock interrupt register
    volatile STM32F4xx_RCC_AHB1RSTR_Regdef_t RCC_AHB1RSTR;      //  0x10 STM32F4xx_RCC AHB1 peripheral reset register
    volatile STM32F4xx_RCC_AHB2RSTR_Regdef_t RCC_AHB2RSTR;      //  0x14 STM32F4xx_RCC AHB2 peripheral reset register
    volatile STM32F4xx_RCC_AHB3RSTR_Regdef_t RCC_AHB3RSTR;      //  0x18 STM32F4xx_RCC AHB3 peripheral reset register
    const    uint32_t _reserved_1;                              //  0x1C Reserved register space
    volatile STM32F4xx_RCC_APB1RSTR_Regdef_t RCC_APB1RSTR;      //  0x20 STM32F4xx_RCC APB1 peripheral reset register
    volatile STM32F4xx_RCC_APB2RSTR_Regdef_t RCC_APB2RSTR;      //  0x24 STM32F4xx_RCC APB2 peripheral reset register
    const    uint32_t _reserved_2;                              //  0x28 Reserved register space
    const    uint32_t _reserved_3;                              //  0x2C Reserved register space
    volatile STM32F4xx_RCC_AHB1ENR_Regdef_t RCC_AHB1ENR;        //  0x30 STM32F4xx_RCC AHB1 peripheral clock enable register
    volatile STM32F4xx_RCC_AHB2ENR_Regdef_t RCC_AHB2ENR;        //  0x34 STM32F4xx_RCC AHB2 peripheral clock enable register
    volatile STM32F4xx_RCC_AHB3ENR_Regdef_t RCC_AHB3ENR;        //  0x38 STM32F4xx_RCC AHB3 peripheral clock enable register
    const    uint32_t _reserved_4;                              //  0x3C Reserved register space
    volatile STM32F4xx_RCC_APB1ENR_Regdef_t RCC_APB1ENR;        //  0x40 STM32F4xx_RCC APB1 peripheral clock enable register
    volatile STM32F4xx_RCC_APB2ENR_Regdef_t RCC_APB2ENR;        //  0x44 STM32F4xx_RCC APB2 peripheral clock enable register
    const    uint32_t _reserved_5;                              //  0x48 Reserved register space
    const    uint32_t _reserved_6;                              //  0x4C Reserved register space
    volatile STM32F4xx_RCC_AHB1LPENR_Regdef_t RCC_AHB1LPENR;    //  0x50 STM32F4xx_RCC AHB1 peripheral clock enable in low power mode register
    volatile STM32F4xx_RCC_AHB2LPENR_Regdef_t RCC_AHB2LPENR;    //  0x54 STM32F4xx_RCC AHB2 peripheral clock enable in low power mode register
    volatile STM32F4xx_RCC_AHB3LPENR_Regdef_t RCC_AHB3LPENR;    //  0x58 STM32F4xx_RCC AHB3 peripheral clock enable in low power mode register
    const    uint32_t _reserved_7;                              //  0x5C Reserved register space
    volatile STM32F4xx_RCC_APB1LPENR_Regdef_t RCC_APB1LPENR;    //  0x60 STM32F4xx_RCC APB1 peripheral clock enable in low power mode register
    volatile STM32F4xx_RCC_APB2LPENR_Regdef_t RCC_APB2LPENR;    //  0x64 STM32F4xx_RCC APB2 peripheral clock enabled in low power mode register
    const    uint32_t _reserved_8;                              //  0x68 Reserved register space
    const    uint32_t _reserved_9;                              //  0x6C Reserved register space
    volatile STM32F4xx_RCC_BDCR_Regdef_t RCC_BDCR;              //  0x70 STM32F4xx_RCC Backup domain control register
    volatile STM32F4xx_RCC_CSR_Regdef_t RCC_CSR;                //  0x74 STM32F4xx_RCC clock control & status register
    const    uint32_t _reserved_10;                             //  0x78 Reserved register space
    const    uint32_t _reserved_11;                             //  0x7C Reserved register space
    volatile STM32F4xx_RCC_SSCGR_Regdef_t RCC_SSCGR;            //  0x80 STM32F4xx_RCC spread spectrum clock generation register
    volatile STM32F4xx_RCC_PLLI2SCFGR_Regdef_t RCC_PLLI2SCFGR;  //  0x84 STM32F4xx_RCC PLLI2S configuration register
    const    uint32_t _reserved_12;                             //  0x88 Reserved register space
    volatile STM32F4xx_RCC_DCKCFGR_Regdef_t RCC_DCKCFGR;        //  0x8C STM32F4xx_RCC Dedicated Clocks Configuration Register
} STM32F4xx_RCC_RegDef_t;

#define STM32F4xx_RCC                ((STM32F4xx_RCC_RegDef_t* ) _MMIO_ADDR_RCC)

#define STM32F4xx_GPIOA_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOAEN = 1)
#define STM32F4xx_GPIOA_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOAEN = 0)
#define STM32F4xx_GPIOB_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOBEN = 1)
#define STM32F4xx_GPIOB_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOBEN = 0)
#define STM32F4xx_GPIOC_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOCEN = 1)
#define STM32F4xx_GPIOC_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOCEN = 0)
#define STM32F4xx_GPIOD_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIODEN = 1)
#define STM32F4xx_GPIOD_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIODEN = 0)
#define STM32F4xx_GPIOE_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOEEN = 1)
#define STM32F4xx_GPIOE_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOEEN = 0)
#define STM32F4xx_GPIOF_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOFEN = 1)
#define STM32F4xx_GPIOF_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOFEN = 0)
#define STM32F4xx_GPIOG_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOGEN = 1)
#define STM32F4xx_GPIOG_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOGEN = 0)
#define STM32F4xx_GPIOH_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOHEN = 1)
#define STM32F4xx_GPIOH_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOHEN = 0)
#define STM32F4xx_GPIOI_PCLK_EN()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOIEN = 1)
#define STM32F4xx_GPIOI_PCLK_DI()    (STM32F4xx_RCC->RCC_AHB1ENR.GPIOIEN = 0)

#define STM32F4xx_CRC_PCLK_EN()      (STM32F4xx_RCC->RCC_AHB1ENR.CRCEN = 1)
#define STM32F4xx_CRC_PCLK_DI()      (STM32F4xx_RCC->RCC_AHB1ENR.CRCEN = 0)

#define STM32F4xx_DMA1_PCLK_EN()     (STM32F4xx_RCC->RCC_AHB1ENR.DMA1EN = 1)
#define STM32F4xx_DMA1_PCLK_DI()     (STM32F4xx_RCC->RCC_AHB1ENR.DMA1EN = 0)
#define STM32F4xx_DMA2_PCLK_EN()     (STM32F4xx_RCC->RCC_AHB1ENR.DMA2EN = 1)
#define STM32F4xx_DMA2_PCLK_DI()     (STM32F4xx_RCC->RCC_AHB1ENR.DMA2EN = 0)

#define STM32F4xx_USB_FS_PCLK_EN()   (STM32F4xx_RCC->RCC_AHB2ENR.OTGFSEN = 1)
#define STM32F4xx_USB_FS_PCLK_DI()   (STM32F4xx_RCC->RCC_AHB2ENR.OTGFSEN = 0)

#define STM32F4xx_TIM1_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR.TIM1EN  = 1)
#define STM32F4xx_TIM1_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR.TIM1EN  = 0)
#define STM32F4xx_TIM2_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.TIM2EN  = 1)
#define STM32F4xx_TIM2_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.TIM2EN  = 0)
#define STM32F4xx_TIM3_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.TIM3EN  = 1)
#define STM32F4xx_TIM3_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.TIM3EN  = 0)
#define STM32F4xx_TIM4_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.TIM4EN  = 1)
#define STM32F4xx_TIM4_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.TIM4EN  = 0)
#define STM32F4xx_TIM5_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.TIM5EN  = 1)
#define STM32F4xx_TIM5_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.TIM5EN  = 0)
#define STM32F4xx_TIM6_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.TIM6EN  = 1)
#define STM32F4xx_TIM6_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.TIM6EN  = 0)
#define STM32F4xx_TIM7_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.TIM7EN  = 1)
#define STM32F4xx_TIM7_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.TIM7EN  = 0)
#define STM32F4xx_TIM8_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR.TIM8EN  = 1)
#define STM32F4xx_TIM8_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR.TIM8EN  = 0)
#define STM32F4xx_TIM9_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR.TIM9EN  = 1)
#define STM32F4xx_TIM9_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR.TIM9EN  = 0)
#define STM32F4xx_TIM10_PCLK_EN()    (STM32F4xx_RCC->RCC_APB2ENR.TIM10EN = 1)
#define STM32F4xx_TIM10_PCLK_DI()    (STM32F4xx_RCC->RCC_APB2ENR.TIM10EN = 0)
#define STM32F4xx_TIM11_PCLK_EN()    (STM32F4xx_RCC->RCC_APB2ENR.TIM11EN = 1)
#define STM32F4xx_TIM11_PCLK_DI()    (STM32F4xx_RCC->RCC_APB2ENR.TIM11EN = 0)
#define STM32F4xx_TIM12_PCLK_EN()    (STM32F4xx_RCC->RCC_APB1ENR.TIM12EN = 1)
#define STM32F4xx_TIM12_PCLK_DI()    (STM32F4xx_RCC->RCC_APB1ENR.TIM12EN = 0)
#define STM32F4xx_TIM13_PCLK_EN()    (STM32F4xx_RCC->RCC_APB1ENR.TIM13EN = 1)
#define STM32F4xx_TIM13_PCLK_DI()    (STM32F4xx_RCC->RCC_APB1ENR.TIM13EN = 0)
#define STM32F4xx_TIM14_PCLK_EN()    (STM32F4xx_RCC->RCC_APB1ENR.TIM14EN = 1)
#define STM32F4xx_TIM14_PCLK_DI()    (STM32F4xx_RCC->RCC_APB1ENR.TIM14EN = 0)

#define STM32F4xx_WWDG_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.WWDGEN = 1)
#define STM32F4xx_WWDG_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.WWDGEN = 0)

#define STM32F4xx_PWR_PCLK_EN()      (STM32F4xx_RCC->RCC_APB1ENR.PWREN = 1)
#define STM32F4xx_PWR_PCLK_DI()      (STM32F4xx_RCC->RCC_APB1ENR.PWREN = 0)

#define STM32F4xx_I2C1_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.I2C1EN = 1)
#define STM32F4xx_I2C1_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.I2C1EN = 0)
#define STM32F4xx_I2C2_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.I2C2EN = 1)
#define STM32F4xx_I2C2_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.I2C2EN = 0)
#define STM32F4xx_I2C3_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.I2C3EN = 1)
#define STM32F4xx_I2C3_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.I2C3EN = 0)

#define STM32F4xx_SPI1_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR.SPI1EN = 1)
#define STM32F4xx_SPI1_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR.SPI1EN = 0)
#define STM32F4xx_SPI2_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.SPI2EN = 1)
#define STM32F4xx_SPI2_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.SPI2EN = 0)
#define STM32F4xx_SPI3_PCLK_EN()     (STM32F4xx_RCC->RCC_APB1ENR.SPI4EN = 1)
#define STM32F4xx_SPI3_PCLK_DI()     (STM32F4xx_RCC->RCC_APB1ENR.SPI4EN = 0)
#define STM32F4xx_SPI4_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR.SPI4EN = 1)
#define STM32F4xx_SPI4_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR.SPI4EN = 0)
#define STM32F4xx_SPI5_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR.SPI5EN = 1)
#define STM32F4xx_SPI5_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR.SPI5EN = 0)

#define STM32F4xx_USART1_PCLK_EN()   (STM32F4xx_RCC->RCC_APB2ENR.UART1EN = 1)
#define STM32F4xx_USART1_PCLK_DI()   (STM32F4xx_RCC->RCC_APB2ENR.UART1EN = 0)
#define STM32F4xx_USART2_PCLK_EN()   (STM32F4xx_RCC->RCC_APB1ENR.UART2EN = 1)
#define STM32F4xx_USART2_PCLK_DI()   (STM32F4xx_RCC->RCC_APB1ENR.UART2EN = 0)
#define STM32F4xx_USART3_PCLK_EN()   (STM32F4xx_RCC->RCC_APB1ENR.UART3EN = 1)
#define STM32F4xx_USART3_PCLK_DI()   (STM32F4xx_RCC->RCC_APB1ENR.UART3EN = 0)
#define STM32F4xx_USART4_PCLK_EN()   (STM32F4xx_RCC->RCC_APB1ENR.UART4EN = 1)
#define STM32F4xx_USART4_PCLK_DI()   (STM32F4xx_RCC->RCC_APB1ENR.UART4EN = 0)
#define STM32F4xx_USART5_PCLK_EN()   (STM32F4xx_RCC->RCC_APB1ENR.UART5EN = 1)
#define STM32F4xx_USART5_PCLK_DI()   (STM32F4xx_RCC->RCC_APB1ENR.UART5EN = 0)
#define STM32F4xx_USART6_PCLK_EN()   (STM32F4xx_RCC->RCC_APB2ENR.UART6EN = 1)
#define STM32F4xx_USART6_PCLK_DI()   (STM32F4xx_RCC->RCC_APB2ENR.UART6EN = 0)

#define STM32F4xx_ADC1_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR.ADCEN = 1)
#define STM32F4xx_ADC1_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR.ADCEN = 0)

#define STM32F4xx_SDIO_PCLK_EN()     (STM32F4xx_RCC->RCC_APB2ENR.SDIOEN = 1)
#define STM32F4xx_SDIO_PCLK_DI()     (STM32F4xx_RCC->RCC_APB2ENR.SDIOEN = 0)

#define STM32F4xx_SYSCFG_PCLK_EN()   (STM32F4xx_RCC->RCC_APB2ENR.SYSCFGEN = 1)
#define STM32F4xx_SYSCFG_PCLK_DI()   (STM32F4xx_RCC->RCC_APB2ENR.SYSCFGEN = 0)

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


typedef union __STM32F4xx_TIM_CR1_Regdef
{
    struct
    {
        volatile uint32_t CEN           :   1;  // Bit     0 | Counter enable
        volatile uint32_t UDIS          :   1;  // Bit     1 | Update disable
        volatile uint32_t URS           :   1;  // Bit     2 | Update request source
        volatile uint32_t OPM           :   1;  // Bit     3 | One pulse mode
        volatile uint32_t DIR           :   1;  // Bit     4 | Direction
        volatile uint32_t CMS           :   2;  // Bit  5- 6 | Center-aligned mode selection
        volatile uint32_t ARPE          :   1;  // Bit     7 | Auto-reload preload enable
        volatile uint32_t CKD           :   2;  // Bit  8- 9 | Clock division
        const uint32_t _reserved_1      :  22;  // Bit 10-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_CR1_Regdef_t;

typedef union __STM32F4xx_TIM_CR2_Regdef
{
    struct
    {
        volatile uint32_t CCPC          :   1;  // Bit     0 | Capture/compare preloaded control
        const uint32_t _reserved_1      :   1;  // Bit     1 | Reserved, must be kept at reset value.
        volatile uint32_t CCUS          :   1;  // Bit     2 | Capture/compare control update selection
        volatile uint32_t CCDS          :   1;  // Bit     3 | Capture/compare DMA selection
        volatile uint32_t MMS           :   3;  // Bit  4- 6 | Master mode selection
        volatile uint32_t TI1S          :   1;  // Bit     7 | TI1 selection
        volatile uint32_t OIS1          :   1;  // Bit     8 | Output Idle state 1 (OC1 output)
        volatile uint32_t OIS1N         :   1;  // Bit     9 | Output Idle state 1 (OC1N output)
        volatile uint32_t OIS2          :   1;  // Bit    10 | Output Idle state 2 (OC2 output)
        volatile uint32_t OIS2N         :   1;  // Bit    11 | Output Idle state 2 (OC2N output)
        volatile uint32_t OIS3          :   1;  // Bit    12 | Output Idle state 3 (OC3 output)
        volatile uint32_t OIS3N         :   1;  // Bit    13 | Output Idle state 3 (OC3N output)
        volatile uint32_t OIS4          :   1;  // Bit    14 | Output Idle state 4 (OC4 output)
        const uint32_t _reserved_2      :  17;  // Bit 15-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_CR2_Regdef_t;

typedef union __STM32F4xx_TIM_SMCR_Regdef
{
    struct
    {
        volatile uint32_t SMS           :   3;  // Bit  0- 2 | Slave mode selection
        const uint32_t _reserved_1      :   1;  // Bit     3 | Reserved, must be kept at reset value.
        volatile uint32_t TS            :   3;  // Bit  4- 6 | Trigger selection
        volatile uint32_t MSM           :   1;  // Bit     7 | Master/slave mode
        volatile uint32_t ETF           :   4;  // Bit  8-11 | External trigger filter
        volatile uint32_t ETPS          :   2;  // Bit 12-13 | External trigger prescaler
        volatile uint32_t ECE           :   1;  // Bit    13 | External clock enable
        volatile uint32_t ETP           :   1;  // Bit    14 | External trigger polarity
        const uint32_t _reserved_2      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_SMCR_Regdef_t;

typedef union __STM32F4xx_TIM_DIER_Regdef
{
    struct
    {
        volatile uint32_t UIE           :   1;  // Bit     0 | Update interrupt enable
        volatile uint32_t CC1IE         :   1;  // Bit     1 | Capture/Compare 1 interrupt enable
        volatile uint32_t CC2IE         :   1;  // Bit     2 | Capture/Compare 2 interrupt enable
        volatile uint32_t CC3IE         :   1;  // Bit     3 | Capture/Compare 3 interrupt enable
        volatile uint32_t CC4IE         :   1;  // Bit     4 | Capture/Compare 4 interrupt enable
        volatile uint32_t COMIE         :   1;  // Bit     5 | COM interrupt enable
        volatile uint32_t TIE           :   1;  // Bit     6 | Trigger interrupt enable
        volatile uint32_t BIE           :   1;  // Bit     7 | Break interrupt enable
        volatile uint32_t UDE           :   1;  // Bit     8 | Update DMA request enable
        volatile uint32_t CC1DE         :   1;  // Bit     9 | Capture/Compare 1 DMA request enable
        volatile uint32_t CC2DE         :   1;  // Bit    10 | Capture/Compare 2 DMA request enable
        volatile uint32_t CC3DE         :   1;  // Bit    11 | Capture/Compare 3 DMA request enable
        volatile uint32_t CC4DE         :   1;  // Bit    12 | Capture/Compare 4 DMA request enable
        volatile uint32_t COMDE         :   1;  // Bit    13 | COM DMA request enable
        volatile uint32_t TDE           :   1;  // Bit    14 | Trigger DMA request enable
        const uint32_t _reserved_1      :  17;  // Bit 15-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_DIER_Regdef_t;

typedef union __STM32F4xx_TIM_SR_Regdef
{
    struct
    {
        volatile uint32_t UIF           :   1;  // Bit     0 | Update interrupt flag
        volatile uint32_t CC1IF         :   1;  // Bit     1 | Capture/Compare 1 interrupt flag
        volatile uint32_t CC2IF         :   1;  // Bit     2 | Capture/Compare 2 interrupt flag
        volatile uint32_t CC3IF         :   1;  // Bit     3 | Capture/Compare 3 interrupt flag
        volatile uint32_t CC4IF         :   1;  // Bit     4 | Capture/Compare 4 interrupt flag
        volatile uint32_t COMIF         :   1;  // Bit     5 | COM interrupt flag
        volatile uint32_t TIF           :   1;  // Bit     6 | Trigger interrupt flag
        volatile uint32_t BIF           :   1;  // Bit     7 | Break interrupt flag
        const uint32_t __reserFed_1     :   1;  // Bit     8 | Reserved, must be kept at reset value.
        volatile uint32_t CC1DF         :   1;  // Bit     9 | Capture/Compare 1 overcapture flag
        volatile uint32_t CC2DF         :   1;  // Bit    10 | Capture/Compare 2 overcapture flag
        volatile uint32_t CC3DF         :   1;  // Bit    11 | Capture/Compare 3 overcapture flag
        volatile uint32_t CC4DF         :   1;  // Bit    12 | Capture/Compare 4 overcapture flag
        const uint32_t _reserved_2      :  19;  // Bit 13-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_SR_Regdef_t;


typedef union __STM32F4xx_TIM_EGR_Regdef
{
    struct
    {
        volatile uint32_t UG            :   1;  // Bit     0 | Update generation
        volatile uint32_t CC1IG         :   1;  // Bit     1 | Capture/Compare 1 generation
        volatile uint32_t CC2IG         :   1;  // Bit     2 | Capture/Compare 2 generation
        volatile uint32_t CC3IG         :   1;  // Bit     3 | Capture/Compare 3 generation
        volatile uint32_t CC4IG         :   1;  // Bit     4 | Capture/Compare 4 generation
        volatile uint32_t COMIG         :   1;  // Bit     5 | Capture/Compare control update generation
        volatile uint32_t TG            :   1;  // Bit     6 | Trigger generation
        volatile uint32_t BG            :   1;  // Bit     7 | Break generation
        const uint32_t _reserved_2      :  24;  // Bit  8-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_EGR_Regdef_t;

typedef union __STM32F4xx_TIM_CCMR1_Regdef
{
    struct
    {
        volatile uint32_t CC1S          :   2;  // Bit  0- 1 | Capture/Compare 1 selection
        volatile uint32_t OC1FE         :   1;  // Bit     2 | Output Compare 1 fast enable
        volatile uint32_t OC1PE         :   1;  // Bit     3 | Output Compare 1 preload enable
        volatile uint32_t OC1M          :   3;  // Bit  4- 6 | Output Compare 1 mode
        volatile uint32_t OC1CE         :   1;  // Bit     7 | Output Compare 1 clear enable
        volatile uint32_t CC2S          :   2;  // Bit  8- 9 | Capture/Compare 2 selection
        volatile uint32_t OC2FE         :   1;  // Bit    10 | Output Compare 2 fast enable
        volatile uint32_t OC2PE         :   1;  // Bit    11 | Output Compare 2 preload enable
        volatile uint32_t OC2M          :   3;  // Bit 12-14 | Output Compare 2 mode
        volatile uint32_t OC2PE         :   1;  // Bit    15 | Output Compare 2 clear enable
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    } oc;                                       // Output compare mode

    struct
    {
        volatile uint32_t CC1S          :   2;  // Bit  0- 1 | Capture/Compare 1 selection
        volatile uint32_t IC1PSC        :   2;  // Bit  2- 3 | Input capture 1 prescaler
        volatile uint32_t IC1F          :   4;  // Bit  4- 7 | Input capture 1 filter
        volatile uint32_t CC2S          :   2;  // Bit  8- 9 | Capture/Compare 2 selection
        volatile uint32_t IC2PSC        :   2;  // Bit 10-11 | Input capture 2 prescaler
        volatile uint32_t IC2F          :   4;  // Bit 12-15 | Input capture 2 filter
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    } ic;                                       // Input Compare Mode
    
    volatile uint32_t raw;
} STM32F4xx_TIM_CCMR1_Regdef_t;

typedef union __STM32F4xx_TIM_CCMR2_Regdef
{
    struct
    {
        volatile uint32_t CC3S          :   2;  // Bit  0- 1 | Capture/Compare 3 selection
        volatile uint32_t OC3FE         :   1;  // Bit     2 | Output Compare 3 fast enable
        volatile uint32_t OC3PE         :   1;  // Bit     3 | Output Compare 3 preload enable
        volatile uint32_t OC3M          :   3;  // Bit  4- 6 | Output Compare 3 mode
        volatile uint32_t OC3CE         :   1;  // Bit     7 | Output Compare 3 clear enable
        volatile uint32_t CC4S          :   2;  // Bit  8- 9 | Capture/Compare 4 selection
        volatile uint32_t OC4FE         :   1;  // Bit    10 | Output Compare 4 fast enable
        volatile uint32_t OC4PE         :   1;  // Bit    11 | Output Compare 4 preload enable
        volatile uint32_t OC4M          :   3;  // Bit 12-14 | Output Compare 4 mode
        volatile uint32_t OC4CE         :   1;  // Bit    15 | Output Compare 4 clear enable
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    } oc;                                       // Output compare mode

    struct
    {
        volatile uint32_t CC3S          :   2;  // Bit  0- 1 | Capture/Compare 3 selection
        volatile uint32_t IC3PSC        :   2;  // Bit  2- 3 | Input capture 3 prescaler
        volatile uint32_t IC3F          :   4;  // Bit  4- 7 | Input capture 3 filter
        volatile uint32_t CC4S          :   2;  // Bit  8- 9 | Capture/Compare 4 selection
        volatile uint32_t IC4PSC        :   2;  // Bit 10-11 | Input capture 4 prescaler
        volatile uint32_t IC4F          :   4;  // Bit 12-15 | Input capture 4 filter
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    } ic;                                       // Input Compare Mode
    
    volatile uint32_t raw;
} STM32F4xx_TIM_CCMR2_Regdef_t;

typedef union __STM32F4xx_TIM_CCER_Regdef
{
    struct
    {
        volatile uint32_t CC1E          :   1;  // Bit     0 | Capture/Compare 1 output enable                
        volatile uint32_t CC1P          :   1;  // Bit     1 | Capture/Compare 1 output polarity              
        volatile uint32_t CC1NE         :   1;  // Bit     2 | Capture/Compare 1 complementary output enable  
        volatile uint32_t CC1NP         :   1;  // Bit     3 | Capture/Compare 1 complementary output polarity
        volatile uint32_t CC2E          :   1;  // Bit     4 | Capture/Compare 2 output enable                
        volatile uint32_t CC2P          :   1;  // Bit     5 | Capture/Compare 2 output polarity              
        volatile uint32_t CC2NE         :   1;  // Bit     6 | Capture/Compare 2 complementary output enable  
        volatile uint32_t CC2NP         :   1;  // Bit     7 | Capture/Compare 2 complementary output polarity
        volatile uint32_t CC3E          :   1;  // Bit     8 | Capture/Compare 3 output enable                          
        volatile uint32_t CC3P          :   1;  // Bit     9 | Capture/Compare 3 output polarity               
        volatile uint32_t CC3NE         :   1;  // Bit    10 | Capture/Compare 3 complementary output enable  
        volatile uint32_t CC3NP         :   1;  // Bit    11 | Capture/Compare 3 complementary output polarity
        volatile uint32_t CC4E          :   1;  // Bit    12 | Capture/Compare 4 output enable
        volatile uint32_t CC4P          :   1;  // Bit    13 | Capture/Compare 4 output polarity
        const uint32_t _reserved_1      :  18;  // Bit 14-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_CCER_Regdef_t;

typedef struct __STM32F4xx_TIM_CNT_Regdef
{
    struct
    {
        volatile uint32_t CNT;                  // Bit  0-31 | Auto-reload value
    } timer_32bit;
    struct
    {
        volatile uint32_t CNT           :  16;  // Bit  0-15 | Auto-reload value
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    } timer_16bit;
    volatile uint32_t raw;
} STM32F4xx_TIM_CNT_Regdef_t;

typedef struct __STM32F4xx_TIM_PSC_Regdef
{
    struct
    {
        volatile uint32_t PSC;                  // Bit  0-31 | Auto-reload value
    } timer_32bit;
    struct
    {
        volatile uint32_t PSC           :  16;  // Bit  0-15 | Auto-reload value
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    } timer_16bit;
    volatile uint32_t raw;
} STM32F4xx_TIM_PSC_Regdef_t;

typedef struct __STM32F4xx_TIM_ARR_Regdef
{
    struct
    {
        volatile uint32_t ARR;                  // Bit  0-31 | Auto-reload value
    } timer_32bit;
    struct
    {
        volatile uint32_t ARR           :  16;  // Bit  0-15 | Auto-reload value
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    } timer_16bit;
    volatile uint32_t raw;
} STM32F4xx_TIM_ARR_Regdef_t;

typedef struct __STM32F4xx_TIM_RCR_Regdef
{
    struct
    {
        volatile uint32_t REP           :  8;  // Bit  0-15 | Auto-reload value
        const uint32_t _reserved_1      : 24;  // Bit 16-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_RCR_Regdef_t;

typedef struct __STM32F4xx_TIM_CCR_Regdef
{
    struct
    {
        volatile uint32_t CCR;                  // Bit  0-31 | Auto-reload value
    } timer_32bit;
    struct
    {
        volatile uint32_t CCR           :  16;  // Bit  0-15 | Auto-reload value
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    } timer_16bit;
    volatile uint32_t raw;
} STM32F4xx_TIM_CCR_Regdef_t;

typedef union __STM32F4xx_TIM_BDTR_Regdef
{
    struct
    {
        volatile uint32_t DTG           :   8;  // Bit  0- 7 | Dead-time generator setup       
        volatile uint32_t LOCK          :   2;  // Bit  8- 9 | Lock configuration               
        volatile uint32_t OSSI          :   1;  // Bit    10 | Off-state selection for Idle mode
        volatile uint32_t OSSR          :   1;  // Bit    11 | Off-state selection for Run mode
        volatile uint32_t BKE           :   1;  // Bit    12 | Break enable
        volatile uint32_t BKP           :   1;  // Bit    13 | Break polarity
        volatile uint32_t AOE           :   1;  // Bit    14 | Automatic output enable
        volatile uint32_t MOE           :   1;  // Bit    15 | Main output enable
        const uint32_t _reserved_1      :  16;  // Bit 16-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_BDTR_Regdef_t;

typedef union __STM32F4xx_TIM_DCR_Regdef
{
    struct
    {
        volatile uint32_t DBA           :   5;  // Bit  0- 4 | DMA base address      
        const uint32_t _reserved_1      :   3;  // Bit  5- 7 | Reserved, must be kept at reset value.        
        volatile uint32_t DBL           :   5;  // Bit  8-10 | DMA burst length
        const uint32_t _reserved_2      :  19;  // Bit 11-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_DCR_Regdef_t;

typedef union __STM32F4xx_TIM_DMAR_Regdef
{
    volatile uint32_t DMAB;                     // Bit  0-31 | DMA register for burst accesses
    volatile uint32_t raw;
} STM32F4xx_TIM_DMAR_Regdef_t;

typedef struct
{
    volatile STM32F4xx_TIM_CR1_Regdef_t TIM_CR1;        // Offset 0x00 | TIM1 and TIM8 control register 1
    volatile STM32F4xx_TIM_CR2_Regdef_t TIM_CR2;        // Offset 0x04 | TIM1 and TIM8 control register 2
    volatile STM32F4xx_TIM_SMCR_Regdef_t TIM_SMCR;      // Offset 0x08 | TIM1 and TIM8 slave mode control register
    volatile STM32F4xx_TIM_DIER_Regdef_t TIM_DIER;      // Offset 0x0C | TIM1 and TIM8 DMA/interrupt enable register
    volatile STM32F4xx_TIM_SR_Regdef_t TIM_SR;          // Offset 0x10 | TIM1 and TIM8 status register 
    volatile STM32F4xx_TIM_EGR_Regdef_t TIM_EGR;        // Offset 0x14 | TIM1 and TIM8 event generation register
    volatile STM32F4xx_TIM_CCMR1_Regdef_t TIM_CCMR1;    // Offset 0x18 | TIM1 and TIM8 capture/compare mode register 1
    volatile STM32F4xx_TIM_CCMR2_Regdef_t TIM_CCMR2;    // Offset 0x1C | TIM1 and TIM8 capture/compare mode register 2
    volatile STM32F4xx_TIM_CCER_Regdef_t TIM_CCER;      // Offset 0x20 | TIM1 and TIM8 capture/compare enable register
    volatile STM32F4xx_TIM_CNT_Regdef_t TIM_CNT;        // Offset 0x24 | TIM1 and TIM8 counter 
    volatile STM32F4xx_TIM_PSC_Regdef_t TIM_PSC;        // Offset 0x28 | TIM1 and TIM8 prescaler
    volatile STM32F4xx_TIM_ARR_Regdef_t TIM_ARR;        // Offset 0x2C | TIM1 and TIM8 auto-reload register
    volatile STM32F4xx_TIM_RCR_Regdef_t TIM_RCR;        // Offset 0x30 | TIM1 and TIM8 repetition counter register
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR1;       // Offset 0x34 | TIM1 and TIM8 capture/compare register 1
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR2;       // Offset 0x38 | TIM1 and TIM8 capture/compare register 2
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR3;       // Offset 0x3C | TIM1 and TIM8 capture/compare register 3
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR4;       // Offset 0x40 | TIM1 and TIM8 capture/compare register 4
    volatile STM32F4xx_TIM_BDTR_Regdef_t TIM_BDTR;      // Offset 0x44 | TIM1 and TIM8 break and dead-time register 
    volatile STM32F4xx_TIM_DCR_Regdef_t TIM_DCR;        // Offset 0x48 | TIM1 and TIM8 DMA control register
    volatile STM32F4xx_TIM_DMAR_Regdef_t TIM_DMARM;     // Offset 0x4C | TIM1 and TIM8 DMA address for full transfer 
} STM32F4xx_TIM_1_8_RegDef_t;

#define _MMIO_ADDR_TIM1     0x40010000UL
#define STM32F4XX_TIM1_REG   ((STM32F4xx_TIM_1_8_RegDef_t* ) _MMIO_ADDR_TIM1)
#define _MMIO_ADDR_TIM8     0x40013400UL
#define STM32F4XX_TIM8_REG   ((STM32F4xx_TIM_1_8_RegDef_t* ) _MMIO_ADDR_TIM8)

typedef union __STM32F4xx_TIM_OR_Regdef
{
    struct
    {
        volatile uint32_t TI1_RMP       :   2;  // Bit  0- 1 | TIM11 Input 1 remapping capability     
        const uint32_t _reserved_1      :   4;  // Bit  2- 5 | Reserved, must be kept at reset value.
        volatile uint32_t TI4_RMP       :   2;  // Bit  6- 7 | Timer Input 4 remap               
        const uint32_t _reserved_2      :   2;  // Bit  8- 9 | Reserved, must be kept at reset value.
        volatile uint32_t ITR1_RMP      :   2;  // Bit 10-11 | Internal trigger 1 remap
        const uint32_t _reserved_3      :  20;  // Bit 12-31 | Reserved, must be kept at reset value.
    };
    volatile uint32_t raw;
} STM32F4xx_TIM_OR_Regdef_t;

typedef struct
{
    volatile STM32F4xx_TIM_CR1_Regdef_t TIM_CR1;        // Offset 0x00 | TIMx control register 1 
    volatile STM32F4xx_TIM_CR2_Regdef_t TIM_CR2;        // Offset 0x04 | TIMx control register 2
    volatile STM32F4xx_TIM_SMCR_Regdef_t TIM_SMCR;      // Offset 0x08 | TIMx slave mode control register
    volatile STM32F4xx_TIM_DIER_Regdef_t TIM_DIER;      // Offset 0x0C | TIMx DMA/Interrupt enable register
    volatile STM32F4xx_TIM_SR_Regdef_t TIM_SR;          // Offset 0x10 | TIMx status register
    volatile STM32F4xx_TIM_EGR_Regdef_t TIM_EGR;        // Offset 0x14 | TIMx event generation register
    volatile STM32F4xx_TIM_CCMR1_Regdef_t TIM_CCMR1;    // Offset 0x18 | TIMx capture/compare mode register 1
    volatile STM32F4xx_TIM_CCMR2_Regdef_t TIM_CCMR2;    // Offset 0x1C | TIMx capture/compare mode register 2
    volatile STM32F4xx_TIM_CCER_Regdef_t TIM_CCER;      // Offset 0x20 | TIMx capture/compare enable register
    volatile STM32F4xx_TIM_CNT_Regdef_t TIM_CNT;        // Offset 0x24 | TIMx counter 
    volatile STM32F4xx_TIM_PSC_Regdef_t TIM_PSC;        // Offset 0x28 | TIMx prescaler 
    volatile STM32F4xx_TIM_ARR_Regdef_t TIM_ARR;        // Offset 0x2C | TIMx auto-reload register
    const uint32_t __reserved_1;                        // Offset 0x30 | Reserved
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR1;       // Offset 0x34 | TIMx capture/compare register 1
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR2;       // Offset 0x38 | TIMx capture/compare register 2
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR3;       // Offset 0x3C | TIMx capture/compare register 3
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR4;       // Offset 0x40 | TIMx capture/compare register 4
    const uint32_t __reserved_2;                        // Offset 0x44 | Reserved
    volatile STM32F4xx_TIM_DCR_Regdef_t TIM_DCR;        // Offset 0x48 | TIMx DMA control register 
    volatile STM32F4xx_TIM_DMAR_Regdef_t TIM_DMARM;     // Offset 0x4C | TIMx DMA address for full transfer
    volatile STM32F4xx_TIM_OR_Regdef_t TIM_OR;          // Offset 0x50 | TIM2 and TIM5 option register
} STM32F4xx_TIM_3_4_RegDef_t;

typedef struct
{
    volatile STM32F4xx_TIM_CR1_Regdef_t TIM_CR1;        // Offset 0x00 | TIMx control register 1 
    volatile STM32F4xx_TIM_CR2_Regdef_t TIM_CR2;        // Offset 0x04 | TIMx control register 2
    volatile STM32F4xx_TIM_SMCR_Regdef_t TIM_SMCR;      // Offset 0x08 | TIMx slave mode control register
    volatile STM32F4xx_TIM_DIER_Regdef_t TIM_DIER;      // Offset 0x0C | TIMx DMA/Interrupt enable register
    volatile STM32F4xx_TIM_SR_Regdef_t TIM_SR;          // Offset 0x10 | TIMx status register
    volatile STM32F4xx_TIM_EGR_Regdef_t TIM_EGR;        // Offset 0x14 | TIMx event generation register
    volatile STM32F4xx_TIM_CCMR1_Regdef_t TIM_CCMR1;    // Offset 0x18 | TIMx capture/compare mode register 1
    volatile STM32F4xx_TIM_CCMR2_Regdef_t TIM_CCMR2;    // Offset 0x1C | TIMx capture/compare mode register 2
    volatile STM32F4xx_TIM_CCER_Regdef_t TIM_CCER;      // Offset 0x20 | TIMx capture/compare enable register
    volatile STM32F4xx_TIM_CNT_Regdef_t TIM_CNT;        // Offset 0x24 | TIMx counter 
    volatile STM32F4xx_TIM_PSC_Regdef_t TIM_PSC;        // Offset 0x28 | TIMx prescaler 
    volatile STM32F4xx_TIM_ARR_Regdef_t TIM_ARR;        // Offset 0x2C | TIMx auto-reload register
    const uint32_t __reserved_1;                        // Offset 0x30 | Reserved
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR1;       // Offset 0x34 | TIMx capture/compare register 1
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR2;       // Offset 0x38 | TIMx capture/compare register 2
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR3;       // Offset 0x3C | TIMx capture/compare register 3
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR4;       // Offset 0x40 | TIMx capture/compare register 4
    const uint32_t __reserved_2;                        // Offset 0x44 | Reserved
    volatile STM32F4xx_TIM_DCR_Regdef_t TIM_DCR;        // Offset 0x48 | TIMx DMA control register 
    volatile STM32F4xx_TIM_DMAR_Regdef_t TIM_DMARM;     // Offset 0x4C | TIMx DMA address for full transfer
    volatile STM32F4xx_TIM_OR_Regdef_t TIM_OR;          // Offset 0x50 | TIM2 and TIM5 option register
} STM32F4xx_TIM_2_5_RegDef_t;


#define _MMIO_ADDR_TIM2     0x40000000UL 
#define STM32F4XX_TIM2_REG   ((STM32F4xx_TIM_2_5_RegDef_t* ) _MMIO_ADDR_TIM2)
#define _MMIO_ADDR_TIM3     0x40000400UL
#define STM32F4XX_TIM3_REG   ((STM32F4xx_TIM_3_4_RegDef_t* ) _MMIO_ADDR_TIM3)
#define _MMIO_ADDR_TIM4     0x40000800UL 
#define STM32F4XX_TIM4_REG   ((STM32F4xx_TIM_3_4_RegDef_t* ) _MMIO_ADDR_TIM4)
#define _MMIO_ADDR_TIM5     0x40000C00UL 
#define STM32F4XX_TIM5_REG   ((STM32F4xx_TIM_2_5_RegDef_t* ) _MMIO_ADDR_TIM5)

typedef struct
{
    volatile STM32F4xx_TIM_CR1_Regdef_t TIM_CR1;        // Offset 0x00 | TIMx control register 1 
    volatile STM32F4xx_TIM_CR2_Regdef_t TIM_CR2;        // Offset 0x04 | TIMx control register 2
    const uint32_t __reserved_1;                        // Offset 0x08 | Reserved
    volatile STM32F4xx_TIM_DIER_Regdef_t TIM_DIER;      // Offset 0x0C | TIMx DMA/Interrupt enable register
    volatile STM32F4xx_TIM_SR_Regdef_t TIM_SR;          // Offset 0x10 | TIMx status register
    volatile STM32F4xx_TIM_EGR_Regdef_t TIM_EGR;        // Offset 0x14 | TIMx event generation register
    const uint32_t __reserved_2[3];                     // Offset 0x18 | Reserved
    volatile STM32F4xx_TIM_CNT_Regdef_t TIM_CNT;        // Offset 0x24 | TIMx counter 
    volatile STM32F4xx_TIM_PSC_Regdef_t TIM_PSC;        // Offset 0x28 | TIMx prescaler 
    volatile STM32F4xx_TIM_ARR_Regdef_t TIM_ARR;        // Offset 0x2C | TIMx auto-reload register
} STM32F4xx_TIM_6_7_RegDef_t;

#define _MMIO_ADDR_TIM6     0x40001000UL
#define STM32F4XX_TIM6_REG   ((STM32F4xx_TIM_6_7_RegDef_t* ) _MMIO_ADDR_TIM6)
#define _MMIO_ADDR_TIM7     0x40001400UL
#define STM32F4XX_TIM7_REG   ((STM32F4xx_TIM_6_7_RegDef_t* ) _MMIO_ADDR_TIM7)

typedef struct
{
    volatile STM32F4xx_TIM_CR1_Regdef_t TIM_CR1;        // Offset 0x00 | TIMx control register 1 
    const uint32_t __reserved_1;                        // Offset 0x04 | Reserved
    const uint32_t __reserved_2;                        // Offset 0x08 | Reserved
    volatile STM32F4xx_TIM_DIER_Regdef_t TIM_DIER;      // Offset 0x0C | TIMx DMA/Interrupt enable register
    volatile STM32F4xx_TIM_SR_Regdef_t TIM_SR;          // Offset 0x10 | TIMx status register
    volatile STM32F4xx_TIM_EGR_Regdef_t TIM_EGR;        // Offset 0x14 | TIMx event generation register
    volatile STM32F4xx_TIM_CCMR1_Regdef_t TIM_CCMR1;    // Offset 0x18 | TIMx capture/compare mode register 1
    const uint32_t __reserved_3;                        // Offset 0x1C | Reserved
    volatile STM32F4xx_TIM_CCER_Regdef_t TIM_CCER;      // Offset 0x20 | TIMx capture/compare enable register
    volatile STM32F4xx_TIM_CNT_Regdef_t TIM_CNT;        // Offset 0x24 | TIMx counter 
    volatile STM32F4xx_TIM_PSC_Regdef_t TIM_PSC;        // Offset 0x28 | TIMx prescaler 
    volatile STM32F4xx_TIM_ARR_Regdef_t TIM_ARR;        // Offset 0x2C | TIMx auto-reload register
    const uint32_t __reserved_4;                        // Offset 0x30 | Reserved
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR1;       // Offset 0x34 | TIMx capture/compare register 1
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR1;       // Offset 0x38 | TIMx capture/compare register 1
    const uint32_t __reserved_5[5];                     // Offset 0x3C | Reserved 
    volatile STM32F4xx_TIM_OR_Regdef_t TIM_OR;          // Offset 0x50 | TIM2 and TIM5 option register
} STM32F4xx_TIM_9_to_12_RegDef_t;


typedef struct
{
    volatile STM32F4xx_TIM_CR1_Regdef_t TIM_CR1;        // Offset 0x00 | TIMx control register 1 
    const uint32_t __reserved_1;                        // Offset 0x04 | Reserved
    const uint32_t __reserved_2;                        // Offset 0x08 | Reserved
    volatile STM32F4xx_TIM_DIER_Regdef_t TIM_DIER;      // Offset 0x0C | TIMx DMA/Interrupt enable register
    volatile STM32F4xx_TIM_SR_Regdef_t TIM_SR;          // Offset 0x10 | TIMx status register
    volatile STM32F4xx_TIM_EGR_Regdef_t TIM_EGR;        // Offset 0x14 | TIMx event generation register
    volatile STM32F4xx_TIM_CCMR1_Regdef_t TIM_CCMR1;    // Offset 0x18 | TIMx capture/compare mode register 1
    const uint32_t __reserved_3;                        // Offset 0x1C | Reserved
    volatile STM32F4xx_TIM_CCER_Regdef_t TIM_CCER;      // Offset 0x20 | TIMx capture/compare enable register
    volatile STM32F4xx_TIM_CNT_Regdef_t TIM_CNT;        // Offset 0x24 | TIMx counter 
    volatile STM32F4xx_TIM_PSC_Regdef_t TIM_PSC;        // Offset 0x28 | TIMx prescaler 
    volatile STM32F4xx_TIM_ARR_Regdef_t TIM_ARR;        // Offset 0x2C | TIMx auto-reload register
    const uint32_t __reserved_4;                        // Offset 0x30 | Reserved
    volatile STM32F4xx_TIM_CCR_Regdef_t TIM_CCR1;       // Offset 0x34 | TIMx capture/compare register 1
    const uint32_t __reserved_5[6];                     // Offset 0x38 | Reserved 
    volatile STM32F4xx_TIM_OR_Regdef_t TIM_OR;          // Offset 0x50 | TIM2 and TIM5 option register
} STM32F4xx_TIM_10_11_13_14_RegDef_t;

#define _MMIO_ADDR_TIM9     0x40014000UL
#define STM32F4XX_TIM9_REG   ((STM32F4xx_TIM_9_to_12_RegDef_t* ) _MMIO_ADDR_TIM9)
#define _MMIO_ADDR_TIM10    0x40014400UL  
#define STM32F4XX_TIM10_REG   ((STM32F4xx_TIM_10_11_13_14_RegDef_t* ) _MMIO_ADDR_TIM10)
#define _MMIO_ADDR_TIM11    0x40014800UL
#define STM32F4XX_TIM11_REG   ((STM32F4xx_TIM_10_11_13_14_RegDef_t* ) _MMIO_ADDR_TIM11)
#define _MMIO_ADDR_TIM12    0x40001800UL
#define STM32F4XX_TIM12_REG   ((STM32F4xx_TIM_9_to_12_RegDef_t* ) _MMIO_ADDR_TIM12)
#define _MMIO_ADDR_TIM13    0x40001C00UL
#define STM32F4XX_TIM13_REG   ((STM32F4xx_TIM_10_11_13_14_RegDef_t* ) _MMIO_ADDR_TIM13)
#define _MMIO_ADDR_TIM14    0x40002000UL
#define STM32F4XX_TIM14_REG   ((STM32F4xx_TIM_10_11_13_14_RegDef_t* ) _MMIO_ADDR_TIM14)

#define _MMIO_ADDR_RTC      0x40002800UL 

typedef union __STM32F4xx_RTC_TR_Regdef
{
    struct
    {
        volatile uint32_t SU            :   4;  // Byte 0, Bit 0-3 |  0- 3
        volatile uint32_t ST            :   3;  // Byte 0, Bit 4-6 |  4- 6
        const uint32_t _reserved_4      :   1;  // Byte 0, Bit   7 |     7
        volatile uint32_t MNU           :   4;  // Byte 1, Bit 0-3 |  8-11
        volatile uint32_t MNT           :   3;  // Byte 1, Bit 4-6 | 12-14
        const uint32_t _reserved_3      :   1;  // Byte 1, Bit   7 |    15
        volatile uint32_t HU            :   4;  // Byte 2, Bit 0-3 | 16-19
        volatile uint32_t HT            :   2;  // Byte 2, Bit 4-5 | 20-21
        volatile uint32_t PM            :   1;  // Byte 2, Bit   6 |    22
        const uint32_t _reserved_2      :   1;  // Byte 2, Bit   7 |    23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_TR_Regdef_t;

typedef union __STM32F4xx_RTC_DR_Regdef
{
    struct
    {
        volatile uint32_t DU            :   4;  // Byte 0, Bit 0-3 |  0- 3
        volatile uint32_t DT            :   2;  // Byte 0, Bit 4-5 |  4- 5
        const uint32_t _reserved_2      :   2;  // Byte 0, Bit 6-7 |  6- 7
        volatile uint32_t MU            :   4;  // Byte 1, Bit 0-3 |  8-11
        volatile uint32_t MT            :   1;  // Byte 1, Bit   6 |    12
        volatile uint32_t WDU           :   3;  // Byte 1, Bit   7 | 13-15
        volatile uint32_t YU            :   4;  // Byte 2, Bit 0-3 | 16-19
        volatile uint32_t YT            :   4;  // Byte 2, Bit 4-7 | 20-23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_DR_Regdef_t;

typedef union __STM32F4xx_RTC_CR_Regdef
{
    struct
    {
        volatile uint32_t WUCKSEL       :   3;  // Byte 0, Bit 0-2 |  0- 2
        volatile uint32_t TSEDGE        :   1;  // Byte 0, Bit   3 |     3
        volatile uint32_t REFCKON       :   1;  // Byte 0, Bit   4 |     4
        volatile uint32_t BYPASHAD      :   1;  // Byte 0, Bit   5 |     5
        volatile uint32_t FMT           :   1;  // Byte 0, Bit   6 |     6
        volatile uint32_t DCE           :   1;  // Byte 0, Bit   7 |     7
        volatile uint32_t ALRAE         :   1;  // Byte 1, Bit   0 |     8
        volatile uint32_t ALRBE         :   1;  // Byte 1, Bit   1 |     9
        volatile uint32_t WUT           :   1;  // Byte 1, Bit   2 |    10
        volatile uint32_t TSE           :   1;  // Byte 1, Bit   3 |    11
        volatile uint32_t ALRAIE        :   1;  // Byte 1, Bit   4 |    12
        volatile uint32_t ALRBIE        :   1;  // Byte 1, Bit   5 |    13
        volatile uint32_t WUTIE         :   1;  // Byte 1, Bit   6 |    14
        volatile uint32_t TSIE          :   1;  // Byte 1, Bit   7 |    15
        volatile uint32_t ADD1H         :   1;  // Byte 2, Bit   0 |    16
        volatile uint32_t SUB1H         :   1;  // Byte 2, Bit   1 |    17
        volatile uint32_t BKP           :   1;  // Byte 2, Bit   2 |    18
        volatile uint32_t COSEL         :   1;  // Byte 2, Bit   3 |    19
        volatile uint32_t POL           :   1;  // Byte 2, Bit   4 |    20
        volatile uint32_t OSEL          :   2;  // Byte 2, Bit 5-6 | 21-22
        volatile uint32_t COE           :   1;  // Byte 2, Bit   7 |    23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_CR_Regdef_t;

typedef union __STM32F4xx_RTC_ISR_Regdef
{
    struct
    {
        volatile uint32_t ALRAWF        :   1;  // Byte 0, Bit   0 |     0
        volatile uint32_t ALRBWF        :   1;  // Byte 0, Bit   1 |     1
        volatile uint32_t WUTWF         :   1;  // Byte 0, Bit   2 |     2
        volatile uint32_t SHPF          :   1;  // Byte 0, Bit   3 |     3
        volatile uint32_t INITS         :   1;  // Byte 0, Bit   4 |     4
        volatile uint32_t RSF           :   1;  // Byte 0, Bit   5 |     5
        volatile uint32_t INITF         :   1;  // Byte 0, Bit   6 |     6
        volatile uint32_t INIT          :   1;  // Byte 0, Bit   7 |     7
        volatile uint32_t ALRAF         :   1;  // Byte 1, Bit   0 |     8
        volatile uint32_t ALRBF         :   1;  // Byte 1, Bit   1 |     9
        volatile uint32_t WUTF          :   1;  // Byte 1, Bit   2 |    10
        volatile uint32_t TSF           :   1;  // Byte 1, Bit   3 |    11
        volatile uint32_t TSOVF         :   1;  // Byte 1, Bit   4 |    12
        volatile uint32_t TAMP1F        :   1;  // Byte 1, Bit   5 |    13
        const uint32_t _reserved_1      :   2;  // Byte 1, Bit 6-7 | 14-15
        volatile uint32_t RECALPF       :   1;  // Byte 2, Bit   0 |    16
        const uint32_t _reserved_2      :   7;  // Byte 2, Bit 1-7 | 17-23
        const uint32_t _reserved_3      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_ISR_Regdef_t;

typedef union __STM32F4xx_RTC_PRER_Regdef
{
    struct
    {
        volatile uint32_t PREDIV_S      :  15;  // Byte 0, Bit 0-7 |  0-14
        const uint32_t _reserved_3      :   1;  // Byte 1, Bit   7 |    15
        volatile uint32_t PREDIV_A      :   7;  // Byte 2, Bit 0-6 | 16-22
        const uint32_t _reserved_2      :   1;  // Byte 2, Bit   7 |    23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_PRER_Regdef_t;

typedef union __STM32F4xx_RTC_WUTR_Regdef
{
    struct
    {
        volatile uint32_t WUT_L         :  16;  // Byte 0-1, Bit 0-15|  0-15
        const uint32_t _reserved_2      :   8;  // Byte   2, Bit 0-7 | 16-23
        const uint32_t _reserved_1      :   8;  // Byte   3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_WUTR_Regdef_t;

typedef union __STM32F4xx_RTC_CALIBR_Regdef
{
    struct
    {
        volatile uint32_t DC            :   5;  // Byte 0, Bit 0-4 |  0- 4
        const uint32_t _reserved_4      :   2;  // Byte 0, Bit 5-6 |  5- 6
        volatile uint32_t DCS           :   1;  // Byte 0, Bit   7 |     7
        const uint32_t _reserved_3      :   8;  // Byte 1, Bit 0-7 |  8-15
        const uint32_t _reserved_2      :   8;  // Byte 2, Bit 0-7 | 16-23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_CALIBR_Regdef_t;

typedef union __STM32F4xx_RTC_ARLMxR_Regdef
{
    struct
    {
        volatile uint32_t SU            :   4;  // Byte 0, Bit 0-3 |  0- 3
        volatile uint32_t ST            :   3;  // Byte 0, Bit 4-6 |  4- 6
        volatile uint32_t MSK1          :   1;  // Byte 0, Bit   7 |     7
        volatile uint32_t MNU           :   4;  // Byte 1, Bit 0-3 |  8-11
        volatile uint32_t MNT           :   3;  // Byte 1, Bit 4-6 | 12-14
        volatile uint32_t MSK2          :   1;  // Byte 1, Bit   7 |    15
        volatile uint32_t HU            :   4;  // Byte 2, Bit 0-3 | 16-19
        volatile uint32_t HT            :   2;  // Byte 2, Bit 4-5 | 20-21
        volatile uint32_t PM            :   1;  // Byte 2, Bit   6 |    22
        volatile uint32_t MSK3          :   1;  // Byte 2, Bit   7 |    23
        volatile uint32_t DT            :   2;  // Byte 3, Bit 2-3 | 24-27
        volatile uint32_t DU            :   4;  // Byte 3, Bit 4-7 | 28-29
        volatile uint32_t WDSEL         :   1;  // Byte 3, Bit   1 |    30
        volatile uint32_t MSK4          :   1;  // Byte 3, Bit   0 |    31
    };
    uint32_t raw;
} STM32F4xx_RTC_ARLMxR_Regdef_t;

typedef union __STM32F4xx_RTC_WPR_Regdef
{
    struct
    {
        volatile uint32_t KEY           :   8;  // Byte 0, Bit 0-4 |  0- 7
        const uint32_t _reserved_1      :   8;  // Byte 1, Bit 0-7 |  7-15
        const uint32_t _reserved_2      :   8;  // Byte 2, Bit 0-7 | 16-23
        const uint32_t _reserved_3      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_WPR_Regdef_t;

typedef union __STM32F4xx_RTC_SSR_Regdef
{
    struct
    {
        volatile uint32_t SS            :  16;  // Byte 0-1, Bit 0-15 |  8-15
        const uint32_t _reserved_2      :   8;  // Byte   2, Bit 0- 7 | 16-23
        const uint32_t _reserved_1      :   8;  // Byte   3, Bit 0- 7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_SSR_Regdef_t;

typedef union __STM32F4xx_RTC_RTC_SHIFTR_Regdef
{
    struct
    {
        volatile uint32_t SUBFS_L       :   8;  // Byte 0, Bit 0-7 |  0- 7
        volatile uint32_t SUBFS_H       :   7;  // Byte 1, Bit 0-6 |  8-14
        const uint32_t _reserved_3      :   1;  // Byte 0, Bit   7 |    15
        const uint32_t _reserved_2      :   8;  // Byte 2, Bit 0-7 | 16-23
        const uint32_t _reserved_1      :   7;  // Byte 3, Bit 0-6 | 24-30
        volatile uint32_t ADD1S         :   1;  // Byte 3, Bit   7 |    31
    };
    uint32_t raw;
} STM32F4xx_RTC_RTC_SHIFTR_Regdef_t;

typedef union __STM32F4xx_RTC_TSTR_Regdef
{
    struct
    {
        volatile uint32_t SU            :   4;  // Byte 0, Bit 0-3 |  0- 3
        volatile uint32_t ST            :   3;  // Byte 0, Bit 4-6 |  4- 6
        const uint32_t _reserved_4      :   1;  // Byte 0, Bit   7 |     7
        volatile uint32_t MNU           :   4;  // Byte 1, Bit 0-3 |  8-11
        volatile uint32_t MNT           :   3;  // Byte 1, Bit 4-6 | 12-14
        const uint32_t _reserved_3      :   1;  // Byte 1, Bit   7 |    15
        volatile uint32_t HU            :   4;  // Byte 2, Bit 0-3 | 16-19
        volatile uint32_t HT            :   2;  // Byte 2, Bit 4-5 | 20-21
        volatile uint32_t PM            :   1;  // Byte 2, Bit   6 |    22
        const uint32_t _reserved_2      :   1;  // Byte 2, Bit   7 |    23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_TSTR_Regdef_t;


typedef union __STM32F4xx_RTC_TSDR_Regdef
{
    struct
    {
        volatile uint32_t DU            :   4;  // Byte 0, Bit 0-3 |  0- 3
        volatile uint32_t DT            :   2;  // Byte 0, Bit 4-5 |  4- 5
        const uint32_t _reserved_3      :   2;  // Byte 0, Bit 6-7 |  6- 7
        volatile uint32_t MU            :   4;  // Byte 1, Bit 0-3 |  8-11
        volatile uint32_t MT            :   1;  // Byte 1, Bit   6 |    12
        volatile uint32_t WDU           :   3;  // Byte 1, Bit   7 | 13-15
        const uint32_t _reserved_2      :   8;  // Byte 2, Bit 0-3 | 16-23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_TSDR_Regdef_t;


typedef union __STM32F4xx_RTC_CALR_Regdef
{
    struct
    {
        volatile uint32_t CALM_L        :   8;  // Byte 0, Bit 0-7 |  0- 7
        volatile uint32_t CALM_H        :   1;  // Byte 1, Bit   0 |     8
        const uint32_t _reserved_3      :   4;  // Byte 1, Bit 1-4 |  9-12
        volatile uint32_t CALW16        :   1;  // Byte 1, Bit   5 |    13
        volatile uint32_t CALW8         :   1;  // Byte 1, Bit   6 |    14
        volatile uint32_t CALP          :   1;  // Byte 1, Bit   7 |    15
        const uint32_t _reserved_2      :   8;  // Byte 2, Bit 0-7 | 16-23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_CALR_Regdef_t;

typedef union __STM32F4xx_RTC_TAFCR_Regdef
{
    struct
    {
        volatile uint32_t TAMP1E        :   1;  // Byte 0, Bit   0 |     0
        volatile uint32_t TAMP1TRG      :   1;  // Byte 0, Bit   1 |     1
        volatile uint32_t TAMPIE        :   1;  // Byte 0, Bit   2 |     2
        const uint32_t _reserved_3      :   4;  // Byte 0, Bit 3-6 |  3- 6
        volatile uint32_t TAMPTS        :   1;  // Byte 0, Bit   7 |     7
        volatile uint32_t TAMPFREQ      :   3;  // Byte 1, Bit 0-2 |  8-10
        volatile uint32_t TAMPFLT       :   2;  // Byte 1, Bit 3-4 | 11-12
        volatile uint32_t TAMPPRCH      :   2;  // Byte 1, Bit 5-6 | 13-14
        volatile uint32_t TAMPPUDIS     :   1;  // Byte 1, Bit   7 |    15
        volatile uint32_t TAMP1INSEL    :   1;  // Byte 2, Bit   0 |    16
        volatile uint32_t TSINSEL       :   1;  // Byte 2, Bit   1 |    17
        volatile uint32_t ALARMOUTTYPE  :   1;  // Byte 2, Bit   2 |    18
        const uint32_t _reserved_2      :   5;  // Byte 2, Bit   7 | 19-23
        const uint32_t _reserved_1      :   8;  // Byte 3, Bit 0-7 | 24-31
    };
    uint32_t raw;
} STM32F4xx_RTC_TAFCR_Regdef_t;

typedef union __STM32F4xx_RTC_ALRMxSSR_Regdef
{
    struct
    {
        volatile uint32_t SS            :  15;  // Byte 0, Bit 0-4 |  0-14
        const uint32_t _reserved_3      :   1;  // Byte 1, Bit   7 |    15
        const uint32_t _reserved_2      :   8;  // Byte 2, Bit 0-7 | 16-23
        volatile uint32_t MASKSS        :   4;  // Byte 3, Bit 0-3 | 24-37
        const uint32_t _reserved_1      :   4;  // Byte 3, Bit 4-7 | 28-31
    };
    uint32_t raw;
} STM32F4xx_RTC_ALRMxSSR_Regdef_t;

typedef struct
{
    volatile STM32F4xx_RTC_TR_Regdef_t RTC_TR;              // 0x00 RTC time register
    volatile STM32F4xx_RTC_DR_Regdef_t RTC_DR;              // 0x04 RTC date register
    volatile STM32F4xx_RTC_CR_Regdef_t RTC_CR;              // 0x08 RTC control register
    volatile STM32F4xx_RTC_ISR_Regdef_t RTC_ISR;            // 0x0C RTC initialization and status register
    volatile STM32F4xx_RTC_PRER_Regdef_t RTC_PRER;          // 0x10 RTC prescaler register 
    volatile STM32F4xx_RTC_WUTR_Regdef_t RTC_WUTR;          // 0x14 RTC wakeup timer register 
    volatile STM32F4xx_RTC_CALIBR_Regdef_t RTC_CALIBR;      // 0x18 RTC calibration register
    volatile STM32F4xx_RTC_ARLMxR_Regdef_t RTC_ALRMAR;      // 0x1C RTC alarm A register
    volatile STM32F4xx_RTC_ARLMxR_Regdef_t RTC_ALRMBR;      // 0x20 RTC alarm B register
    volatile STM32F4xx_RTC_WPR_Regdef_t RTC_WPR;            // 0x24 RTC write protection register
    volatile STM32F4xx_RTC_SSR_Regdef_t RTC_SSR;            // 0x28 RTC sub second register
    volatile STM32F4xx_RTC_RTC_SHIFTR_Regdef_t RTC_SHIFTR;  // 0x2C RTC shift control register
    volatile STM32F4xx_RTC_TSTR_Regdef_t RTC_TSTR;          // 0x30 RTC time stamp time register
    volatile STM32F4xx_RTC_TSDR_Regdef_t RTC_TSDR;          // 0x34 RTC time stamp date register 
    volatile STM32F4xx_RTC_SSR_Regdef_t RTC_TSSSR;          // 0x38 RTC timestamp sub second register 
    volatile STM32F4xx_RTC_CALR_Regdef_t RTC_CALR;          // 0x3C RTC calibration register
    volatile STM32F4xx_RTC_TAFCR_Regdef_t RTC_TAFCR;        // 0x40 RTC tamper and alternate function configuration register
    volatile STM32F4xx_RTC_ALRMxSSR_Regdef_t RTC_ALRMASSR;  // 0x44 RTC alarm A sub second register
    volatile STM32F4xx_RTC_ALRMxSSR_Regdef_t RTC_ALRMBSSR;  // 0x48 RTC alarm B sub second register 
    const uint32_t __reserved;                              // 0x4C reserved register
    volatile uint32_t RTC_BKPR[20];                         // 0x50-0x9C RTC backup registers
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
        volatile uint16_t PE            :   1;  // Byte 0, Bit 0 |  0
        volatile uint16_t SMBUS         :   1;  // Byte 0, Bit 1 |  1
        const uint16_t _reserved_2      :   1;  // Byte 0, Bit 2 |  2
        volatile uint16_t SMBTYPE       :   1;  // Byte 0, Bit 3 |  3
        volatile uint16_t ENARP         :   1;  // Byte 0, Bit 4 |  4
        volatile uint16_t ENPEC         :   1;  // Byte 0, Bit 5 |  5
        volatile uint16_t ENGC          :   1;  // Byte 0, Bit 6 |  6
        volatile uint16_t NOSTRETCH     :   1;  // Byte 0, Bit 7 |  7
        volatile uint16_t START         :   1;  // Byte 1, Bit 0 |  8
        volatile uint16_t STOP          :   1;  // Byte 1, Bit 1 |  9
        volatile uint16_t ACK           :   1;  // Byte 1, Bit 2 | 10
        volatile uint16_t POS           :   1;  // Byte 1, Bit 3 | 11
        volatile uint16_t PEC           :   1;  // Byte 1, Bit 4 | 12
        volatile uint16_t ALERT         :   1;  // Byte 1, Bit 5 | 13
        const uint16_t _reserved_1      :   1;  // Byte 1, Bit 6 | 14
        volatile uint16_t SWRST         :   1;  // Byte 1, Bit 7 | 15
    };
    uint16_t raw;
} STM32F4xx_I2C_CR1_Regdef_t;

typedef union __STM32F4xx_I2C_CR2_Regdef
{
    struct
    {
        volatile uint16_t FREQ          :   6;  // Byte 0, Bit 0-5 |  0-5
        const uint16_t _reserved_2      :   2;  // Byte 0, Bit 6-7 |  6-7
        volatile uint16_t ITERREN       :   1;  // Byte 1, Bit 0   |  8
        volatile uint16_t ITEVTEN       :   1;  // Byte 1, Bit 1   |  9
        volatile uint16_t ITBUFEN       :   1;  // Byte 1, Bit 2   | 10
        volatile uint16_t DMAEN         :   1;  // Byte 1, Bit 3   | 11
        volatile uint16_t LAST          :   1;  // Byte 1, Bit 4   | 12
        const uint16_t _reserved_1      :   3;  // Byte 1, Bit 5-7 | 13-15
    };
    uint16_t raw;
} STM32F4xx_I2C_CR2_Regdef_t;

typedef union __STM32F4xx_I2C_OAR1_Regdef
{
    struct
    {
        volatile uint16_t ADD0          :   1;  // Byte 0, Bit 0   |  0
        volatile uint16_t ADD1          :   7;  // Byte 0, Bit 1-7 |  1-7
        volatile uint16_t ADD2          :   1;  // Byte 1, Bit 0-1 |  8-9
        const uint16_t _reserved_1      :   5;  // Byte 1, Bit 2-6 | 10-14
        volatile uint16_t ADDMODE       :   1;  // Byte 1, Bit 7   | 15

    };
    uint16_t raw;
} STM32F4xx_I2C_OAR1_Regdef_t;

typedef union __STM32F4xx_I2C_OAR2_Regdef
{
    struct
    {
        volatile uint16_t ENDUAL        :   1;  // Byte 0, Bit 0   |  0
        volatile uint16_t ADD2          :   7;  // Byte 0, Bit 1-7 |  1-7
        const uint16_t _reserved_1      :   8;  // Byte 1, Bit 0-7 |  8-15

    };
    uint16_t raw;
} STM32F4xx_I2C_OAR2_Regdef_t;

typedef union __STM32F4xx_I2C_DR_Regdef
{
    struct
    {
        volatile uint16_t DR            :   8;  // Byte 0, Bit 0-7 |  0-7
        const uint16_t _reserved_1      :   8;  // Byte 1, Bit 0-7 |  8-15

    };
    uint16_t raw;
} STM32F4xx_I2C_DR_Regdef_t;

typedef union __STM32F4xx_I2C_SR1_Regdef
{
    struct
    {
        volatile uint16_t SB            :   1;  // Byte 0, Bit 0 |  0
        volatile uint16_t ADDR          :   1;  // Byte 0, Bit 1 |  1
        volatile uint16_t BTF           :   1;  // Byte 0, Bit 2 |  2
        volatile uint16_t ADD10         :   1;  // Byte 0, Bit 3 |  3
        volatile uint16_t STOPF         :   1;  // Byte 0, Bit 4 |  4
        const uint16_t __reserved_2     :   1;  // Byte 0, Bit 5 |  5
        volatile uint16_t RxNE          :   1;  // Byte 0, Bit 6 |  6
        volatile uint16_t TxE           :   1;  // Byte 0, Bit 7 |  7
        volatile uint16_t BERR          :   1;  // Byte 1, Bit 0 |  8
        volatile uint16_t ARLO          :   1;  // Byte 1, Bit 1 |  9
        volatile uint16_t AF            :   1;  // Byte 1, Bit 2 | 10
        volatile uint16_t OVR           :   1;  // Byte 1, Bit 3 | 11
        volatile uint16_t PEC_ERR       :   1;  // Byte 1, Bit 4 | 12
        const uint16_t _reserved_1      :   1;  // Byte 1, Bit 5 | 13
        volatile uint16_t TIMEOUT       :   1;  // Byte 1, Bit 6 | 14
        volatile uint16_t SMBALER       :   1;  // Byte 1, Bit 7 | 15
    };
    uint16_t raw;
} STM32F4xx_I2C_SR1_Regdef_t;

typedef union __STM32F4xx_I2C_SR2_Regdef
{
    struct
    {
        volatile uint16_t MSL           :   1;  // Byte 0, Bit 0   |  0
        volatile uint16_t BUSY          :   1;  // Byte 0, Bit 1   |  1
        volatile uint16_t TRA           :   1;  // Byte 0, Bit 2   |  2
        const uint16_t __reserved       :   1;  // Byte 0, Bit 3   |  3
        volatile uint16_t GENCALL       :   1;  // Byte 0, Bit 4   |  4
        volatile uint16_t SMBDEFAULT    :   1;  // Byte 0, Bit 5   |  5
        volatile uint16_t SMBHOST       :   1;  // Byte 0, Bit 6   |  6
        volatile uint16_t DAUALF        :   1;  // Byte 0, Bit 7   |  7
        volatile uint16_t PEC           :   8;  // Byte 1, Bit 0-7 |  8-15
    };
    uint16_t raw;
} STM32F4xx_I2C_SR2_Regdef_t;

typedef union __STM32F4xx_I2C_CCR_Regdef
{
    struct
    {
        volatile uint16_t CCR           :  12;  // Byte 0, Bit 0-7 |  0-11
        const uint16_t __reserved       :   2;  // Byte 1, Bit 4-5 |  12-13
        volatile uint16_t DUTY          :   1;  // Byte 1, Bit 6   |  14
        volatile uint16_t FS            :   1;  // Byte 1, Bit 7   |  15
    };
    uint16_t raw;
} STM32F4xx_I2C_CCR_Regdef_t;

typedef union __STM32F4xx_I2C_TRISE_Regdef
{
    struct
    {
        volatile uint16_t TRISE         :   6;  // Byte 0, Bit 0-5 |  0-5
        const uint16_t __reserved_2     :   2;  // Byte 0, Bit 6-7 |  6-7
        const uint16_t __reserved_1     :   8;  // Byte 1, Bit 0-7 |   8-15
    };
    uint16_t raw;
} STM32F4xx_I2C_TRISE_Regdef_t;

typedef union __STM32F4xx_I2C_FLTR_Regdef
{
    struct
    {
        volatile uint16_t DNF           :   4;  // Byte 0, Bit 0-3 |  0-3
        volatile uint16_t ANOFF         :   4;  // Byte 0, Bit 4   |  4
        const uint16_t __reserved_2     :   3;  // Byte 0, Bit 5-7 |  5-7
        const uint16_t __reserved_1     :   8;  // Byte 1, Bit 0-7 |  8-15
    };
    uint16_t raw;
} STM32F4xx_I2C_FLTR_Regdef_t;


typedef struct
{
    volatile STM32F4xx_I2C_CR1_Regdef_t I2C_CR1;    // 0x00 I2C Control register 1
    const uint16_t __reserved_1;                    // 0x02 reserved
    volatile STM32F4xx_I2C_CR2_Regdef_t I2C_CR2;    // 0x04 I2C Control register 2
    const uint16_t __reserved_2;                    // 0x06 reserved
    volatile STM32F4xx_I2C_OAR1_Regdef_t I2C_OAR1;  // 0x08 I2C Own address register 1
    const uint16_t __reserved_3;                    // 0x0A reserved 
    volatile STM32F4xx_I2C_OAR2_Regdef_t I2C_OAR2;  // 0x0C I2C Own address register 2
    const uint16_t __reserved_4;                    // 0x0E reserved
    volatile STM32F4xx_I2C_DR_Regdef_t I2C_DR;      // 0x10 I2C Data register
    const uint16_t __reserved_5;                    // 0x12 reserved 
    volatile STM32F4xx_I2C_SR1_Regdef_t I2C_SR1;    // 0x14 I2C Status register 1
    const uint16_t __reserved_6;                    // 0x16 reserved
    volatile STM32F4xx_I2C_SR2_Regdef_t I2C_SR2;    // 0x18 I2C Status register 2
    const uint16_t __reserved_7;                    // 0x1A reserved 
    volatile STM32F4xx_I2C_CCR_Regdef_t I2C_CCR;    // 0x1C I2C Clock control register
    const uint16_t __reserved_8;                    // 0x1E reserved 
    volatile STM32F4xx_I2C_TRISE_Regdef_t I2C_TRISE;// 0x20 I2C TRISE register 
    const uint16_t __reserved_9;                    // 0x22 reserved
    volatile STM32F4xx_I2C_FLTR_Regdef_t I2C_FLTR;  // 0x24 I2C FLTR register
    const uint16_t __reserved_10;                   // 0x26 reserved
} STM32F4xx_I2C_RegDef_t;

#define _MMIO_ADDR_I2C1     0x40005400UL
#define STM32F4XX_I2C1_REG   ((STM32F4xx_I2C_RegDef_t* ) _MMIO_ADDR_I2C1)
#define _MMIO_ADDR_I2C2     0x40005800UL 
#define STM32F4XX_I2C2_REG   ((STM32F4xx_I2C_RegDef_t* ) _MMIO_ADDR_I2C2)
#define _MMIO_ADDR_I2C3     0x40005C00UL  
#define STM32F4XX_I2C3_REG   ((STM32F4xx_I2C_RegDef_t* ) _MMIO_ADDR_I2C3)

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
