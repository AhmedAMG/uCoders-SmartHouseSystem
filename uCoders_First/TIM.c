/*
 * TIM.c
 *
 *  Created on: Dec 17, 2019
 *      Author: DELL
 */

#include "Std_types.h"
#include "BitOperations.h"
#include "Registers.h"
#include "TIM.h"
#include "DIO.h"
#include <avr/interrupt.h>

static U16 count = 0;
static U16 delay = 0;

static void (*TIM0_COMP_ptr)(void);
static void (*TIM2_COMP_ptr)(void);
static void (*TIM2_OVF_ptr)(void);

void TIM0_Init(void){
	TIMSK = (TIMSK & (~0x03)) | (3 << 0);
	SetBit(SREG,7);
}

void TIM0_Start(void){
	TCCR0 = (TCCR0 & (~0x07)) | (2 << 0);
}

void TIM0_Stop(void){
	TCCR0 = (TCCR0 & (~0x07)) | (0 << 0);
}

void TIM0_COMP_SetISR(void (*ptr)(void)){
	TIM0_COMP_ptr = ptr;
}

void TIM0_SetTimeMS(U32 time_ms){
	delay = time_ms * 1000.0 / 256.0;
	count = delay;
	OCR0 = (time_ms * 1000) % 256;
}

void TIM2_Init(void){
	//Fast PWM
	SetBit(TCCR2,3);
	SetBit(TCCR2,6);

	//Global Interrupt
	//SetBit(SREG,7);

	//OC2 Pin (non-inverting)
	SetBit(TCCR2,5);

	//Interrupt Enable
	SetBit(TIMSK,6);
	SetBit(TIMSK,7);

	if(((float)Clk_Freq/(Req_Freq*256.0)) < 8){
		TCCR2 = (TCCR2 & (~0x07)) | (1 << 0);
	}else if(((float)Clk_Freq/(Req_Freq*256.0)) < 32){
		TCCR2 = (TCCR2 & (~0x07)) | (2 << 0);
	}else if(((float)Clk_Freq/(Req_Freq*256.0)) < 64){
		TCCR2 = (TCCR2 & (~0x07)) | (3 << 0);
	}else if(((float)Clk_Freq/(Req_Freq*256.0)) < 128){
		TCCR2 = (TCCR2 & (~0x07)) | (4 << 0);
	}else if(((float)Clk_Freq/(Req_Freq*256.0)) < 256){
		TCCR2 = (TCCR2 & (~0x07)) | (5 << 0);
	}else if(((float)Clk_Freq/(Req_Freq*256.0)) < 1024){
		TCCR2 = (TCCR2 & (~0x07)) | (6 << 0);
	}else{
		TCCR2 = (TCCR2 & (~0x07)) | (7 << 0);
	}


}

void TIM2_SetDutyCycle(U8 DC){
	OCR2 = (U8)((DC/100.0)*255);
}

void TIM2_COMP_SetISR(void (*ptr)(void)){
	TIM2_COMP_ptr = ptr;
}

void TIM2_OVF_SetISR(void (*ptr)(void)){
	TIM2_OVF_ptr = ptr;
}

ISR(TIMER0_OVF_vect){
	count--;
}

ISR(TIMER0_COMP_vect){
	if(count == 0){
		TIM0_COMP_ptr();
		count = delay;
	}
}

ISR(TIMER2_OVF_vect){
	TIM2_OVF_ptr();
}

ISR(TIMER2_COMP_vect){
	TIM2_COMP_ptr();
}

