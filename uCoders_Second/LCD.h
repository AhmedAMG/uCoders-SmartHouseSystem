/*
 * LCD.h
 *
 *  Created on: Dec 16, 2019
 *      Author: DELL
 */

#ifndef LCD_H_
#define LCD_H_

#include "DIO.h"

#define LCD_8Bit_Mode	0

/* Configuration */
#define LCD_RS_PORT	DIO_PORTA
#define LCD_RW_PORT	DIO_PORTA
#define LCD_E_PORT	DIO_PORTA

#define LCD_RS_PIN	PIN7
#define LCD_RW_PIN	PIN2
#define LCD_E_PIN	PIN6

#define LCD_DATA_PORT	DIO_PORTB
/*****************/

/* Commands */
#define LCD_COMMAND_RETURN_HOME 0x02
#define LCD_COMMAND_CLEARDISP 0x01
#define LCD_COMMAND_8BIT_2LINES_5X8	0x38
#define LCD_COMMAND_LCDON_CURSORON_BLINKON 	0x0F
#define LCD_COMMAND_INCADDR_NOSHIFT	0x06

#define LCD_COMMAND_4BIT	0x02
#define LCD_COMMAND_4BIT_2LINES_5X8	0x08
#define LCD_COMMAND_LCDON_CURSOROFF_BLINKOFF 0x0C
#define LCD_COMMAND_2ND_LINE	0xC0
#define LCD_COMMAND_X_Y(X,Y) (X? 0xC0|Y : 0x80|Y)

/************/

void LCD_Init(void);
void LCD_SendCommand(U8 command);
void LCD_SendData(U8 data);
void LCD_PrintString(U8* string);
void LCD_PrintNumber(U32 number, U8 digit);
void LCD_PrintFloatNumber(float number, U8 digit);

#endif /* LCD_H_ */
