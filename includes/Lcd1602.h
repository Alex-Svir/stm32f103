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
	static const unsigned BIT_E = 4;
	static const unsigned BIT_LIGHT = 8;

	static const unsigned SZ = 1024;
	static const int DELAY_1 = 1;
	static const int DELAY_50 = 50;
	static const int DELAY_RETRY = 25;
	enum State {READY, TIMEOUT, SENDING, RETRY, MAX = 0x1F};

	Timer2 tim;
	uint32_t queue[SZ];
	uint32_t front, back;
	State status;

	uint32_t b_command;
	uint16_t b_delay;
	char b_byte;
	char persistant;

	void init();
	uint32_t& move_ptr(uint32_t& p) {if (++p == SZ) p = 0; return p;}
	void push(uint32_t c) {queue[back] = c; move_ptr(back);}
	uint32_t pop()
		{if (back == front) return 0; uint32_t tmp = queue[front]; move_ptr(front); return tmp;}

	bool preload();
	bool tmout_called();
	void load();
	void write();
	void queue_peek_sequence();
	void transmit() { if (status == READY) queue_peek_sequence(); }
	void comm(char c, unsigned mks, bool ds = false, int laps = 6)
		{push(c | ((mks & 0xFFFF) << 8) | ((--laps & 7) << 24) | (ds << 27)); transmit();}

	friend State& operator--(State& s, int) { return s = State(int(s) - 1); }
	friend State& operator-=(State& s, int i) { return s = State(int(s) - i); }
	friend State& operator|=(State& s, int i) { return s = State(int(s) | i); }
public:
	Lcd1602()
		: tim(this), front(0), back(0), status(READY),
		  b_command(0), b_delay(0), b_byte(0), persistant(0)
		{i2c.setCallback(this); init();}
	void timerCallback();
	void iicCallback();

	void wait(int mks) {comm(0, mks);}
	void instruction(char c, unsigned mks = 0) { comm(c, mks); }
	void print(char c) { comm(c, 0, true); }
	void print(const char* s) { while (*s) print(*s++); }
};

#endif
