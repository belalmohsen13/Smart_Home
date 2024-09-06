
/*
* Smart_Home.c
*
* Created: 9/3/2024 2:15:51 PM
* Author : Belal Mohsen Mosbah
*/

#include <avr/io.h>
#include "string.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <util/delay.h>

#include "ADC_interface.h"
#include "CLCD_interface.h"
#include "DIO_interface.h"
#include "Keypad2_interface.h"
#include "USART_interface.h"


U8 checker(U8 Enter[]) {
	U8 User_ID_1[]={'1','2','3'};
	U8 User_ID_2[]={'2','2','2'};
		

		 if (memcmp(Enter, User_ID_1, sizeof(User_ID_1)) == 0) {
			 return 3;
		 }
		 
		 if (memcmp(Enter, User_ID_2, sizeof(User_ID_2)) == 0) {
			 return 2;
			 }
	 
		return 0;
}



void Ringer(void){
	u8 x;
	 static U8 zzz=0;
	 static U8 zz=1;
	DIO_enumGetPinValue(DIO_PORTD,DIO_PIN7,&x );
	if (x==0){
		//DIO_enumSetPinValue(DIO_PIN7,DIO_PORTA,DIO_HIGH);
		DIO_enumSetPinValue(DIO_PIN2,DIO_PORTA,DIO_HIGH);
		
		  CLCD_GoTo(1,1);
		CLCD_SendString(" ringing          ");
		CLCD_GoTo(2,1);
		CLCD_SendString("                  ");
		_delay_ms(4000);
		
		if(zzz==0){
			USART_voidSendChar('\r'); 
			USART_voidSendChar('\n'); // Send newline
			USART_VoidSendString(" Someone is ringing");
			USART_voidSendChar('\r'); 
			USART_voidSendChar('\n'); // Send newline
			zzz=1;
			zz=0;
		}
	}
	else{
		//DIO_enumSetPinValue(DIO_PIN7,DIO_PORTA,DIO_LOW);
		DIO_enumSetPinValue(DIO_PIN2,DIO_PORTA,DIO_LOW);
		if(zz==0){
		USART_voidSendChar('\r');
		USART_voidSendChar('\n'); // Send newline
		USART_VoidSendString(" Answered  Continue");
		USART_voidSendChar('\r');
		USART_voidSendChar('\n'); // Send newline
		zz=1;
		}
		zzz=0;
	}
	
}

int temperature(U8 x){
	U16 temp;
	U8 cc=x;
	u8 flag_fire=0;
	temp = ADC_u16GetChannalResult(ADC_CHANNAL_4);
	float tempf = temp /2.01 ;
	CLCD_GoTo(1,1);
	//CLCD_WritNum(tempf);
	

	if (tempf>30.0){
		flag_fire=1;
		while(flag_fire){
			CLCD_GoTo(1,1);
			CLCD_SendString(" fire             ");
			CLCD_GoTo(2,1);
			CLCD_SendString("                   ");
			DIO_enumSetPinValue(DIO_PIN7,DIO_PORTA,DIO_HIGH);
			DIO_enumSetPinValue(DIO_PIN2,DIO_PORTA,DIO_HIGH);
			cc = Kypad_GetKey();
			
				if (tempf<30.0){
					flag_fire=0;
				}


			if (cc=='c')
			{
				DIO_enumSetPinValue(DIO_PIN7,DIO_PORTA,DIO_LOW);
				DIO_enumSetPinValue(DIO_PIN2,DIO_PORTA,DIO_LOW);
				return 0;
				break;
				
			}
		}
	}
	
	return 1;

}




int main(void)
{
	DIO_enumSetPinDirection(DIO_PIN0,DIO_PORTA,DIO_OUTPUT);
	DIO_enumSetPinDirection(DIO_PIN1,DIO_PORTA,DIO_OUTPUT);
	DIO_enumSetPinDirection(DIO_PIN2,DIO_PORTA,DIO_OUTPUT);
	DIO_enumSetPinDirection(DIO_PIN3,DIO_PORTA,DIO_OUTPUT);
	DIO_enumSetPinDirection(DIO_PIN7,DIO_PORTA,DIO_OUTPUT);
	
	DIO_enumSetPinDirection(DIO_PIN4, DIO_PORTA,DIO_INPUT);

	DIO_enumSetPinDirection(DIO_PIN7, DIO_PORTD,DIO_INPUT);
	
	DIO_enumSetPinValue(DIO_PIN7, DIO_PORTD, DIO_HIGH);
	
	U8 Home_Checker = 1, flag_Home = 1, flag_Room2 = 0;
	U8 led1_flag = 0, led_flag2 = 0, flag_Room1 = 0, fan_flag=0;



	CLCD_init();
	ADC_voidInit();
	Kypad_init();
	USART_voidINIT();
	ADC_voidInit();

	U8 User_ID_1[] = {'1', '2', '3'}; // lookout team the keypad gives huskyyyyyy code 
	U8 User_ID_2[] = {'2', '2', '2'};

	U8 User_Pass_1[] = {'1', '1', '1'};
	U8 User_Pass_2[] = {'2', '2', '2'};
		
	U8 Enter[3];	
	
	U8 person;

	U8 passwordIndex = 0;
	const U8 MAX_PASSWORD_LENGTH = 3;
	U8 EnteredPassword[3];
	U8 KEY;
	U8 i = 0;
	U8 flag = 0;
	U8 cc_checker=9;
	U8 menu_printed=0;

	USART_VoidSendString("(Use (=) as Enter like keyboard)");
	USART_voidSendChar('\r'); // Send carriage return
	USART_voidSendChar('\n'); // Send newline
	USART_voidSendChar('\r'); // Send carriage return
	USART_voidSendChar('\n'); // Send newline
	USART_VoidSendString(" Welcome! Enter ID: \n");
	USART_voidSendChar('\r'); // Send carriage return
	USART_voidSendChar('\n'); // Send newline

	while (1)
	{
		Ringer();
		if (cc_checker !=0)
		{
			cc_checker=temperature(1);
		}
		
		KEY = Kypad_GetKey();
		if (KEY != 0xFF)
		{
			
			
			 if (KEY != '='){
			 USART_voidTRANSMITR(KEY);
				Enter[i++] = KEY;
			 
			}

			if (KEY == '=')
			{
				
				flag  =3;
				 person = checker(Enter);
				if (person==0)
				{
					USART_voidSendChar('\r'); // Send carriage return
					USART_voidSendChar('\n'); // Send newline
					USART_VoidSendString(" Error, system close");
					_delay_ms(500);
					break;
				}
				
				
				
				KEY = 0;
				passwordIndex = 0; // Reset password index for new input

				while (flag > 0)
				{
					Ringer();
					if (cc_checker !=0)
					{
					cc_checker=temperature(1);
					}
					if (flag!=99 && flag!=0)
					{
					Ringer();
					if (cc_checker !=0)
					{
						cc_checker=temperature(1);
					}
					
					USART_voidSendChar('\r'); // Send carriage return
					USART_voidSendChar('\n'); // Send newline
					USART_VoidSendString(" Enter Password:\n");
					USART_voidSendChar('\r'); // Send carriage return
					USART_voidSendChar('\n'); // Send newline
					}

					while (1)
					{
						Ringer();
						if (cc_checker !=0)
						{
							cc_checker=temperature(1);
						}
						KEY = Kypad_GetKey();

						if (KEY != 0xFF)
						{
							if (cc_checker !=0)
							{
								cc_checker=temperature(1);
							}
							if (KEY == '=')
							{
								Ringer();
								
								if (cc_checker !=0)
								{
									cc_checker=temperature(1);
								}
								EnteredPassword[passwordIndex] = '\0'; 

					
								if ((person == 3 && memcmp(EnteredPassword, User_Pass_1, MAX_PASSWORD_LENGTH) == 0) ||
								(person == 2 && memcmp(EnteredPassword, User_Pass_2, MAX_PASSWORD_LENGTH) == 0))
								{
									Ringer();
									USART_voidSendChar('\r'); // Send carriage return
									USART_voidSendChar('\n'); // Send newline
									USART_VoidSendString(" Welcome Admin!\n");
									flag=99;
									/////////////////////////////////////////////////////////////////////////////
									//part2
									
									USART_voidSendChar('\r'); // Send carriage return
									USART_voidSendChar('\n'); // Send newline
									
									
									
									
								while (Home_Checker) {
									Ringer();
									if (cc_checker !=0)
									{
										cc_checker=temperature(1);
									}
									
									CLCD_WriteInes(0x01); // Clear the LCD
									CLCD_SendString(" Welcome Home!");
									_delay_ms(4000);

									while (flag_Home) {
										Ringer();
										CLCD_GoTo(1, 1);
										CLCD_SendString("1.Room1  2.Room2");
										CLCD_GoTo(2, 1);
										CLCD_SendString("3.Exit          ");
										
										if (!menu_printed) {
										USART_voidSendChar('\r'); // Send carriage return
										USART_voidSendChar('\n'); // Send newline
										USART_VoidSendString(" 1.Room1  2.Room2");
										
										USART_voidSendChar('\r'); // Send carriage return
										USART_voidSendChar('\n'); // Send newline
										USART_VoidSendString(" 3.Exit");
										USART_voidSendChar('\r'); // Send carriage return
										USART_voidSendChar('\n'); // Send newline
										menu_printed=1;
										}
										
										if (cc_checker !=0)
										{
											cc_checker=temperature(1);
										}
										
										KEY = Kypad_GetKey();
										
										
										
										if (cc_checker !=0)
										{
											cc_checker=temperature(1);
										}
										
										if (KEY != 0xFF) {
											menu_printed=0;
											switch (KEY) {
												case '1':
												// Room 1 Controls
												Ringer();
												if (cc_checker !=0)
												{
													cc_checker=temperature(1);
												}
												
												flag_Room1 = 1;
												CLCD_WriteInes(0x01);  // Clear the LCD
												CLCD_SendString(" Room 1 Selected");
												
												
												if (!menu_printed) {
												USART_voidSendChar('\r'); // Send carriage return
												USART_voidSendChar('\n'); // Send newline
												USART_VoidSendString(" Room 1 Selected");
												USART_voidSendChar('\r'); // Send carriage return
												USART_voidSendChar('\n'); // Send newline
												
												menu_printed=1;
												}
												menu_printed=0;
												_delay_ms(4000);
												while (flag_Room1) {
													Ringer();
													
													if (cc_checker !=0)
													{
														cc_checker=temperature(1);
													}
													
													CLCD_GoTo(1, 1);
													CLCD_SendString("1.LED_1  2.LED_2");
													CLCD_GoTo(2, 1);
													CLCD_SendString("3.FAN     4.Back");
													
													if (!menu_printed) {
													USART_voidSendChar('\r'); // Send carriage return
													USART_voidSendChar('\n'); // Send newline
													USART_VoidSendString(" 1.LED_1     2.LED_2");
													
													USART_voidSendChar('\r'); // Send carriage return
													USART_voidSendChar('\n'); // Send newline
													USART_VoidSendString(" 3.FAN        4.Back");
													USART_voidSendChar('\r'); // Send carriage return
													USART_voidSendChar('\n'); // Send newline
													menu_printed=1;
													}
													if (cc_checker !=0)
													{
														cc_checker=temperature(1);
													}
													
													KEY = Kypad_GetKey();
													
						
													
													if (KEY != 0xFF) {
														menu_printed=0;
														switch (KEY) {
															case '1':
															// LED 1 Controls
															led1_flag = 1;
															while (led1_flag) {
																Ringer();
																
																if (cc_checker !=0)
																{
																	cc_checker=temperature(1);
																};
																
																CLCD_GoTo(1,1);
																CLCD_SendString("1.LED_on        ");
																CLCD_GoTo(2,1);
																CLCD_SendString("2.LED_off 3.Back");
																
																
																if (!menu_printed) {
																USART_voidSendChar('\r'); // Send carriage return
																USART_voidSendChar('\n'); // Send newline
																USART_VoidSendString(" 1.LED_on        2.LED_off");
																
																USART_voidSendChar('\r'); // Send carriage return
																USART_voidSendChar('\n'); // Send newline
																USART_VoidSendString(" 3.Back      ");
																USART_voidSendChar('\r'); // Send carriage return
																USART_voidSendChar('\n'); // Send newline
																
																
																menu_printed=1;
																}
																
																
																
																if (cc_checker !=0)
																{
																	cc_checker=temperature(1);
																}
																
																KEY = Kypad_GetKey();
																
														
																
																if (KEY != 0xFF) {
																	
																	
																	switch (KEY) {
																		Ringer();
																		
																		
																		case '1':
																		DIO_enumSetPinValue(DIO_PIN0, DIO_PORTA, DIO_HIGH);
																		break;
																		case '2':
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		
																		DIO_enumSetPinValue(DIO_PIN0, DIO_PORTA, DIO_LOW);
																		break;
																		case '3':
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		
																		led1_flag = 0;
																		menu_printed=0;
																		break;
																	}
																}
															}
															break;
															case '2':
															Ringer();
															
															if (cc_checker !=0)
															{
																cc_checker=temperature(1);
															}
															
															// LED 2 Controls
															led_flag2 = 1;
															while (led_flag2) {
																Ringer();
																
																if (cc_checker !=0)
																{
																	cc_checker=temperature(1);
																}
																
																CLCD_GoTo(1,1);
																CLCD_SendString("1.LED_on        ");
																CLCD_GoTo(2,1);
																CLCD_SendString("2.LED_off 3.Back");
																
																
																if (!menu_printed) {
																USART_voidSendChar('\r'); // Send carriage return
																USART_voidSendChar('\n'); // Send newline
																USART_VoidSendString(" 1.LED_on        2.LED_off ");
																
																USART_voidSendChar('\r'); // Send carriage return
																USART_voidSendChar('\n'); // Send newline
																USART_VoidSendString(" 3.Back      ");
																USART_voidSendChar('\r'); // Send carriage return
																USART_voidSendChar('\n'); // Send newline
																menu_printed=1;
																}
																
																KEY = Kypad_GetKey();
																
																if (cc_checker !=0)
																{
																	cc_checker=temperature(1);
																}
																
																if (KEY != 0xFF) {
														
																	switch (KEY) {
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		case '1':
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		
																		DIO_enumSetPinValue(DIO_PIN1, DIO_PORTA, DIO_HIGH);
																		break;
																		case '2':
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		
																		DIO_enumSetPinValue(DIO_PIN1, DIO_PORTA, DIO_LOW);
																		break;
																		case '3':
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		
																		led_flag2 = 0;
																		menu_printed=0;
																		break;
																	}
																}
															}
															break;
															case '3':
															Ringer();
															if (cc_checker !=0)
															{
																cc_checker=temperature(1);
															}
															
															// FAN Controls Placeholder
															
															
															
															
															
															Ringer();
															
															if (cc_checker !=0)
															{
																cc_checker=temperature(1);
															}
															
															// LED 2 Controls
															fan_flag = 1;
															while (fan_flag) {
																Ringer();
																
																if (cc_checker !=0)
																{
																	cc_checker=temperature(1);
																}
																
																CLCD_GoTo(1,1);
																CLCD_SendString("1.FAN_on        ");
																CLCD_GoTo(2,1);
																CLCD_SendString("2.FAN_off 3.Back");
																
																
																if (!menu_printed) {
																	USART_voidSendChar('\r'); // Send carriage return
																	USART_voidSendChar('\n'); // Send newline
																	USART_VoidSendString(" 1.FAN_on        2.FAN_off ");
																	
																	USART_voidSendChar('\r'); // Send carriage return
																	USART_voidSendChar('\n'); // Send newline
																	USART_VoidSendString(" 3.Back      ");
																	USART_voidSendChar('\r'); // Send carriage return
																	USART_voidSendChar('\n'); // Send newline
																	menu_printed=1;
																}
																
																KEY = Kypad_GetKey();
																
																if (cc_checker !=0)
																{
																	cc_checker=temperature(1);
																}
																
																if (KEY != 0xFF) {
																	
																	switch (KEY) {
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		case '1':
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		
																		DIO_enumSetPinValue(DIO_PIN3, DIO_PORTA, DIO_HIGH);
																		break;
																		case '2':
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		
																		DIO_enumSetPinValue(DIO_PIN3, DIO_PORTA, DIO_LOW);
																		break;
																		case '3':
																		Ringer();
																		
																		if (cc_checker !=0)
																		{
																			cc_checker=temperature(1);
																		}
																		
																		fan_flag = 0;
																		menu_printed=0;
																		break;
																	}
																}
															}
															                     
															
															
															
															
															
															case '4':
															Ringer();
															if (cc_checker !=0)
															{
																cc_checker=temperature(1);
															}
															flag_Room1 = 0;
															break;
														}
													}
												}
												break;

												case '2':
												Ringer();
												if (cc_checker !=0)
												{
													cc_checker=temperature(1);
												}
												// Room 2 Controls
												flag_Room2 = 1;
												CLCD_WriteInes(0x01);  // Clear the LCD
												CLCD_SendString("  Room 2 Selected");
												
												if (!menu_printed) {
												USART_voidSendChar('\r'); // Send carriage return
												USART_voidSendChar('\n'); // Send newline
												USART_VoidSendString("  Room 2 Selected ");
												USART_voidSendChar('\r'); // Send carriage return
												USART_voidSendChar('\n'); // Send newline
												
												
												menu_printed=1;
												}
												menu_printed=0;
												_delay_ms(4000);
												while (flag_Room2) {
													Ringer();
													if (cc_checker !=0)
													{
														cc_checker=temperature(1);
													}
													
													CLCD_GoTo(1, 1);
													CLCD_SendString("1.LED_1  2.LED_2");
													CLCD_GoTo(2, 1);
													CLCD_SendString("3.FAN     4.Back");
													
													if (!menu_printed) {
													USART_voidSendChar('\r'); // Send carriage return
													USART_voidSendChar('\n'); // Send newline
													USART_VoidSendString(" 1.LED_1    2.LED_2 ");
													 
													 USART_voidSendChar('\r'); // Send carriage return
													 USART_voidSendChar('\n'); // Send newline
													 USART_VoidSendString(" 3.FAN      4.Back ");
													 USART_voidSendChar('\r'); // Send carriage return
													 USART_voidSendChar('\n'); // Send newline
													 menu_printed=1;
													}
													
													KEY = Kypad_GetKey();
													if (cc_checker !=0)
													{
														cc_checker=temperature(1);
													}
													
													if (KEY != 0xFF && KEY == '4') {
														menu_printed=0;
														
														flag_Room2 = 0;
													}
												}
												break;

												case '3':
												Ringer();
												if (cc_checker !=0)
												{
													cc_checker=temperature(1);
												}
												// Exit Home Control
												flag_Home = 0;
												CLCD_WriteInes(0x01);
												CLCD_SendString(" Logging out...");
												_delay_ms(6000);
												
												if (!menu_printed) {
												 USART_voidSendChar('\r'); // Send carriage return
												 USART_voidSendChar('\n'); // Send newline
												 USART_VoidSendString(" Logging out... ");
												 USART_voidSendChar('\r'); // Send carriage return
												 USART_voidSendChar('\n'); // Send newline
												menu_printed=1;
												}
												menu_printed=0;
												Home_Checker = 0;
												break;
											}
										}
									}
								}
							
							
																								
						
								///////////////////////////////////////////////////////////
									break;
								}
								else
								{
									
									flag--; 
									
									if (flag != 0)
									{
										Ringer();
										if (cc_checker !=0)
										{
											cc_checker=temperature(1);
										}
									USART_voidSendChar('\r'); // Send carriage return
									USART_voidSendChar('\n'); // Send newline
									USART_VoidSendString(" Incorrect, Try Again\n");
									USART_voidSendChar('4'- flag);
									passwordIndex = 0; 
									
									break;
									}
									break;
								}
							}
							else
							{
								if (passwordIndex < MAX_PASSWORD_LENGTH)
								{
									EnteredPassword[passwordIndex++] = KEY; 
									USART_voidSendChar('*'); 
								}
							}
						}
					}

					if (flag == 0)
					{
						Ringer();
						USART_voidSendChar('\r'); // Send carriage return
						USART_voidSendChar('\n'); // Send newline
						USART_VoidSendString(" System locked.");
						return 0;
					}
				}
			}
		}
	}
}