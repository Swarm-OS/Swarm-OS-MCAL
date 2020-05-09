#ifndef MCAL_DATATYPES_H
#define MCAL_DATATYPES_H

#include <stdint.h>

/**
 * @brief Identifier
 *
 * Used as identifier type. Set to negative value to mark
 * invalid values
 */
typedef int16_t identifier_t;

typedef enum
{
    FALSE = 0,
    TRUE = !FALSE,
} boolean;

typedef enum
{
    E_OK                    = 0x00,     //  Everything ok, no error
    E_ERR                   = 0x01,     //  General error
    E_VALUE_ERR             = 0x11,     //  Input value error
    E_VALUE_NULL            = 0x12,     //  Input value is NULL
    E_VALUE_OUT_OF_RANGE    = 0x13,     //  Input value is out of supported range
    E_CFG_ERR               = 0x20,     //  Error in configuration 
    E_STATE_ERR             = 0x30,     //  Error due to current state
    E_STATE_INIT            = 0x31,     //  Module/Class already initialized
    E_STATE_NOINIT          = 0x32,     //  Module/Class not initialized
    E_STATE_TIMEOUT         = 0x33,     //  State timed out
    E_NOT_SUPPORTED         = 0xD0,     //  This is not supported on the MCU
    E_NOT_EXISTING          = 0xD1,     //  This port/peripheral does not exissst on the MCU
    E_NOT_IMPLEMENTED       = 0xE0,     //  Function not implemented yet
} std_return_type_t;

#endif