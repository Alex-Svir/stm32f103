/*
 * Usart2.cpp
 *
 *  Created on: 12 окт. 2022 г.
 *      Author: shurik
 */
#include "Usart2.h"
#include "CorePeripherals.h"
#include "MemoryMap.h"

void Usart2::begin() {
	nvic_setenbl(idx + (idx<4 ? 36 : 48));
	USART_REGS usart = USART(idx);
	usart->CR1 = 0x2000;
	usart->BRR = 0x0341;
	usart->CR1 = 0x2008;
}

void Usart2::print(char c) {
	buf.push(c);
	settxeie();
}

void Usart2::print(const char* s) {
	buf.push(s);
	settxeie();
}

void Usart2::transmit_next() {
	if (char c = buf.pop()) tdr(c);
	else clrtxeie();
}
