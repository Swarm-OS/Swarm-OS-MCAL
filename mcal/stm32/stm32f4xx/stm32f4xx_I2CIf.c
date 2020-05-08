/**
 * @file stm32f4xx_I2CIf.c
 * @author Christoph Lehr
 * @date 26 Apr 2020
 * @brief File containing STM32F4xx I2C API
 *
 * This file implements the generic I2C interface 
 * API for the STM32F4xx series.
 */

#include <stdint.h>
#include "datatypes.h"
#include "stm32f4xx.h"
#include "I2CIf.h"
#include "SysClockIf.h"

const char parent_clock[] = "APB1";

static std_return_type_t stm32f4xx_I2CIf_config_master(identifier_t i2c_bus_id, I2CIf_handle_t *bus_cfg);
static std_return_type_t stm32f4xx_I2CIf_config_slave(identifier_t i2c_bus_id, I2CIf_slave_cfg_t *slave_cfg);

typedef struct _stm32f4xx_I2C_config
{ 
    void (*send_callback)(I2CIf_status_t);                      // callback function when the write cycle has finished
    void (*read_callback)(I2CIf_status_t,uint8_t, uint8_t*);    // callback to return buffer and read length when read is finished
    void (*error_callback)(I2CIf_status_t);                     // callback if a error was detected
    void (*receive_callback)(I2CIf_status_t, uint8_t);          // callback function for starting transmission and finish of write
    uint8_t (*request_callback)(I2CIf_status_t);                // callback function for starting transmission and finish of write
    uint16_t buffer_index;                                      // current index of the buffer
    uint16_t buffer_length;                                     // total buffer length
    uint8_t buffer;                                             // buffer where data is stored
    I2CIf_bus_state_t state;                                    // current state of the bus
} stm32f4xx_I2C_config_t;

stm32f4xx_I2C_config_t bus_config[3];

std_return_type_t I2CIf_init(identifier_t i2c_bus_id)
{
    switch (i2c_bus_id)
    {
    case 1:
        STM32F4xx_I2C1_PCLK_EN();
        STM32F4XX_I2C1_REG->I2C_CR1.PE = 1;
        if(STM32F4XX_I2C1_REG->I2C_SR2.BUSY == 1)
        {
            bus_config[0].state = I2CIF_STATE_BUSY;
        }
        else
        {
            bus_config[0].state = I2CIF_STATE_IDLE;
        }
        break;
    case 2:
        STM32F4xx_I2C2_PCLK_EN();
        STM32F4XX_I2C2_REG->I2C_CR1.PE = 1;

        if(STM32F4XX_I2C1_REG->I2C_SR2.BUSY == 1)
        {
            bus_config[1].state = I2CIF_STATE_BUSY;
        }
        else
        {
            bus_config[1].state = I2CIF_STATE_IDLE;
        }
        break;
    case 3:
        STM32F4xx_I2C3_PCLK_EN();
        STM32F4XX_I2C3_REG->I2C_CR1.PE = 1;

        if(STM32F4XX_I2C1_REG->I2C_SR2.BUSY == 1)
        {
            bus_config[2].state = I2CIF_STATE_BUSY;
        }
        else
        {
            bus_config[2].state = I2CIF_STATE_IDLE;
        }
        break;    
    default:
        return E_NOT_EXISTING;
        break;
    }
    return E_OK;
}

std_return_type_t I2CIf_deinit(identifier_t i2c_bus_id)
{
    switch (i2c_bus_id)
    {
    case 1:
        STM32F4xx_I2C1_PCLK_DI();
        STM32F4XX_I2C1_REG->I2C_CR1.PE = 0;
        break;
    case 2:
        STM32F4xx_I2C2_PCLK_DI();
        STM32F4XX_I2C2_REG->I2C_CR1.PE = 0;
        break;
    case 3:
        STM32F4xx_I2C3_PCLK_DI();
        STM32F4XX_I2C3_REG->I2C_CR1.PE = 0;
        break;    
    default:
        return E_NOT_EXISTING;
        break;
    }
    return E_OK;
}

std_return_type_t I2CIf_config(identifier_t i2c_bus_id, I2CIf_handle_t *bus_cfg)
{
    std_return_type_t status = E_OK;
    
    if(bus_cfg->device_mode & I2CIF_MASTER)
    {
        status = stm32f4xx_I2CIf_config_master(i2c_bus_id, bus_cfg->master_cfg);
        if(status != E_OK)
        {
            return status;
        }
    }

    if(bus_cfg->device_mode & I2CIF_SLAVE)
    {
        status = stm32f4xx_I2CIf_config_slave(i2c_bus_id, bus_cfg->slave_cfg);
        if(status != E_OK)
        {
            return status;
        }
    }

    return E_OK;
}

static std_return_type_t stm32f4xx_I2CIf_config_master(identifier_t i2c_bus_id, I2CIf_handle_t *bus_cfg)
{
    I2CIf_master_config *master_cfg = bus_cfg->master_cfg;
    identifier_t clock_id = SysClockIf_get_clock_id(&parent_clock);
    uint32_t input_clock_frequeny = SysClockIf_get_clock_frequency(clock_id);
    STM32F4xx_I2C_RegDef_t *i2c_registers;

    if(i2c_bus_id == 1)
    {
        i2c_registers = STM32F4XX_I2C1_REG;
    }
    else if(i2c_bus_id == 2)
    {
        i2c_registers = STM32F4XX_I2C2_REG;
    }
    else if(i2c_bus_id == 3)
    {
        i2c_registers = STM32F4XX_I2C3_REG;
    }
    else
    {
        return E_NOT_EXISTING;
    }

    i2c_registers->I2C_CR2.FREQ = (uint16_t)(input_clock_frequeny/1000000);
    uint32_t ccr_value = master_cfg->scl_frequency;
    if(master_cfg->speed == I2CIF_MODE_FM)
    {
        // clock exceeds FM specification
        if(master_cfg->scl_frequency > 400000)
        {
            return E_VALUE_OUT_OF_RANGE;
        }
        
        if(master_cfg->duty_cycle == I2CIF_DUTY_CYCLE_2_1)
        {
            i2c_registers->I2C_CCR.DUTY = 0;
            // duty cycle is 2:1, thererfore SCL sampling frequency *3
            ccr_value *= 3;
        }
        else if(master_cfg->duty_cycle == I2CIF_DUTY_CYCLE_16_9)
        {
            i2c_registers->I2C_CCR.DUTY = 1;
            // duty cycle is 16:9, thererfore SCL sampling frequency *25
            ccr_value *= 25;
        }
        else
        {
            return E_NOT_SUPPORTED;
        }

        // calculate maximum rise time
        i2c_registers->I2C_TRISE.TRISE = ((i2c_registers->I2C_CR2.FREQ*300)/1000) +1;
    }
    else if(master_cfg->speed == I2CIF_MODE_SM)
    {
        // clock exceeds SM specification
        if(master_cfg->scl_frequency > 100000)
        {
            return E_VALUE_OUT_OF_RANGE;
        }
        // duty cycle is allways 1:1
        ccr_value <<= 1;

        // calculate maximum rise time
        i2c_registers->I2C_TRISE.TRISE = i2c_registers->I2C_CR2.FREQ +1;
    }
    else
    {
        return E_NOT_SUPPORTED;
    }
    
    // CCR = (f_ahb1)/(duty_cycle*f_scl)
    ccr_value = input_clock_frequeny/ccr_value;
    i2c_registers->I2C_CCR.CCR_L = ccr_value;
    ccr_value >>= 8;
    i2c_registers->I2C_CCR.CCR_H = ccr_value;

    return E_OK;
}

static std_return_type_t stm32f4xx_I2CIf_config_slave(identifier_t i2c_bus_id, I2CIf_slave_cfg_t *slave_cfg)
{
    return E_NOT_IMPLEMENTED;
}


std_return_type_t I2CIf_send(identifier_t i2c_bus_id, I2CIf_flags_t flags, uint16_t address, 
                             uint16_t data_length, uint8_t *data)
{
    return E_NOT_IMPLEMENTED;
}

std_return_type_t I2CIf_read(identifier_t i2c_bus_id, I2CIf_flags_t flags, uint16_t address,
                             uint16_t buffer_length, uint8_t *buffer)
{
    return E_NOT_IMPLEMENTED;
}

std_return_type_t I2CIf_stop_transmission(identifier_t i2c_bus_id)
{
    return E_NOT_IMPLEMENTED;
}

void I2C1_EV_Handler(void)
{

}

void I2C1_ER_Handler(void)
{

}

void I2C2_EV_Handler(void)
{

}

void I2C2_ER_Handler(void)
{

}

void I2C3_EV_Handler(void)
{

}

void I2C3_ER_Handler(void)
{

}