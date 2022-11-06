/*
 * Timer_template.h
 *
 *  Created on: 30 окт. 2022 г.
 *      Author: shurik
 */

#ifndef __TIMER__TEMPLATE__H__
#define __TIMER__TEMPLATE__H__
#include "MemoryMap.h"

class TimerCallback {
public:
	virtual ~TimerCallback() {}
	virtual void timerCallback() = 0;
};

class Timer2 {
	TIMx_REGS regs;
	TimerCallback *callback;
	bool kostyl;
public:
	Timer2(TimerCallback* = nullptr);
	~Timer2();
	void start(unsigned);
	void interrupt();
};



#endif
