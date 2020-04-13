/**
 * @file gpio.h
 * @author Christoph Lehr
 * @date 4 Aug 2019
 * @brief File containing API for accessing GPIO's
 *
 * This file specifies a generic API which shall be used to 
 * interact with the GPIO's of different Microcontrollers.
 * This API handles digital input/outputs. For analog inputs
 * check ADC.h. 
 */

#ifndef MCAL_GPIO_H
#define MCAL_GPIO_H

#include <stdint.h>
#include <datatypes.h>

#define MCAL_GPIO_get_port(id) (id | 0x00FF)
#define MCAL_GPIO_get_port_number(id) ((id >> 8) & 0xFF)
#define MCAL_GPIO_get_pin_number(id) (id & 0x00FF)
#define MCAL_GPIO_is_port(id) ((id & 0x00FF) == 0x00FF ? TRUE : FALSE)

/**
 * @brief Pin identifier
 *
 * Uses the high byte to identify the Port and
 * the low byte to identfy the Pin of the port.
 */
typedef uint16_t MCAL_GPIO_pin_t;

/**
 * @brief Definition of different pin modes supported.
 *
 * GPIO_INPUT          : use pin as input pin
 * GPIO_INPUT_PULLUP   : use pin as input pin with active pullup
 * GPIO_INPUT_ANALOG   : use pin as analog input
 * GPIO_OUTPUT         : use pin as digital output
 * GPIO_OUTPUT_ANALOG  : use pin as analog output
 */
typedef enum _MCAL_GPIO_pin_mode { 
    MCAL_GPIO_INPUT          = 0x00,
    MCAL_GPIO_INPUT_ANALOG   = 0x01,
    MCAL_GPIO_OUTPUT         = 0x10,
    MCAL_GPIO_OUTPUT_ANALOG  = 0x11,
    MCAL_GPIO_INPUT_ITR_BOTH=5,
    MCAL_GPIO_INPUT_ITR_RISE=6,
    MCAL_GPIO_INPUT_ITR_FALL=7,
} MCAL_GPIO_pin_mode_t;

typedef enum _MCAL_GPIO_pullup_mode{
    MCAL_GPIO_NO_PULLUP     = 0x00,
    MCAL_GPIO_PULLUP        = 0x01,
    MCAL_GPIO_PULLDOWN      = 0x02,
} MCAL_GPIO_pullup_mode_t;

typedef enum
{
    MCAL_GPIO_NO_TRIGGER    = 0x00,
    MCAL_GPIO_FALLING_EDGE  = 0x01,
    MCAL_GPIO_RISING_EDGE   = 0x02,
    MCAL_GPIO_BOTH_EDGES    = 0x03,
    
} MCAL_GPIO_trigger_t;

/**
 * @brief Initialize GPIO Port
 *  
 * This function initilializes the given GPIO Port.
 * If the given port does not exist on the microcontroller, the function
 * return E_NOT_SUPPORTED. 
 * Else it returns E_OK.
 * 
 * @param  MCAL_GPIO_pin_t port     : GPIO port to be initialized
 * @return std_return_type_t status : If the given port does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t MCAL_GPIO_init(MCAL_GPIO_pin_t port);

/**
 * @brief Deinitialize GPIO Port
 *  
 * This function deinitilializes the given GPIO Port, i.e. resets all reqisters.
 * 
 * @param  MCAL_GPIO_pin_t port          : GPIO port to be initialized
 * @return std_return_type_t status : If the given port does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t MCAL_GPIO_deinit(MCAL_GPIO_pin_t port);

/**
 * @brief Configuration of a pin
 *  
 * This function configures a given pin based on a desired mode.
 * 
 * @param  MCAL_GPIO_pin_t pin      : Which pin shall be configured
 * @param  MCAL_GPIO_pin_mode_t mode: Which mode shall be used
 * @return std_return_type_t status : If the mode is not supported on the pin
 *                                    the function return E_NOT_SUPPORTED. If
 *                                    the functionality is not implemented on 
 *                                    the function returns E_NOT_IMPLEMENTED.
 *                                    Else it returns E_OK.
 */
std_return_type_t MCAL_GPIO_config_pin(MCAL_GPIO_pin_t pin, 
                                       MCAL_GPIO_pin_mode_t mode, 
                                       MCAL_GPIO_pullup_mode_t pullup);

/**
 * @brief Set GPIO pin
 *  
 * Sets the given GPIO pin/port.
 * 
 * @param  MCAL_GPIO_pin_t pin      : Which pin shall be port
 * @return std_return_type_t status : If the pin is not available is not
 *                                    available the function return 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t MCAL_GPIO_pin_set(MCAL_GPIO_pin_t pin);

/**
 * @brief Clears GPIO pin
 *  
 * Clears the given GPIO pin/port.
 * 
 * @param  MCAL_GPIO_pin_t pin      : Which pin shall be cleared
 * @return std_return_type_t status : If the pin is not available is not
 *                                    available the function return 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t MCAL_GPIO_pin_clear(MCAL_GPIO_pin_t pin);

/**
 * @brief Sets GPIO port to value
 *  
 * Sets a GPIO port to given value
 * 
 * @param  MCAL_GPIO_pin_t port     : Which port shall be set
 * @param  uint16_t value           : Value to be set
 * @return std_return_type_t status : If the pin is not available is not
 *                                    available the function return 
 *                                    E_NOT_SUPPORTED. If the value is out
 *                                    of range the function returns 
 *                                    E_VALUE_ERR. Else it returns E_OK.
 */
std_return_type_t MCAL_GPIO_port_set(MCAL_GPIO_pin_t pin, uint16_t value);

/**
 * @brief Sets an analog value of a pin
 *  
 * This function sets an anlog value of the pin and waits until the value is 
 * set.
 * 
 * @param  MCAL_GPIO_pin_t pin      : Which pin shall be configured
 * @param  uint16_t value           : Analog value to be set.
 * @return std_return_type_t status : If the mode is not supported on the pin
 *                                    the function return E_NOT_SUPPORTED. If
 *                                    the functionality is not implemented  
 *                                    the function returns E_NOT_IMPLEMENTED.
 *                                    If the value is out of range the function
 *                                    returns E_VALUE_ERR. Else it returns E_OK.
 */
std_return_type_t MCAL_GPIO_pin_set_analog(MCAL_GPIO_pin_t pin, uint16_t value);

/**
 * @brief Sets an analog value of a pin.
 *  
 * This function sets an anlog value of the pin and returns directly.
 * 
 * @param  MCAL_GPIO_pin_t pin      : Which pin shall be configured
 * @param  uint16_t value           : Analog value to be set.
 * @return std_return_type_t status : If the mode is not supported on the pin
 *                                    the function return E_NOT_SUPPORTED. If
 *                                    the functionality is not implemented  
 *                                    the function returns E_NOT_IMPLEMENTED.
 *                                    If the value is out of range the function
 *                                    returns E_VALUE_ERR. Else it returns E_OK.
 */
std_return_type_t MCAL_GPIO_pin_iset_analog(MCAL_GPIO_pin_t pin, uint16_t value);

/**
 * @brief Reads the state of a pin
 *  
 * This function reads the current state of a pin. 
 * 
 * @param  MCAL_GPIO_pin_t pin      : Which pin shall be configured
 * @return boolean status           : Digital value of the pin. If the pin
 *                                    does not exist, FALSE is returned.
 */
boolean MCAL_GPIO_pin_read(MCAL_GPIO_pin_t pin);

/**
 * @brief Reads the state of a port
 *  
 * This function reads the current state of a whole port. 
 * 
 * @param  MCAL_GPIO_pin_t pin      : Which pin shall be configured
 * @return boolean status           : Pin values of the whole port. 
 */
std_return_type_t MCAL_GPIO_port_read(MCAL_GPIO_pin_t pin, uint16_t* buffer);

/**
 * @brief Sets trigger options of a specific pin
 *  
 * This function sets interrupts according to the given trigger condition.
 * Please check your processor manual which pins support triggering interrupts
 * on edge changes. 
 * 
 * @param  MCAL_GPIO_pin_t pin      : Which pin shall be configured
 * @param  MCAL_GPIO_trigger_t trigger: Trigger condition
 * @param  void (*callback)(void)   : callback function which shall be called
 *                                    after the trigger was acitvated. If 
 *                                    MCAL_GPIO_NO_TRIGGER is used for tigger
 *                                    condition, the callback argument will be
 *                                    ignored. 
 * @return std_return_type_t status : If the pin does not exist or does not
 *                                    support edge detection, E_NOT_SUPPORTED
 *                                    will be returned. 
 */
std_return_type_t MCAL_GPIO_input_trigger(MCAL_GPIO_pin_t pin, MCAL_GPIO_trigger_t trigger, void (*callback)(void));

#endif