/*
 * Lcd1602.cpp
 *
 *  Created on: 30 окт. 2022 г.
 *      Author: shurik
 */
#include "Lcd1602.h"

void Lcd1602::init() {
	comm(0, 0xFFFF, 8);		// FFFF mks * 8 == 7FFF8 == 524.280mks ~~ 0,5 sek
	comm(0, 0xFFFF, 8);
	comm(0x38, 4500, 3);
	comm(0x38, 4500, 3);
	comm(0x38, 150, 3);
	comm(0x28, 0, 3);
}

bool Lcd1602::prepare() {
	//uint32_t item = pop();
	b_command = pop();
	if (!b_command) return false; ser.print('p');

	status = State((b_command >> 22) & 0x1F);

	//status = PREPARED;
	b_byte = b_command & 0xFF;
	//delay = (b_command >> 8) & 0xFFFF;
	loadbuf();
	return true;
}

void Lcd1602::loadbuf() {
	status |= RETRY;
	switch (status & 0x1F) {
	case 5 << 2:
	case 2 << 2:
		b_delay = 0;
		b_byte &= ~BIT_E;
		break;
	case 4 << 2:
	case 1 << 2:
		b_delay = DELAY_1;
		b_byte |= BIT_E;
		break;
	case 3 << 2:
		b_byte &= ~BIT_E;
		b_delay = DELAY_50;
		break;
	case 0:
		b_byte &= ~BIT_E;
		b_delay = DELAY_50 + ((b_command >> 8) & 0xFFFF);
		break;
	}
}

void Lcd1602::write() {ser.print('1');
	//assuming entering with status RETRY
	if (!b_byte) {////////////////////////////////////////////////////??????????
		status -= 2;		//	RETRY -> TIMEOUT
		tim.start(b_delay);
		return;
	}

	if (i2c.send(b_byte)) {
		//status = SENDING;ser.print('4');
		status--;		//	RETRY -> SENDING
	}
	else {
		//status = RETRY;
		tim.start(DELAY_RETRY);ser.print('5');
	}
}

void Lcd1602::transmit() {
	if (status != READY) return;
	//status = SENDING;
	if (prepare())
		write();
}

void Lcd1602::timerCallback() {
	if ((status & 3) == RETRY) {ser.print('6');
		write();
	} else if ((status & 3) == TIMEOUT) {
		if ((status & ~3)) {		// next lap
			status -= 2;		//	TIMEOUT -> READY next lap
			loadbuf();
			write();
		} else
		if (prepare()) {ser.print('7');
			write();
		}
		else {ser.print('9');
			status = READY;
		}
	}
}

void Lcd1602::iicCallback() {ser.print('8');
	//assumed entering with status SENDING
	if (b_delay) {
		status--;		//	SENDING -> TIMEOUT
		tim.start(b_delay);
	} else {
		//status &= ~3;
		if ((status & ~3) == READY) {		//	all laps passed
			if (prepare()) write();
			else status = READY;
		}
		else {		//	next lap
			status -= 3;		//	RETRY of next lap
			loadbuf();
			write();
		}
	}
}
/*
Lcd1602::State& operator--(Lcd1602::State& s) {
	return s = Lcd1602::State(int(s) - 1);
}

Lcd1602::State& operator-=(Lcd1602::State& s, int i) {
	return s = Lcd1602::State(int(s) - i);
}
*/
