/**
 * @file RTCIf.h
 * @author Christoph Lehr
 * @date 23 Apr 2020
 * @brief File containing wrapper for RTC API
 *
 * This file specifies a generic wrapper for accessing the
 * RTC peripherals of a MCU.
 */

#ifndef RTCIF_H
#define RTCIF_H

#include <stdint.h>
#include "datatypes.h"

typedef struct _RTCIf_date_time
{
    // byte 0
    uint8_t second_tens             :   3;
    uint8_t minute_tens             :   3;
    uint8_t date_tens               :   2;
    // byte 1
    uint8_t second_units            :   4;
    uint8_t minute_units            :   4;    
    // byte 3
    uint8_t hour_tens               :   2;
    uint8_t hour_units              :   4;
    uint8_t year_tens               :   2;
    // byte 4
    uint8_t year_units              :   4;
    uint8_t month_units             :   4;
    // byte 5
    uint8_t month_tens              :   1;
    uint8_t date_of_week            :   3;
    uint8_t date_units              :   4;
    // byte 6
    boolean is_PM                   :   1; 
} RTCIf_date_time_t;

typedef struct _RTCIf_handle
{
    boolean use_24h_mode            :   1;
    boolean calibration_output_en   :   1;

} RTCIf_handle_t;

typedef struct _RTCIf_alarm_handle
{
    void *callback;                         // function to be called when alarm rings
    RTCIf_date_time_t alarm;                // time when the alarm shall rang
    RTCIf_date_time_t interval;             // intervall of the alarm
    identifier_t alarm_id;                          // alarm id
} RTCIf_alarm_handle_t;

/**
 * @brief Initialize RTC 
 *  
 * This function initilializes the MCUs RTC
 * 
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. 
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_init();

/**
 * @brief Deinitialize RTC 
 *  
 * This function deinitilializes the MCUs RTC
 * 
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. 
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_deinit();

/**
 * @brief Configures RTC 
 *  
 * This function configures the MCUs RTC
 * @param  RTCIf_handle_t cfg       : Configuration of the RTC
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. If
 *                                    a setting is not supported by the 
 *                                    RTC, the function returns E_NOT_SUPPORTED 
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_config(RTCIf_handle_t cfg);

/**
 * @brief Updates RTC time
 *  
 * This function uptest the time of the MCUs RTC
 * 
 * @param  RTCIf_date_time_t date   : Time value
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. 
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_set_time(RTCIf_date_time_t time);

/**
 * @brief Updates RTC date
 *  
 * This function uptest the date of the MCUs RTC
 * 
 * @param  RTCIf_date_time_t date   : Date value
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. 
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_set_date(RTCIf_date_time_t date);

/**
 * @brief Updates RTC date and time
 *  
 * This function uptest the date and time of the MCUs RTC
 * 
 * @param  RTCIf_date_time_t date   : Date and time value
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. 
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_set_date_time(RTCIf_date_time_t date_time);

/**
 * @brief Get current date and time
 *  
 * This function returns the current date and time of the MCUs RTC
 * 
 * @param  RTCIf_date_time_t *date  : Current date and time
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. 
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_get_date_time(RTCIf_date_time_t *date_time);

/**
 * @brief Get current date and time
 *  
 * This function returns the current date and time of the MCUs RTC
 * 
 * @param  RTCIf_alarm_handle_t *alarm: Alarm configuration
 * @return std_return_type_t status : If the MCU does not have a RTC or 
 *                                    the alarm does not exist the  
 *                                    function returns E_NOT_EXISTING. 
 *                                    If the provided callback function
 *                                    is a NULL the function returns
 *                                    E_VALUE_NULL. 
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_set_alarm(RTCIf_alarm_handle_t *alarm);


#endif