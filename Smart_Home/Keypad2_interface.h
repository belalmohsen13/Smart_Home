/*
 * Keypad_interface.h
 *
 *  Created on: Mar 10, 2022
 *      Author: INTEL
 */

#ifndef HAL_KEYPAD2_KEYPAD2_INTERFACE_H_
#define HAL_KEYPAD2_KEYPAD2_INTERFACE_H_

#define KeyPad_Rw_NUM   4
#define KeyPad_COL_NUM  4

void Keypad_voidInit(void);
U8   Keypad_U8GetPressed(void);

#endif /* HAL_KEYPAD2_KEYPAD2_INTERFACE_H_ */
