/*
 * I2C_template.h
 *
 *  Created on: 24 окт. 2022 г.
 *      Author: shurik
 */
#include "I2C_template.h"
#include <inttypes.h>
#include "CorePeripherals.h"
#include "HardwareInit.h"

#include "Usart2.h"

I2C1 i2c;

void I2C1::init() {
	regs->CR1 = 0;
	_init_i2c1(true);
	regs->CR2 = /*I2C_ITBUFEN |*/ IIC_ITEVTEN | IIC_ITERREN | 0x08;		//	move
	//regs->OAR1 = adr << 1;
	regs->CCR = 0x28;
	regs->TRISE = 9;
	nvic_setenbl(31);
	nvic_setenbl(32);
	regs->CR1 = IIC_PE;
}

extern Usart2 ser;

bool I2C1::send(char d) {
	if (busy()) return false;
	/*
	if (regs->SR2 & (IIC_BUSY | IIC_MSL)) {
		//ser.print("Busy HAX!\n");
		return false;
	}
	*/
	status = BUSY;
	ser.print('s');//..
	sdata = d;
	prep_act();
	ser.print('\n');
	ser.print((regs->SR1 & IIC_SB) ? '<' : '>');	ser.print(d);//
	//	interrupts enable: move from
	regs->CR1 |= IIC_START;
	ser.print('S');//..
	return true;
}

void I2C1::interrupt() {
	ser.print('|');
	uint32_t sr1 = regs->SR1;
	if (sr1 & IIC_SB) {
		ser.print('^');
		regs->DR = (adr << 1);
		return;							//
	}
	if (sr1 & IIC_BTF) {
		ser.print('.');
		//prep_act();					//	?????????? double STOP?
		if (status == BUSY) {
			status = STOPPING;
			regs->CR1 |= IIC_STOP;
			ser.print('!');
		}
		return;
	}
	if (sr1 & IIC_ADDR) {
		ser.print('@');
		if (regs->SR2 & IIC_TRA) regs->DR = sdata;	//	need to read SR2 to clear ADDR
	}
	if (sr1 & IIC_TXE  /*&& ITBUFEN*/) {
		//if buf is empty -- disable ITBUFEN
		ser.print('_');
		return;
	}
	if (sr1 & IIC_STOPF) {ser.print('*');return;}		//	just for lulz
	//	a mysterious interrupt in the end without any flags set. A BUG????
	ser.print('?');
	status = IDLE;
	if (callback) callback->iicCallback();
}

void I2C1::err() {
	uint16_t e = regs->SR1;
	e >>= 8;
	int cnt = 1;
	if (e) while (! (e & 1)) {e >>= 1; cnt++;}
	char a = (e == 1) ? 'A' + cnt : 'X';

	ser.print(a);
	ser.print("_ERROR\n");
	regs->SR1 &= 0;
}

void ihr_I2C1_EV() {
	i2c.interrupt();
}

void ihr_I2C1_ER() {
	i2c.err();
}
