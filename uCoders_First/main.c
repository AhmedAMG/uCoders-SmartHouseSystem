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
#include "ADC.h"
#include "LCD.h"
#include "INT.h"
#include "USART.h"
#include "TIM.h"
#include "util/delay.h"
#include "DATA_TABLE.h"

void Set_Temperature(void);
void Set_LDR(void);
void USART_Broadcast(void);

//Search: Successive approximation circuit.
//Try: Read both low and high data registers in one-shot.

typedef struct{
	U8 Temperature_sensor;
	U8 ldr_sensor;
}Sensors;

Sensors sensors;

#define DOOR_OFF 0
#define DOOR_ON 1

#define LEDS_OFF 0
#define LEDS_ON 1

#define DOOR_PIN DIO_PORTD,PIN5
#define FAN_PIN DIO_PORTD,PIN7
#define LEDS_PIN DIO_PORTD,PIN6
#define PIR_PIN DIO_PORTD,PIN2

void FAN_OFF(void);
void FAN_ON(void);
void Receive(void);

static U8 lock_fan = 0;
static U8 lock_leds = 0;
static U8 lock_door = 0;

static U8 FAN_DATA = 0;
static U8 LEDS_DATA = 0;
static U8 DOOR_DATA = 0;

int main(void){
	LCD_Init();
	//INT0_Init();
	ADC_Init();

	TIM2_COMP_SetISR(FAN_OFF);
	TIM2_OVF_SetISR(FAN_ON);
	TIM2_Init();

	//Global Interrupt
	SetBit(SREG,7);

	USART_Init(9600);
	USART_RX_SetISR(Receive);

	DIO_SetPinDirection(PIR_PIN,INPUT);

	DIO_SetPinDirection(DOOR_PIN,OUTPUT);
	DIO_SetPinDirection(FAN_PIN,OUTPUT);
	DIO_SetPinDirection(LEDS_PIN,OUTPUT);

	DIO_SetPinDirection(DIO_PORTD,PIN3,OUTPUT);
	DIO_SetPinValue(DIO_PORTD,PIN3,LOW);

	while(1){
		////////////////Temperature sensor + Fan//////////////////////
		ADC_Read(0);
		ADC_SetISR(Set_Temperature);
		_delay_ms(1);
		if(lock_fan == 0){
			FAN_DATA = sensors.Temperature_sensor*100.0/255.0;
			TIM2_SetDutyCycle(FAN_DATA);
		}else{
			TIM2_SetDutyCycle(FAN_DATA);
		}

		//////////////////////////////////////////////////////////////
		LCD_PrintString("POT=");
		LCD_PrintNumber(sensors.Temperature_sensor,3);
		//////////////////////PIR sensor + DOOR///////////////////////
		if(DIO_GetPinValue(PIR_PIN) == 0){
			DOOR_DATA = DOOR_OFF;
		}
		else{
			DOOR_DATA = DOOR_ON;
		}
		DIO_SetPinValue(DOOR_PIN,DOOR_DATA);
		//////////////////////////////////////////////////////////////

		//////////////////////LDR sensor + LEDS///////////////////////
		LCD_SendCommand(LCD_COMMAND_2ND_LINE);
		ADC_Read(1);
		ADC_SetISR(Set_LDR);
		_delay_ms(1);
		if(sensors.ldr_sensor*5.0/255.0 > 1.25){
			LEDS_DATA = LEDS_ON;
		}else{
			LEDS_DATA = LEDS_OFF;
		}
		DIO_SetPinValue(LEDS_PIN,LEDS_DATA);
		//////////////////////////////////////////////////////////////
		LCD_PrintString("LDR=");
		LCD_PrintFloatNumber(sensors.ldr_sensor*5.0/255.0,3);
		LCD_SendCommand(LCD_COMMAND_X_Y(0,0));

		USART_Broadcast();

		_delay_ms(400);
	}

	return 0;
}

void USART_Broadcast(void){
	USART_Transmit(TEMP_ID);
	USART_Transmit(sensors.Temperature_sensor);

	USART_Transmit(FAN_ID);
	USART_Transmit(sensors.Temperature_sensor*100.0/255);

	USART_Transmit(LDR_ID);
	USART_Transmit(sensors.ldr_sensor);

	USART_Transmit(LEDS_ID);
	USART_Transmit(LEDS_DATA);

	USART_Transmit(DOOR_ID);
	USART_Transmit(DOOR_DATA);
}

void Set_Temperature(void){
	sensors.Temperature_sensor = ADC_GetResult();
	//sensors.Temperature_sensor = sensors.Temperature_sensor / 3.996;
}

void Set_LDR(void){
	sensors.ldr_sensor = ADC_GetResult();
}

void FAN_ON(void){
	//Clear the flag
	SetBit(TIFR,6);

	DIO_SetPinValue(FAN_PIN,HIGH);
}

void FAN_OFF(void){
	//Clear the flag
	SetBit(TIFR,7);

	DIO_SetPinValue(FAN_PIN,LOW);
}

void Receive(void){
	U8 data = UDR;
	/* Enable Interrupt */
	ClearBit(UCSRB,7);
	ClearBit(UCSRB,6);
	switch(data){
	case FAN_ID:
		FAN_DATA = USART_Receive();
		if(FAN_DATA > 99){
			FAN_DATA = 99;
		}
		lock_fan = 1;
		break;
	case LEDS_ID:
		LEDS_DATA = USART_Receive();
		if(LEDS_DATA >= 1){
			LEDS_DATA = LEDS_ON;
		}else{
			LEDS_DATA = LEDS_OFF;
		}
		lock_leds = 1;
		break;
	case DOOR_ID:
		DOOR_DATA = USART_Receive();
		if(LEDS_DATA >= 1){
			DOOR_DATA = DOOR_ON;
		}else{
			DOOR_DATA = DOOR_OFF;
		}
		lock_door = 1;
		break;
	}
	/* Enable Interrupt */
	SetBit(UCSRB,7);
	SetBit(UCSRB,6);
}
