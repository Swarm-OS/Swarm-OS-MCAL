/**
 * @file stm32f4xx_SysClockIf.h
 * @author Christoph Lehr
 * @date 7 May 2020
 * @brief File containing STM32F4xx specific configurations
 *
 * This file defines some generic datastructures for STM32F4
 * MCU's
 */

#ifndef STM32F4XX_SYSCLOCKIF_H
#define STM32F4XX_SYSCLOCKIF_H

#include "mcus.h"
#include <SysClockIf.h>

#if IS_MCU(MCU_STM32F411)
const char clock_names[27][30] =
{
    "HSI",                          
    "HSE",                        
    "LSI",                          
    "LSE",                          
    "Main PLL Input Clock Source",  
    "Main PLL Input Clock Divisor", 
    "Main PLL Clock Multiplier",    
    "Main PLL USB Clock Divisor",   
    "Main PLL System Clock Divisor",
    "System Clock",                 
    "PTP Clock",                    
    "AHB1",                         
    "HCLK",                         
    "System Timer",                 
    "FCLK",                         
    "APB1",                         
    "APB1 Timer",                   
    "APB2",                         
    "APB2 Timer",                   
    "I2S PLL Input Clock Divisor",  
    "I2S PLL Multiplier",           
    "I2S PLL Divisor",              
    "I2S Input Clock",              
    "I2S Clock",                    
    "IWDG Clock",                   
    "RTC HSE Prescaler",            
    "RTC Clock Source"
};

SystemClock_clock_t sys_clock_config[] =
{
    // Freuqecy     Min Frequency   Max Frequency   parrent   child   sibling    factor                               type          name
    {  16000000,                 0,       16000000,       -1,     9,       1,         1,            SYSCLOCK_CLK_SRC_INTERNAL_OSC,  clock_names[ 0]}, // HSI                            
    {  25000000,           1000000,       50000000,       -1,     9,      -1,         1,            SYSCLOCK_CLK_SRC_EXTERNAL_OSC,  clock_names[ 1]}, // HSE                            
    {     32000,                 0,          32000,       -1,    21,       3,         1,  SYSCLOCK_CLK_SRC_INTERNAL_SECONDARY_OSC,  clock_names[ 2]}, // LSI                            
    {     32768,                 0,        1000000,       -1,    23,      -1,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[ 3]}, // LSE                            
    {  16000000,                 0,              0,        0,     5,      -1,         1,                    SYSCLOCK_CLK_SELECTOR,  clock_names[ 4]}, // Main PLL Input Clock Source        
    {   1000000,            950000,        2100000,        4,     6,      -1,        16,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[ 5]}, // Main PLL Input Clock Divisor       
    { 192000000,         100000000,      432000000,        5,     7,      -1,       192,              SYSCLOCK_CLK_PLL_MULTIPLIER,  clock_names[ 6]}, // Main PLL Clock Multiplier          
    {  48000000,                 0,       75000000,        6,    -1,       8,         4,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[ 7]}, // Main PLL USB Clock Divisor         
    {  96000000,          24000000,      100000000,        6,     9,      -1,         2,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[ 8]}, // Main PLL System Clock Divisor
    {  16000000,                 0,              0,        8,    10,      -1,         1,                    SYSCLOCK_CLK_SELECTOR,  clock_names[ 9]}, // System Clock                       
    {  16000000,                 0,              0,        9,    -1,      11,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[10]}, // PTP Clock                          
    {  16000000,                 0,      100000000,        9,    12,      -1,         1,                   SYSCLOCK_CLK_PRESCALER,  clock_names[11]}, // AHB1                               
    {  16000000,                 0,              0,       11,    -1,      13,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[12]}, // HCLK                                   
    {  16000000,                 0,              0,       11,    -1,      14,         1,                   SYSCLOCK_CLK_PRESCALER,  clock_names[13]}, // System Timer                           
    {  16000000,                 0,              0,       11,    -1,      15,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[14]}, // FCLK                               
    {  16000000,                 0,       50000000,       11,    16,      17,         1,                   SYSCLOCK_CLK_PRESCALER,  clock_names[15]}, // APB1                               
    {  16000000,                 0,              0,       15,    -1,      -1,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[16]}, // APB1 Timer                             
    {  16000000,                 0,      100000000,       11,    18,      -1,         1,                   SYSCLOCK_CLK_PRESCALER,  clock_names[17]}, // APB2                                   
    {  16000000,                 0,              0,       17,    -1,      -1,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[18]}, // APB2 Timer                             
    {   1000000,            950000,        2100000,        4,    20,      -1,        16,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[19]}, // I2S PLL Input Clock Divisor                    
    { 192000000,         100000000,      432000000,       19,    21,      -1,       192,              SYSCLOCK_CLK_PLL_MULTIPLIER,  clock_names[20]}, // I2S PLL Multiplier                
    {  96000000,                 0,      216000000,       21,    22,      -1,         2,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[21]}, // I2S PLL Divisor                   
    {  96000000,                 0,      216000000,       -1,    23,      -1,         2,            SYSCLOCK_CLK_SRC_EXTERNAL_SIG,  clock_names[22]}, // I2S Input Clock                    
    {  96000000,                 0,              0,       23,    -1,      -1,         1,                    SYSCLOCK_CLK_SELECTOR,  clock_names[23]}, // I2S Clock                          
    {     32000,                 0,              0,        2,    -1,      -1,         1,  SYSCLOCK_CLK_SRC_INTERNAL_SECONDARY_OSC,  clock_names[24]}, // IWDG Clock                             
    {  12500000,                 0,              0,        1,    26,      -1,         2,                   SYSCLOCK_CLK_PRESCALER,  clock_names[25]}, // RTC HSE Prescaler                      
    {     32000,                 0,        1000000,        2,     1,      -1,         1,                    SYSCLOCK_CLK_SELECTOR,  clock_names[26]}, // RTC Clock Source                   
};
#endif

#if IS_MCU(MCU_STM32F407)
const char clock_names[27][30] =
{
    "HSI",                          
    "HSE",                        
    "LSI",                          
    "LSE",                          
    "Main PLL Input Clock Source",  
    "Main PLL Input Clock Divisor", 
    "Main PLL Clock Multiplier",    
    "Main PLL AHB2 Clock Divisor",   
    "Main PLL System Clock Divisor",
    "System Clock",                 
    "PTP Clock",                    
    "AHB1",                         
    "HCLK",                         
    "System Timer",                 
    "FCLK",                         
    "APB1",                         
    "APB1 Timer",                   
    "APB2",                         
    "APB2 Timer",                   
    "I2S PLL Input Clock Divisor",  
    "I2S PLL Multiplier",           
    "I2S PLL Divisor",              
    "I2S Input Clock",              
    "I2S Clock",                    
    "IWDG Clock",                   
    "RTC HSE Prescaler",            
    "RTC Clock Source"
};

SystemClock_clock_t sys_clock_config[] =
{
    // Freuqecy     Min Frequency   Max Frequency   parrent   child   sibling    factor                               type          name
    {  16000000,                 0,       16000000,       -1,     9,       1,         1,            SYSCLOCK_CLK_SRC_INTERNAL_OSC,  clock_names[ 0]}, // HSI                            
    {  25000000,           1000000,       50000000,       -1,     9,      -1,         1,            SYSCLOCK_CLK_SRC_EXTERNAL_OSC,  clock_names[ 1]}, // HSE                            
    {     32000,                 0,          32000,       -1,    21,       3,         1,  SYSCLOCK_CLK_SRC_INTERNAL_SECONDARY_OSC,  clock_names[ 2]}, // LSI                            
    {     32768,                 0,        1000000,       -1,    23,      -1,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[ 3]}, // LSE                            
    {  16000000,                 0,              0,        0,     5,      -1,         1,                    SYSCLOCK_CLK_SELECTOR,  clock_names[ 4]}, // Main PLL Input Clock Source        
    {   1000000,            950000,        2100000,        4,     6,      -1,        16,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[ 5]}, // Main PLL Input Clock Divisor       
    { 192000000,         100000000,      432000000,        5,     7,      -1,       192,              SYSCLOCK_CLK_PLL_MULTIPLIER,  clock_names[ 6]}, // Main PLL Clock Multiplier          
    {  48000000,                 0,       75000000,        6,    -1,       8,         4,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[ 7]}, // Main PLL AHB2 Clock Divisor         
    {  96000000,          24000000,      168000000,        6,     9,      -1,         2,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[ 8]}, // Main PLL System Clock Divisor
    {  16000000,                 0,              0,        8,    10,      -1,         1,                    SYSCLOCK_CLK_SELECTOR,  clock_names[ 9]}, // System Clock                       
    {  16000000,                 0,              0,        9,    -1,      11,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[10]}, // PTP Clock                          
    {  16000000,                 0,      168000000,        9,    12,      -1,         1,                   SYSCLOCK_CLK_PRESCALER,  clock_names[11]}, // AHB1                               
    {  16000000,                 0,              0,       11,    -1,      13,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[12]}, // HCLK                                   
    {  16000000,                 0,              0,       11,    -1,      14,         1,                   SYSCLOCK_CLK_PRESCALER,  clock_names[13]}, // System Timer                           
    {  16000000,                 0,              0,       11,    -1,      15,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[14]}, // FCLK                               
    {  16000000,                 0,       42000000,       11,    16,      17,         1,                   SYSCLOCK_CLK_PRESCALER,  clock_names[15]}, // APB1                               
    {  16000000,                 0,              0,       15,    -1,      -1,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[16]}, // APB1 Timer                             
    {  16000000,                 0,       84000000,       11,    18,      -1,         1,                   SYSCLOCK_CLK_PRESCALER,  clock_names[17]}, // APB2                                   
    {  16000000,                 0,              0,       17,    -1,      -1,         1,                    SYSCLOCK_CLK_INTERNAL,  clock_names[18]}, // APB2 Timer                             
    {   1000000,            950000,        2100000,        4,    20,      -1,        16,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[19]}, // I2S PLL Input Clock Divisor                    
    { 192000000,         100000000,      432000000,       19,    21,      -1,       192,              SYSCLOCK_CLK_PLL_MULTIPLIER,  clock_names[20]}, // I2S PLL Multiplier                
    {  96000000,                 0,      216000000,       21,    22,      -1,         2,                 SYSCLOCK_CLK_PLL_DIVISOR,  clock_names[21]}, // I2S PLL Divisor                   
    {  96000000,                 0,      216000000,       -1,    23,      -1,         2,            SYSCLOCK_CLK_SRC_EXTERNAL_SIG,  clock_names[22]}, // I2S Input Clock                    
    {  96000000,                 0,              0,       23,    -1,      -1,         1,                    SYSCLOCK_CLK_SELECTOR,  clock_names[23]}, // I2S Clock                          
    {     32000,                 0,              0,        2,    -1,      -1,         1,  SYSCLOCK_CLK_SRC_INTERNAL_SECONDARY_OSC,  clock_names[24]}, // IWDG Clock                             
    {  12500000,                 0,              0,        1,    26,      -1,         2,                   SYSCLOCK_CLK_PRESCALER,  clock_names[25]}, // RTC HSE Prescaler                      
    {     32000,                 0,        1000000,        2,     1,      -1,         1,                    SYSCLOCK_CLK_SELECTOR,  clock_names[26]}, // RTC Clock Source                   
};
#endif

#define SYSCLOCK_ENTRIES() (sizeof(sys_clock_config)/sizeof(SystemClock_clock_t))

#endif
