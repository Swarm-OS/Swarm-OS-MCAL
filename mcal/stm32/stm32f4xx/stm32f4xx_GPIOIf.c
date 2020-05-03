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

boolean pin_exists(GPIOIf_pin_t pin);
void set_interrupt_register(GPIOIf_pin_t pin);
void clear_interrupt_register(GPIOIf_pin_t pin);

std_return_type_t GPIOIf_init(GPIOIf_pin_t port)
{
    switch (GPIOIf_get_port(port))
    {
    case PORT_A:
        STM32F4xx_GPIOA_PCLK_EN();
        break;
    case PORT_B:
        STM32F4xx_GPIOB_PCLK_EN();
        break;
    case PORT_C:
        STM32F4xx_GPIOC_PCLK_EN();
        break;
    case PORT_D:
        STM32F4xx_GPIOD_PCLK_EN();
        break;
    case PORT_E:
        STM32F4xx_GPIOE_PCLK_EN();
        break;
    case PORT_H:
        STM32F4xx_GPIOH_PCLK_EN();
        break;
    default:
        return E_NOT_EXISTING;
        break;
    }
    return E_OK;
    
}

std_return_type_t GPIOIf_deinit(GPIOIf_pin_t port)
{
    switch (GPIOIf_get_port(port))
    {
    case PORT_A:
        STM32F4xx_GPIOA_PCLK_DI();
        break;
    case PORT_B:
        STM32F4xx_GPIOB_PCLK_DI();
        break;
    case PORT_C:
        STM32F4xx_GPIOC_PCLK_DI();
        break;
    case PORT_D:
        STM32F4xx_GPIOD_PCLK_DI();
        break;
    case PORT_E:
        STM32F4xx_GPIOE_PCLK_DI();
        break;
    case PORT_H:
        STM32F4xx_GPIOH_PCLK_DI();
        break;
    default:
        return E_NOT_EXISTING;
        break;
    }
    return E_OK;
}

std_return_type_t GPIOIf_config_pin(GPIOIf_pin_t pin, GPIOIf_pin_mode_t mode, GPIOIf_pullup_mode_t pullup)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_EXISTING;
    }

    STM32F4xx_GPIO_RegDef_t *port;
    
    uint8_t pin_number = (uint8_t) GPIOIf_get_pin_number(pin);
    
    switch (GPIOIf_get_port(pin))
    {
    case PORT_A:
        port = STM32F4xx_GPIOA;
        break;
    case PORT_B:
        port = STM32F4xx_GPIOB;
        break;
    case PORT_C:
        port = STM32F4xx_GPIOC;
        break;
    case PORT_D:
        port = STM32F4xx_GPIOD;
        break;
    case PORT_E:
        port = STM32F4xx_GPIOE;
        break;
    case PORT_H:
        port = STM32F4xx_GPIOH;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    switch (mode)
    {
    case GPIOIf_INPUT:
        // set pin mode
        port->MODER &= ~(0x3 << (pin_number <<1));
        break;
    case GPIOIf_INPUT_ANALOG   :
        // set pin mode
        port->MODER |= (0x3 << (pin_number <<1));
        break;
    case GPIOIf_OUTPUT         :
        // set pin mode
        port->MODER &= ~(0x2 << (pin_number <<1));
        port->MODER |=  (0x1 << (pin_number <<1));
        // output driver configuration - push-pull
        port->OTYPER &= ~(0x1 << (pin_number));
        break;
    case GPIOIf_OUTPUT_ANALOG  :
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    switch (pullup)
    {
    case GPIOIf_NO_PULLUP:
        // disable pullups/pulldowns
        port->PUPDR &= ~(0x3 << (pin_number <<1));
        break;
    case GPIOIf_PULLUP   :
        // set pullups
        port->PUPDR &= ~(0x2 << (pin_number <<1));
        port->PUPDR |=  (0x1 << (pin_number <<1));
        break;
    case GPIOIf_PULLDOWN  :
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

std_return_type_t GPIOIf_pin_set(GPIOIf_pin_t pin)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_EXISTING;
    }

    STM32F4xx_GPIO_RegDef_t *port;
    uint8_t pin_number = (uint8_t) GPIOIf_get_pin_number(pin);
    
    switch (GPIOIf_get_port(pin))
    {
    case PORT_A:
        port = STM32F4xx_GPIOA;
        break;
    case PORT_B:
        port = STM32F4xx_GPIOB;
        break;
    case PORT_C:
        port = STM32F4xx_GPIOC;
        break;
    case PORT_D:
        port = STM32F4xx_GPIOD;
        break;
    case PORT_E:
        port = STM32F4xx_GPIOE;
        break;
    case PORT_H:
        port = STM32F4xx_GPIOH;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }
   
    port->BSRR |= (1 << pin_number);
    return E_OK;
}

std_return_type_t GPIOIf_pin_clear(GPIOIf_pin_t pin)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_EXISTING;
    }

    STM32F4xx_GPIO_RegDef_t *port;
    uint8_t pin_number = (uint8_t) GPIOIf_get_pin_number(pin)+ 16;

    switch (GPIOIf_get_port(pin))
    {
    case PORT_A:
        port = STM32F4xx_GPIOA;
        break;
    case PORT_B:
        port = STM32F4xx_GPIOB;
        break;
    case PORT_C:
        port = STM32F4xx_GPIOC;
        break;
    case PORT_D:
        port = STM32F4xx_GPIOD;
        break;
    case PORT_E:
        port = STM32F4xx_GPIOE;
        break;
    case PORT_H:
        port = STM32F4xx_GPIOH;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    port->BSRR |= (1 << pin_number);
    return E_OK;
}

std_return_type_t GPIOIf_port_set(GPIOIf_pin_t pin, uint16_t value)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_EXISTING;
    }
    
    STM32F4xx_GPIO_RegDef_t *port;

    switch (GPIOIf_get_port(pin))
    {
    case PORT_A:
        port = STM32F4xx_GPIOA;
        break;
    case PORT_B:
        port = STM32F4xx_GPIOB;
        break;
    case PORT_C:
        port = STM32F4xx_GPIOC;
        break;
    case PORT_D:
        port = STM32F4xx_GPIOD;
        break;
    case PORT_E:
        port = STM32F4xx_GPIOE;
        break;
    case PORT_H:
        port = STM32F4xx_GPIOH;
        break;
    default:
        return E_NOT_SUPPORTED;
        break;
    }

    port->ODR |= value;
    port->ODR &= (((uint32_t)0xFFFF) << 16 )| value;
    

    return E_NOT_IMPLEMENTED;
}

std_return_type_t GPIOIf_pin_set_analog(GPIOIf_pin_t pin, uint16_t value)
{
    return E_NOT_SUPPORTED;
}

std_return_type_t GPIOIf_pin_iset_analog(GPIOIf_pin_t pin, uint16_t value)
{    
    return E_NOT_SUPPORTED;
}

boolean GPIOIf_pin_read(GPIOIf_pin_t pin)
{
    if(FALSE == pin_exists( pin))
    {
        return FALSE;
    }

    STM32F4xx_GPIO_RegDef_t *port;
    uint8_t pin_number = (uint8_t) GPIOIf_get_pin_number(pin);

    switch (GPIOIf_get_port(pin))
    {
    case PORT_A:
        port = STM32F4xx_GPIOA;
        break;
    case PORT_B:
        port = STM32F4xx_GPIOB;
        break;
    case PORT_C:
        port = STM32F4xx_GPIOC;
        break;
    case PORT_D:
        port = STM32F4xx_GPIOD;
        break;
    case PORT_E:
        port = STM32F4xx_GPIOE;
        break;
    case PORT_H:
        port = STM32F4xx_GPIOH;
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

std_return_type_t GPIOIf_port_read(GPIOIf_pin_t pin, uint16_t* buffer)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_EXISTING;
    }

    STM32F4xx_GPIO_RegDef_t *port;
    
    switch (GPIOIf_get_port(pin))
    {
    case PORT_A:
        port = STM32F4xx_GPIOA;
        break;
    case PORT_B:
        port = STM32F4xx_GPIOB;
        break;
    case PORT_C:
        port = STM32F4xx_GPIOC;
        break;
    case PORT_D:
        port = STM32F4xx_GPIOD;
        break;
    case PORT_E:
        port = STM32F4xx_GPIOE;
        break;
    case PORT_H:
        port = STM32F4xx_GPIOH;
        break;
    default:
        return FALSE;
        break;
    }
    *buffer = port->IDR & 0xFFFF;
    return E_OK;
}

std_return_type_t GPIOIf_input_trigger(GPIOIf_pin_t pin, GPIOIf_trigger_t trigger, void (*callback)(void))
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_EXISTING;
    }
    
    uint8_t pin_number = (uint8_t) GPIOIf_get_pin_number(pin);
    
    if(pin_number > 4)
    {
        return E_NOT_IMPLEMENTED;
    } 

    switch (trigger)
    {
        case GPIOIf_NO_TRIGGER:
            // clear rising trigger flag
            STM32F4xx_EXTI->EXTI_RTSR    &= ~(0x1 << pin_number);
            // clear falling trigger flag
            STM32F4xx_EXTI->EXTI_FTSR    &= ~(0x1 << pin_number);

            break;
        case GPIOIf_BOTH_EDGES :
            // set rising trigger flag
            STM32F4xx_EXTI->EXTI_RTSR    |= (0x1 << pin_number);
            // set falling trigger flag
            STM32F4xx_EXTI->EXTI_FTSR    |= (0x1 << pin_number);
            
            break;
        case GPIOIf_RISING_EDGE :
            // set rising trigger flag
            STM32F4xx_EXTI->EXTI_RTSR    |= (0x1 << pin_number);
            // clear falling trigger flag
            STM32F4xx_EXTI->EXTI_FTSR    &= ~(0x1 << pin_number);

            break;
        case GPIOIf_FALLING_EDGE :
            // clear rising trigger flag
            STM32F4xx_EXTI->EXTI_RTSR    &= ~(0x1 << pin_number);
            // set falling trigger flag
            STM32F4xx_EXTI->EXTI_FTSR    |= (0x1 << pin_number);

            break;
        default:
            return E_NOT_SUPPORTED;
            break;
    }

    if(trigger == GPIOIf_NO_TRIGGER)
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

boolean pin_exists(GPIOIf_pin_t pin)
{
    GPIOIf_pin_t pin_port = GPIOIf_get_port(pin);

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

    pin_port = GPIOIf_get_pin_number(pin);

    if(pin_port > 0xF)
    {
        return FALSE;
    }

    return TRUE;
}


void set_interrupt_register(GPIOIf_pin_t pin)
{
    uint8_t pin_number = (uint8_t) GPIOIf_get_pin_number(pin);
    uint8_t shift = (pin_number & 0x3) << 2;
    uint8_t port_number = (uint8_t) GPIOIf_get_port_number(pin);
    
    uint32_t temp = 0x0F ^ port_number;  
    temp = ! (temp << shift);
    
    STM32F4xx_SYSCFG_PCLK_EN();
    STM32F4xx_EXTI->EXTI_IMR |= (0x01 << pin_number);

    // enable interrupt line
    if(pin_number <4)
    {
        STM32F4xx_SYSCFG->SYSCFG_EXTICR1 |= (port_number << shift);
        STM32F4xx_SYSCFG->SYSCFG_EXTICR1 &= temp;
    }
    else if(pin_number <8)
    {
        STM32F4xx_SYSCFG->SYSCFG_EXTICR2 |= (port_number << shift);
        STM32F4xx_SYSCFG->SYSCFG_EXTICR2 &= temp;
    }
    else if(pin_number <12)
    {
        STM32F4xx_SYSCFG->SYSCFG_EXTICR3 |= (port_number << shift);
        STM32F4xx_SYSCFG->SYSCFG_EXTICR3 &= temp;
    }
    else
    {
        STM32F4xx_SYSCFG->SYSCFG_EXTICR4 |= (port_number << shift);
        STM32F4xx_SYSCFG->SYSCFG_EXTICR4 &= temp;
    }

    switch (pin_number)
    {
    case 0:
        stm32f4xx_enable_interrupt(STM32F4xx_EXTI0_IRQ);
        break;
    case 1:
        stm32f4xx_enable_interrupt(STM32F4xx_EXTI1_IRQ);
        break;
    case 2:
        stm32f4xx_enable_interrupt(STM32F4xx_EXTI2_IRQ);
        break;
    case 3:
        stm32f4xx_enable_interrupt(STM32F4xx_EXTI3_IRQ);
        break;
    case 4:
        stm32f4xx_enable_interrupt(STM32F4xx_EXTI4_IRQ);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        stm32f4xx_enable_interrupt(STM32F4xx_EXTI9_5_IRQ);
        break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        stm32f4xx_enable_interrupt(STM32F4xx_EXTI15_10_IRQ);
        break;
    default:
        break;
    } 
}   

void clear_interrupt_register(GPIOIf_pin_t pin)
{
    uint8_t pin_number = (uint8_t) GPIOIf_get_pin_number(pin);
    
    STM32F4xx_EXTI->EXTI_IMR &= ~(0x01 << pin_number);

    switch (pin_number)
    {
    case 0:
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI0_IRQ);
        break;
    case 1:
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI1_IRQ);
        break;
    case 2:
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI2_IRQ);
        break;
    case 3:
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI3_IRQ);
        break;
    case 4:
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI4_IRQ);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI9_5_IRQ);
        break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI15_10_IRQ);
        break;
    default:
        break;
    } 
}   

void EXTI0_Handler(void)
{
    STM32F4xx_EXTI->EXTI_PR |= ( 0x01 );
    if(EXTI_mask & 1 )
    {
        EXTI_cbs[0]();
    }
    else
    {
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI0_IRQ);
    }    
}

void EXTI1_Handler(void)
{
    uint8_t id = ( 0x01 << 1)
    STM32F4xx_EXTI->EXTI_PR |= id;
    if(EXTI_mask & id )
    {
        EXTI_cbs[1]();
    }
    else
    {
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI1_IRQ);
    }    
}

void EXTI2_Handler(void)
{
    uint8_t id = ( 0x01 << 2)
    STM32F4xx_EXTI->EXTI_PR |= id;
    if(EXTI_mask & id )
    {
        EXTI_cbs[2]();
    }
    else
    {
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI2_IRQ);
    }    
}

void EXTI3_Handler(void)
{
    uint8_t id = ( 0x01 << 3)
    STM32F4xx_EXTI->EXTI_PR |= id;
    if(EXTI_mask & id )
    {
        EXTI_cbs[3]();
    }
    else
    {
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI3_IRQ);
    }    
}

void EXTI4_Handler(void)
{
    uint8_t id = ( 0x01 << 4)
    STM32F4xx_EXTI->EXTI_PR |= id;
    if(EXTI_mask & id )
    {
        EXTI_cbs[4]();
    }
    else
    {
        stm32f4xx_disable_interrupt(STM32F4xx_EXTI4_IRQ);
    }    
}
#endif

