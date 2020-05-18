/**
 * @file I2CIf.h
 * @author Christoph Lehr
 * @date 21 Apr 2020
 * @brief File containing wrapper for I2C API
 *
 * This file specifies a generic wrapper for accessing the
 * I2C peripherals of a MCU.
 */

#ifndef I2CIF_H
#define I2CIF_H

#include <stdint.h>
#include "datatypes.h"


typedef enum _I2CIf_device_mode
{
    I2CIF_DISABLED                  = 0x00, // disable I2C bus access
    I2CIF_MASTER                    = 0x01, // I2C bus access as I2C master device
    I2CIF_SLAVE                     = 0x02, // I2C bus access as I2C slave device
    I2CIF_MASTER_SLAVE              = 0x03, // I2C bus access as I2C master and slave device
} I2CIf_device_mode_t;

typedef enum _I2CIf_address_mode
{
    I2CIF_ADDRESS_7BIT              = 0x01, // use 7 Bit address mode
    I2CIF_ADDRESS_10BIT             = 0x02, // use 10 Bit address mode
} I2CIf_address_mode_t;

typedef enum _I2CIf_speed_mode
{
    I2CIF_MODE_SM                   = 0x01, // use I2C standard mode
    I2CIF_MODE_FM                   = 0x02, // use I2C fast mode
    I2CIF_MODE_FM_plus              = 0x03, // use I2C fast mode plus
    I2CIF_MODE_HS                   = 0x04, // use I2C high speed mode
} I2CIf_speed_mode_t;

typedef enum _I2CIf_flags
{
    I2CIF_SEND_START                = 0x01, // send start condition
    I2CIF_SEND_STOP                 = 0x02, // send stop condition after transfer
    I2CIF_SEND_ACK                  = 0x04, // send acknowledge
    I2CIF_SEND_NACK                 = 0x08, // send not acknowledge
} I2CIf_flags_t;

typedef enum _I2CIf_duty_cycle
{
    I2CIF_DUTY_CYCLE_1_1            = 0x00, // T_low of clock equals T_high of clock 
    I2CIF_DUTY_CYCLE_2_1            = 0x01, // T_low of clock double T_high of clock
    I2CIF_DUTY_CYCLE_16_9           = 0x02, // T_low to T_high ration is 16:9
} I2CIf_duty_cycle_t;

typedef enum _I2CIf_bus_state
{
    I2CIF_STATE_DISABLED            = 0x00, // Bus currently disabled
    I2CIF_STATE_IDLE                = 0x01, // Bus is idle, no communication is taking place
    I2CIF_STATE_BUSY                = 0x02, // Bus is corrently in used by other devices
    I2CIF_STATE_ARBITRATION         = 0x03, // Device tries to get the arbitration of the bus i.e. waiting on successful send of start condition
    I2CIF_STATE_MASTER_TRANSMITTER  = 0x10, // This device is active as master transmitter
    I2CIF_STATE_MASTER_RECEIVER     = 0x11, // This device is active as master receiver
    I2CIF_STATE_SLAVE_TRANSMITTER   = 0x20, // This device is active as slave transmitter
    I2CIF_STATE_SLAVE_RECEIVER      = 0x21, // This device is active as slave receiver
    
} I2CIf_bus_state_t;

typedef union _I2CIf_status
{
    struct 
    {
        uint16_t start_bit_sent         :   1;
        uint16_t address_sent_matched   :   1;
        uint16_t header_10bit_sent      :   1;
        uint16_t stop_received          :   1;
        uint16_t transmit_finished      :   1;
        uint16_t receive_finished       :   1;
        uint16_t rcv_buffer_not_empty   :   1;
        uint16_t transmit_buffer_empty  :   1;
        uint16_t bus_error              :   1;
        uint16_t arbitration_lost       :   1;
        uint16_t acknowledge_failure    :   1;
        uint16_t overrun_underrun       :   1;
        uint16_t PEC_error              :   1;
        uint16_t timeout                :   1;
        uint16_t general_addr_call_rcv  :   1;
    };
    uint16_t raw;    
} I2CIf_status_t;


typedef struct _I2CIf_slave_config
{
    uint16_t slave_address;                                     // slave address of device
    uint16_t slave_address_2;                                   // 2nd slave address of device, if supported
    uint16_t slave_address_msk;                                 // slave address masking, 1 if bit shall be ignored, if supported
    boolean clock_strech_en;                                    // enable clock stretching
    boolean default_addr_listening_en;                          // enable listening to default address
    void (*receive_callback)(I2CIf_status_t, uint8_t);          // callback function for starting transmission and finish of write
    uint8_t (*request_callback)(I2CIf_status_t);                // callback function for starting transmission and finish of write
} I2CIf_slave_cfg_t;

typedef struct _I2CIf_master_config
{
    void (*send_callback)();                                    // callback function when the write cycle has finished
    void (*read_callback)(uint8_t, uint8_t*);                   // callback to return buffer and read length when read is finished
    void (*error_callback)(I2CIf_status_t);                     // callback if a error was detected
    uint32_t scl_frequency;                                     // desired frequency of the I2C Serial Clock
    uint16_t prescaler;                                         // prescaler for the peripheral
    I2CIf_speed_mode_t speed;                                   // on which speed the I2C bus shall operate
    I2CIf_duty_cycle_t duty_cycle;                              // duty cycle of generated clock
} I2CIf_master_config;

typedef struct _I2CIf_handle
{ 
    I2CIf_master_config *master_cfg;                            // configeration if devices operates as master
    I2CIf_slave_cfg_t *slave_cfg;                               // configuration if devices operates as slave
    I2CIf_device_mode_t device_mode;                            // in which mode the MCU shall eact
    I2CIf_address_mode_t addr_mode;                             // address mode of I2C bus
} I2CIf_handle_t;


/**
 * @brief Initialize a I2C bus peripheral
 *  
 * This function initilializes the given I2C bus peripheral.
 * 
 * @param  uint8_t i2c_bus_id       : I2C bus to be initialized
 * @return std_return_type_t status : If the given I2C bus does not exist on  
 *                                    the microcontroller, the function return 
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t I2CIf_init(identifier_t i2c_bus_id);

/**
 * @brief Deinitialize a I2C bus peripheral
 *  
 * This function deinitilializes the given I2C bus peripherla, i.e. resets 
 * all reqisters.
 * 
 * @param  uint8_t i2c_bus_id       : I2C bus to be deinitialized
 * @return std_return_type_t status : If the given I2C bus does not exist on  
 *                                    the microcontroller, the function return 
 *                                    E_NOT_EXISTING. Else it returns E_OK.
 */
std_return_type_t I2CIf_deinit(identifier_t i2c_bus_id);

/**
 * @brief Configuration of a I2C bus
 *  
 * This function configures a given I2C bus
 * 
 * @param  identifier_t i2c_bus_id  : I2C bus to be configured
 * @param  I2CIf_handle_t *bus_cfg  : I2C bus configuration 
 * @return std_return_type_t status : If the bus id does not exist on the host
 *                                    the function returns E_NOT_EXISTING. If
 *                                    prescaler if the prescaler value is no
 *                                    supported or the scl frequency is out of range,
 *                                    the function returns E_VALUE_OUT_OF_RANGE.
 *                                    If one of the device modes or duty cycle is 
 *                                    not supported the function returns E_NOT_SUPPORTED. 
 *                                    Else it returns E_OK.
 */
std_return_type_t I2CIf_config(identifier_t i2c_bus_id, I2CIf_handle_t *bus_cfg);

/**
 * @brief Transmits data via I2C
 *  
 * This function transmits a given buffer on an active transmission. If 
 * I2CIF_SEND_STOP is set in flags and null passed as buffer, only the
 * stop condition is sent on the bus. If I2CIF_SEND_START is set in flags
 * a new start condition will be sent. 
 * 
 * @param  identifier_t i2c_bus_id  : I2C bus which shall start the connection
 * @param  I2CIf_flags flags        : Flags to be sent
 * @param  uint16_t address         : I2C to be used
 * @param  uint16_t data_length     : data length to transmat
 * @param  uint8_t data             : data to be transmitted
 * @return std_return_type_t status : If the bus id does not exist on the host
 *                                    the function returns E_NOT_EXISTING. If
 *                                    no transmission is active and I2CIF_SEND_START
 *                                    is not set in flags the function returns
 *                                    E_STATE_ERR. If data is null and I2CIF_SEND_STOP
 *                                    is not set, the function returns E_VALUE_NULL.
 * 
 *  Else it returns E_OK.
 */
std_return_type_t I2CIf_send(identifier_t i2c_bus_id, I2CIf_flags_t flags, uint16_t address, 
                             uint16_t data_length, uint8_t *data);

/**
 * @brief Read from I2C bus
 *  
 * This function starts reading from the I2C bus. If I2CIF_SEND_START is set in 
 * flags a new start condition will be sent. 
 * 
 * @param  identifier_t i2c_bus_id  : I2C bus which shall start the connection
 * @param  I2CIf_flags flags        : Flags to be sent
 * @param  uint16_t address         : I2C to be used
 * @param  uint16_t buffer_length   : size of data to be read from the bus
 * @param  uint8_t buffer           : buffer for received buffer
 * @return std_return_type_t status : If the bus id does not exist on the host
 *                                    the function returns E_NOT_EXISTING. If
 *                                    no transmission is active the function
 *                                    returns E_STATE_ERR. Else it returns E_OK.
 */
std_return_type_t I2CIf_read(identifier_t i2c_bus_id, I2CIf_flags_t flags, uint16_t address,
                             uint16_t buffer_length, uint8_t *buffer);

/**
 * @brief Stops a transmission
 *  
 * This function triggers the I2C to send a stop condition.
 * 
 * @param  identifier_t i2c_bus_id  : I2C bus which shall start the connection
 * @return std_return_type_t status : If the bus id does not exist on the host
 *                                    the function returns E_NOT_EXISTING. If
 *                                    the I2C is not master or did not start the
 *                                    bus configuration the function returns 
 *                                    E_STATE_ERR. Else it returns E_OK.
 */
std_return_type_t I2CIf_stop_transmission(identifier_t i2c_bus_id);

/**
 * @brief Get the current devices status
 *  
 * This function returns the current device status.
 * 
 * @param  identifier_t i2c_bus_id  : I2C bus which shall start the connection
 * @return I2CIf_status_t status    : The status of the device
 */
I2CIf_status_t I2CIf_get_status(identifier_t i2c_bus_id);

/**
 * @brief Get the current state of the bus
 *  
 * This function returns the current bus status.
 * 
 * @param  identifier_t i2c_bus_id  : I2C bus which shall start the connection
 * @return I2CIf_bus_state_t status : The status of the bus
 */
I2CIf_bus_state_t I2CIf_get_bus_status(identifier_t i2c_bus_id);


#endif