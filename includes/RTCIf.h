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

typedef struct _RTCIf_bcd_date_time
{
    // byte 0
    uint8_t second_tens             :   3;
    uint8_t minute_tens             :   3;
    uint8_t day_tens                :   2;
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
    uint8_t day_of_week             :   3;
    uint8_t day_units               :   4;
    // byte 6
    boolean is_PM                   :   1;
    boolean uses_24h_format         :   1;
} RTCIf_bcd_date_time_t;

typedef struct _RTCIf_bin_date_time
{
    // byte 1
    uint8_t seconds                 :   7;
    boolean is_PM                   :   1; 
    // byte 2
    uint8_t minutes                 :   7;
    boolean uses_24h_format         :   1;
    // byte 3
    uint8_t hour                    :   5;
    uint8_t day_of_week             :   3;
    // byte 4-5
    uint16_t day_of_month           :   5;
    uint16_t year                   :   7;
    uint16_t month                  :   4;
} RTCIf_bin_date_time_t;

typedef enum __RTCIf_date_time_format
{
    RTCIF_FORMAT_BIN                = 0x00, // time and date information is in binary representation
    RTCIF_FORMAT_BCD                = 0x01, // time and date information is in binary counted decimal representaiton
} RTCIf_date_time_format_t;

typedef union __RTCIf_Alarm_flags
{
    struct
    {
        uint8_t mask_seconds            :   1;  // set to ignore seconds field
        uint8_t mask_minutes            :   1;  // set to ignore minutes field
        uint8_t mask_hours              :   1;  // set to ignore hours field
        uint8_t mask_date               :   1;  // set to ignore date field
        uint8_t use_day_of_week         :   1;  // enable to use day of week instead of date
    };
    uint8_t raw;
} RTCIf_Alarm_flags_t;

typedef struct __RTCIf_date_time
{
    RTCIf_date_time_format_t input_format; 
    union {
        RTCIf_bcd_date_time_t bcd;
        RTCIf_bin_date_time_t bin;
    };
} RTCIf_date_time_t;


typedef struct _RTCIf_handle
{
    RTCIf_date_time_t *time;
    boolean use_24h_mode;
} RTCIf_handle_t;

typedef struct _RTCIf_alarm_handle
{
    void (*callback)(RTCIf_date_time_t*);   // function to be called when alarm rings
    RTCIf_date_time_t *alarm;               // time when the alarm shall rang
    RTCIf_date_time_t *buffer;              // buffer for the timestamp of the callback function
    RTCIf_Alarm_flags_t flags;              // flags of the alarm
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
 *                                    RTC, the function returns E_NOT_SUPPORTED.
 *                                    If one of the time/date values is out of range
 *                                    the function returns E_VALUE_OUT_OF_RANGE
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_config(RTCIf_handle_t *cfg);

/**
 * @brief Updates RTC time
 *  
 * This function uptest the time of the MCUs RTC
 * 
 * @param  RTCIf_date_time_t date   : Time value
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. If 
 *                                    one of the time values is out of range
 *                                    the function returns E_VALUE_OUT_OF_RANGE
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_set_time(RTCIf_date_time_t *time);

/**
 * @brief Updates RTC date
 *  
 * This function uptest the date of the MCUs RTC
 * 
 * @param  RTCIf_date_time_t date   : Date value
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. 
 *                                    If one of the date values is out of range
 *                                    the function returns E_VALUE_OUT_OF_RANGE
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_set_date(RTCIf_date_time_t *date);

/**
 * @brief Updates RTC date and time
 *  
 * This function uptest the date and time of the MCUs RTC
 * 
 * @param  RTCIf_date_time_t date   : Date and time value
 * @return std_return_type_t status : If the MCU does not have a RTC the 
 *                                    function returns E_NOT_EXISTING. 
 *                                    If one of the date/time values is out of range
 *                                    the function returns E_VALUE_OUT_OF_RANGE
 *                                    Else it returns E_OK.
 */
std_return_type_t RTCIf_set_date_time(RTCIf_date_time_t *date_time);

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
 * @brief Set alarm
 *  
 * This sets a alarm of the MCUs RTC. If alarms are identified via characters
 * use 1 for alarm A, 2 for alarm B and so on as identifier.
 * 
 * @param  identifier_t alarm_id        : ID of the alarm
 * @param  RTCIf_alarm_handle_t *alarm  : Alarm configuration
 * @return std_return_type_t status     : If the MCU does not have a RTC or 
 *                                        the alarm does not exist the  
 *                                        function returns E_NOT_EXISTING. 
 *                                        If the provided callback function
 *                                        is NULL the function returns
 *                                        E_VALUE_NULL. If one of the date/time 
 *                                        values is out of range the function  
 *                                        returns E_VALUE_OUT_OF_RANGE Else it 
 *                                        returns E_OK.
 */
std_return_type_t RTCIf_set_alarm(identifier_t alarm_id, RTCIf_alarm_handle_t *alarm);

/**
 * @brief Clear alarm
 *  
 * This disables a alarm of the MCUs RTC. If alarms are identified via characters
 * use 1 for alarm A, 2 for alarm B and so on as identifier. 
 * 
 * @param  identifier_t alarm_id        : ID of the alarm
 * @return std_return_type_t status     : If the MCU does not have a RTC or 
 *                                        the alarm does not exist the  
 *                                        function returns E_NOT_EXISTING. 
 *                                        Else it returns E_OK.
 */
std_return_type_t RTCIf_clear_alarm(identifier_t alarm_id);

#endif