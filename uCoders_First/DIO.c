/*
 * DIO.c
 *
 *  Created on: Dec 15, 2019
 *      Author: DELL
 */
#include "Std_types.h"
#include "Registers.h"
#include "BitOperations.h"
#include "DIO.h"

void DIO_SetPortDirection(U8 Port_Number, U8 Directions){
	switch(Port_Number){
	case DIO_PORTA:
		DDRA = Directions;
		break;
	case DIO_PORTB:
		DDRB = Directions;
		break;
	case DIO_PORTC:
		DDRC = Directions;
		break;
	case DIO_PORTD:
		DDRD = Directions;
		break;
	}
}

void DIO_SetPortValue(U8 Port_Number, U8 Value){
	switch(Port_Number){
	case DIO_PORTA:
		PORTA = Value;
		break;
	case DIO_PORTB:
		PORTB = Value;
		break;
	case DIO_PORTC:
		PORTC = Value;
		break;
	case DIO_PORTD:
		PORTD = Value;
		break;
	}
}

U8 DIO_GetPortValue(U8 Port_Number){
	U8 ret = 0;
	switch(Port_Number){
	case DIO_PORTA:
		ret = PINA;
		break;
	case DIO_PORTB:
		ret = PINB;
		break;
	case DIO_PORTC:
		ret = PINC;
		break;
	case DIO_PORTD:
		ret = PIND;
		break;
	}
	return ret;
}


void DIO_SetPinDirection(U8 Port_Number, U8 Pin_Number, U8 Direction){
	switch(Port_Number){
	case DIO_PORTA:
		if(Direction == INPUT) ClearBit(DDRA,Pin_Number);
		else if(Direction == OUTPUT) SetBit(DDRA,Pin_Number);
		else; //ERROR
		break;
	case DIO_PORTB:
		if(Direction == INPUT) ClearBit(DDRB,Pin_Number);
		else if(Direction == OUTPUT) SetBit(DDRB,Pin_Number);
		else; //ERROR
		break;
	case DIO_PORTC:
		if(Direction == INPUT) ClearBit(DDRC,Pin_Number);
		else if(Direction == OUTPUT) SetBit(DDRC,Pin_Number);
		else; //ERROR
		break;
	case DIO_PORTD:
		if(Direction == INPUT) ClearBit(DDRD,Pin_Number);
		else if(Direction == OUTPUT) SetBit(DDRD,Pin_Number);
		else; //ERROR
		break;
	}
}

void DIO_SetPinPullUp(U8 Port_Number, U8 Pin_Number){
	ClearBit(SFIOR,2);
	switch(Port_Number){
	case DIO_PORTA:
		if(GetBit(DDRA,Pin_Number) == INPUT){
			SetBit(PORTA,Pin_Number);
		}else; //ERROR
		break;
	case DIO_PORTB:
		if(GetBit(DDRB,Pin_Number) == INPUT){
			SetBit(PORTB,Pin_Number);
		}else; //ERROR
		break;
	case DIO_PORTC:
		if(GetBit(DDRC,Pin_Number) == INPUT){
			SetBit(PORTC,Pin_Number);
		}else; //ERROR
		break;
	case DIO_PORTD:
		if(GetBit(DDRD,Pin_Number) == INPUT){
			SetBit(PORTD,Pin_Number);
		}else; //ERROR
		break;
	}
}

void DIO_SetPinValue(U8 Port_Number, U8 Pin_Number, U8 Value){
	switch(Port_Number){
	case DIO_PORTA:
		if(Value == HIGH) SetBit(PORTA,Pin_Number);
		else if(Value == LOW) ClearBit(PORTA,Pin_Number);
		else; //ERROR
		break;
	case DIO_PORTB:
		if(Value == HIGH) SetBit(PORTB,Pin_Number);
		else if(Value == LOW) ClearBit(PORTB,Pin_Number);
		else; //ERROR
		break;
	case DIO_PORTC:
		if(Value == HIGH) SetBit(PORTC,Pin_Number);
		else if(Value == LOW) ClearBit(PORTC,Pin_Number);
		else; //ERROR
		break;
	case DIO_PORTD:
		if(Value == HIGH) SetBit(PORTD,Pin_Number);
		else if(Value == LOW) ClearBit(PORTD,Pin_Number);
		else; //ERROR
		break;
	}
}

U8 DIO_GetPinValue(U8 Port_Number, U8 Pin_Number){
	U8 retBit = 0;
	switch(Port_Number){
	case DIO_PORTA:
		retBit = GetBit(PINA,Pin_Number);
		break;
	case DIO_PORTB:
		retBit = GetBit(PINB,Pin_Number);
		break;
	case DIO_PORTC:
		retBit = GetBit(PINC,Pin_Number);
		break;
	case DIO_PORTD:
		retBit = GetBit(PIND,Pin_Number);
		break;
	}
	return retBit;
}
