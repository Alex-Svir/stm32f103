/*
 * Lcd1602.cpp
 *
 *  Created on: 30 окт. 2022 г.
 *      Author: shurik
 */
#include "Lcd1602.h"

void Lcd1602::init() {
	for (int i = 16; i--;) comm(0, 0xFFFF);	//	timeout 16 * FFFF mks			<<<<<<
	comm(0x3, 4500, false, 3);
	comm(0x3, 4500, false, 3);
	comm(0x3, 150, false, 3);
	comm(0x2, 0, false, 3);

	persistant = 8;			//	back light on
	comm(0x28, 0);			//	FUNCTION SET: 4D; 2 rows; 5x7 style
	comm(0x0C, 0);			//	DISPLAY SWITCH: Display +, cursor -, blink -
	comm(1, 2000);			//	SCREEN CLEAR
	comm(6, 0);				//	INPUT SET: ...									<<<<<<??

	comm(2, 2000);			//	CURSOR RETURN

	print(' ');
	comm('S', 0, true, 6);
	print('T');
	comm('E', 0, true);
	print('L');
	print('L');
	print('A');
	print(" MY LOVE");
}

bool Lcd1602::preload() {
	b_command = pop();
	if (!b_command) {ser.print('p');
		status = READY;
		return false;
	}
	status = State((b_command >> 22) & 0x1C);		//	laps count: lll..
	b_byte = persistant | ((b_command >> 27) & 1);	//	light | ~E | RW | RS
	return true;
}

bool Lcd1602::tmout_called() {
	if (b_command & 0xFF) return false;
	status = TIMEOUT;
	tim.start((b_command >> 8) & 0xFFFF);
	return true;
}

void Lcd1602::load() {
	status |= RETRY;
	switch (status & 0x1C) {	//	lap id
	case 5 << 2:
		b_byte |= b_command & 0xF0;		//	most sign 4 bits
		b_delay = 0;
		break;
	case 2 << 2:
		b_byte = ((b_command << 4) & 0xF0) | (b_byte & 0x0F);	//	less sign 4 bits
		b_delay = 0;
		break;
	case 4 << 2:
	case 1 << 2:
		b_delay = DELAY_1;
		b_byte |= BIT_E;			//	latch on
		break;
	case 3 << 2:
		b_byte &= ~BIT_E;			//	latch off
		b_delay = DELAY_50;
		break;
	case 0:
		b_byte &= ~BIT_E;			//	latch off
		b_delay = DELAY_50 + ((b_command >> 8) & 0xFFFF);	//	+ command delay
		break;
	}
}

void Lcd1602::write() {ser.print('1');
	//assuming entering with status RETRY
	if (i2c.send(b_byte)) {
		status--;		//	RETRY -> SENDING
	}
	else {
		tim.start(DELAY_RETRY);ser.print('5');		//status = RETRY;
	}
}

void Lcd1602::queue_peek_sequence() {
	if (!preload()) return;
	if (tmout_called()) return;
	load();
	write();
}
/*
void Lcd1602::transmit() {
	if (status != READY) return;
	queue_peek_sequence();
}
*/
void Lcd1602::timerCallback() {
	if ((status & 3) == RETRY) {ser.print('6');
		write();
	} else if ((status & 3) == TIMEOUT) {
		if ((status & ~3)) {		// next lap
			status -= 2;		//	TIMEOUT -> READY next lap
			load();
			write();
		} else {
			queue_peek_sequence();
		}
	}
}

void Lcd1602::iicCallback() {ser.print('8');
	//assumed entering with status SENDING
	if (b_delay) {
		status--;		//	SENDING -> TIMEOUT
		tim.start(b_delay);
	} else {
		if ((status & ~3) == READY) {		//	all laps passed
			queue_peek_sequence();
		}
		else {		//	next lap
			status -= 3;		//	RETRY of next lap
			load();
			write();
		}
	}
}
