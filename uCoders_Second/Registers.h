/*
 * Registers.h
 *
 *  Created on: Dec 15, 2019
 *      Author: DELL
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

#define PORTA (*(volatile U8*)0x3B)
#define DDRA (*(volatile U8*)0x3A)
#define PINA (*(volatile U8*)0x39)

#define PORTB (*(volatile U8*)0x38)
#define DDRB (*(volatile U8*)0x37)
#define PINB (*(volatile U8*)0x36)

#define PORTC (*(volatile U8*)0x35)
#define DDRC (*(volatile U8*)0x34)
#define PINC (*(volatile U8*)0x33)

#define PORTD (*(volatile U8*)0x32)
#define DDRD (*(volatile U8*)0x31)
#define PIND (*(volatile U8*)0x30)

#define SFIOR (*(volatile U8*)0x50)

#define MCUCR (*(volatile U8*)0x55)
#define MCUCSR (*(volatile U8*)0x54)

#define GICR (*(volatile U8*)0x5B)
#define GIFR (*(volatile U8*)0x5A)
#define SREG (*(volatile U8*)0x5F)

#define ADMUX (*(volatile U8*)0x27)
#define ADCSRA (*(volatile U8*)0x26)
#define ADCH (*(volatile U8*)0x25)
#define ADCL (*(volatile U8*)0x24)

#define TCCR0 (*(volatile U8*)0x53)
#define TCNT0 (*(volatile U8*)0x52)
#define OCR0 (*(volatile U8*)0x5C)
#define TIMSK (*(volatile U8*)0x59)
#define TIFR (*(volatile U8*)0x58)

#define TCCR2 (*(volatile U8*)0x45)
#define TCNT2 (*(volatile U8*)0x44)
#define OCR2 (*(volatile U8*)0x43)

#define UDR   (*(volatile U8*)0x2C)
#define UCSRA (*(volatile U8*)0x2B)
#define UCSRB (*(volatile U8*)0x2A)
#define UBRRL (*(volatile U8*)0x29)
#define UBRRH (*(volatile U8*)0x40)
#define UCSRC (*(volatile U8*)0x40)



#endif /* REGISTERS_H_ */
