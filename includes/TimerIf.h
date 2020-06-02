/**
 * @file TimerIf.h
 * @author Christoph Lehr
 * @date 13 Apr 2020
 * @brief File containing wrapper for timer API
 *
 * This file specifies a generic wrapper for accessing the
 * timer of a MCU.
 */

#ifndef TIMERIF_H
#define TIMERIF_H

#include <stdint.h>
#include <datatypes.h>

typedef enum _TimerIf_timer_mode
{
    TIMERIF_MODE_DISABLED               = 0x00, //  disable Timer
    TIMERIF_MODE_NORMAL                 = 0x01, //  Normal operation, i.e. just counting
    TIMERIF_MODE_INPUT_COMPTURE         = 0x10, //  Timer/Channel operates in input capture mode
    TIMERIF_MODE_INPUT_PWM_COMPTURE     = 0x11, //  Timer/Channel operates in PWM input capture mode
    TIMERIF_MODE_OUTPUT_COMPARE         = 0x20, //  Timer/Channel operates in output compare mode
    TIMERIF_MODE_OUTPUT_PWM             = 0x21, //  Timer/Channel generates a PWM
    TIMERIF_MODE_OUTPUT_SINGLE_SHOT     = 0x22, //  Timer/Channel generates a single impulse after a given time
} TimerIf_timer_mode_t;

typedef enum _TimerIf_PWM_mode
{
    TIMERIF_PWM                         = 0x10, // general PWM mode 
    TIMERIF_FAST_PWM                    = 0x11, // Fast PWM mode
    TIMERIF_PHASE_PWM                   = 0x12, // Phase correct PWM mode
    TIMERIF_PHASE_FREQUENCy_PWM         = 0x13, // Phase and frequency correct PWM mode
} TimerIf_PWM_mode_t;

typedef enum __TimerIf_outputs
{
    TIMERIF_OUTPUT_NO                      = 0x00, // no PWM output 
    TIMERIF_OUTPUT_NORMAL                  = 0x01, // only use normal output
    TIMERIF_OUTPUT_COMPLEMTARY             = 0x02, // only use complementary output
    TIMERIF_OUTPUT_BOTH                    = 0x03, // use normal and complementary output
} TimerIf_outputs_t;


typedef enum _TimerIf_PWM_polarity
{
    TIMERIF_POLARITY_ACTIVE_HIGH        = 0x00, // Cycle starts active and switches to passive
    TIMERIF_POLARITY_ACTIVE_LOW         = 0x01, // Cycle starts passive and switches to active
} TimerIf_PWM_polarity_t; 

typedef enum _TimerIf_clk_source
{
    TIMERIF_INTERNAL_CLK                = 0x00, // Use internal clock
    TIMERIF_INTERNAL_CLK_TRIGGER        = 0x01, // Use internal clock as trigger
    TIMERIF_EXTERNAL_CLK                = 0x10, // Use external clock
    TIMERIF_EXTERNAL_CLK_TRIGGER_RISE   = 0x11, // Use external clocks rising edge as trigger
    TIMERIF_EXTERNAL_CLK_TRIGGER_FALL   = 0x12, // Use external clocks falling edge as trigger
} TimerIf_clk_source_t;

typedef enum _TimerIf_conting_mode
{
    TimerIf_COUNTING_UP                 = 0x00, // Counter counts upwards 
    TimerIf_COUNTING_DOWN               = 0x01, // Counter counts downwards
    TimerIf_COUNTING_CENTER_UP          = 0x10, // The counter counts up and down alternatively, output compare triggered only during upcounting
    TimerIf_COUNTING_CENTER_DOWN        = 0x11, // The counter counts up and down alternatively, output compare triggered only during downcounting
    TimerIf_COUNTING_CENTER_UP_DOWN     = 0x12, // The counter counts up and down alternatively, output compare triggered in both directions
} TimerIf_counting_mode_t;

typedef struct 
{
    void (*callback)(void);                 //  Callback when output compare was triggered
} TimerIf_CTC_handle_t;

typedef struct 
{
    TimerIf_PWM_polarity_t polarity_pwm;    //  PWM polarity 
    TimerIf_PWM_mode_t pwm_mode;            //  PWM Mode
} TimerIf_PWM_handle_t;

typedef enum _TimerIf_edge_selection
{
    TIMERIF_EDGE_NONE                   = 0x00, // No edge selected
    TIMERIF_RISING_EDGE                 = 0x01, // Generate/Trigger on rising edge
    TIMERIF_FALLING_EDGE                = 0x02, // Generate/Trigger on faling edge
    TIMERIF_BOTH_EDGES                  = 0x03, // Generate alternating edges /Trigger on both edges
} TimerIf_edge_selection_t;

typedef struct 
{
    uint32_t prescaler;                 //  Input capture prescaler
    TimerIf_edge_selection_t edge;      //  Selection of which edge the input capture shall be triggered
    uint8_t samples;                    //  Number of samples for input capture
    void (*callback)(uint32_t);         //  Callback with timer value when input capture is triggered
} TimerIf_IC_handle_t;

typedef struct 
{
    TimerIf_edge_selection_t edge;      //  Selection of which edge which shall be generated, set to TIMERIF_EDGE_NONE to disable output compare 
    void (*callback)(void);             //  Callback when output compare was triggered, set to NULL if only a waveform shall be generated
} TimerIf_OC_handle_t;

typedef struct 
{
    uint32_t period;                        //  Reset value of the timer, set to 0 to use complete value range of timer
    uint32_t prescaler;                     //  Timer prescaler
    uint8_t timer_id;                       //  Timer to be configured
    TimerIf_counting_mode_t cnt_mode;       //  counting mode
    TimerIf_clk_source_t clk_source;        //  Clock source for the Timer peripherla
} TimerIf_config_t;

typedef struct __TimerIf_channel_config
{
    TimerIf_timer_mode_t mode;              //  Mode in which the channel shall operater
    struct
    {
        boolean invert_polarity_channel;        //  polarity of normal output
        boolean invert_polarity_compchannel;    //  polarity of complementary output
        TimerIf_outputs_t output;               //  Waveform generation output configuration
    } output;
    
    union 
    {
        TimerIf_CTC_handle_t ctc;           //  
        TimerIf_PWM_handle_t pwm;           //
        TimerIf_IC_handle_t input_capture;  //
        TimerIf_OC_handle_t output_compare; //
    };
    uint8_t timer_id;                       //  Timer to be configured
    uint8_t channel_id;                     //  Timer channel to be configured
} TimerIf_channel_config_t;



/**
 * @brief Initialize Timer
 *  
 * This function initilializes the given Timer.
 * 
 * @param  uint8_t timer_id         : Timer Number to be initialized
 * @return std_return_type_t status : If the given port does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t TimerIf_init(uint8_t timer_id);

/**
 * @brief Deinitialize Timer
 *  
 * This function deinitilializes the given Timer, i.e. resets all reqisters.
 * 
 * @param  uint8_t timer_id         : Timer Number to be deinitialized
 * @return std_return_type_t status : If the given timer does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t TimerIf_deinit(uint8_t timer_id);

/**
 * @brief Starts a Timer
 *  
 * This function starts the Timer if it is not already running
 * 
 * @param  uint8_t timer_id         : Timer Number to be started
 * @return std_return_type_t status : If the given timer does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t TimerIf_Timer_start(uint8_t timer_id);

/**
 * @brief Stops a Timer
 *  
 * This function starts the Timer if it is not already running
 * 
 * @param  uint8_t timer_id         : Timer Number to be started
 * @return std_return_type_t status : If the given timer does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t TimerIf_Timer_stop(uint8_t timer_id);

/**
 * @brief Configuration of a Timer
 *  
 * This function sets general configuration of a Timer.
 * 
 * @param  uint8_t timer_id         : Timer Number 
 * @param  uint32_t prescaler       : Integer value for the timer prescaler
 * @param  TimerIf_clk_source_t clk_src : What clock source shall be used 
 * @return std_return_type_t status : If the given timer does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. If the prescaler value
 *                                    is not supported the function returns
 *                                    E_NOT_SUPPORTED. If the clock source is
 *                                    not available the function returns 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t TimerIf_config(TimerIf_config_t *cfg);

/**
 * @brief Configuration of a channel as PWM
 *  
 * This function sets general configuration of a Timer.
 * 
 * @param  uint8_t timer_id         : Timer Number 
 * @param  uint8_t channel_id       : Channel Number 
 * @param  TimerIf_PWM_mode_t mode  : PWM mode
 * @return std_return_type_t status : If the given timer does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. If the prescaler value
 *                                    is not supported the function returns
 *                                    E_NOT_SUPPORTED. If the clock source is
 *                                    not available the function returns 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t TimerIf_channel_config(TimerIf_channel_config_t *cfg);

std_return_type_t TimerIf_set_duty_cycle(identifier_t timer_id, identifier_t channel, uint32_t duty_cycle);

std_return_type_t TimerIf_set_output_compare_offset(identifier_t timer_id, identifier_t channel, uint32_t duty_cycle);

std_return_type_t TimerIf_reset_counter(identifier_t timer_id);

std_return_type_t TimerIf_get_counter(identifier_t timer_id, uint32_t *buffer);

#endif