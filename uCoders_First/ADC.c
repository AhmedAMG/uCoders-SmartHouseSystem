/*
 * ADC.c
 *
 *  Created on: Dec 16, 2019
 *      Author: DELL
 */

#include "Std_types.h"
#include "BitOperations.h"
#include "Registers.h"
#include "DIO.h"
#include "ADC.h"
#include "ADC_CFG.h"
#include "avr/interrupt.h"

static void (*ADC_ptr)(void);

#if ADC_BITS == ADC_BITS_10BIT
static U16 ADC_Result = 0;
static U16* ptr_g = (U16*)&ADCL;
#elif ADC_BITS == ADC_BITS_8BIT
static U8 ADC_Result = 0;
static U16* ptr_g = (U8*)&ADCH;
#endif

void ADC_Init(void){

#if ADC_MODE == ADC_MODE_SINGLE
	ClearBit(ADCSRA,5);
#elif ADC_MODE == ADC_MODE_AUTOTRIGGER
	SetBit(ADCSRA,5);

	switch(ADC_AUTOTRIGGERSOURCE){
	case ADC_AUTOTRIGGERSOURCE_EXINT0:
		SFIOR = (SFIOR & (~0xE0)) | (ADC_AUTOTRIGGERSOURCE_EXINT0 << 5);
		break;
	}

	SetBit(ADCSRA,3);
#endif

	switch(ADC_PRESCALAR){
	case ADC_PRESCALAR_4:
		ADCSRA = (ADCSRA & (~0x07)) | (2 << 0);
		break;
	case ADC_PRESCALAR_8:
		ADCSRA = (ADCSRA & (~0x07)) | (3 << 0);
		break;
	case ADC_PRESCALAR_16:
		ADCSRA = (ADCSRA & (~0x07)) | (4 << 0);
		break;
	case ADC_PRESCALAR_32:
		ADCSRA = (ADCSRA & (~0x07)) | (5 << 0);
		break;
	case ADC_PRESCALAR_64:
		ADCSRA = (ADCSRA & (~0x07)) | (6 << 0);
		break;
	case ADC_PRESCALAR_128:
		ADCSRA = (ADCSRA & (~0x07)) | (7 << 0);
		break;
	}

#if ADC_BITS == ADC_BITS_8BIT
	SetBit(ADMUX,5);
#elif ADC_BITS == ADC_BITS_10BIT
	ClearBit(ADMUX,5);
#endif

#if ADC_REF == ADC_REF_AVCC
	SetBit(ADMUX,6);
	ClearBit(ADMUX,7);
#elif ADC_REF == ADC_REF_INTERNAL
	SetBit(ADMUX,6);
	SetBit(ADMUX,7);
#endif

	ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH0 << 0);

	//Enable ADC
	SetBit(ADCSRA,7);

	//Start Conversion
	SetBit(ADCSRA,6);

	//Global Interrupts
	//SetBit(SREG,7);

}

#if ADC_BITS == ADC_BITS_10BIT
U16 ADC_Read(U8 ADC_CHANNEL_CHx){

	switch(ADC_CHANNEL_CHx){
	case ADC_CHANNEL_CH0:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH0 << 0);
		break;
	case ADC_CHANNEL_CH1:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH1 << 0);
		break;
	case ADC_CHANNEL_CH2:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH2 << 0);
		break;
	case ADC_CHANNEL_CH3:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH3 << 0);
		break;
	case ADC_CHANNEL_CH4:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH4 << 0);
		break;
	case ADC_CHANNEL_CH5:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH5 << 0);
		break;
	case ADC_CHANNEL_CH6:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH6 << 0);
		break;
	case ADC_CHANNEL_CH7:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH7 << 0);
		break;
	}

	SetBit(ADCSRA,6);
	#if ADC_AUTOTRIGGERSOURCE == UNINIT
		SetBit(ADCSRA,4);
		while(GetBit(ADCSRA,6) == 1);
		return *ptr_g;
	#else
		return 0;
	#endif

}

U16 ADC_GetResult(void){
	return ADC_Result & (0x03FF);
}

#elif ADC_BITS == ADC_BITS_8BIT
U8 ADC_Read(U8 ADC_CHANNEL_CHx){
	switch(ADC_CHANNEL_CHx){
	case ADC_CHANNEL_CH0:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH0 << 0);
		break;
	case ADC_CHANNEL_CH1:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH1 << 0);
		break;
	case ADC_CHANNEL_CH2:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH2 << 0);
		break;
	case ADC_CHANNEL_CH3:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH3 << 0);
		break;
	case ADC_CHANNEL_CH4:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH4 << 0);
		break;
	case ADC_CHANNEL_CH5:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH5 << 0);
		break;
	case ADC_CHANNEL_CH6:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH6 << 0);
		break;
	case ADC_CHANNEL_CH7:
		ADMUX = (ADMUX & (~0x1F)) | (ADC_CHANNEL_CH7 << 0);
		break;
	}
	SetBit(ADCSRA,6);

#if ADC_AUTOTRIGGERSOURCE == UNINIT
	while(GetBit(ADCSRA,6) == 1);
	SetBit(ADCSRA,4);
	return ADCH;
#else
	return 0;
#endif
}

U8 ADC_GetResult(void){
	return ADC_Result & (0x03FF);
}

#endif

ISR(ADC_vect){
	ADC_Result = *ptr_g;
	ADC_ptr();

	SetBit(GIFR,6);
}

void ADC_SetISR(void (*ptr)(void)){
	ADC_ptr = ptr;
}
