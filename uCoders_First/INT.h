/*
 * INT.h
 *
 *  Created on: Dec 16, 2019
 *      Author: DELL
 */

#ifndef INT_H_
#define INT_H_

#define INT0_PIN DIO_PORTD,PIN2
#define INT1_PIN DIO_PORTD,PIN3
#define INT2_PIN DIO_PORTB,PIN2

void INT0_SetISR(void (*ptr)(void));
void INT0_Init(void);

void INT1_SetISR(void (*ptr)(void));
void INT1_Init(void);

void INT2_SetISR(void (*ptr)(void));
void INT2_Init(void);

#endif /* INT_H_ */
