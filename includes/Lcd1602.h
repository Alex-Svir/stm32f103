/*
 * Lcd1602.h
 *
 *  Created on: 24 окт. 2022 г.
 *      Author: shurik
 */

#ifndef __LCD__1602__H__
#define __LCD__1602__H__

#include "I2C_template.h"
#include "Usart2.h"
#include "Timer_template.h"

extern Usart2 ser;

class Lcd1602 : public TimerCallback, public IICCallback {
	static const unsigned SZ = 256;
	static const int delay_1 = 500;
	static const int delay_retry = 25;
	enum State {READY, PREPARED, RETRY, SENDING, TIMEOUT};
	Timer2 tim;
	uint32_t queue[SZ];
	uint32_t front, back;
	State status;
	uint16_t delay;
	char byte;
	//bool active;
	uint32_t& move(uint32_t& p) {if (++p == SZ) p = 0; return p;}
	void push(uint32_t c) {queue[back] = c; move(back);}
	uint32_t pop()
		{if (back == front) return 0; uint32_t tmp = queue[front]; move(front); return tmp;}
	bool prepare();
	void write();
	void transmit();
public:
	Lcd1602() : tim(this), front(0), back(0), status(READY), delay(0), byte(0)/*, active(false)*/
		{i2c.setCallback(this);}
	void wait(int mks) {mks *= 3; while(--mks);}
	void comm(char c, unsigned mks = 50) {push(c | (mks << 8)); transmit();}
	void timerCallback();
	void iicCallback();
};

#endif
