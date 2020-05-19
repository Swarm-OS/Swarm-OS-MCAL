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
#include "stm32f4xx_interrupt.h"

typedef struct _stm32f4xx_I2C_config
{ 
    void (*send_callback)();                            // callback function when the write cycle has finished
    void (*read_callback)(uint8_t, uint8_t*);           // callback to return buffer and read length when read is finished
    void (*error_callback)(I2CIf_status_t);             // callback if a error was detected
    void (*receive_callback)(I2CIf_status_t, uint8_t);  // callback function for starting transmission and finish of write
    uint8_t (*request_callback)(I2CIf_status_t);        // callback function for starting transmission and finish of write
    uint16_t address;                                   // address buffer
    uint16_t buffer_index;                              // current index of the buffer
    uint16_t buffer_length;                             // total buffer length
    uint8_t *buffer;                                    // buffer where data is stored
    I2CIf_bus_state_t state;                            // current state of the bus
    I2CIf_flags_t flags;                                // I2C flags
} stm32f4xx_I2C_config_t;

char parent_clock[] = "APB1";

static void set_interrupts(identifier_t i2c_bus_id, I2CIf_handle_t *bus_cfg, STM32F4xx_I2C_RegDef_t *i2c_registers);

static std_return_type_t stm32f4xx_I2CIf_config_master(identifier_t i2c_bus_id, I2CIf_master_config *master_cfg);
static std_return_type_t stm32f4xx_I2CIf_config_slave(identifier_t i2c_bus_id, I2CIf_slave_cfg_t *slave_cfg);

static void handle_I2C_event(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg);
static void handle_I2C_event_master_transmit(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg);
static void handle_I2C_event_master_receive(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg);
static void handle_I2C_event_slave_transmit(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg);
static void handle_I2C_event_slave_receive(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg);

stm32f4xx_I2C_config_t bus_config[3];

std_return_type_t I2CIf_init(identifier_t i2c_bus_id)
{

    std_return_type_t status = E_OK;

    switch (i2c_bus_id)
    {
    case 1:
        if(bus_config[0].state == I2CIF_STATE_DISABLED)
        {
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
        }
        else
        {
            status = E_STATE_INIT;
        }   
        break;
    case 2:
        if(bus_config[1].state == I2CIF_STATE_DISABLED)
        {
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
        }
        else
        {
            status = E_STATE_INIT;
        } 
        break;
    case 3:
        if(bus_config[2].state == I2CIF_STATE_DISABLED)
        {
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
        }
        else
        {
            status = E_STATE_INIT;
        }
        break;    
    default:
        status =  E_NOT_EXISTING;
        break;
    }
    return status;
}

std_return_type_t I2CIf_deinit(identifier_t i2c_bus_id)
{

    std_return_type_t status = E_OK;

    switch (i2c_bus_id)
    {
    case 1:
        if(bus_config[0].state == I2CIF_STATE_IDLE)
        {
            STM32F4xx_I2C1_PCLK_DI();
            STM32F4XX_I2C1_REG->I2C_CR1.PE = 0;
            bus_config[0].state = I2CIF_STATE_DISABLED;
        }
        else
        {
            status = E_STATE_ERR;
        }

        break;
    case 2:
        if(bus_config[1].state == I2CIF_STATE_IDLE)
        {
            STM32F4xx_I2C2_PCLK_DI();
            STM32F4XX_I2C2_REG->I2C_CR1.PE = 0;
            bus_config[1].state = I2CIF_STATE_DISABLED;
        }
        else
        {
            status = E_STATE_ERR;
        }
        break;
    case 3:
        if(bus_config[2].state == I2CIF_STATE_IDLE)
        {
            STM32F4xx_I2C3_PCLK_DI();
            STM32F4XX_I2C3_REG->I2C_CR1.PE = 0;
            bus_config[2].state = I2CIF_STATE_DISABLED;
        }
        else
        {
            status = E_STATE_ERR;
        }
        break;    
    default:
        status =  E_NOT_EXISTING;
        break;
    }

    return status;
}

std_return_type_t I2CIf_config(identifier_t i2c_bus_id, I2CIf_handle_t *bus_cfg)
{
    std_return_type_t status = E_OK;
    STM32F4xx_I2C_RegDef_t *i2c_registers;
    
    if(i2c_bus_id == 1)
    {
        if(bus_config[0].state == I2CIF_STATE_IDLE)
        {
            i2c_registers = STM32F4XX_I2C1_REG;
        }
        else if (bus_config[0].state == I2CIF_STATE_DISABLED)
        {
            return E_STATE_NOINIT;
        }
        else
        {
            return E_STATE_ERR;
        }
    }
    else if(i2c_bus_id == 2)
    {
        if(bus_config[1].state == I2CIF_STATE_IDLE)
        {
            i2c_registers = STM32F4XX_I2C2_REG;
        }
        else if (bus_config[1].state == I2CIF_STATE_DISABLED)
        {
            return E_STATE_NOINIT;
        }
        else
        {
            return E_STATE_ERR;
        }
    }
    else if(i2c_bus_id == 3)
    {
        if(bus_config[2].state == I2CIF_STATE_IDLE)
        {
            i2c_registers = STM32F4XX_I2C3_REG;
        }
        else if (bus_config[2].state == I2CIF_STATE_DISABLED)
        {
            return E_STATE_NOINIT;
        }
        else
        {
            return E_STATE_ERR;
        }
    }
    else
    {
        return E_NOT_EXISTING;
    }
    
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
    
    set_interrupts(i2c_bus_id, bus_cfg, i2c_registers);

    return E_OK;
}

static void set_interrupts(identifier_t i2c_bus_id, I2CIf_handle_t *bus_cfg, STM32F4xx_I2C_RegDef_t *i2c_registers)
{
    if(bus_cfg->device_mode == I2CIF_DISABLED)
    {
        i2c_registers->I2C_CR2.ITEVTEN = 0;
        i2c_registers->I2C_CR2.ITBUFEN = 0;
        i2c_registers->I2C_CR2.ITERREN = 0;
        
        // enable IRQs for interrupts
        if(i2c_bus_id == 1)
        {
            stm32f4xx_disable_interrupt(STM32F4xx_I2C1_EV_IRQ);
            stm32f4xx_disable_interrupt(STM32F4xx_I2C1_ER_IRQ);
        }
        else if(i2c_bus_id == 2)
        {
            stm32f4xx_disable_interrupt(STM32F4xx_I2C2_EV_IRQ);
            stm32f4xx_disable_interrupt(STM32F4xx_I2C2_ER_IRQ);
        }
        else if(i2c_bus_id == 3)
        {
            stm32f4xx_disable_interrupt(STM32F4xx_I2C3_EV_IRQ);
            stm32f4xx_disable_interrupt(STM32F4xx_I2C3_ER_IRQ);
        }
    }
    else
    {
        i2c_registers->I2C_CR2.ITEVTEN = 1;
        i2c_registers->I2C_CR2.ITBUFEN = 1;
        i2c_registers->I2C_CR2.ITERREN = 1;
        // enable IRQs for interrupts
        if(i2c_bus_id == 1)
        {
            stm32f4xx_enable_interrupt(STM32F4xx_I2C1_EV_IRQ);
            stm32f4xx_enable_interrupt(STM32F4xx_I2C1_ER_IRQ);
        }
        else if(i2c_bus_id == 2)
        {
            stm32f4xx_enable_interrupt(STM32F4xx_I2C2_EV_IRQ);
            stm32f4xx_enable_interrupt(STM32F4xx_I2C2_ER_IRQ);
        }
        else if(i2c_bus_id == 3)
        {
            stm32f4xx_enable_interrupt(STM32F4xx_I2C3_EV_IRQ);
            stm32f4xx_enable_interrupt(STM32F4xx_I2C3_ER_IRQ);
        }
    }
}

static std_return_type_t stm32f4xx_I2CIf_config_master(identifier_t i2c_bus_id, I2CIf_master_config *master_cfg)
{
    identifier_t clock_id = SysClockIf_get_clock_id(parent_clock);
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
    i2c_registers->I2C_CCR.CCR = ccr_value;

    bus_config[i2c_bus_id-1].send_callback = master_cfg->send_callback;
    bus_config[i2c_bus_id-1].read_callback = master_cfg->read_callback;

    return E_OK;
}

static std_return_type_t stm32f4xx_I2CIf_config_slave(identifier_t i2c_bus_id, I2CIf_slave_cfg_t *slave_cfg)
{
    return E_NOT_IMPLEMENTED;
}


std_return_type_t I2CIf_send(identifier_t i2c_bus_id, I2CIf_flags_t flags, uint16_t address, 
                             uint16_t data_length, uint8_t *data)
{

    if(i2c_bus_id <= 0 || i2c_bus_id > 3)
    {
        return E_NOT_EXISTING;
    }
    else if(bus_config[i2c_bus_id-1].state != I2CIF_STATE_IDLE)
    {
        return E_STATE_ERR;
    }
    else if(data == NULL)
    {
        return E_VALUE_NULL;
    }
    else if(data_length == 0)
    {
        return E_VALUE_ERR;
    }
    else
    {
        bus_config[i2c_bus_id-1].buffer = data;
        bus_config[i2c_bus_id-1].buffer_length = data_length;
    }
    

    // check if address is 10 bit address
    if(address & 0xFF80)
    {
        uint16_t address_10bit = 0xF000;
        address_10bit |= (address & 0x0300 << 1);
        address_10bit |= (address & 0xFF );
        bus_config[i2c_bus_id-1].address = address_10bit;
    }
    else
    {
        bus_config[i2c_bus_id-1].address = address << 1;
    }

    if(i2c_bus_id == 1)
    {
        STM32F4XX_I2C1_REG->I2C_CR1.START = 1;
    }
    else if(i2c_bus_id == 2)
    {
        STM32F4XX_I2C2_REG->I2C_CR1.START = 1;
    }
    else if(i2c_bus_id == 3)
    {
        STM32F4XX_I2C3_REG->I2C_CR1.START = 1;
    }

    bus_config[i2c_bus_id-1].state = I2CIF_STATE_ARBITRATION;
    bus_config[i2c_bus_id-1].flags = flags;
    
    return E_OK;
}

std_return_type_t I2CIf_read(identifier_t i2c_bus_id, I2CIf_flags_t flags, uint16_t address,
                             uint16_t buffer_length, uint8_t *buffer)
{
    if(i2c_bus_id <= 0 || i2c_bus_id > 3)
    {
        return E_NOT_EXISTING;
    }
    else if(bus_config[i2c_bus_id-1].state == I2CIF_STATE_IDLE)
    {
        return E_STATE_ERR;
    }
    else if(buffer == NULL)
    {
        return E_VALUE_NULL;
    }
    else if(buffer_length == 0)
    {
        return E_VALUE_ERR;
    }
    else
    {
        bus_config[i2c_bus_id-1].buffer = buffer;
        bus_config[i2c_bus_id-1].buffer_length = buffer_length;
    }

    bus_config[i2c_bus_id-1].flags = flags;
    // check if address is 10 bit address
    if(address & 0xFF80)
    {
        uint16_t address_10bit = 0xF000;
        address_10bit |= (address & 0x0300 << 1);
        address_10bit |= (address & 0xFF );
        bus_config[i2c_bus_id-1].address = address_10bit;
    }
    else
    {
        bus_config[i2c_bus_id-1].address = address << 1 | 1;
    }

    if(i2c_bus_id == 1)
    {
        STM32F4XX_I2C1_REG->I2C_CR1.START = 1;
    }
    else if(i2c_bus_id == 2)
    {
        STM32F4XX_I2C2_REG->I2C_CR1.START = 1;
    }
    else if(i2c_bus_id == 3)
    {
        STM32F4XX_I2C3_REG->I2C_CR1.START = 1;
    }

    bus_config[i2c_bus_id-1].state = I2CIF_STATE_ARBITRATION;

    return E_OK;
}

std_return_type_t I2CIf_stop_transmission(identifier_t i2c_bus_id)
{
    std_return_type_t status = E_OK;
    
    if( i2c_bus_id < 1 || i2c_bus_id > 3)
    {
        status = E_NOT_EXISTING;
    }
    else if( bus_config[i2c_bus_id-1].state == I2CIF_STATE_MASTER_RECEIVER || 
             bus_config[i2c_bus_id-1].state == I2CIF_STATE_MASTER_TRANSMITTER)
    {
        bus_config[i2c_bus_id-1].state = I2CIF_STATE_IDLE;

        if(i2c_bus_id == 1)
        {
            STM32F4XX_I2C1_REG->I2C_CR1.STOP = 1;
        } 
        else if(i2c_bus_id == 1)
        {
            STM32F4XX_I2C2_REG->I2C_CR1.STOP = 1;
        }
        else if(i2c_bus_id == 1)
        {
            STM32F4XX_I2C3_REG->I2C_CR1.STOP = 1;
        }
    }
    else
    {
        status = E_STATE_ERR;
    }

    return status;
}

I2CIf_status_t I2CIf_get_status(identifier_t i2c_bus_id)
{
    I2CIf_status_t status;
    status.raw = 0;

    STM32F4xx_I2C_RegDef_t* registers;
    if(i2c_bus_id == 1)
    {
        registers = STM32F4XX_I2C1_REG;
    } 
    else if(i2c_bus_id == 1)
    {
        registers = STM32F4XX_I2C1_REG;
    }
    else if(i2c_bus_id == 1)
    {
        registers = STM32F4XX_I2C1_REG;
    }
    else
    {
        return status;
    }

    status.address_sent_matched = registers->I2C_SR1.ADDR;
    status.header_10bit_sent = registers->I2C_SR1.ADD10;
    status.start_bit_sent = registers->I2C_SR1.SB;
    status.transmit_buffer_empty = registers->I2C_SR1.TxE;
    status.rcv_buffer_not_empty = registers->I2C_SR1.RxNE;
    status.stop_received = registers->I2C_SR1.STOPF;
    status.PEC_error = registers->I2C_SR1.PEC_ERR;
    status.bus_error = registers->I2C_SR1.BERR;
    status.arbitration_lost = registers->I2C_SR1.ARLO;
    status.acknowledge_failure = registers->I2C_SR1.AF;
    status.overrun_underrun = registers->I2C_SR1.OVR;
    status.PEC_error = registers->I2C_SR1.PEC_ERR;
    status.timeout = registers->I2C_SR1.TIMEOUT;
    status.general_addr_call_rcv = registers->I2C_SR2.GENCALL;
    status.transmit_finished = registers->I2C_SR1.BTF;

    return status;
}

I2CIf_bus_state_t I2CIf_get_bus_status(identifier_t i2c_bus_id)
{
    if(i2c_bus_id < 1 || i2c_bus_id > 3)
    {
        return I2CIF_STATE_DISABLED;
    }
    else
    {
        return bus_config[i2c_bus_id-1].state;
    } 
}

static void handle_I2C_event(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg)
{
    if(reg->I2C_SR1.SB == 1)
    {
        i2c_bus_cfg->buffer_index = 0;
        uint16_t dummy =  reg->I2C_SR1.raw;
        dummy++;
        // I2C Peripheral aquired bus arbitration
        if( i2c_bus_cfg->state == I2CIF_STATE_ARBITRATION )
        {
            if(i2c_bus_cfg->address & 0xFF00)
            {
                reg->I2C_DR.DR = (i2c_bus_cfg->address >> 8 )& 0xFF;
            }
            else
            {
                reg->I2C_DR.DR = (i2c_bus_cfg->address & 0xFF);
            }

            if(i2c_bus_cfg->address & 0x1)
            {
                i2c_bus_cfg->state = I2CIF_STATE_MASTER_RECEIVER;
                reg->I2C_CR1.ACK = 1;
            }
            else
            {
                i2c_bus_cfg->state = I2CIF_STATE_MASTER_TRANSMITTER;
            }
        }
        // i2c address is 10 bit, send 2nd header
        else if(i2c_bus_cfg->state == I2CIF_STATE_MASTER_RECEIVER)
        {
            uint8_t addr = (i2c_bus_cfg->address >> 8 )& 0xFF;
            addr |= 1;
            reg->I2C_DR.DR = addr ;
        }
        // I2C Peripheral is acting as lave
        else
        {
            // TODO: implement slave handling
        }
    }
    else if(i2c_bus_cfg->state == I2CIF_STATE_MASTER_RECEIVER)
    {
        handle_I2C_event_master_receive(i2c_bus_cfg, reg);
    }
    else if(i2c_bus_cfg->state == I2CIF_STATE_MASTER_TRANSMITTER)
    {
        handle_I2C_event_master_transmit(i2c_bus_cfg, reg);
    }
    else if(i2c_bus_cfg->state == I2CIF_STATE_SLAVE_TRANSMITTER)
    {
        handle_I2C_event_slave_transmit(i2c_bus_cfg, reg);
    }
    else if(i2c_bus_cfg->state == I2CIF_STATE_SLAVE_RECEIVER)
    {
        handle_I2C_event_slave_receive(i2c_bus_cfg, reg);
    }

}

static void handle_I2C_event_master_transmit(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg)
{
    // sending low byte of 10 bit address
    if(reg->I2C_SR1.ADD10 == 1)
    {
        reg->I2C_DR.DR = (i2c_bus_cfg->address & 0xFF );
    }
    // sending buffer
    else if((reg->I2C_SR1.ADDR == 1 || reg->I2C_SR1.TxE == 1) && i2c_bus_cfg->buffer_index < i2c_bus_cfg->buffer_length )
    {
        uint16_t dummy =  reg->I2C_SR1.raw;
        dummy+=  reg->I2C_SR2.raw;

        uint8_t index = i2c_bus_cfg->buffer_index;
        reg->I2C_DR.DR = i2c_bus_cfg->buffer[index];
        i2c_bus_cfg->buffer_index++;
    }
    // buffer sent completely
    else if(reg->I2C_SR1.BTF == 1 && reg->I2C_SR1.TxE == 1 )
    {
        if(i2c_bus_cfg->flags & I2CIF_SEND_STOP)
        {
            reg->I2C_CR1.STOP = 1;
            i2c_bus_cfg->state = I2CIF_STATE_IDLE;
        }

        if(i2c_bus_cfg->send_callback != NULL)
        {
            i2c_bus_cfg->send_callback();
        }
    }
}

static void handle_I2C_event_master_receive(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg)
{
    // sending low byte of 10 bit address
    if(reg->I2C_SR1.ADD10 == 1)
    {
        reg->I2C_DR.DR = (i2c_bus_cfg->address & 0xFF );
    }
    // sending buffer
    else if(reg->I2C_SR1.ADDR == 1)
    {
        // check if device operates in 10 bit addressing mode
        if(i2c_bus_cfg->address & 0xFF00 && (i2c_bus_cfg->address & 0x0100) == 0 )
        {
            reg->I2C_CR1.START;
        }
        else if(i2c_bus_cfg->address & 0xFF00)
        {
            reg->I2C_CR1.START;
        }
        // dummy read of SR2
        (void) reg->I2C_SR2;
    }
    // fill receive buffer
    else if(reg->I2C_SR1.RxNE == 1)
    {
        uint8_t index = i2c_bus_cfg->buffer_index;
        i2c_bus_cfg->buffer[index] = reg->I2C_DR.DR;
        i2c_bus_cfg->buffer_index++;
        
        if( i2c_bus_cfg->buffer_index >= i2c_bus_cfg->buffer_length && 
            i2c_bus_cfg->read_callback != NULL)
        {
            i2c_bus_cfg->read_callback(index, i2c_bus_cfg->buffer);
        }

        if(i2c_bus_cfg->flags & I2CIF_SEND_STOP)
        {
            reg->I2C_CR1.ACK = 0;
            reg->I2C_CR1.STOP = 1;
            i2c_bus_cfg->state = I2CIF_STATE_IDLE;
        }
        
    }
}

static void handle_I2C_event_slave_transmit(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg)
{

}

static void handle_I2C_event_slave_receive(stm32f4xx_I2C_config_t *i2c_bus_cfg, STM32F4xx_I2C_RegDef_t* reg)
{

}

void I2C1_EV_Handler(void)
{
    handle_I2C_event(&bus_config[0], STM32F4XX_I2C1_REG);
}

void I2C1_ER_Handler(void)
{
    if(bus_config[0].error_callback != NULL)
    {
        bus_config[0].error_callback(I2CIf_get_status(3));
    }
}

void I2C2_EV_Handler(void)
{
    handle_I2C_event(&bus_config[1], STM32F4XX_I2C2_REG);
}

void I2C2_ER_Handler(void)
{
    if(bus_config[1].error_callback != NULL)
    {
        bus_config[1].error_callback(I2CIf_get_status(2));
    }
}

void I2C3_EV_Handler(void)
{
    handle_I2C_event(&bus_config[2], STM32F4XX_I2C3_REG);
}

void I2C3_ER_Handler(void)
{
    if(bus_config[2].error_callback != NULL)
    {
        bus_config[2].error_callback(I2CIf_get_status(3));
    }
}