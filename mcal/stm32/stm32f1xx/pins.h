#ifndef MCAL_PINS_H
#define MCAL_PINS_H

// define a pin
// format : #define PIN_<Port>_Portnumber 0x<Port No [15:8]><Pin No[7:0]> 
// example: #define PINB1 0x0101
// definitoin for a whole port
// format : #define PORT_<Port> 0x<Port No [15:8]>FF
// example: #define PORT_C 0x02FF

#define PIN_A_00    0x0000
#define PIN_A_01    0x0001
#define PIN_A_02    0x0002
#define PIN_A_03    0x0003
#define PIN_A_04    0x0004
#define PIN_A_05    0x0005
#define PIN_A_06    0x0006
#define PIN_A_07    0x0007
#define PIN_A_08    0x0008
#define PIN_A_09    0x0009
#define PIN_A_10    0x000A
#define PIN_A_11    0x000B
#define PIN_A_12    0x000C
#define PIN_A_13    0x000D
#define PIN_A_14    0x000E
#define PIN_A_15    0x000F
#define PORT_A      0x00FF

#define PIN_B_00    0x0100
#define PIN_B_01    0x0101
#define PIN_B_02    0x0102
#define PIN_B_03    0x0103
#define PIN_B_04    0x0104
#define PIN_B_05    0x0105
#define PIN_B_06    0x0106
#define PIN_B_07    0x0107
#define PIN_B_08    0x0108
#define PIN_B_09    0x0109
#define PIN_B_10    0x010A
#define PIN_B_11    0x010B
#define PIN_B_12    0x010C
#define PIN_B_13    0x010D
#define PIN_B_14    0x010E
#define PIN_B_15    0x010F
#define PORT_B      0x01FF

#define PIN_C_00    0x0200
#define PIN_C_01    0x0201
#define PIN_C_02    0x0202
#define PIN_C_03    0x0203
#define PIN_C_04    0x0204
#define PIN_C_05    0x0205
#define PIN_C_06    0x0206
#define PIN_C_07    0x0207
#define PIN_C_08    0x0208
#define PIN_C_09    0x0209
#define PIN_C_10    0x020A
#define PIN_C_11    0x020B
#define PIN_C_12    0x020C
#define PIN_C_13    0x020D
#define PIN_C_14    0x020E
#define PIN_C_15    0x020F
#define PORT_C      0x02FF

#define PIN_D_00    0x0300
#define PIN_D_01    0x0301
#define PIN_D_02    0x0302
#define PIN_D_03    0x0303
#define PIN_D_04    0x0304
#define PIN_D_05    0x0305
#define PIN_D_06    0x0306
#define PIN_D_07    0x0307
#define PIN_D_08    0x0308
#define PIN_D_09    0x0309
#define PIN_D_10    0x030A
#define PIN_D_11    0x030B
#define PIN_D_12    0x030C
#define PIN_D_13    0x030D
#define PIN_D_14    0x030E
#define PIN_D_15    0x030F
#define PORT_D      0x03FF

#define PIN_E_00    0x0400
#define PIN_E_01    0x0401
#define PIN_E_02    0x0402
#define PIN_E_03    0x0403
#define PIN_E_04    0x0404
#define PIN_E_05    0x0405
#define PIN_E_06    0x0406
#define PIN_E_07    0x0407
#define PIN_E_08    0x0408
#define PIN_E_09    0x0409
#define PIN_E_10    0x040A
#define PIN_E_11    0x040B
#define PIN_E_12    0x040C
#define PIN_E_13    0x040D
#define PIN_E_14    0x040E
#define PIN_E_15    0x040F
#define PORT_E      0x04FF

#endif