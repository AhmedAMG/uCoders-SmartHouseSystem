/*
 * INT.c
 *
 *  Created on: Dec 16, 2019
 *      Author: DELL
 */

#include <avr/interrupt.h>
#include "Std_types.h"
#include "BitOperations.h"
#include "Registers.h"
#include "DIO.h"
#include "INT.h"

static void (*INT0_ptr)(void);
static void (*INT1_ptr)(void);
static void (*INT2_ptr)(void);

void INT0_SetISR(void (*ptr)(void)){
	INT0_ptr = ptr;
}

void INT0_Init(void){
	DIO_SetPinDirection(INT0_PIN,INPUT);

	SetBit(SREG,7);

	SetBit(MCUCR,0);
	SetBit(MCUCR,1);

	//SetBit(GICR,6);

}

ISR(INT0_vect){
	INT0_ptr();
}


void INT1_SetISR(void (*ptr)(void)){
	INT1_ptr = ptr;
}

void INT1_Init(void){
	DIO_SetPinDirection(INT1_PIN,INPUT);

	SetBit(SREG,7);

	SetBit(MCUCR,2);
	SetBit(MCUCR,3);

	SetBit(GICR,7);
}

ISR(INT1_vect){
	INT1_ptr();
}

void INT2_SetISR(void (*ptr)(void)){
	INT2_ptr = ptr;
}

void INT2_Init(void){
	DIO_SetPinDirection(INT2_PIN,INPUT);

	SetBit(SREG,7);

	SetBit(MCUCSR,6);

	SetBit(GICR,5);
}


ISR(INT2_vect){
	INT2_ptr();
}
