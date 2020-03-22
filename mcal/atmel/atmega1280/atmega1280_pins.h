#ifndef MCAL_PINS_H
#define MCAL_PINS_H

// define a pin
// format : #define PIN_<Port>_Portnumber 0x<Port No [15:8]><Pin No[7:0]> 
// example: #define PINB1 0x0101
// definitoin for a whole port
// format : #define PORT_<Port> 0x<Port No [15:8]>FF
// example: #define PORT_C 0x02FF

#define PIN_A_0 0x0000
#define PIN_A_1 0x0001
#define PIN_A_2 0x0002
#define PIN_A_3 0x0003
#define PIN_A_4 0x0004
#define PIN_A_5 0x0005
#define PIN_A_6 0x0006
#define PIN_A_7 0x0007
#define PORT_A  0x00FF

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

#define PIN_E_0 0x0400
#define PIN_E_1 0x0401
#define PIN_E_2 0x0402
#define PIN_E_3 0x0403
#define PIN_E_4 0x0404
#define PIN_E_5 0x0405
#define PIN_E_6 0x0406
#define PIN_E_7 0x0407
#define PORT_E  0x04FF

#define PIN_F_0 0x0500
#define PIN_F_1 0x0501
#define PIN_F_2 0x0502
#define PIN_F_3 0x0503
#define PIN_F_4 0x0504
#define PIN_F_5 0x0505
#define PIN_F_6 0x0506
#define PIN_F_7 0x0507
#define PORT_F  0x05FF

#define PIN_G_0 0x0600
#define PIN_G_1 0x0601
#define PIN_G_2 0x0602
#define PIN_G_3 0x0603
#define PIN_G_4 0x0604
#define PIN_G_5 0x0605
#define PIN_G_6 0x0606
#define PIN_G_7 0x0607
#define PORT_G  0x06FF

#define PIN_H_0 0x0700
#define PIN_H_1 0x0701
#define PIN_H_2 0x0702
#define PIN_H_3 0x0703
#define PIN_H_4 0x0704
#define PIN_H_5 0x0705
#define PIN_H_6 0x0706
#define PIN_H_7 0x0707
#define PORT_H  0x07FF

#define PIN_I_0 0x0800
#define PIN_I_1 0x0801
#define PIN_I_2 0x0802
#define PIN_I_3 0x0803
#define PIN_I_4 0x0804
#define PIN_I_5 0x0805
#define PIN_I_6 0x0806
#define PIN_I_7 0x0807
#define PORT_I  0x08FF

#define PIN_J_0 0x0900
#define PIN_J_1 0x0901
#define PIN_J_2 0x0902
#define PIN_J_3 0x0903
#define PIN_J_4 0x0904
#define PIN_J_5 0x0905
#define PIN_J_6 0x0906
#define PIN_J_7 0x0907
#define PORT_J  0x09FF

#define PIN_K_0 0x0A00
#define PIN_K_1 0x0A01
#define PIN_K_2 0x0A02
#define PIN_K_3 0x0A03
#define PIN_K_4 0x0A04
#define PIN_K_5 0x0A05
#define PIN_K_6 0x0A06
#define PIN_K_7 0x0A07
#define PORT_K  0x0AFF

#endif