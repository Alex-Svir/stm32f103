/*
 * Usart2.h
 *
 *  Created on: 12 окт. 2022 г.
 *      Author: shurik
 */
#include <inttypes.h>
#include "MemoryMap.h"
#include "HardwareInit.h"
#include "Buffers.h"

#ifndef __USART2__H__
#define __USART2__H__

class Usart2 {
	static const unsigned sz = 2048;
	const unsigned idx;
	AsyncTextOutBuffer<sz> buf;
	USART_REGS regs;
	void tdr(char c) {regs->DR = c;}
	void settxeie() {regs->CR1 |= 0x80;}
	void clrtxeie() {regs->CR1 &= ~0x80;}
public:
	Usart2() : idx(2), buf('\0') {_init_usart2(); regs = USART(idx);}
	void begin();
	void print(char);
	void print(const char*);
	void transmit_next();
};

#endif
