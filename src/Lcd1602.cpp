/*
 * Lcd1602.cpp
 *
 *  Created on: 30 окт. 2022 г.
 *      Author: shurik
 */
#include "Lcd1602.h"

bool Lcd1602::prepare() {
	uint32_t item = pop();
	if (!item) return false;ser.print('p');
	status = PREPARED;
	byte = item & 0xFF;
	delay = (item >> 8) & 0xFFFF;
	return true;
}

void Lcd1602::write() {ser.print('1');
	//uint32_t it = pop();ser.print('2');
	//if (!it) return;ser.print('3');

	if (i2c.send(byte)) {
		status = SENDING;ser.print('4');
	}
	else {
		status = RETRY;
		tim.start(delay_retry);ser.print('5');
	}
	//tim.start(((it >> 8) & 0xFFFF) + delay1);
}

void Lcd1602::transmit() {
	if (status != READY) return;
	//status = SENDING;
	if (prepare())
	write();
}

void Lcd1602::timerCallback() {
	if (status == RETRY) {ser.print('6');
		write();
	} else if (status == TIMEOUT) {
		if (prepare()) {ser.print('7');
			write();
		}
		else {ser.print('9');
			status = READY;
		}
	}
}

void Lcd1602::iicCallback() {ser.print('8');
	status = TIMEOUT;
	tim.start(delay);
}

