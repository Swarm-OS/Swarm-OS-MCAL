/**
 * @file stm32f411_gpio.c
 * @author Christoph Lehr
 * @date 21 Jan 2020
 * @brief STM32F411 implentation ofAPI for accessing GPIO's
 *
 * This file implements the generic API which shall be used to 
 * interact with the GPIO's of different Microcontrollers.
 */

#include <SysClockIf.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <datatypes.h>
#include <stddef.h>
#include "stm32f4xx_SysClockIf.h"

boolean _stm32f4xx_sysclock_initiliazid = FALSE;

std_return_type_t SysClockIf_config(SystemClock_clock_t *cfg)
{
    return E_NOT_IMPLEMENTED;
}


std_return_type_t SysClockIf_config_clock(identifier_t id, SystemClock_clock_t *cfg)
{
    return E_NOT_IMPLEMENTED;
}


std_return_type_t SysClockIf_get_config(SystemClock_clock_t *cfg, size_t size)
{
    if(size < sizeof(sys_clock_config))
    {
        return E_VALUE_ERR;
    }
    memcpy(cfg, &sys_clock_config, sizeof(sys_clock_config));
    return E_OK;
}


std_return_type_t SysClockIf_get_clock_config(identifier_t id, SystemClock_clock_t *cfg)
{
    if(id > SYSCLOCK_ENTRIES())
    {
        return E_NOT_EXISTING;
    }
    memcpy(cfg, &sys_clock_config[id], sizeof(SystemClock_clock_t));
    return E_OK;
}


std_return_type_t SysClockIf_get_clock_config_name(char *name, SystemClock_clock_t *cfg)
{
    identifier_t id = SysClockIf_get_clock_id(name);
    if(id == -1)
    {
        return E_NOT_EXISTING;
    }
    memcpy(cfg, &sys_clock_config[id], sizeof(SystemClock_clock_t));
    return E_NOT_IMPLEMENTED;
}


identifier_t SysClockIf_get_clock_id(char* name)
{
    for(uint8_t i=0; i< SYSCLOCK_ENTRIES(); i++)
    {
        // maximum length of available clock name is 29 chars 
        if(strncmp(name, clock_names[i], 30) == 0)
        {
            return i;
        }
    }
    // clock does not exist
    return -1;
}

const char * SysClockIf_get_clock_name(identifier_t id)
{
    if(id >= SYSCLOCK_ENTRIES())
    {
        return NULL;
    }
    return clock_names[id];
}

uint8_t SysClockIf_get_number_of_clocks(void)
{
    return SYSCLOCK_ENTRIES();
}

uint32_t SysClockIf_get_clock_frequency(identifier_t id)
{
    if(id >= SYSCLOCK_ENTRIES())
    {
        return 0;
    }
    
    return sys_clock_config[id].frequency;
}
