#ifndef MCAL_PINS_H
#define MCAL_PINS_H

// define a pin
// format : #define PIN_<Port>_Portnumber 0x<Port No [15:8]><Pin No[7:0]> 
// example: #define PINB1 0x0101
// definitoin for a whole port
// format : #define PORT_<Port> 0x<Port No [15:8]>FF
// example: #define PORT_C 0x02FF

#define PIN_B_0 0x0100
#define PIN_B_1 0x0101
#define PIN_B_2 0x0102
#define PIN_B_3 0x0103
#define PIN_B_4 0x0104
#define PIN_B_5 0x0105
#define PIN_B_6 0x0106
#define PIN_B_7 0x0107
#define PORT_B  0x01FF

#define PIN_C_0 0x0200
#define PIN_C_1 0x0201
#define PIN_C_2 0x0202
#define PIN_C_3 0x0203
#define PIN_C_4 0x0204
#define PIN_C_5 0x0205
#define PIN_C_6 0x0206
#define PIN_C_7 0x0207
#define PORT_C  0x02FF

#define PIN_D_0 0x0300
#define PIN_D_1 0x0301
#define PIN_D_2 0x0302
#define PIN_D_3 0x0303
#define PIN_D_4 0x0304
#define PIN_D_5 0x0305
#define PIN_D_6 0x0306
#define PIN_D_7 0x0307
#define PORT_D  0x03FF

#endif