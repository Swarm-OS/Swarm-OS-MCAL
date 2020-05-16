#ifndef MCAL_MCUS_H
#define MCAL_MCUS_H

/**
 * @file mcus.h
 * @author Christoph Lehr
 * @date 22 Mar 2020
 * @brief File containing all microcontroller definitions
 *
 * This file containing all microcontroller definitions
 * 8 Bit MCU Venodr/Major type e.g. STM32, STM8, Atmel 
 */

// Atmel Base                   0x0100 0000
#define MCU_ATMEL               0x01000000

// Atmel Atmegea                0x0101 0000
#define MCU_ATMEL_ATMEGA        0x01010000  
#define MCU_ATMEL_ATMEGA328     0x01010001  


// STMicro STM32 Base           0x0200 0000
#define MCU_STM32               0x02000000

// STMicro STM32F4 family       0x0204 0000
#define MCU_STM32F4             0x02040000
#define MCU_STM32F411           0x0204000B

#define MCU_FAMILY(MCU)         (MCU & 0xFFFF0000)
#define MCU_VENDOR(MCU)         (MCU & 0xFF000000)

#define IS_MCU(MCU)             ( CURRENT_MCU==MCU )
#define IS_MCU_FAMILY(MCU)      ( MCU_FAMILY(CURRENT_MCU) == MCU_FAMILY(MCU))
#define IS_MCU_VENDOR(MCU)      ( MCU_VENDOR(CURRENT_MCU) == MCU_VENDOR(MCU))

#ifndef CURRENT_MCU
#   if defined(ATMEGA328)
#       define CURRENT_MCU MCU_ATMEL_ATMEGA328
#   elif defined(STM32F411)
#       define CURRENT_MCU MCU_STM32F411
#   elif defined(STM32F407VG)
#       define CURRENT_MCU MCU_STM32F407
#   endif
#endif

#endif