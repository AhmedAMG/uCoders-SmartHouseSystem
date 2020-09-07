/*
 * KEYPAD.c
 *
 *  Created on: Dec 16, 2019
 *      Author: DELL
 */
#include "Std_types.h"
#include "DIO.h"
#include "KEYPAD.h"



static U16 CurrentCounts = 0;

void KEYPAD_Init(void){
	DIO_SetPinDirection(ROW0PORT,ROW0PIN,ROW0DIR);
	DIO_SetPinDirection(ROW1PORT,ROW1PIN,ROW1DIR);
	DIO_SetPinDirection(ROW2PORT,ROW2PIN,ROW2DIR);
	DIO_SetPinDirection(ROW3PORT,ROW3PIN,ROW3DIR);

	DIO_SetPinDirection(COL0PORT,COL0PIN,COL0DIR);
	DIO_SetPinDirection(COL1PORT,COL1PIN,COL1DIR);
	DIO_SetPinDirection(COL2PORT,COL2PIN,COL2DIR);
	DIO_SetPinDirection(COL3PORT,COL3PIN,COL3DIR);

	DIO_SetPinPullUp(COL0PORT,COL0PIN);
	DIO_SetPinPullUp(COL1PORT,COL1PIN);
	DIO_SetPinPullUp(COL2PORT,COL2PIN);
	DIO_SetPinPullUp(COL3PORT,COL3PIN);

	DIO_SetPinValue(ROW0PORT,ROW0PIN,HIGH);
	DIO_SetPinValue(ROW1PORT,ROW1PIN,HIGH);
	DIO_SetPinValue(ROW2PORT,ROW2PIN,HIGH);
	DIO_SetPinValue(ROW3PORT,ROW3PIN,HIGH);
}

U8 KEYPAD_Scan(void){
	U8 i = 0, j = 0;
	U8 ret = NOT_PRESSED_VALUE;
	for(i = 0; i < 4; i++)
	{

		DIO_SetPinValue(ROW0PORT,ROW0PIN,HIGH);
		DIO_SetPinValue(ROW1PORT,ROW1PIN,HIGH);
		DIO_SetPinValue(ROW2PORT,ROW2PIN,HIGH);
		DIO_SetPinValue(ROW3PORT,ROW3PIN,HIGH);

		DIO_SetPinValue(ROW0PORT,ROW0PIN+i,LOW);

		for(j = 0; j < 4; j++){
			ret = 4*i + j + 1;
			while(CurrentCounts < COUNTS && DIO_GetPinValue(COL0PORT,COL0PIN+j) == LOW){
				CurrentCounts++;
			}
			if(CurrentCounts != COUNTS){
				ret = NOT_PRESSED_VALUE;
			}
			CurrentCounts = 0;

			if(ret != NOT_PRESSED_VALUE) {
				break;
			}
		}
		if(ret != NOT_PRESSED_VALUE) {
			break;
		}
	}
	return ret;
}

