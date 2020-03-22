#if defined(ATMEGA328)

#ifndef MCAL_ATMEGA328_H
#define MCAL_ATMEGA328_H

#include <gpio.h>
#include <datatypes.h>
#include <mcal/atmel/atmega328/pins.h>

#include <avr/io.h>

std_return_type_t gpio_config_pin(gpio_pin_t pin, gpio_pin_mode_t mode)
{
    uint8_t port = gpio_get_port(pin);
    uint8_t pin_num = 1 << gpio_get_pin_numer(pin);

    if( mode == GPIO_INPUT_FLOATING || mode == GPIO_OUTPUT_ANALOG)
    {
        return E_NOT_SUPPORTED;
    }
    elif(port == gpio_get_port(PORT_B))
    {
        switch(mode):
        {
            case GPIO_INPUT_PULLUP:
                {
                    PORTB |= pin_num; 
                    DDRB &= ~(pin_num);
                    break;
                }
            case GPIO_INPUT: 
                {
                    PORTB &= ~(pin_num);
                    DDRB &= ~(pin_num);
                    break;
                }
            case GPIO_INPUT_ANALOG:
                {
                    return E_NOT_IMPLEMENTED;
                }
            case GPIO_OUTPUT:
                {
                    DDRB |= pin_num;
                    break;
                }
            default: break
        }
    }
    elif(port == gpio_get_port(PORT_C))
    {
        switch(mode):
        {
            case GPIO_INPUT_PULLUP:
                {
                    PORTC |= pin_num; 
                    DDRC &= ~(pin_num);
                    break;
                }
            case GPIO_INPUT: 
                {
                    PORTC &= ~(pin_num);
                    DDRC &= ~(pin_num);
                    break;
                }
            case GPIO_INPUT_ANALOG:
                {
                    return E_NOT_IMPLEMENTED;
                }
            case GPIO_OUTPUT:
                {
                    DDRC |= pin_num;
                    break;
                }
            default: break
        }
    }
    elif(port == gpio_get_port(PORT_D))
    {
        switch(mode):
        {
            case GPIO_INPUT_PULLUP:
                {
                    PORTD |= pin_num; 
                    DDRD &= ~(pin_num);
                    break;
                }
            case GPIO_INPUT: 
                {
                    PORTD &= ~(pin_num);
                    DDRD &= ~(pin_num);
                    break;
                }
            case GPIO_INPUT_ANALOG:
                {
                    return E_NOT_IMPLEMENTED;
                }
            case GPIO_OUTPUT:
                {
                    DDRD |= pin_num;
                    break;
                }
            default: break
        }
    }

    return E_OK;
}

std_return_type_t gpio_enable_sampling(gpio_pin_t pin, uint16_t interval, void (*callback)(uint16_t))
{
    return E_NOT_IMPLEMENTED;
}

std_return_type_t gpio_pin_set(gpio_pin_t pin)
{
    uint8_t port = gpio_get_port(pin);
    uint8_t pin_num = 1 << gpio_get_pin_numer(pin);

   if(port == gpio_get_port(PORT_B))
    {
        PORTB |= pin_num; 
    }
    elif(port == gpio_get_port(PORT_C))
    {
        PORTC |= pin_num; 
    }
    elif(port == gpio_get_port(PORT_D))
    {
        PORTD |= pin_num; 
    }
    return E_OK;
}

std_return_type_t gpio_pin_set_analog(gpio_pin_t pin, uint16_t value)
{
    return E_NOT_IMPLEMENTED;
}

std_return_type_t gpio_pin_iset_analog(gpio_pin_t pin, uint16_t value)
{
    return E_NOT_IMPLEMENTED;
}

std_return_type_t gpio_pin_clear(gpio_pin_t pin)
{
    uint8_t port = gpio_get_port(pin);
    uint8_t pin_num = 1 << gpio_get_pin_numer(pin);

    if(port == gpio_get_port(PORT_B))
    {
        PORTB &= ~(pin_num) 
    }
    elif(port == gpio_get_port(PORT_C))
    {
        PORTC &= ~(pin_num)
    }
    elif(port == gpio_get_port(PORT_D))
    {
        PORTD &= ~(pin_num)
    }
    return E_OK;
}

boolean gpio_pin_read(gpio_pin_t pin)
{
    uint8_t port = gpio_get_port(pin);
    uint8_t pin_num = gpio_get_pin_numer(pin);
    uint8_t pin_value = 0

    if(port == gpio_get_port(PORT_B))
    {
        pin_value = PINB;
    }
    elif(port == gpio_get_port(PORT_C))
    {
        pin_value = PINC;
    }
    elif(port == gpio_get_port(PORT_D))
    {
        pin_value = PIND;
    }

    pin_value = pin_value >> pin_num;
    pin_value &= 0x01;

    if(pin_value)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

uint16_t gpio_pin_read_analog(gpio_pin_t pin)
{
    return E_NOT_IMPLEMENTED;
}

std_return_type_t gpio_pin_iread_analog(gpio_pin_t pin, void (*callback)(uint16_t))
{
    return E_NOT_IMPLEMENTED;
}

uint16_t gpio_pin_last_sample(gpio_pin_t pin)
{
    return E_NOT_IMPLEMENTED;
}


#endif
#endif
