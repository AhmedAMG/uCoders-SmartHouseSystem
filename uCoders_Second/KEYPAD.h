/*
 * KEYPAD.h
 *
 *  Created on: Dec 16, 2019
 *      Author: DELL
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define COUNTS 100
#define NOT_PRESSED_VALUE 255

#define ROW0PORT DIO_PORTC
#define ROW1PORT DIO_PORTC
#define ROW2PORT DIO_PORTC
#define ROW3PORT DIO_PORTC

#define ROW0PIN PIN4
#define ROW1PIN PIN5
#define ROW2PIN PIN6
#define ROW3PIN PIN7

#define ROW0DIR OUTPUT
#define ROW1DIR OUTPUT
#define ROW2DIR OUTPUT
#define ROW3DIR OUTPUT

#define COL0PORT DIO_PORTD
#define COL1PORT DIO_PORTD
#define COL2PORT DIO_PORTD
#define COL3PORT DIO_PORTD

#define COL0PIN PIN4
#define COL1PIN PIN5
#define COL2PIN PIN6
#define COL3PIN PIN7

#define COL0DIR INPUT
#define COL1DIR INPUT
#define COL2DIR INPUT
#define COL3DIR INPUT

void KEYPAD_Init(void);
U8 KEYPAD_Scan(void);

#endif /* KEYPAD_H_ */
