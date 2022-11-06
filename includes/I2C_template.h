/*
 * I2C_template.h
 *
 *  Created on: 24 окт. 2022 г.
 *      Author: shurik
 */
#ifndef __I2C__TEMPLATE__H__
#define __I2C__TEMPLATE__H__

#include "MemoryMap.h"
class IICCallback {
public:
	virtual ~IICCallback() {}
	virtual void iicCallback() = 0;
};
/**
 *		single byte master transmitter
 */
class I2C1 {
	IICCallback *callback;
	IIC_REGS regs;
	char sdata;
	char adr;
	enum Status {IDLE, BUSY, STOPPING};
	Status status;
	void prep_act() {while (regs->CR1 & (IIC_PEC | IIC_STOP | IIC_START));}//????
	bool busy() {return status != IDLE;}
public:
	I2C1() : callback(0), sdata('#'), adr(0x27), status(IDLE) {regs = IIC(1); init();}
	void init();
	void setCallback(IICCallback *cb) {callback = cb;}
	bool send(char);
	void interrupt();
	void err();
};

extern I2C1 i2c;

#endif
