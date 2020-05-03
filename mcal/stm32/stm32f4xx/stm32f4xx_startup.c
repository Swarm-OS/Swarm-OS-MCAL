/**
 * @file stm32f4xx_startup.c
 * @author Christoph Lehr
 * @date 12 Apr 2020
 * @brief Minimal startup code for STM32F4xx series
 *
 * This file contains the minimal startup code required
 * for the STM32F4xx series. Declares the Reset Handler,
 * which initializes the stack pointer, initializes 
 * variables with default values and zeros. 
 */


#ifndef STM32F4xx_EXTERNAL_RESET_HANDLER

#include <stdint.h>
#include "stm32f4xx_interrupt.h"

/* These are defined in the linker script */
extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sstack;
extern uint32_t _estack;

/* Forward define functions */
int main(void);
/**
 * This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler(void)
{
    /* Copy init values from text to data */
    uint32_t *init_values_ptr = &_etext;
    uint32_t *data_ptr = &_sdata;

    if (init_values_ptr != data_ptr) {
        for (; data_ptr < &_edata;) {
            *data_ptr++ = *init_values_ptr++;
        }
    }
            
    /* Clear the zero segment */
    for (uint32_t *bss_ptr = &_sbss; bss_ptr < &_ebss;) {
        *bss_ptr++ = 0;
    }

    /* Branch to main function */
    main();

    /* Infinite loop */
    while (1);
}

#endif