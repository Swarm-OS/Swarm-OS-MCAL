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

#include "../../../includes/datatypes.h"
#include "../../../includes/gpio.h"
#include "stm32f411.h"
#include "stm32f4xx_pins.h"
#include "stm32f4xx_gpio.h"

boolean pin_exists(MCAL_GPIO_pin_t pin);

std_return_type_t MCAL_GPIO_init(MCAL_GPIO_pin_t port)
{
    switch (port)
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
    switch (port)
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

std_return_type_t MCAL_GPIO_config_pin(MCAL_GPIO_pin_t pin, MCAL_GPIO_pin_mode_t mode)
{
    uint8_t temp;
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }

    MCAL_GPIO_RegDef_t *port;

    switch (pin)
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

    temp = (uint8_t) MCAL_GPIO_get_pin_numer(pin);

    switch (mode)
    {
    case GPIO_INPUT:
    case GPIO_INPUT_FLOATING :
        // set pin mode
        port->MODER &= ~(0x3 << (temp <<1));
        // set pullup/pulldowns
        port->PUPDR &= ~(0x3 << (temp <<1));
        break;
    case GPIO_INPUT_PULLUP   :
        // set pin mode
        port->MODER &= ~(0x3 << (temp <<1));
        // set pullup/pulldowns
        port->PUPDR &= ~(0x2 << (temp <<1));
        port->PUPDR |=  (0x1 << (temp <<1));
        break;
    case GPIO_INPUT_PULDOWN  :
        // set pin mode
        port->MODER &= ~(0x3 << (temp <<1));
        // set pullup/pulldowns
        port->PUPDR &= ~(0x1 << (temp <<1));
        port->PUPDR |=  (0x2 << (temp <<1));
        break;
    case GPIO_INPUT_ANALOG   :
        // set pin mode
        port->MODER |= (0x3 << (temp <<1));
        break;
    case GPIO_OUTPUT         :
        // set pin mode
        port->MODER &= ~(0x2 << (temp <<1));
        port->MODER |=  (0x1 << (temp <<1));
        // set pullup/pulldowns
        port->PUPDR &= ~(0x3 << (temp <<1));
        // output driver configuration - push-pull
        port->OTYPER &= ~(0x1 << (temp));
        break;
    case GPIO_OUTPUT_PULLUP  :
        // set pin mode
        port->MODER &= ~(0x2 << (temp <<1));
        port->MODER |=  (0x1 << (temp <<1));
        // set pullup/pulldowns
        port->PUPDR &= ~(0x2 << (temp <<1));
        port->PUPDR |=  (0x1 << (temp <<1));
        // output driver configuration - push-pull
        port->OTYPER &= ~(0x1 << (temp));
        break;
    case GPIO_OUTPUT_PULLDOWN:
        // set pin mode
        port->MODER &= ~(0x2 << (temp <<1));
        port->MODER |=  (0x1 << (temp <<1));
        // set pullup/pulldowns
        port->PUPDR &= ~(0x1 << (temp <<1));
        port->PUPDR |=  (0x2 << (temp <<1));
        // output driver configuration - push-pull
        port->OTYPER &= ~(0x1 << (temp));
        break;
    case GPIO_OUTPUT_OPEN_DRAIN:
    case GPIO_INPUT_ITR      :
    case GPIO_INPUT_ITR_RISE :
    case GPIO_INPUT_ITR_FALL :
        return E_NOT_IMPLEMENTED;
        break;
    case GPIO_OUTPUT_ANALOG  :
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
    uint8_t shift = (uint8_t) MCAL_GPIO_get_pin_numer(pin);

    switch (pin)
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

    port->ODR |= (1 << shift);

    return E_OK;
}

std_return_type_t MCAL_GPIO_pin_clear(MCAL_GPIO_pin_t pin)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }

    MCAL_GPIO_RegDef_t *port;
    uint8_t shift = (uint8_t) MCAL_GPIO_get_pin_numer(pin);

    switch (pin)
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

    port->ODR &= ~(1 << shift);

    return E_OK;
}

std_return_type_t MCAL_GPIO_port_set(MCAL_GPIO_pin_t pin, uint16_t value)
{
    if(FALSE == pin_exists( pin))
    {
        return E_NOT_SUPPORTED;
    }
    
    MCAL_GPIO_RegDef_t *port;

    switch (pin)
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
    uint8_t shift = (uint8_t) MCAL_GPIO_get_pin_numer(pin);

    switch (pin)
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

    if(port->IDR & (1 << shift))
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
    
    switch (pin)
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
    
    return port->IDR & 0xFFFF;
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

    pin_port = MCAL_GPIO_get_pin_numer(pin);

    if(pin_port > 0xF)
    {
        return FALSE;
    }

    return TRUE;
}
#endif

