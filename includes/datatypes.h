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
    E_OK = 0x00,
    E_NOT_SUPPORTED = 0x01,
    E_NOT_IMPLEMENTED = 0x02,
    E_VALUE_ERR = 0x03,
    E_ERR = 0xFF,
} std_return_type_t;

#endif