#ifndef MCAL_DATATYPES_H
#define MCAL_DATATYPES_H

#include <stdint.h>

typedef enum
{
    FALSE = 0,
    TRUE = !FALSE,
} boolean;

typedef enum
{
    E_OK                = 0x00,     //  Everything ok, no error
    E_NOT_SUPPORTED     = 0x01,     //  This is not supported on the MCU
    E_NOT_IMPLEMENTED   = 0x02,     //  Function not implemented yet
    E_VALUE_ERR         = 0x03,     //  Input value error
    E_ERR               = 0xFF,     //  General error
} std_return_type_t;

#endif