/**
 * @file ADC.h
 * @author Christoph Lehr
 * @date 22 Mar 2020
 * @brief File containing API for accessing ADC
 *
 * This file specifies a generic API which shall be used to 
 * interact with the ADC's of different Microcontrollers.
 */

#ifndef MCAL_ADC_H
#define MCAL_ADC_H

#include <stdint.h>
#include <datatypes.h>

typedef struct 
{
    // byte 1
    uint8_t ADC_no              :2; // 64 Channels per ADC
    uint8_t ADC_channel         :6; // 64 Channels per ADC
} MCAL_ADC_Channel_t;

typedef struct 
{
    // byte 1
    uint8_t ADC_no              :2; // 64 Channels per ADC
    boolean enable_ADC          :1; // Set to enable ADC Peripheral
    boolean left_align          :1; // Set if left alignmet, cleared right alignment
    ADC_prescaler_t prescaler   :4; // prescaler of ADC Clock

    // byte 2
    ADC_prescaler_t resolution  :4; // Resolution of ADC result
    ADC_sampling_t sampling_cyc :4; // Number of Cycles for sampling    
} MCAL_ADC_config_t;

typedef enum MCAL_ADC_prescaler { 
    ADC_PRESCALER_1     = 0x00, 
    ADC_PRESCALER_2     = 0x01, 
    ADC_PRESCALER_4     = 0x02, 
    ADC_PRESCALER_6     = 0x03, 
    ADC_PRESCALER_8     = 0x04, 
    ADC_PRESCALER_16    = 0x05,
    ADC_PRESCALER_32    = 0x06,
    ADC_PRESCALER_64    = 0x07,
    ADC_PRESCALER_128   = 0x08,
} MCAL_ADC_prescaler_t;

typedef enum MCAL_ADC_resolution { 
    ADC_RES_12  = 0x00, 
    ADC_RES_10  = 0x01, 
    ADC_RES_8   = 0x02, 
    ADC_RES_6   = 0x03, 
} MCAL_ADC_prescaler_t;

typedef enum MCAL_ADC_sampling { 
    ADC_SAMPLING_3_CYCLES       = 0x00, 
    ADC_SAMPLING_15_CYCLES      = 0x01, 
    ADC_SAMPLING_28_CYCLES      = 0x02, 
    ADC_SAMPLING_56_CYCLES      = 0x03, 
    ADC_SAMPLING_84_CYCLES      = 0x00, 
    ADC_SAMPLING_112_CYCLES     = 0x01, 
    ADC_SAMPLING_144_CYCLES     = 0x02, 
    ADC_SAMPLING_480_CYCLES     = 0x03, 
} MCAL_ADC_sampling_t;

/**
 * @brief Initialize ADC
 *  
 * This function initilializes the given ADC. If the MCU only has a single 
 * ADC, the ADC number is ignored. 
 * Else it returns E_OK.
 * 
 * @param  uint8_t ADC_no           : ADC to be initialized
 * @return std_return_type_t status : If the given ADC does not exist on the 
 *                                    microcontroller, the function returns
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t MCAL_ADC_init(uint8_t ADC_no);

/**
 * @brief Deinitialize ADC
 *  
 * This function deinitilializes the given ADC. If the MCU only has a single 
 * ADC, the ADC number is ignored. 
 * 
 * @param  uint8_t ADC_no           : ADC to be deinitialized
 * @return std_return_type_t status : If the given ADC does not exist on the 
 *                                    microcontroller, the function returns
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t MCAL_ADC_deinit(uint8_t ADC_no);

/**
 * @brief Configuration of ADC
 *  
 * This function configures a given ADC. If the MCU only has a single 
 * ADC, the ADC number is ignored. If the MCU does not provide setting
 * resolution, the setting is ignored. 
 * 
 * @param  ADC_config_t ADC_cfg     : Which ADC shall be configured
 * @return std_return_type_t status :  If the given ADC does not exist on the 
 *                                    microcontroller, the function returns
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t MCAL_ADC_config(ADC_config_t ADC_cfg);


/**
 * @brief Reads the state of a channel
 *  
 * This function triggers a ADC conversion and waits until the conversion is 
 * finished. The conversion result is stored in the provided buffer. If the
 * MCU only has a single ADC, ADC number is ignored.
 * 
 * @param  ADC_Channel_t ADC_no     : ADC Channel selection
 * @param  uin16_t buffer           : Buffer where the conversion result is 
 *                                    stored in
 * @return std_return_type_t status : If the channel does not exist the function 
 *                                    return E_NOT_SUPPORTED. Else E_OK.
 */
std_return_type_t MCAL_ADC_channel_read(ADC_Channel_t ADC_no, uint16_t* buffer);

/**
 * @brief Reads the state of a channel
 *  
 * This function triggers a ADC conversion and returns. The conversion result is 
 * stored in the provided buffer and then the callback is callled. If the MCU only 
 * has a single ADC, ADC number is ignored.
 * 
 * @param  ADC_Channel_t ADC_no     : ADC Channel selection
 * @param  uin16_t buffer           : Buffer where the conversion result is 
 *                                    stored in.
 * @param  void (*callback)(void)   : Callback function which shall be called
 *                                    When the conversion has finished.
 * @return std_return_type_t status : If the channel does not exist the function 
 *                                    return E_NOT_SUPPORTED. Else E_OK.
 */
std_return_type_t MCAL_ADC_channel_iread(ADC_Channel_t ADC_no, uint16_t* buffer, void (*callback)(void));


#endif