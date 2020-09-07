/*
 * main.c
 *
 *  Created on: Dec 18, 2019
 *      Author: DELL
 */

#include "Std_types.h"
#include "Registers.h"
#include "BitOperations.h"
#include "DIO.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "USART.h"
#include "DATA_TABLE.h"
//#include <util/delay.h>

typedef struct{
	U8 Temperature_sensor;
	U8 ldr_sensor;
}SENSORS;

typedef enum{
	STATE_POT_LDR = 0,
	STATE_FAN_LEDS,
	STATE_DOOR
}STATE;

SENSORS sensors;

#define DOOR_OFF 0
#define DOOR_ON 1

#define LEDS_OFF 0
#define LEDS_ON 1

#define DOOR_PIN DIO_PORTD,PIN5
#define FAN_PIN DIO_PORTD,PIN7
#define LEDS_PIN DIO_PORTD,PIN6
#define PIR_PIN DIO_PORTD,PIN2

static U8 FAN_DATA = 0;
static U8 LEDS_DATA = 0;
static U8 DOOR_DATA = 0;

void Receive(void);

U8 newState = 1;

int main(void){
	STATE state = STATE_POT_LDR;
	U8 scan = 0;


	LCD_Init();
	KEYPAD_Init();
	USART_Init(9600);
	USART_RX_SetISR(Receive);

	LCD_SendCommand(LCD_COMMAND_CLEARDISP);
	LCD_SendCommand(LCD_COMMAND_LCDON_CURSOROFF_BLINKOFF);

	DIO_SetPinDirection(DIO_PORTA,PIN1,OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,PIN2,OUTPUT);
	DIO_SetPinDirection(DIO_PORTD,PIN3,OUTPUT);
	DIO_SetPinDirection(DIO_PORTC,PIN0,OUTPUT);

	DIO_SetPinValue(DIO_PORTC,PIN0,LOW);

	sensors.Temperature_sensor = 0;
	sensors.ldr_sensor = 0;

	SetBit(SREG,7);

	while(1){
		scan = NOT_PRESSED_VALUE;
		scan = KEYPAD_Scan();
		switch(scan){
		case 8:
			if(state != STATE_DOOR){
				state++;
			}else{
				state = STATE_POT_LDR;
			}
			LCD_SendCommand(LCD_COMMAND_CLEARDISP);
			newState = 1;
			break;
		case 5:
			if(state != STATE_POT_LDR){
				state--;
			}else{
				state = STATE_DOOR;
			}
			LCD_SendCommand(LCD_COMMAND_CLEARDISP);
			newState = 1;
			break;
		}

		if(newState == 1){
			//ClearBit(SREG,7);
			LCD_SendCommand(LCD_COMMAND_X_Y(0,0));
			switch(state){
			case STATE_POT_LDR:
				LCD_PrintString("POT=");
				LCD_PrintNumber(sensors.Temperature_sensor,3);
				LCD_SendCommand(LCD_COMMAND_2ND_LINE);
				LCD_PrintString("FAN=");
				LCD_PrintNumber(sensors.Temperature_sensor*100.0/255.0,3);


				break;
			case STATE_FAN_LEDS:
				LCD_PrintString("LDR=");
				LCD_PrintFloatNumber(sensors.ldr_sensor*5.0/255.0,3);
				LCD_SendCommand(LCD_COMMAND_2ND_LINE);
				if(LEDS_DATA == LEDS_ON){
					LCD_PrintString("LEDS ARE ON ");
				}else if(LEDS_DATA == LEDS_OFF){
					LCD_PrintString("LEDS ARE OFF");
				}

				break;
			case STATE_DOOR:
				if(DOOR_DATA == DOOR_ON){
					LCD_PrintString("DOOR IS OPENED");
				}else if(DOOR_DATA == DOOR_OFF){
					LCD_PrintString("DOOR IS CLOSED");
				}

				break;
			}
			newState = 0;
			//SetBit(SREG,7);
		}


	}

	return 0;
}


void Receive(void){
	U8 data = UDR;
	/* Enable Interrupt */
	//ClearBit(UCSRB,7);
	//ClearBit(UCSRB,6);

	ClearBit(SREG,7);

	switch(data){
	case FAN_ID:
		FAN_DATA = USART_Receive();
		//LCD_SendCommand(LCD_COMMAND_X_Y(0,0));
		//LCD_PrintNumber(FAN_DATA,1);
		newState = 1;

		break;
	case LEDS_ID:
		LEDS_DATA = USART_Receive();
		//LCD_SendCommand(LCD_COMMAND_X_Y(0,0));
		//LCD_PrintNumber(LEDS_DATA,1);
		newState = 1;

		break;
	case DOOR_ID:
		DOOR_DATA = USART_Receive();
		//LCD_SendCommand(LCD_COMMAND_X_Y(0,0));
		//LCD_PrintNumber(DOOR_DATA,1);
		newState = 1;


		break;
	case TEMP_ID:
		sensors.Temperature_sensor = USART_Receive();
		//LCD_SendCommand(LCD_COMMAND_X_Y(0,0));
		//LCD_PrintNumber(sensors.Temperature_sensor,1);
		newState = 1;

		break;
	case LDR_ID:
		sensors.ldr_sensor = USART_Receive();
		//LCD_SendCommand(LCD_COMMAND_X_Y(0,0));
		//LCD_PrintNumber(sensors.ldr_sensor,1);
		//while(1);
		newState = 1;

		break;
	}

	/* Enable Interrupt */
	//SetBit(UCSRB,7);
	//SetBit(UCSRB,6);

	SetBit(SREG,7);

	if(DIO_GetPinValue(DIO_PORTD,PIN3) == HIGH) DIO_SetPinValue(DIO_PORTD,PIN3,LOW);
	else DIO_SetPinValue(DIO_PORTD,PIN3,HIGH);

}

