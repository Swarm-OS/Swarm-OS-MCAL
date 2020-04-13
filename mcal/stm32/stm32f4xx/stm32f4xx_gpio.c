/**
 * @file stm32f411_gpio.c
 * @author Christoph Lehr
 * @date 21 Jan 2020
 * @brief STM32F411 implentation ofAPI for accessing GPIO's
 *
 * This file implements the generic API which shall be used to 
 * interact with the GPIO's of different Microcontrollers.
 */

#include <mcus.h>
#if IS_MCU(MCU_STM32F411)

#include <stdint.h>
#include "../../../includes/datatypes.h"
#include "../../../includes/gpio.h"
#include "stm32f4xx.h"
#include "stm32f4xx_pins.h"
#include "stm32f4xx_interrupt.h"



static void (*EXTI_cbs[16]) (void) = {};
static uint16_t EXTI_mask = 0; 

boolean pin_exists(MCAL_GPIO_pin_t pin);
void set_interrupt_register(MCAL_GPIO_pin_t pin);
void clear_interrupt_register(MCAL_GPIO_pin_t pin);

std_return_type_t MCAL_GPIO_init(MCAL_GPIO_pin_t port)
{
    switch (MCAL_GPIO_get_port(port))
    {
    case PORT_A:
        MCAL_GPIOA_PCLK_EN();
        break;
    case PORT_B:
        MCAL_GPIOB_PCLK_EN();
        break;
    case PORT_C:
        MCAL_GPIOC_PCLK_EN();
        break;
    case PORT_D:
        MCAL_GPIOD_PCLK_EN();
        break;
    case PORT_E:
        MCAL_GPIOE_PCLK_EN();
        break;
    case PORT_H:
        MCAL_GPIOH_PCLK_EN();
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }
    return E_OK;
    
}

std_return_type_t MCAL_GPIO_deinit(MCAL_GPIO_pin_t port)
{
    switch (MCAL_GPIO_get_port(port))
    {
    case PORT_A:
        MCAL_GPIOA_PCLK_DI();
        break;
    case PORT_B:
        MCAL_GPIOB_PCLK_DI();
        break;
    case PORT_C:
        MCAL_GPIOC_PCLK_DI();
        break;
    case PORT_D:
        MCAL_GPIOD_PCLK_DI();
        break;
    case PORT_E:
        MCAL_GPIOE_PCLK_DI();
        break;
    case PORT_H:
        MCAL_GPIOH_PCLK_DI();
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }
    return E_OK;
}

std_return_type_t MCAL_GPIO_config_pin(MCAL_GPIO_pin_t pin, MCAL_GPIO_pin_mode_t mode, MCAL_GPIO_pullup_mode_t pullup)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }

    MCAL_GPIO_RegDef_t *port;
    
    uint8_t pin_number = (uint8_t) MCAL_GPIO_get_pin_number(pin);
    
    switch (MCAL_GPIO_get_port(pin))
    {
    case PORT_A:
        port = MCAL_GPIOA;
        break;
    case PORT_B:
        port = MCAL_GPIOB;
        break;
    case PORT_C:
        port = MCAL_GPIOC;
        break;
    case PORT_D:
        port = MCAL_GPIOD;
        break;
    case PORT_E:
        port = MCAL_GPIOE;
        break;
    case PORT_H:
        port = MCAL_GPIOH;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    switch (mode)
    {
    case MCAL_GPIO_INPUT:
        // set pin mode
        port->MODER &= ~(0x3 << (pin_number <<1));
        break;
    case MCAL_GPIO_INPUT_ANALOG   :
        // set pin mode
        port->MODER |= (0x3 << (pin_number <<1));
        break;
    case MCAL_GPIO_OUTPUT         :
        // set pin mode
        port->MODER &= ~(0x2 << (pin_number <<1));
        port->MODER |=  (0x1 << (pin_number <<1));
        // output driver configuration - push-pull
        port->OTYPER &= ~(0x1 << (pin_number));
        break;
    case MCAL_GPIO_OUTPUT_ANALOG  :
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    switch (pullup)
    {
    case MCAL_GPIO_NO_PULLUP:
        // disable pullups/pulldowns
        port->PUPDR &= ~(0x3 << (pin_number <<1));
        break;
    case MCAL_GPIO_PULLUP   :
        // set pullups
        port->PUPDR &= ~(0x2 << (pin_number <<1));
        port->PUPDR |=  (0x1 << (pin_number <<1));
        break;
    case MCAL_GPIO_PULLDOWN  :
        // set pulldowns
        port->PUPDR &= ~(0x1 << (pin_number <<1));
        port->PUPDR |=  (0x2 << (pin_number <<1));
        break;
    
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    return E_OK;
}

std_return_type_t MCAL_GPIO_pin_set(MCAL_GPIO_pin_t pin)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }

    MCAL_GPIO_RegDef_t *port;
    uint8_t pin_number = (uint8_t) MCAL_GPIO_get_pin_number(pin);
    
    switch (MCAL_GPIO_get_port(pin))
    {
    case PORT_A:
        port = MCAL_GPIOA;
        break;
    case PORT_B:
        port = MCAL_GPIOB;
        break;
    case PORT_C:
        port = MCAL_GPIOC;
        break;
    case PORT_D:
        port = MCAL_GPIOD;
        break;
    case PORT_E:
        port = MCAL_GPIOE;
        break;
    case PORT_H:
        port = MCAL_GPIOH;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }
   
    port->BSRR |= (1 << pin_number);
    return E_OK;
}

std_return_type_t MCAL_GPIO_pin_clear(MCAL_GPIO_pin_t pin)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }

    MCAL_GPIO_RegDef_t *port;
    uint8_t pin_number = (uint8_t) MCAL_GPIO_get_pin_number(pin)+ 16;

    switch (MCAL_GPIO_get_port(pin))
    {
    case PORT_A:
        port = MCAL_GPIOA;
        break;
    case PORT_B:
        port = MCAL_GPIOB;
        break;
    case PORT_C:
        port = MCAL_GPIOC;
        break;
    case PORT_D:
        port = MCAL_GPIOD;
        break;
    case PORT_E:
        port = MCAL_GPIOE;
        break;
    case PORT_H:
        port = MCAL_GPIOH;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    port->BSRR |= (1 << pin_number);
    return E_OK;
}

std_return_type_t MCAL_GPIO_port_set(MCAL_GPIO_pin_t pin, uint16_t value)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }
    
    MCAL_GPIO_RegDef_t *port;

    switch (MCAL_GPIO_get_port(pin))
    {
    case PORT_A:
        port = MCAL_GPIOA;
        break;
    case PORT_B:
        port = MCAL_GPIOB;
        break;
    case PORT_C:
        port = MCAL_GPIOC;
        break;
    case PORT_D:
        port = MCAL_GPIOD;
        break;
    case PORT_E:
        port = MCAL_GPIOE;
        break;
    case PORT_H:
        port = MCAL_GPIOH;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    port->ODR |= value;
    port->ODR &= (((uint32_t)0xFFFF) << 16 )| value;
    

    return E_NOT_IMPLEMENTED;
}

std_return_type_t MCAL_GPIO_pin_set_analog(MCAL_GPIO_pin_t pin, uint16_t value)
{
    return E_NOT_SUPPORTED;
}

std_return_type_t MCAL_GPIO_pin_iset_analog(MCAL_GPIO_pin_t pin, uint16_t value)
{    
    return E_NOT_SUPPORTED;
}

boolean MCAL_GPIO_pin_read(MCAL_GPIO_pin_t pin)
{
    if(FALSE == pin_exists( pin))
    {
        return FALSE;
    }

    MCAL_GPIO_RegDef_t *port;
    uint8_t pin_number = (uint8_t) MCAL_GPIO_get_pin_number(pin);

    switch (MCAL_GPIO_get_port(pin))
    {
    case PORT_A:
        port = MCAL_GPIOA;
        break;
    case PORT_B:
        port = MCAL_GPIOB;
        break;
    case PORT_C:
        port = MCAL_GPIOC;
        break;
    case PORT_D:
        port = MCAL_GPIOD;
        break;
    case PORT_E:
        port = MCAL_GPIOE;
        break;
    case PORT_H:
        port = MCAL_GPIOH;
        break;
    default:
        return FALSE;
        break;
    }

    if(port->IDR & (1 << pin_number))
    {
        return TRUE;
    }
        
    return FALSE;
}

std_return_type_t MCAL_GPIO_port_read(MCAL_GPIO_pin_t pin, uint16_t* buffer)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }

    MCAL_GPIO_RegDef_t *port;
    
    switch (MCAL_GPIO_get_port(pin))
    {
    case PORT_A:
        port = MCAL_GPIOA;
        break;
    case PORT_B:
        port = MCAL_GPIOB;
        break;
    case PORT_C:
        port = MCAL_GPIOC;
        break;
    case PORT_D:
        port = MCAL_GPIOD;
        break;
    case PORT_E:
        port = MCAL_GPIOE;
        break;
    case PORT_H:
        port = MCAL_GPIOH;
        break;
    default:
        return FALSE;
        break;
    }
    *buffer = port->IDR & 0xFFFF;
    return E_OK;
}

std_return_type_t MCAL_GPIO_input_trigger(MCAL_GPIO_pin_t pin, MCAL_GPIO_trigger_t trigger, void (*callback)(void))
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }
    
    uint8_t pin_number = (uint8_t) MCAL_GPIO_get_pin_number(pin);
    
    switch (trigger)
    {
        case MCAL_GPIO_NO_TRIGGER:
            // clear rising trigger flag
            MCAL_EXTI->EXTI_RTSR    &= ~(0x1 << pin_number);
            // clear falling trigger flag
            MCAL_EXTI->EXTI_FTSR    &= ~(0x1 << pin_number);

            break;
        case MCAL_GPIO_BOTH_EDGES :
            // set rising trigger flag
            MCAL_EXTI->EXTI_RTSR    |= (0x1 << pin_number);
            // set falling trigger flag
            MCAL_EXTI->EXTI_FTSR    |= (0x1 << pin_number);
            
            break;
        case MCAL_GPIO_RISING_EDGE :
            // set rising trigger flag
            MCAL_EXTI->EXTI_RTSR    |= (0x1 << pin_number);
            // clear falling trigger flag
            MCAL_EXTI->EXTI_FTSR    &= ~(0x1 << pin_number);

            break;
        case MCAL_GPIO_FALLING_EDGE :
            // clear rising trigger flag
            MCAL_EXTI->EXTI_RTSR    &= ~(0x1 << pin_number);
            // set falling trigger flag
            MCAL_EXTI->EXTI_FTSR    |= (0x1 << pin_number);

            break;
        default:
            return E_NOT_SUPPORTED;
            break;
    }

    if(trigger == MCAL_GPIO_NO_TRIGGER)
    {
        EXTI_mask &= ~(1 << pin_number);
        EXTI_cbs[pin_number] = 0UL;
        clear_interrupt_register(pin);
    }
    else
    {
        EXTI_cbs[pin_number] = callback;
        EXTI_mask |= (1 << pin_number);
        set_interrupt_register(pin);
    }

    return E_OK;
}

boolean pin_exists(MCAL_GPIO_pin_t pin)
{
    MCAL_GPIO_pin_t pin_port = MCAL_GPIO_get_port(pin);

    switch (pin_port)
    {
    case PORT_A:
    case PORT_B:
    case PORT_C:
    case PORT_D:
    case PORT_E:
    case PORT_H:
        break;
    default:
        return FALSE;
        break;
    }

    pin_port = MCAL_GPIO_get_pin_number(pin);

    if(pin_port > 0xF)
    {
        return FALSE;
    }

    return TRUE;
}


void set_interrupt_register(MCAL_GPIO_pin_t pin)
{
    uint8_t pin_number = (uint8_t) MCAL_GPIO_get_pin_number(pin);
    uint8_t shift = (pin_number & 0x3) << 2;
    uint8_t port_number = (uint8_t) MCAL_GPIO_get_port_number(pin);
    
    uint32_t temp = 0x0F ^ port_number;  
    temp = ! (temp << shift);
    
    MCAL_SYSCFG_PCLK_EN();
    MCAL_EXTI->EXTI_IMR |= (0x01 << pin_number);

    // enable interrupt line
    if(pin_number <4)
    {
        MCAL_SYSCFG->SYSCFG_EXTICR1 |= (port_number << shift);
        MCAL_SYSCFG->SYSCFG_EXTICR1 &= temp;
    }
    else if(pin_number <8)
    {
        MCAL_SYSCFG->SYSCFG_EXTICR2 |= (port_number << shift);
        MCAL_SYSCFG->SYSCFG_EXTICR2 &= temp;
    }
    else if(pin_number <12)
    {
        MCAL_SYSCFG->SYSCFG_EXTICR3 |= (port_number << shift);
        MCAL_SYSCFG->SYSCFG_EXTICR3 &= temp;
    }
    else
    {
        MCAL_SYSCFG->SYSCFG_EXTICR4 |= (port_number << shift);
        MCAL_SYSCFG->SYSCFG_EXTICR4 &= temp;
    }

    switch (pin_number)
    {
    case 0:
        stm32f4xx_enable_interrupt(MCAL_EXTI0_IRQ);
        break;
    case 1:
        stm32f4xx_enable_interrupt(MCAL_EXTI1_IRQ);
        break;
    case 2:
        stm32f4xx_enable_interrupt(MCAL_EXTI2_IRQ);
        break;
    case 3:
        stm32f4xx_enable_interrupt(MCAL_EXTI3_IRQ);
        break;
    case 4:
        stm32f4xx_enable_interrupt(MCAL_EXTI4_IRQ);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        stm32f4xx_enable_interrupt(MCAL_EXTI9_5_IRQ);
        break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        stm32f4xx_enable_interrupt(MCAL_EXTI15_10_IRQ);
        break;
    default:
        break;
    } 
}   

void clear_interrupt_register(MCAL_GPIO_pin_t pin)
{
    uint8_t pin_number = (uint8_t) MCAL_GPIO_get_pin_number(pin);
    
    MCAL_EXTI->EXTI_IMR &= ~(0x01 << pin_number);

    switch (pin_number)
    {
    case 0:
        stm32f4xx_disable_interrupt(MCAL_EXTI0_IRQ);
        break;
    case 1:
        stm32f4xx_disable_interrupt(MCAL_EXTI1_IRQ);
        break;
    case 2:
        stm32f4xx_disable_interrupt(MCAL_EXTI2_IRQ);
        break;
    case 3:
        stm32f4xx_disable_interrupt(MCAL_EXTI3_IRQ);
        break;
    case 4:
        stm32f4xx_disable_interrupt(MCAL_EXTI4_IRQ);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        stm32f4xx_disable_interrupt(MCAL_EXTI9_5_IRQ);
        break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        stm32f4xx_disable_interrupt(MCAL_EXTI15_10_IRQ);
        break;
    default:
        break;
    } 
}   

void EXTI0_Handler(void)
{
    MCAL_EXTI->EXTI_PR |= ( 0x01 );
    if(EXTI_mask & 1 )
    {
        EXTI_cbs[0]();
    }
    else
    {
        stm32f4xx_disable_interrupt(MCAL_EXTI0_IRQ);
    }    
}

void EXTI1_Handler(void)
{
    uint8_t id = ( 0x01 << 1)
    MCAL_EXTI->EXTI_PR |= id;
    if(EXTI_mask & id )
    {
        EXTI_cbs[1]();
    }
    else
    {
        stm32f4xx_disable_interrupt(MCAL_EXTI1_IRQ);
    }    
}

void EXTI2_Handler(void)
{
    uint8_t id = ( 0x01 << 2)
    MCAL_EXTI->EXTI_PR |= id;
    if(EXTI_mask & id )
    {
        EXTI_cbs[2]();
    }
    else
    {
        stm32f4xx_disable_interrupt(MCAL_EXTI2_IRQ);
    }    
}

void EXTI3_Handler(void)
{
    uint8_t id = ( 0x01 << 3)
    MCAL_EXTI->EXTI_PR |= id;
    if(EXTI_mask & id )
    {
        EXTI_cbs[3]();
    }
    else
    {
        stm32f4xx_disable_interrupt(MCAL_EXTI3_IRQ);
    }    
}

void EXTI4_Handler(void)
{
    uint8_t id = ( 0x01 << 4)
    MCAL_EXTI->EXTI_PR |= id;
    if(EXTI_mask & id )
    {
        EXTI_cbs[4]();
    }
    else
    {
        stm32f4xx_disable_interrupt(MCAL_EXTI4_IRQ);
    }    
}
#endif

