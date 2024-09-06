/*
 * Kypd.c
 *
 *  Created on: Oct 11, 2023
 *      Author: MaKa
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Kypd.h"
#include "DIO_interface.h"
#include "DIO_privet.h"
#include <util/delay.h>
#define DEBOUNCE_DELAY 10 // 50 milliseconds debounce delay
U8 Key_arr[4][4]={{'7','8','9','/'}//r0
                 ,{'4','5','6','*'}//r1
                 ,{'1','2','3','-'}//r2
                 ,{'c','0','=','+'}/*r3*/};

void Kypad_init(void)
{
	// Set columns as input with pull-up resistors
	for(U8 i=0; i<4; i++)
	{
		DIO_enumSetPinDirection(FIRSTCOL+i, DIO_PORTB, DIO_INPUT);
		DIO_enumSetPinValue(FIRSTCOL+i, DIO_PORTB, DIO_HIGH);  // Enable pull-up resistor
	}
	
	// Set rows as output and set them high
	for(U8 i=0; i<4; i++)
	{
		DIO_enumSetPinDirection(FIRSTRW+i, DIO_PORTB, DIO_OUTPUT);
		DIO_enumSetPinValue(FIRSTRW+i, DIO_PORTB, DIO_HIGH);
	}
}


/*set any switch pressed&return this sw&loop 16 sw*/
U8 Kypad_GetKey(void)
{
	U8 COLITERATION=0;
	U8 RWITERATION=0;
	U8 RETURN_VAL='f';
	U8 KEY_VAL;

	// Assume no key is pressed initially
	RETURN_VAL = 0xFF;

	for(RWITERATION=0; RWITERATION<4; RWITERATION++)
	{
		DIO_enumSetPinValue(RWITERATION, DIO_PORTB, DIO_LOW);

		for(COLITERATION=4; COLITERATION<8; COLITERATION++)
		{
			DIO_enumGetPinValue(DIO_PORTB, COLITERATION, &KEY_VAL);
			if(KEY_VAL == 0)
			{
				
				RETURN_VAL = Key_arr[RWITERATION][COLITERATION-4];
				while(GET_BIT(PINB_Reg, COLITERATION) == 0); // Wait for key release
			}
		}
		DIO_enumSetPinValue(RWITERATION, DIO_PORTB, DIO_HIGH);
	}

	return RETURN_VAL;
}