/*
 * USART.c
 *
 *  Created on: Dec 18, 2019
 *      Author: DELL
 */

#include "Std_types.h"
#include "Registers.h"
#include "BitOperations.h"
#include "DIO.h"
#include "USART.h"
#include <avr/interrupt.h>

#define F_CPU 8000000UL
U8 DATA = 0;

static void (*USART_ptr)(void);

void USART_Init(int baudRate){

	baudRate = ((F_CPU/(baudRate*16UL))-1);

	/* Enable receiver and transmitter */
	SetBit(UCSRB,3);
	SetBit(UCSRB,4);

	/* Set frame format: 0parity, 8data, 1stop bit */
	SetBit(UCSRC,2);
	SetBit(UCSRC,1);

	/* Enable Interrupt */
	SetBit(UCSRB,7);
	SetBit(UCSRB,6);

	/* Set baud rate */
	SetBit(UCSRC,7);
	UBRRH = (baudRate >> 8);
	UBRRL = baudRate;


}


U8 USART_Receive(void){
	U8 ret = 0;

	// Wait for data to be received
	while (GetBit(UCSRA,7) == 0);
	// Get and return received data from buffer
	ret = UDR;

	return ret;
}

/*
U8 USART_Receive(void){
	return DATA;
}
*/


void USART_Transmit(U8 data){
	/* Wait for empty transmit buffer */
	while (GetBit(UCSRA,5) == 0);
	/* Put data into buffer, sends the data */
	UDR = data;

}

void USART_RX_SetISR(void (*ptr)(void)){
	USART_ptr = ptr;
}

//USART_RXC_vect, USART_UDRE_vect, USART_TXC_vect
ISR(USART_RXC_vect){
	USART_ptr();
}

ISR(USART_TXC_vect){

}

