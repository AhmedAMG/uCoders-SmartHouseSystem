/*
 * BitOperations.h
 *
 *  Created on: Dec 15, 2019
 *      Author: DELL
 */

#ifndef BITOPERATIONS_H_
#define BITOPERATIONS_H_

#define SetBit(X,BIT) (X |= (1<<BIT))
#define ClearBit(X,BIT) (X &= ~(1<<BIT))
#define ToggleBit(X,BIT) (X ^= (1<<BIT))
#define GetBit(X,BIT) ((X & (1<<BIT)) >> BIT)

#endif /* BITOPERATIONS_H_ */
