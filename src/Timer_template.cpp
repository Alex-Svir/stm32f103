/*
 * Timer_template.cpp
 *
 *  Created on: 30 окт. 2022 г.
 *      Author: shurik
 */
#include "Timer_template.h"
#include "CorePeripherals.h"
#include "HardwareInit.h"

#include "Usart2.h"

static Timer2* __tim2_adapter = nullptr;

Timer2::Timer2(TimerCallback *cb) : callback(cb), kostyl(false) {
	_init_tim2();
	regs = TIMX(2);
	regs->SR = 0;
	regs->DIER = 1;
	regs->PSC = 8;
	__tim2_adapter = this;
	nvic_setenbl(28);
}
Timer2::~Timer2() {
	if (__tim2_adapter == this) __tim2_adapter = nullptr;
}

void Timer2::start(unsigned t) {
	regs->CR1 = 0;
	kostyl = true;
	regs->ARR = t;
	regs->CNT = 0;
	//regs->CR1 = 8;
	regs->CR1 = 9;
}

extern Usart2 ser;

void ihr_TIM2() {
	if (__tim2_adapter) __tim2_adapter->interrupt();
}

void Timer2::interrupt() {
	//if (!(regs->SR & TIM_UIF)) return;
	regs->SR = 0;
	if (!kostyl) return;
	kostyl = false;
	ser.print('%');
	ser.print("Timer!\n");
	if (callback) callback->timerCallback();//(*callback)();
}
