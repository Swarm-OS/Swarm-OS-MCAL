/**
 * @file SysClockIf.h
 * @author Christoph Lehr
 * @date 27 Apr 2020
 * @brief File containing API for generic clock configuration
 *
 * This file specifies a generic API which shall be used to 
 * configure a MCU's clock and configuration of the whole 
 * clock tree.
 */

#ifndef SYSCLOCKIF_H
#define SYSCLOCKIF_H

#include <stdint.h>
#include <datatypes.h>
#include <stddef.h>

typedef enum _SysClock_clock_source
{
    SYSCLOCK_CLK_INTERNAL                   = 0x00, // internal clock
    SYSCLOCK_CLK_SELECTOR                   = 0x01, // clock source selector for child clocks, the parent of this clock can be changed         
    SYSCLOCK_CLK_PRESCALER                  = 0x02, // divisor of a internal clock         
    SYSCLOCK_CLK_PLL_DIVISOR                = 0x10, // PLL divisor stage         
    SYSCLOCK_CLK_PLL_MULTIPLIER             = 0x11, // PLL multiplier stage     
    SYSCLOCK_CLK_SRC_INTERNAL_OSC           = 0xE1, // source of this clock is a internal oscillator
    SYSCLOCK_CLK_SRC_INTERNAL_SECONDARY_OSC = 0xE2, // source of this clock is the secondary internal oscillator
    SYSCLOCK_CLK_SRC_EXTERNAL_OSC           = 0xF1, // source of this clock is a external oscillator
    SYSCLOCK_CLK_SRC_EXTERNAL_SIG           = 0xF2, // source of this clock is a external signal
    SYSCLOCK_CLK_SRC_EXTERNAL_SECONDARY_OSC = 0xF3, // source of this clock is a secondary external oscillator    
    SYSCLOCK_CLK_SRC_EXTERNAL_SECONDARY_SIG = 0xF4, // source of this clock is a secondary external signal    

} SysClock_clock_type_t;

typedef struct _SystemClock_clock
{
    uint32_t frequency;                     // if root clock, give oscilator frequency, else this value will be calculated by the mdoule
    uint32_t min_frequency;                 // minimum frequency allowed for this clock
    uint32_t max_frequency;                 // maximum frequency allowed for this clock, 0 if no maximum
    uint16_t factor;                        // if clock is the multiply stage of a PLL this is the multiplier, else it is used as prescaler, 0 is clock disable 
    identifier_t parent_clock_id;                   // if not root clock, link to clock source, -1 if not existing
    identifier_t child_clock_id;                    // list of clocks which use this clock as input -1 if not existing
    identifier_t sibling_clock_id;                  // next clock which uses parent_clock as direct parent -1 if not existing
    SysClock_clock_type_t clock_type;       // type of clock source for this clock
    const char ** name;                     // name of the clock
} SystemClock_clock_t;


/**
 * @brief Reconfigure Clock Tree
 *  
 * This function reconfigures the systems clock tree
 * 
 * @param  SystemClock_clock_t *cfg : clock tree configuration
 * @return std_return_type_t status : If a referenced clock does not exist
 *                                    the function returns E_NOT_EXISTING. If
 *                                    a multiplier is referenced but the clock
 *                                    does not have PLL the function returns    
 *                                    E_NOT_SUPPRTED. If the calculated frequency
 *                                    undeflows or exceeds the maximum rated
 *                                    frequency of the clock E_VALUE_OUT_OF_RANGE.
 *                                    If cfg is a null, the function returns 
 *                                    E_VALUE_NULL. If a prescaler or a multiplexer
 *                                    is not available the function returns E_VALUE_ERR.
 *                                    Else it returns E_OK.
 */
std_return_type_t SysClockIf_config(SystemClock_clock_t *cfg);


/**
 * @brief Reconfigure a single clock
 *  
 * This function reconfigures one of the systems clock and recalculates the
 * dependent clock tree parts. 
 * 
 * @param  identifier_t id                  : ID of the clock to be reconfigured
 * @param  SystemClock_clock_t *cfg : Clock configuration
 * @return std_return_type_t status : If a referenced clock does not exist
 *                                    the function returns E_NOT_EXISTING. 
 *                                    If the calculated frequency undeflows 
 *                                    or exceeds the maximum rated frequency 
 *                                    of the clock E_VALUE_OUT_OF_RANGE. If 
 *                                    cfg is a null, the function returns 
 *                                    E_VALUE_NULL. If a prescaler or a multiplier
 *                                    is not available the function returns 
 *                                    E_VALUE_ERR. If a clock does not provide a
 *                                    prescaler/multipier, the function returns 
 *                                    E_NOT_SUPPORTED. Else it returns E_OK.
 */
std_return_type_t SysClockIf_config_clock(identifier_t id, SystemClock_clock_t *cfg);


/**
 * @brief Get current Clock Tree configuration
 *  
 * This function returns copies the current configuration into the provided
 * buffer.
 * 
 * @param  SystemClock_clock_t *cfg : Buffer for clock tree configuration
 * @param  size_t size              : Size of the provided buffer
 * @return std_return_type_t status : Returns E_VALUE_NULL if configuration
 *                                    buffer is null. If the buffer size does
 *                                    not have the required size the function
 *                                    returns E_VALUE_ERR. Else it returns E_OK.
 */
std_return_type_t SysClockIf_get_config(SystemClock_clock_t *cfg, size_t size);


/**
 * @brief Get the configuration of a Clock
 *  
 * This function returns the configuration one of the systems clock, based
 * on the given id. The desired clock configuration will be copied into the
 * provided buffer cfg.
 * 
 * @param  identifier_t id                  : ID of the desired clock
 * @param  SystemClock_clock_t *cfg : Clock configuration buffer
 * @return std_return_type_t status : If a referenced clock does not exist
 *                                    the function returns E_NOT_EXISTING. If
 *                                    a multiplier is referenced but the clock
 *                                    does not have PLL the function returns    
 *                                    E_NOT_SUPPRTED. If the calculated frequency
 *                                    undeflows or exceeds the maximum rated
 *                                    frequency of the clock E_VALUE_OUT_OF_RANGE.
 *                                    If cfg is a null, the function returns 
 *                                    E_VALUE_NULL. If a prescaler or a multiplexer
 *                                    is not available the function returns E_VALUE_ERR.
 *                                    Else it returns E_OK.
 */
std_return_type_t SysClockIf_get_clock_config(identifier_t id, SystemClock_clock_t *cfg);


/**
 * @brief Get the configuration of a Clock
 *  
 * This function returns the configuration one of the systems clock, based
 * on the given name of the desired clock. The desired clock configuration 
 * will be copied into the provided buffer cfg.
 * 
 * @param  char *name               : Name of the clock
 * @param  SystemClock_clock_t *cfg : Clock configuration
 * @return std_return_type_t status : If a referenced clock does not exist
 *                                    the function returns E_NOT_EXISTING. If
 *                                    a multiplier is referenced but the clock
 *                                    does not have PLL the function returns    
 *                                    E_NOT_SUPPRTED. If the calculated frequency
 *                                    undeflows or exceeds the maximum rated
 *                                    frequency of the clock E_VALUE_OUT_OF_RANGE.
 *                                    If cfg is a null, the function returns 
 *                                    E_VALUE_NULL. If a prescaler or a multiplexer
 *                                    is not available the function returns E_VALUE_ERR.
 *                                    Else it returns E_OK.
 */
std_return_type_t SysClockIf_get_clock_config_name(char *name, SystemClock_clock_t *cfg);


/**
 * @brief Get the ID of a Clock
 *  
 * This function checks the provided name and returns the id of the clock
 * 
 * @param  char *name               : Name of the clock
 * @return identifier_t id                  : -1 if the clock does not exitst, else the ID 
 *                                    of the clock
 */

identifier_t SysClockIf_get_clock_id(char* name);


/**
 * @brief Get the name of a Clock
 *  
 * This function checks the provided ID and returns the name of the clock
 * 
 * @return identifier_t id          : ID of the desired clock
 * @param  const char *name         : Null if the clock id does not exist. Else
 *                                    a pointer to the Name of the clock
 */
const char * SysClockIf_get_clock_name(identifier_t id);


/**
 * @brief Get Number of clock tree members
 *  
 * This function returns the number SystemClock_clock_t entries 
 * required to store the whole clock tree in a array. This is 
 * required to provide a large enough buffer that the function
 * SysClockIf_get_config can store the whole clock tree in it. 
 * 
 * @return uint8_t number_of_clocks : Number of clocks in the Clock tree
 */
uint8_t SysClockIf_get_number_of_clocks(void);


#endif