/**
 * @file ADC.h
 * @author Christoph Lehr
 * @date 22 Mar 2020
 * @brief File containing API for accessing ADC
 *
 * This file specifies a generic API which shall be used to 
 * interact with the ADC's of different Microcontrollers.
 */

#ifndef ADCIf_H
#define ADCIf_H

#include <stdint.h>
#include <datatypes.h>

typedef enum __ADCIf_alignment
{
    ADCIf_ALIGNMENT_RIGHT   =0x00,
    ADCIf_ALIGNMENT_LEFT    =0x01,
} ADCIf_alignment_t;

typedef enum __ADCIf_channel_mode
{
    ADCIf_CONVERSION_MODE_SINGLE_ENDED   =0x00,
    ADCIf_CONVERSION_MODE_DIFFERENTIAL   =0x01,
} ADCIf_channel_mode_t;

typedef enum __ADCIf_voltage_reference
{
    ADCIf_REFERENCE_VCC         =0x00,
    ADCIf_REFERENCE_INTERNAL    =0x01,
    ADCIf_REFERENCE_EXTERNAL    =0x02,
}ADCIf_voltage_reference_t;

typedef struct _ADCIf_config
{
    uint8_t adc_id;                     //  ADC to be configured
    uint8_t resolution;                 //  if supported, desired resolution of the ADC
    int8_t gain;                        //  if supported, gain factor of the ADC. Use negative values for division
    uint16_t accumulation;              //  if supported, accumulation of n samples and calculating the average
    uint16_t prescaler;                 //  prescaler for hte ADC peripheral
    uint16_t sampling_duration;         //  if configurable, number of cycles to sample a value
    ADCIf_alignment_t alignment;        //  alignment of the result
    boolean continous_conversion;       //  enables continous sampling mode
    ADCIf_voltage_reference_t reference;//  Voltage reference of the ADC
    uint8_t voltage_ref_id;             //  Identifier for the voltage reference if multiple are available of the same kind. Higher voltage higher identifier.
} ADCIf_config_t;

typedef struct __ADCIf_channel_identifier
{
    ADCIf_channel_mode_t conv_mode;     //  Conversion mode
    union 
    {
        uint8_t channel;                //  input channel for single ended operation
        uint8_t positiv_input_channel;  //  Positive Differential input for different operation
    };
    uint8_t negativ_input_channel;      //  Negative Differential input, in single ended input mode this can be ignored
} ADCIf_channel_identifier_t;

typedef struct _ADCIf_channel_config
{
    identifier_t adc_id;                //  Id of the corresponding ADC
    ADCIf_channel_identifier_t channel; //  Channel identifier
    uint8_t resolution;                 //  If supported, desired resolution of the ADC channel
    uint16_t prescaler;                 //  If configurable, per channel prescaler
    uint16_t sampling_duration;         //  If configurable, per channel number of cycles to sample a value
} ADCIf_channel_config_t;

typedef enum __ADCIf_trigger_type
{
    ADCIF_TRIGGER_FREE_RUNNING,
    ADCIF_TRIGGER_ANALOG_COMPERATOR,
    ADCIF_TRIGGER_EXTERNAL,
    ADCIF_TRIGGER_TIMER,
    ADCIF_TRIGGER_TIMER_CAPTURE,
    ADCIF_TRIGGER_TIMER_COMPARE,
    ADCIF_TRIGGER_TIMER_CAPTURE_COMPARE,
    ADCIF_TRIGGER_TIMER_OVERFLOW,
} ADCIf_trigger_type_t;

typedef enum __ADCIf_trigger_edge_t
{
    ADCIF_TRIGGER_NONE,
    ADCIF_TRIGGER_FALLING_EDGE,
    ADCIF_TRIGGER_RISING_EDGE,
    ADCIF_TRIGGER_BOTH_EDGES,
} ADCIf_trigger_edge_t;

typedef struct __ADCIf_trigger_timer_config
{
    uint8_t timer;
    uint8_t channel;
} ADCIf_trigger_timer_config_t;

typedef struct __ADCIf_trigger_analog_comperator_config
{
    uint8_t comperator_id;
} ADCIf_trigger_analog_comperator_config_t;

typedef struct __ADCIf_trigger_external_config
{
    uint8_t external_interrup_id;
} ADCIf_trigger_external_config_t;

typedef struct __ADCIf_trigger_config
{
    uint8_t channel_group_id;                               //  id of the channel group, leave empty if no channel groups exist
    ADCIf_trigger_type_t type;                              //  type of the trigger
    ADCIf_trigger_edge_t edge_select;                       //  execute on which edge of the trigger
    union 
    {
        ADCIf_trigger_timer_config_t timer;                 //  configuration for timer related ADC triggers
        ADCIf_trigger_analog_comperator_config_t analog;    //  configuration for analog comperator ADC triggers
        ADCIf_trigger_external_config_t external;           //  configuration for external ADC triggers
    };
} ADCIf_trigger_config_t;

typedef struct __ADCIf_value_window
{
    uint16_t lower_bound;           // lower boudn for valid values
    uint16_t upper_bound;           // upper bound for valid values 
    boolean only_valid_outside;     // set if the value is valid if it is outside of the bounds 
} ADCIf_value_window_t;

typedef enum __ADCIf_conversion_mode
{
    ADCIF_SINGLE_CHANNEL,
    ADCIF_CHANNEL_GROUP,
} ADCIf_conversion_mode_t;

typedef struct __ADCIf_channel_group_config
{
    identifier_t group_id;                  // Channel group to be configured, ids are ordered in decending priority 
    uint8_t group_size;                     // Desired group size
    ADCIf_channel_identifier_t *members;    // List of channel groups, multiple occurrences of the same channel are allowed
    uint8_t group_split;                    // split conversion into groups of size n, use 0 to convert all members at once
} ADCIf_channel_group_config_t;

typedef struct __ADCIf_conversion_config
{
    identifier_t adc_id;
    ADCIf_conversion_mode_t conv_mode;
    union 
    {
        ADCIf_channel_group_config_t *group_config;
        ADCIf_channel_identifier_t *channel;
    };
    boolean enable_trigger;
    ADCIf_trigger_config_t trigger_config;
    void (*callback)(uint16_t*);        //  callback for a finished conversion
} ADCIf_conversion_config_t;

typedef struct __ADCIf_supported_features
{
    struct 
    {
        boolean resolution_configuration        :1; //  set if the resolution is configurabel 
        boolean sampling_duration_configuration :1; //  set if the number of sampling cycles is configurable
        boolean sample_accumulation             :1; //  set if multiple samples can be accumulated
        boolean differential_measurement        :1; //  set if differntial measurements are supported
        boolean conversion_chains               :1; //  set if the ADC supports conversion chains
        boolean multiple_channel_groups         :1; //  set if the channels can be clustered into multiple groups
        boolean DMA_trigger                     :1; //  set if the ADC can trigger a DMA stream 
        boolean analog_value_monitor            :1; //  set if the ADC supports monitoring of analog values
    } general;
    struct 
    {
        boolean configuration                   :1; //  set if per channel configuraiton is available
        boolean resolution                      :1; //  set if the resolution of a channel can be configured
        boolean sampling_duration               :1; //  set if the number of sampling cycles for a channel can be configured

    } per_channel;
    struct 
    {
        boolean timer                           :1; //  set if the ADC can be triggerd by a timer trigger
        boolean timer_capture                   :1; //  set if the ADC can be triggerd by a timer capture event 
        boolean timer_compare                   :1; //  set if the ADC can be triggerd by a timer compare event
        boolean timer_capture_compare           :1; //  set if the ADC can be triggerd by a timer capture and compare event
        boolean timer_overflow                  :1; //  set if the ADC can be triggerd by a timer overflow event
        boolean analog_comperator               :1; //  set if the ADC can be triggerd by an analog comperator
        boolean external_event                  :1; //  set if the ADC can be triggerd by an external event
    } triggers;
    
} ADCIf_supported_features_t;

/**
 * @brief Initialize ADC
 *  
 * This function initilializes the given ADC. If the MCU only has a single 
 * ADC, the ADC number is ignored. 
 * Else it returns E_OK.
 * 
 * @param  identifier_t adc_id      : ADC to be initialized
 * @return std_return_type_t status : If the given ADC does not exist on the 
 *                                    microcontroller, the function returns
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t ADCIf_init(identifier_t adc_id);

/**
 * @brief Deinitialize ADC
 *  
 * This function deinitilializes the given ADC. If the MCU only has a single 
 * ADC, the ADC number is ignored. 
 * 
 * @param  identifier_t ADCIf_no    : ADC to be deinitialized
 * @return std_return_type_t status : If the given ADC does not exist on the 
 *                                    microcontroller, the function returns
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t ADCIf_deinit(identifier_t adc_id);

/**
 * @brief Provides supported features of the ADC
 *  
 * This function returns a struct where all features that are supported by
 * the ADC peripheral.
 * 
 * @param  identifier_t ADCIf_no    : ADC to be deinitialized
 * @return ADCIf_supported_features_t features : Suported features of the 
 *                                    ADC peripheral. If the id does not   
 *                                    exist all values are 0.
 */
ADCIf_supported_features_t ADCIf_get_supported_features(identifier_t adc_id);

/**
 * @brief Configuration of ADC
 *  
 * This function configures a given ADC. If the MCU only has a single 
 * ADC, the ADC number is ignored. If the MCU does not provide setting
 * resolution, the setting is ignored. 
 * 
 * @param  ADCIf_config_t *adc_cfg  : Which ADC shall be configured
 * @return std_return_type_t status : If the given ADC does not exist on the 
 *                                    microcontroller, the function returns
 *                                    E_NOT_EXISTING. If a functioniality is 
 *                                    not available on the MCU the function 
 *                                    retursn E_NOT_SUPPORTED. If a given 
 *                                    configuration value is out of range 
 *                                    the function returns E_VALUE_OUT_OF_RANGE.
 *                                    If a value is not supported the function
 *                                    returns E_VALUE_ERR. Else it returns E_OK.
 */
std_return_type_t ADCIf_config(ADCIf_config_t *adc_cfg);


/**
 * @brief Configuration of an ADC channel
 *  
 * This function configures a given ADC channel. If the MCU does not provide 
 * one of the configuration options, the value is ignored.
 * 
 * @param  ADCIf_channel_config_t adc_cfg   : Configuration of the ADC Channel
 * @return std_return_type_t status : If the given ADC or the channel does not 
 *                                    exist on the microcontroller, the function 
 *                                    returns E_NOT_EXISTING. If a given 
 *                                    configuration value is out of range 
 *                                    the function returns E_VALUE_OUT_OF_RANGE.
 *                                    If a value is not supported the function
 *                                    returns E_VALUE_ERR. Else it returns E_OK.
 */
std_return_type_t ADCIf_config_channel(ADCIf_channel_config_t *channel_cfg);

/**
 * @brief ADC Channel conversion configuration
 *  
 * This function configures how conversions shall be executed. Whether the conversions
 * are executed as single conversions or as channel group. In addition conversion triggers
 * are also configured by this function.
 * 
 * @param  ADCIf_conversion_config_t *conv_conf         : List of channel group members 
 * @return std_return_type_t status : If the given ADC, channel or the channel group does  
 *                                    not exist on the microcontroller, the function 
 *                                    returns E_NOT_EXISTING. If the MCU does not support
 *                                    channel groups the function returns E_NOT_SUPPORTED.
 *                                    If a given number of members exceeds the maximum lenght 
 *                                    the function returns E_VALUE_OUT_OF_RANGE. Else it 
 *                                    returns E_OK.
 */
std_return_type_t ADCIf_config_conversion(ADCIf_conversion_config_t *conv_conf);

/**
 * @brief Trigger configuration of an ADC
 *  
 * This function configures the start of conversion trigger of the ADC. If the
 * ADC does not support channel groups, the channel group id is ignored.
 * 
 * @param  identifier_t adc_id      : ADC id
 * @param  ADCIf_trigger_config_t trigger_cfg: Trigger configuration of the ADC
 *                                    channel groups 
 * @return std_return_type_t status : If the given ADC or the channel group does  
 *                                    not exist on the microcontroller, the function 
 *                                    returns E_NOT_EXISTING. If a trigger type is 
 *                                    not supported by the MCU the function returns
 *                                    E_NOT_SUPPORTED. If a given configuration value  
 *                                    is out of range the function returns 
 *                                    E_VALUE_OUT_OF_RANGE. If a value is not 
 *                                    supported the function returns E_VALUE_ERR. 
 *                                    Else it returns E_OK.
 */
std_return_type_t ADCIf_set_channel(identifier_t adc_id, ADCIf_channel_identifier_t channel);


/**
 * @brief ADC valid value configuration
 *  
 * This function configures the value range in which the value is valid
 * 
 * @param  identifier_t adc_id      : ADC id
 * @param  ADCIf_value_window_t window  : Valid value window
 * @return std_return_type_t status : If the given ADC does not exist on the microcontroller, 
 *                                    the function returns E_NOT_EXISTING. If the MCU does 
 *                                    not support value monitoring the function returns 
 *                                    E_NOT_SUPPORTED. If window values exceed the maximum
 *                                    range supported by the ACD the function returns 
 *                                    E_VALUE_OUT_OF_RANGE. Else it 
 *                                    returns E_OK.
 */
std_return_type_t ADCIf_config_valid_window(identifier_t adc_id, ADCIf_value_window_t window);

/**
 * @brief Reads the state of a channel
 *  
 * This function triggers a ADC conversion and waits until the conversion is 
 * finished. The conversion result is stored in the provided buffer. If the
 * MCU only has a single ADC, ADC number is ignored.
 * 
 * @param  ADCIf_Channel_t *adc_id  : ADC Channel selection
 * @param  uin16_t buffer           : Buffer where the conversion result is 
 *                                    stored in
 * @return std_return_type_t status : If the channel does not exist the function 
 *                                    return E_NOT_EXISTING. Else E_OK.
 */
std_return_type_t ADCIf_start_conversion(identifier_t adc_id, uint16_t* buffer);

/**
 * @brief Reads the state of a channel
 *  
 * This function triggers a ADC conversion and returns immidiatly. The conversion  
 * result is stored in the provided buffer. The prior provided callback function 
 * will be called when the conversion has finished. If the MCU only has a single ADC, 
 * ADC number is ignored.
 * 
 * @param  ADCIf_Channel_t ADCIf_no : ADC Channel selection
 * @param  uin16_t buffer           : Buffer where the conversion result is 
 *                                    stored in.
 * @return std_return_type_t status : If the ADC or the ADC channel does not exist the 
 *                                    function returns E_NOT_EXISTING. If neither a ADC 
 *                                    or a channel specific call back are configured the 
 *                                    function returns E_CFG_ERR. Else E_OK.
 */
std_return_type_t ADCIf_start_conversion(identifier_t ADCIf_no, uint16_t* buffer);



#endif