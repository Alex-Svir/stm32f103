/*
 * SPI_template.h
 *
 *  Created on: 23 окт. 2022 г.
 *      Author: shurik
 */
#ifndef __SPI__TEMPLATE__H__
#define __SPI__TEMPLATE__H__

#include "Buffers.h"
#include "MemoryMap.h"
#include "CorePeripherals.h"

template<int BS, int ID, typename FR, void(*PIN)(bool), int NVIC>
class __spiTemplate {
	AsyncTextOutBuffer<BS> buf;
	SPI_REGS regs;
	void (*cbk)(FR);
	void setints() {regs->CR2 |= SPI_TXEIE | SPI_RXNEIE;}
	void clrints() {regs->CR2 &= ~(SPI_TXEIE | SPI_RXNEIE);}
	void settxeie() {regs->CR2 |= SPI_TXEIE;}
	void clrtxeie() {regs->CR2 &= ~SPI_TXEIE;}
	void setrxneie() {regs->CR2 |= SPI_RXNEIE;}
	void clrrxneie() {regs->CR2 &= ~SPI_RXNEIE;}
	bool master() {return regs->CR1 & SPI_MSTR;}
	bool txeie() {return regs->CR2 & SPI_TXEIE;}
	bool txe() {return regs->SR & SPI_TXE;}
	bool rxne() {return regs->SR & SPI_RXNE;}
public:
	__spiTemplate() : buf('#'), cbk(0) {regs = SPI(ID);}
	void config(bool, void (*)(FR));
	void queue(const char* s)	{buf.push(s); if (!master()) settxeie();}
	void queue(char c)			{buf.push(c); if (!master()) settxeie();}
	void transfer() {if (master() && !buf.empty()) settxeie();}
	void transfer(char c)			{buf.push(c); settxeie();}
	void transfer(const char* s)	{buf.push(s); settxeie();}
	inline void interrupt();
};
//----------------------------------------------------------------------
template<int BS, int ID, typename FR, void(*PIN)(bool), int NVIC>
void __spiTemplate<BS, ID, FR, PIN, NVIC>::config(bool mstr, void (*cb)(FR)) {
	clrints();
	regs->CR1 &= ~SPI_SPE;				//	SPE	off
	//_init_spi2(mstr);			//	not later!
	PIN(mstr);					//
	//SETTINGS
	regs->CR1 = SPI_LSBFIRST | (mstr ? SPI_MSTR : 0) | 0x18;	//	LSBFIRST MSTR BR
	regs->CR2 = mstr ? SPI_SSOE : 0;	//	SSOE
	nvic_setenbl(NVIC);
	cbk = cb;
	setrxneie();
	regs->CR1 |= SPI_SPE;				//	SPE
}
//----------------------------------------------------------------------
template<int BS, int ID, typename FR, void(*PIN)(bool), int NVIC>
void __spiTemplate<BS, ID, FR, PIN, NVIC>::interrupt() {
	/*
	if ((regs->SR & SPI_TXE) && (regs->CR2 & SPI_TXEIE)) {
		regs->DR = buf.pop();
		if (buf.empty()) clrtxeie();
	}
	if (regs->SR & SPI_RXNE) {
		if (cbk) cbk(regs->DR);
	}
	*/

	if ((regs->SR & SPI_TXE) && (regs->CR2 & SPI_TXEIE)) {	//	TXE
		FR c = buf.pop();	//
		regs->DR = c;				//
		//+:regs->DR = buf.pop();
		if (buf.empty()) clrtxeie();
		if (cbk) cbk(c);//ser.print(c);		//
		if (cbk) cbk('.');//ser.print('<');		//
	}
	if (regs->SR & SPI_RXNE) {								//	RXNE
		//+:callback(regs->DR);
		if (cbk) cbk(regs->DR);//ser.print(regs->DR);		//
		if (cbk) cbk(',');//ser.print('>');			//
	}
	if (cbk) cbk('|');//ser.print('|');		//
}

#endif
