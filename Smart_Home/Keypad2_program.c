/*
 * Keypad_program.c
 *
 *  Created on: Mar 10, 2022
 *      Author: INTEL
 */
#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"Keypad2_interface.h"
#include "Keypad2_privet.h"
#include"util/delay.h"

void Keypad_voidInit(void){
	DIO_enumSetPinDirection(Keypad_RW0,Keypad_Port,DIO_INPUT);
	DIO_enumSetPinDirection(Keypad_RW1,Keypad_Port,DIO_INPUT);
	DIO_enumSetPinDirection(Keypad_RW2,Keypad_Port,DIO_INPUT);
	DIO_enumSetPinDirection(Keypad_RW3,Keypad_Port,DIO_INPUT);
	//ENABLE PULLUP
	DIO_enumSetPinValue(Keypad_RW0,Keypad_Port,DIO_HIGH);
	DIO_enumSetPinValue(Keypad_RW1,Keypad_Port,DIO_HIGH);
	DIO_enumSetPinValue(Keypad_RW2,Keypad_Port,DIO_HIGH);
	DIO_enumSetPinValue(Keypad_RW3,Keypad_Port,DIO_HIGH);

	DIO_enumSetPinDirection(Keypad_col0,Keypad_Port,DIO_OUTPUT);
	DIO_enumSetPinDirection(Keypad_col1,Keypad_Port,DIO_OUTPUT);
	DIO_enumSetPinDirection(Keypad_col2,Keypad_Port,DIO_OUTPUT);
	DIO_enumSetPinDirection(Keypad_col3,Keypad_Port,DIO_OUTPUT);

	DIO_enumSetPinValue(Keypad_col0,Keypad_Port,DIO_HIGH);
	DIO_enumSetPinValue(Keypad_col1,Keypad_Port,DIO_HIGH);
	DIO_enumSetPinValue(Keypad_col2,Keypad_Port,DIO_HIGH);
	DIO_enumSetPinValue(Keypad_col3,Keypad_Port,DIO_HIGH);


}
U8   Keypad_U8GetPressed(void){
	U8 LOC_u8ReturnValue=0;
	U8 LOC_u8ColItiration=0;
	U8 LOC_u8RWItiration=0;
	U8 LOC_u8GetPressed=0;
	for(LOC_u8ColItiration=0;LOC_u8ColItiration<4;LOC_u8ColItiration++){
		DIO_enumSetPinValue(KeyPad_u8COL[LOC_u8ColItiration],Keypad_Port,DIO_LOW);
		for(LOC_u8RWItiration=0;LOC_u8RWItiration<4;LOC_u8RWItiration++){
			DIO_enumGetPinValue(Keypad_Port,KeyPad_u8RW[LOC_u8RWItiration],&LOC_u8GetPressed);
			if(LOC_u8GetPressed==0){
				_delay_ms(50);
				DIO_enumGetPinValue(Keypad_Port,KeyPad_u8RW[LOC_u8RWItiration],&LOC_u8GetPressed);
				if(LOC_u8GetPressed==0){
					LOC_u8ReturnValue=Keypad_u8Buttons[LOC_u8RWItiration][LOC_u8ColItiration];
				}
				DIO_enumGetPinValue(Keypad_Port,KeyPad_u8RW[LOC_u8RWItiration],&LOC_u8GetPressed);
				while(LOC_u8GetPressed==0){
					DIO_enumGetPinValue(Keypad_Port,KeyPad_u8RW[LOC_u8RWItiration],&LOC_u8GetPressed);
				}
				break;
			}
		}
		DIO_enumSetPinValue(KeyPad_u8COL[LOC_u8ColItiration],Keypad_Port,DIO_HIGH);
	}
	return LOC_u8ReturnValue;
}

