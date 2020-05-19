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

typedef enum _TimerIf_CC_mode
{
    TIMERIF_NORMAL                      = 0x00, // Normal operation, i.e. just counting
    TIMERIF_CAPTURE_COMPARE             = 0x01, // Compares timer value with a given "compare" value
    TIMERIF_INPUT_CAPTURE               = 0x02, // Captures external events
    TIMERIF_SINGLE_SHOT                 = 0x03, // Single shot timer
} TimerIf_CC_mode_t;

typedef enum _TimerIf_PWM_mode
{
    TIMERIF_PWM                         = 0x10, // general PWM mode 
    TIMERIF_FAST_PWM                    = 0x11, // Fast PWM mode
    TIMERIF_PHASE_PWM                   = 0x12, // Phase correct PWM mode
    TIMERIF_PHASE_FREQUENCy_PWM         = 0x13, // Phase and frequency correct PWM mode
} TimerIf_PWM_mode_t;

typedef enum _TimerIf_PWM_polarity
{
    TIMERIF_POLARITY_ACTIVE_LOW         = 0x00, // Cycle starts active and switches to passive
    TIMERIF_POLARITY_ACTIVE_HIGH        = 0x01, // Cycle starts passive and switches to active
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
    uint8_t num_channels;               //  Number of available channels
    uint8_t resolution;                 //  Timer Resolution in Bit
} TimerIf_info_t;

typedef struct 
{
    uint32_t period;                    //  Reset value of the timer
    uint32_t prescaler;                 //  Timer prescaler
    uint8_t ch_prescaler;               //  Channel prescaler
    uint8_t timer_id;                   //  Timer to be configured
    uint8_t channel_id;                 //  Timer channel to be configured
    TimerIf_counting_mode_t cnt_mode;   //  counting mode
} TimerIf_timer_t;

typedef struct 
{
    void (*callback)(void);             //  Callback when output compare was triggered
    TimerIf_timer_t handle;             //  General Timer Configuration 
    boolean is_single_shot;             //  Duty cycle of the PWM
} TimerIf_CTC_handle_t;

typedef struct 
{
    TimerIf_timer_t handle;             //  General Timer Configuration 
    uint32_t duty_cycle;                //  Duty cycle of the PWM
    TimerIf_PWM_polarity_t polarity;    //  PWM polarity
} TimerIf_PWM_handle_t;

typedef struct 
{
    void (*callback)(uint32_t);         //  Callback with timer value when input capture is triggered
    TimerIf_timer_t handle;             //  General Timer Configuration

} TimerIf_IC_handle_t;

typedef struct 
{
    void (*callback)(void);     //  Callback when output compare was triggered
    TimerIf_timer_t handle;     //  General Timer Configuration
} TimerIf_OC_handle_t;


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
 * @brief Get information of Hardware Timer
 *  
 * This function returns the information of a given timer.
 * 
 * @param  uint8_t timer_id         : Timer Number 
 * @param  TimerIf_info_t *info     : Buffer for returning the timer information
 * @return std_return_type_t status : If the given timer does not exist on the 
 *                                    microcontroller, the function return 
 *                                    E_NOT_EXISTING. If given pointer is NULL
 *                                    the function returns E_VALUE_NULL. Else it 
 *                                    returns E_OK.
 */
std_return_type_t TimerIf_get_information(uint8_t timer_id, TimerIf_info_t *info);

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
std_return_type_t TimerIf_config(uint8_t timer_id, uint16_t prescaler, TimerIf_clk_source_t clk_src);

std_return_type_t TimerIf_CTC_config(uint8_t timer_id, uint16_t prescaler);

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
std_return_type_t TimerIf_PWM_config(uint8_t timer_id, uint16_t period, TimerIf_PWM_mode_t mode);

std_return_type_t TimerIf_set_PWM_duty_cylce(uint8_t timer_id, uint8_t channel_id, uint32_t duty_cycle);

std_return_type_t TimerIf_IC_config(uint8_t timer_id, uint8_t channel_id, void (*callback)(uint32_t));

std_return_type_t TimerIf_config_OC(uint8_t timer_id, uint8_t channel_id, uint32_t period, void (*callback)(void));


#endif