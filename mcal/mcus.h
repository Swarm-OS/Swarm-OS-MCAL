#ifndef MCAL_MCUS_H
#define MCAL_MCUS_H

/**
 * @file mcus.h
 * @author Christoph Lehr
 * @date 22 Mar 2020
 * @brief File containing all microcontroller definitions
 *
 * This file containing all microcontroller definitions
 */

// Atmel Atmega Base 0x0001 0000
#define ATMEGA328       0x00010001  

// STMicro STM32 Base 0x0002 0000
#define STM32F411       0x00020001

#define IS_MCU(MCU)            defined MCU && (CURRENT_MCU==MCU)

#endif