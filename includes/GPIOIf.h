/**
 * @file GPIOPIf.h
 * @author Christoph Lehr
 * @date 4 Aug 2019
 * @brief File containing API for accessing GPIO's
 *
 * This file specifies a generic API which shall be used to 
 * interact with the GPIO's of different Microcontrollers.
 * This API handles digital input/outputs. For analog inputs
 * check ADC.h. 
 */

#ifndef GPIOIF_H
#define GPIOIF_H

#include <stdint.h>
#include <datatypes.h>

#define GPIOIf_get_port(id) (id | 0x00FF)
#define GPIOIf_get_port_number(id) ((id >> 8) & 0xFF)
#define GPIOIf_get_pin_number(id) (id & 0x00FF)
#define GPIOIf_is_port(id) ((id & 0x00FF) == 0x00FF ? TRUE : FALSE)

/**
 * @brief Pin identifier
 *
 * Uses the high byte to identify the Port and
 * the low byte to identfy the Pin of the port.
 */
typedef uint16_t GPIOIf_pin_t;

/**
 * @brief Definition of different pin modes supported.
 *
 * GPIO_INPUT          : use pin as input pin
 * GPIO_INPUT_PULLUP   : use pin as input pin with active pullup
 * GPIO_INPUT_ANALOG   : use pin as analog input
 * GPIO_OUTPUT         : use pin as digital output
 * GPIO_OUTPUT_ANALOG  : use pin as analog output
 */
typedef enum _GPIOIf_pin_mode { 
    GPIOIf_INPUT            = 0x00,
    GPIOIf_INPUT_ANALOG     = 0x01,
    GPIOIf_OUTPUT           = 0x10,
    GPIOIf_OUTPUT_ANALOG    = 0x11,
    GPIOIf_ALTERNAT_FN      = 0x20,
} GPIOIf_pin_mode_t;

typedef enum _GPIOIf_pullup_mode{
    GPIOIf_NO_PULLUP        = 0x00,
    GPIOIf_PULLUP           = 0x01,
    GPIOIf_PULLDOWN         = 0x02,
} GPIOIf_pullup_mode_t;

typedef enum __GPIOIf_output_mode
{
    GPIOIF_OUTPUT_PUSH_PULL =    0x01,
    GPIOIF_OUTPUT_OPEN_DRAIN=    0x02,
}GPIOIf_output_mode_t;

typedef enum
{
    GPIOIf_NO_TRIGGER    = 0x00,
    GPIOIf_FALLING_EDGE  = 0x01,
    GPIOIf_RISING_EDGE   = 0x02,
    GPIOIf_BOTH_EDGES    = 0x03,
} GPIOIf_trigger_t;

typedef struct __GPIOIf_pin_config
{ 
    void (*callback)(void);
    GPIOIf_pin_t pin;
    GPIOIf_pin_mode_t pin_mode;
    uint8_t alternate_function;
    GPIOIf_pullup_mode_t pullup_mode;
    GPIOIf_output_mode_t output_mode;
    GPIOIf_trigger_t trigger;
} GPIOIf_pin_config_t;


/**
 * @brief Initialize GPIO Port
 *  
 * This function initilializes the given GPIO Port.
 * 
 * @param  GPIOIf_pin_t port        : GPIO port to be initialized
 * @return std_return_type_t status : If the given port does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t GPIOIf_init(GPIOIf_pin_t port);

/**
 * @brief Deinitialize GPIO Port
 *  
 * This function deinitilializes the given GPIO Port, i.e. resets all reqisters.
 * 
 * @param  GPIOIf_pin_t port        : GPIO port to be deinitialized
 * @return std_return_type_t status : If the given port does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t GPIOIf_deinit(GPIOIf_pin_t port);

/**
 * @brief Configuration of a pin
 *  
 * This function configures a given pin based on a desired mode.
 * 
 * @param  GPIOIf_pin_t pin         : Which pin shall be configured
 * @param  GPIOIf_pin_mode_t mode   : Which mode shall be used
 * @return std_return_type_t status : If the mode is not supported on the pin
 *                                    the function return E_NOT_SUPPORTED. If
 *                                    the functionality is not implemented on 
 *                                    the function returns E_NOT_IMPLEMENTED.
 *                                    If the pin does not exist the function
 *                                    returns E_NOT_EXISTING. Else it returns 
 *                                    E_OK.
 */
std_return_type_t GPIOIf_config_pin(GPIOIf_pin_config_t *cfg);


/**
 * @brief Set GPIO pin
 *  
 * Sets the given GPIO pin/port.
 * 
 * @param  GPIOIf_pin_t pin         : Which pin shall be port
 * @return std_return_type_t status : If the pin is not available the
 *                                    function returns E_NOT_EXISTING.
 *                                    If the function is not supported
 *                                    on the port the function returns 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t GPIOIf_pin_set(GPIOIf_pin_t pin);

/**
 * @brief Clears GPIO pin
 *  
 * Clears the given GPIO pin/port.
 * 
 * @param  GPIOIf_pin_t pin         : Which pin shall be cleared
 * @return std_return_type_t status : If the pin is not available the 
 *                                    function retruns E_NOT_EXISTING. If
 *                                    the functionallity is not supported
 *                                    by the pin the function returns 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t GPIOIf_pin_clear(GPIOIf_pin_t pin);

/**
 * @brief Sets GPIO port to value
 *  
 * Sets a GPIO port to given value
 * 
 * @param  GPIOIf_pin_t port        : Which port shall be set
 * @param  uint16_t value           : Value to be set
 * @return std_return_type_t status : If the port is not available the 
 *                                    function returns E_NOT_EXISTING.
 *                                    If the value is out of range the 
 *                                    function returns E_VALUE_ERR. 
 *                                    Else it returns E_OK.
 */
std_return_type_t GPIOIf_port_set(GPIOIf_pin_t pin, uint16_t value);

/**
 * @brief Sets an analog value of a pin
 *  
 * This function sets an anlog value of the pin and waits until the value is 
 * set.
 * 
 * @param  GPIOIf_pin_t pin         : Which pin shall be configured
 * @param  uint16_t value           : Analog value to be set.
 * @return std_return_type_t status : If the pin does not exist the functions
 *                                    returns E_NOT_EXISTING. If the mode is 
 *                                    not supported on the pin the function 
 *                                    returns E_NOT_SUPPORTED. If the 
 *                                    functionality is not implemented the
 *                                    function returns E_NOT_IMPLEMENTED.
 *                                    If the value is out of range the function
 *                                    returns E_VALUE_ERR. Else it returns E_OK.
 */
std_return_type_t GPIOIf_pin_set_analog(GPIOIf_pin_t pin, uint16_t value);

/**
 * @brief Sets an analog value of a pin.
 *  
 * This function sets an anlog value of the pin and returns directly.
 * 
 * @param  GPIOIf_pin_t pin         : Which pin shall be configured
 * @param  uint16_t value           : Analog value to be set.
 * @return std_return_type_t status : If the pin does not exist the functions
 *                                    returns E_NOT_EXISTING. If the mode is 
 *                                    not supported on the pin the function 
 *                                    returns E_NOT_SUPPORTED. If the
 *                                    functionality is not implemented the
 *                                    function returns E_NOT_IMPLEMENTED.If 
 *                                    the value is out of range the function
 *                                    returns E_VALUE_ERR. Else it returns E_OK.
 */
std_return_type_t GPIOIf_pin_iset_analog(GPIOIf_pin_t pin, uint16_t value);

/**
 * @brief Reads the state of a pin
 *  
 * This function reads the current state of a pin. 
 * 
 * @param  GPIOIf_pin_t pin         : Which pin shall be configured
 * @return boolean status           : Digital value of the pin. If the pin
 *                                    does not exist, FALSE is returned.
 */
boolean GPIOIf_pin_read(GPIOIf_pin_t pin);

/**
 * @brief Reads the state of a port
 *  
 * This function reads the current state of a whole port. 
 * 
 * @param  GPIOIf_pin_t pin         : Which pin shall be configured
 * @return boolean status           : Pin values of the whole port. 
 */
std_return_type_t GPIOIf_port_read(GPIOIf_pin_t pin, uint16_t* buffer);

#endif