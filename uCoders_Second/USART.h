/*
 * USART.h
 *
 *  Created on: Dec 18, 2019
 *      Author: DELL
 */

#ifndef USART_H_
#define USART_H_

void USART_Init(int baudRate);
U8 USART_Receive(void);
void USART_Transmit(U8 data);
void USART_RX_SetISR(void (*ptr)(void));


#endif /* USART_H_ */
