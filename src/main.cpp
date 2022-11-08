/*
 * main.cpp
 *
 *  Created on: 9 окт. 2022 г.
 *      Author: shurik
 *
 *      test_empty
 */
#include <inttypes.h>

#include "VectorsTable.h"
#include "CorePeripherals.h"
#include "MemoryMap.h"
#include "Usart2.h"
//#include "SPI.h"
#include "Lcd1602.h"
//#include "Timer_template.h"

class CC {
public:
	const char *c1, *c2, *c3;
	CC(const char* c1, const char *c2, const char *c3) : c1(c1), c2(c2), c3(c3) {}
};

CC c("\nBaba z vozy\n", "Dupel'-Zalupel'\n", "Xyxer-muxer\n");

volatile bool hseswflag;

void ihr_RCC() {
	RCC_REGS rcc = RCC();
	if (rcc->CIR & 0x08) {
		rcc->CIR = 0x80000;
		hseswflag = false;
	}
}

void blink() {
	GPIOx_REGS gpioC = GPIOX(C);			// off		// on
	gpioC->BSRR = (gpioC->ODR & 0x2000) ? 0x20000000 : 0x2000;
}

void ihr_SysTick() {
	blink();
}

Usart2 ser;
void ihr_USART2() {
	USART_REGS usart2 = USART(2);
	if (usart2->SR & 0x80) ser.transmit_next();
}

void spi_print(char c) {
	ser.print(c);
}

//Timer2 tim2;

void main() {
/*************************************************************************
*************************************************************************/
//************************************************************************
//************************************************************************
	RCC_REGS rcc = RCC();
//----------	switch to HSE		---------------
	nvic_setenbl(5);			//	set RCC_global interrupt
	rcc->CIR = 0x80800;			//	-HSERDY, +HSERDYIE
	rcc->CR |= 0x10000;			//	+HSEON
	hseswflag = true;
	while(hseswflag) {}
	nvic_clrenbl(5);
	rcc->CFGR = 1;				//	SW = HSE
	rcc->CR &= ~1;				//	-HSION
//----------	configure built in led		--------
	rcc->APB2ENR |= 0x10;
	GPIOx_REGS gpioC = GPIOX(C);
	gpioC->CRH = 0x44244444;
	gpioC->BSRR = 0x2000;			//	OFF
	//gpioC->BSRR = 0x2000 << 16;		//	ON
//-----------		setup SysTick		-------------
	STK_REGS stk = STK();
	stk->LOAD = 999999;
	stk->VAL = 0;
	stk->CTRL |= 3;
//----------------------------------------------------
	ser.begin();

	ser.print('f');
	ser.print('a');
	ser.print("gggggggggggggggg\n");
	ser.print('r');
	ser.print('h');
	ser.print("sgcycys\n");
	ser.print('d');
	ser.print(c.c1);
	ser.print(c.c2);
	ser.print(c.c3);

	//SPI2.config(true, spi_print);
	//SPI2.transfer("Bolshaja Zadnica!");

	//tim2.start(65000);

	Lcd1602 lcd;/*
	lcd.wait(2000000);
		lcd.comm(8, 1000000);
	lcd.comm(0x38);
		lcd.comm(0x3C, 1);
		lcd.comm(0x38, 4550);
	lcd.comm(0x38);
		lcd.comm(0x3C, 1);
		lcd.comm(0x38, 4550);
	lcd.comm(0x38);
		lcd.comm(0x3C, 1);
		lcd.comm(0x38, 200);
	lcd.comm(0x28);
		lcd.comm(0x2C, 1);
		lcd.comm(0x28, 50);*/


	/*
	lcd.wait(2000000);
		lcd.comm('A', 1000000);
	lcd.comm('B');
		lcd.comm('C', 1);
		lcd.comm('D', 4550);
	lcd.comm('E');
		lcd.comm('F', 1);
		lcd.comm('G', 4550);
	lcd.comm('H');
		lcd.comm('I', 1);
		lcd.comm('J', 200);
	lcd.comm('K');
		lcd.comm('L', 1);
		lcd.comm('M', 50);
*/
	//ser.print("Gotovo!\n");

	while(1);
}
