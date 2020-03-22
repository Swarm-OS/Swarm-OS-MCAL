#ifndef MCAL_PINS_H
#define MCAL_PINS_H

/**
 * @file io.h
 * @author Christoph Lehr
 * @date 6 Aug 2019
 * @brief File containing wrapper for accessing registers
 *
 * This file specifies a generic wrapper for accessing registers.
 */
#include <mcus.h>

#if IS_MCU(STM32F411XX)
    #include <stm32f411xx_pins.h>
#elif IS_MCU(ATMEGA328)
    #include <atmeg328_pins.h>
#endif

#endif