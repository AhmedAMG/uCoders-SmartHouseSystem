/*
 * DIO.h
 *
 *  Created on: Dec 15, 2019
 *      Author: DELL
 */

#ifndef DIO_H_
#define DIO_H_

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

void DIO_SetPortValue(U8 Port_Number, U8 Value);
void DIO_SetPortDirection(U8 Port_Number, U8 Direction);
void DIO_SetPinDirection(U8 Port_Number, U8 Pin_Number, U8 Direction);
void DIO_SetPinPullUp(U8 Port_Number, U8 Pin_Number);
void DIO_SetPinValue(U8 Port_Number, U8 Pin_Number, U8 Value);
U8 DIO_GetPinValue(U8 Port_Number, U8 Pin_Number);
U8 DIO_GetPortValue(U8 Port_Number);


#endif /* DIO_H_ */
