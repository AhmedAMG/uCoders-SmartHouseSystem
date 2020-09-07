/*
 * LCD.c
 *
 *  Created on: Dec 16, 2019
 *      Author: DELL
 */

#include "Std_types.h"
#include "BitOperations.h"
#include "DIO.h"
#include "LCD.h"
#include <util/delay.h>

void LCD_Init(void){
	DIO_SetPinDirection(LCD_RS_PORT,LCD_RS_PIN,OUTPUT);
	DIO_SetPinDirection(LCD_RW_PORT,LCD_RW_PIN,OUTPUT);
	DIO_SetPinDirection(LCD_E_PORT,LCD_E_PIN,OUTPUT);

	DIO_SetPortDirection(LCD_DATA_PORT,0xFF);

#if LCD_8Bit_Mode == 1
	LCD_SendCommand(LCD_COMMAND_8BIT_2LINES_5X8);
	LCD_SendCommand(LCD_COMMAND_LCDON_CURSORON_BLINKON);
	LCD_SendCommand(LCD_COMMAND_INCADDR_NOSHIFT);
	LCD_SendCommand(LCD_COMMAND_CLEARDISP);
#else
	LCD_SendCommand(0x03);
	_delay_ms(5);

	LCD_SendCommand(0x03);
	_delay_ms(1);

	LCD_SendCommand(0x03);
	_delay_ms(5);

	LCD_SendCommand(LCD_COMMAND_4BIT);
	LCD_SendCommand(LCD_COMMAND_4BIT_2LINES_5X8);
	LCD_SendCommand(LCD_COMMAND_CLEARDISP);
	LCD_SendCommand(LCD_COMMAND_INCADDR_NOSHIFT);
	LCD_SendCommand(LCD_COMMAND_LCDON_CURSOROFF_BLINKOFF);
#endif

}

void LCD_SendCommand(U8 command){
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,LOW);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
	_delay_ms(2);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);
	DIO_SetPortValue(LCD_DATA_PORT,command);
	_delay_ms(2);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,LOW);
	_delay_ms(2);

#if LCD_8Bit_Mode == 0
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,LOW);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
	_delay_ms(2);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);
	DIO_SetPortValue(LCD_DATA_PORT,command<<4);
	_delay_ms(2);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,LOW);
	_delay_ms(2);
#endif
}

void LCD_SendData(U8 data){
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,HIGH);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
	_delay_ms(2);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);
	DIO_SetPortValue(LCD_DATA_PORT,data);
	_delay_ms(2);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,LOW);
	_delay_ms(2);

#if LCD_8Bit_Mode == 0
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,HIGH);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
	_delay_ms(2);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,HIGH);
	_delay_ms(2);
	DIO_SetPortValue(LCD_DATA_PORT,data<<4);
	_delay_ms(2);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,LOW);
	_delay_ms(2);
#endif
}

void LCD_PrintString(U8* string){
	int i = 0;
	while(string[i] != '\0'){
		LCD_SendData(string[i]);
		i++;
	}
}

void LCD_PrintNumber(U32 number, U8 digit){
	char string[16] = {0};
	short int i = 0;
	char flag = 0;
	if(number == 0){
		while(digit > 0){
			LCD_SendData('0');
			digit--;
		}
		return;
	}
	else if(number < 0){
		number = number * -1;
		flag = 1;
	}

	while(number > 0){
		string[i] = (number%10) + '0';
		number = number / 10;
		i++;
	}

	while(i < digit){
		LCD_SendData('0');
		digit--;
	}

	i--;
	if(flag == 1) LCD_SendData('-');
	while(i >= 0){
		LCD_SendData(string[i]);
		i--;
	}
}

void LCD_PrintFloatNumber(float number, U8 digit){
	LCD_PrintNumber(number,2);
	U32 i = 1;
	U8 temp = digit;
	while(temp > 0){
		i = i*10;
		temp--;
	}
	number = (number - (int)number) * i;
	LCD_SendData('.');
	LCD_PrintNumber(number,digit);
}
