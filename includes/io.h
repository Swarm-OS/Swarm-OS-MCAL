#ifndef MCAL_IO_H
#define MCAL_IO_H

/**
 * @file io.h
 * @author Christoph Lehr
 * @date 6 Aug 2019
 * @brief File containing wrapper for accessing registers
 *
 * This file specifies a generic wrapper for accessing registers.
 */
#if defined(STM32F1XX)
    #include <src/stm32/stm32f1xx/pins.h>
    #include <src/stm32/stm32f1xx/sfr.h>
#elif defined(ATMEGA1280) 
    #include <src/atmel/atmega1280/pins.h>
    #include <avr/io.h>
#elif defined(ATMEGA328)
    #include <src/atmel/atmega328/pins.h>
    #include <avr/io.h>
#endif


#endif