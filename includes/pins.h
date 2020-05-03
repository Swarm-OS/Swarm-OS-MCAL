#ifndef MCAL_PINS_H
#define MCAL_PINS_H

/**
 * @file timer.h
 * @author Christoph Lehr
 * @date 6 Aug 2019
 * @brief File containing wrapper for pins
 *
 * This file specifies a generic wrapper for the pin 
 * definitions of the single MCUs
 */

#define __pin_t      (GPIOIf_pin_t)

#define PIN_A_00    (__pin_t 0x0000)
#define PIN_A_01    (__pin_t 0x0001)
#define PIN_A_02    (__pin_t 0x0002)
#define PIN_A_03    (__pin_t 0x0003)
#define PIN_A_04    (__pin_t 0x0004)
#define PIN_A_05    (__pin_t 0x0005)
#define PIN_A_06    (__pin_t 0x0006)
#define PIN_A_07    (__pin_t 0x0007)
#define PIN_A_08    (__pin_t 0x0008)
#define PIN_A_09    (__pin_t 0x0009)
#define PIN_A_10    (__pin_t 0x000A)
#define PIN_A_11    (__pin_t 0x000B)
#define PIN_A_12    (__pin_t 0x000C)
#define PIN_A_13    (__pin_t 0x000D)
#define PIN_A_14    (__pin_t 0x000E)
#define PIN_A_15    (__pin_t 0x000F)
#define PORT_A      (__pin_t 0x00FF)

#define PIN_B_00    (__pin_t 0x0100)
#define PIN_B_01    (__pin_t 0x0101)
#define PIN_B_02    (__pin_t 0x0102)
#define PIN_B_03    (__pin_t 0x0103)
#define PIN_B_04    (__pin_t 0x0104)
#define PIN_B_05    (__pin_t 0x0105)
#define PIN_B_06    (__pin_t 0x0106)
#define PIN_B_07    (__pin_t 0x0107)
#define PIN_B_08    (__pin_t 0x0108)
#define PIN_B_09    (__pin_t 0x0109)
#define PIN_B_10    (__pin_t 0x010A)
#define PIN_B_11    (__pin_t 0x010B)
#define PIN_B_12    (__pin_t 0x010C)
#define PIN_B_13    (__pin_t 0x010D)
#define PIN_B_14    (__pin_t 0x010E)
#define PIN_B_15    (__pin_t 0x010F)
#define PORT_B      (__pin_t 0x01FF)

#define PIN_C_00    ( __pin_t 0x0200)
#define PIN_C_01    ( __pin_t 0x0201)
#define PIN_C_02    ( __pin_t 0x0202)
#define PIN_C_03    ( __pin_t 0x0203)
#define PIN_C_04    ( __pin_t 0x0204)
#define PIN_C_05    ( __pin_t 0x0205)
#define PIN_C_06    ( __pin_t 0x0206)
#define PIN_C_07    ( __pin_t 0x0207)
#define PIN_C_08    ( __pin_t 0x0208)
#define PIN_C_09    ( __pin_t 0x0209)
#define PIN_C_10    ( __pin_t 0x020A)
#define PIN_C_11    ( __pin_t 0x020B)
#define PIN_C_12    ( __pin_t 0x020C)
#define PIN_C_13    ( __pin_t 0x020D)
#define PIN_C_14    ( __pin_t 0x020E)
#define PIN_C_15    ( __pin_t 0x020F)
#define PORT_C      ( __pin_t 0x02FF)

#define PIN_D_00    ( __pin_t 0x0300)
#define PIN_D_01    ( __pin_t 0x0301)
#define PIN_D_02    ( __pin_t 0x0302)
#define PIN_D_03    ( __pin_t 0x0303)
#define PIN_D_04    ( __pin_t 0x0304)
#define PIN_D_05    ( __pin_t 0x0305)
#define PIN_D_06    ( __pin_t 0x0306)
#define PIN_D_07    ( __pin_t 0x0307)
#define PIN_D_08    ( __pin_t 0x0308)
#define PIN_D_09    ( __pin_t 0x0309)
#define PIN_D_10    ( __pin_t 0x030A)
#define PIN_D_11    ( __pin_t 0x030B)
#define PIN_D_12    ( __pin_t 0x030C)
#define PIN_D_13    ( __pin_t 0x030D)
#define PIN_D_14    ( __pin_t 0x030E)
#define PIN_D_15    ( __pin_t 0x030F)
#define PORT_D      ( __pin_t 0x03FF)

#define PIN_E_00    ( __pin_t 0x0400)
#define PIN_E_01    ( __pin_t 0x0401)
#define PIN_E_02    ( __pin_t 0x0402)
#define PIN_E_03    ( __pin_t 0x0403)
#define PIN_E_04    ( __pin_t 0x0404)
#define PIN_E_05    ( __pin_t 0x0405)
#define PIN_E_06    ( __pin_t 0x0406)
#define PIN_E_07    ( __pin_t 0x0407)
#define PIN_E_08    ( __pin_t 0x0408)
#define PIN_E_09    ( __pin_t 0x0409)
#define PIN_E_10    ( __pin_t 0x040A)
#define PIN_E_11    ( __pin_t 0x040B)
#define PIN_E_12    ( __pin_t 0x040C)
#define PIN_E_13    ( __pin_t 0x040D)
#define PIN_E_14    ( __pin_t 0x040E)
#define PIN_E_15    ( __pin_t 0x040F)
#define PORT_E      ( __pin_t 0x04FF)

#define PIN_F_00    ( __pin_t 0x0500)
#define PIN_F_01    ( __pin_t 0x0501)
#define PIN_F_02    ( __pin_t 0x0502)
#define PIN_F_03    ( __pin_t 0x0503)
#define PIN_F_04    ( __pin_t 0x0504)
#define PIN_F_05    ( __pin_t 0x0505)
#define PIN_F_06    ( __pin_t 0x0506)
#define PIN_F_07    ( __pin_t 0x0507)
#define PIN_F_08    ( __pin_t 0x0508)
#define PIN_F_09    ( __pin_t 0x0509)
#define PIN_F_10    ( __pin_t 0x050A)
#define PIN_F_11    ( __pin_t 0x050B)
#define PIN_F_12    ( __pin_t 0x050C)
#define PIN_F_13    ( __pin_t 0x050D)
#define PIN_F_14    ( __pin_t 0x050E)
#define PIN_F_15    ( __pin_t 0x050F)
#define PORT_F      ( __pin_t 0x05FF)

#define PIN_G_00    ( __pin_t 0x0600)
#define PIN_G_01    ( __pin_t 0x0601)
#define PIN_G_02    ( __pin_t 0x0602)
#define PIN_G_03    ( __pin_t 0x0603)
#define PIN_G_04    ( __pin_t 0x0604)
#define PIN_G_05    ( __pin_t 0x0605)
#define PIN_G_06    ( __pin_t 0x0606)
#define PIN_G_07    ( __pin_t 0x0607)
#define PIN_G_08    ( __pin_t 0x0608)
#define PIN_G_09    ( __pin_t 0x0609)
#define PIN_G_10    ( __pin_t 0x060A)
#define PIN_G_11    ( __pin_t 0x060B)
#define PIN_G_12    ( __pin_t 0x060C)
#define PIN_G_13    ( __pin_t 0x060D)
#define PIN_G_14    ( __pin_t 0x060E)
#define PIN_G_15    ( __pin_t 0x060F)
#define PORT_G      ( __pin_t 0x06FF)

#define PIN_H_00    ( __pin_t 0x0700)
#define PIN_H_01    ( __pin_t 0x0701)
#define PIN_H_02    ( __pin_t 0x0702)
#define PIN_H_03    ( __pin_t 0x0703)
#define PIN_H_04    ( __pin_t 0x0704)
#define PIN_H_05    ( __pin_t 0x0705)
#define PIN_H_06    ( __pin_t 0x0706)
#define PIN_H_07    ( __pin_t 0x0707)
#define PIN_H_08    ( __pin_t 0x0708)
#define PIN_H_09    ( __pin_t 0x0709)
#define PIN_H_10    ( __pin_t 0x070A)
#define PIN_H_11    ( __pin_t 0x070B)
#define PIN_H_12    ( __pin_t 0x070C)
#define PIN_H_13    ( __pin_t 0x070D)
#define PIN_H_14    ( __pin_t 0x070E)
#define PIN_H_15    ( __pin_t 0x070F)
#define PORT_H      ( __pin_t 0x07FF)

#endif