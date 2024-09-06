/*
 * Keypad_config.h
 *
 *  Created on: Mar 10, 2022
 *      Author: INTEL
 */

#ifndef HAL_KEYPAD2_KEYPAD2_CONFIG_H_
#define HAL_KEYPAD2_KEYPAD2_CONFIG_H_
#define KeyPad_SW_1  '7'
#define KeyPad_SW_2  '8'
#define KeyPad_SW_3  '9'
#define KeyPad_SW_4  '/'
#define KeyPad_SW_5  '4'
#define KeyPad_SW_6  '5'
#define KeyPad_SW_7  '6'
#define KeyPad_SW_8  '*'
#define KeyPad_SW_9  '1'
#define KeyPad_SW_10 '2'
#define KeyPad_SW_11 '3'
#define KeyPad_SW_12 '-'
#define KeyPad_SW_13 'C'
#define KeyPad_SW_14 '0'
#define KeyPad_SW_15 '='
#define KeyPad_SW_16 '+'

//BUTTONS ARRAY            /*C0        , C1        ,C2         ,C3          */
U8 Keypad_u8Buttons[KeyPad_Rw_NUM][KeyPad_COL_NUM]={{KeyPad_SW_1,KeyPad_SW_2,KeyPad_SW_3,KeyPad_SW_4},//RW0
                           {KeyPad_SW_5,KeyPad_SW_6,KeyPad_SW_7,KeyPad_SW_8},//RW1
						   {KeyPad_SW_9,KeyPad_SW_10,KeyPad_SW_11,KeyPad_SW_12},//RW2
						   {KeyPad_SW_13,KeyPad_SW_14,KeyPad_SW_15,KeyPad_SW_16}//RW3
};
/*option
 * DIO_PORTA
 * DIO_PORTB
 * DIO_PORTC
 * DIO_PORTD*/
#define Keypad_Port DIO_PORTB
/*RW&COL PINS OPTION
 * DIO_PIN0
 * DIO_PIN1
 * DIO_PIN2
 * DIO_PIN3
 * DIO_PIN4
 * DIO_PIN5
 * DIO_PIN6
 * DIO_PIN7*/
//ROWS PINS
#define Keypad_RW0  DIO_PIN0
#define Keypad_RW1  DIO_PIN1
#define Keypad_RW2  DIO_PIN2
#define Keypad_RW3  DIO_PIN3
//COL PINS
#define Keypad_col0 DIO_PIN4
#define Keypad_col1 DIO_PIN5
#define Keypad_col2 DIO_PIN6
#define Keypad_col3 DIO_PIN7


#endif /* HAL_KEYPAD2_KEYPAD2_CONFIG_H_ */
