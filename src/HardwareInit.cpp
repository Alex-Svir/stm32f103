/*
 * HardwareInit.cpp
 *
 *  Created on: 20 окт. 2022 г.
 *      Author: shurik
 */
#include "HardwareInit.h"
#include "MemoryMap.h"
/*****************************************************************************
 * 							USART 1, 2, 3
 *****************************************************************************/
void _init_usart1() {
	RCC()->APB2ENR |= 0x4004;		//	IOPAEN, USART1EN
	GPIOx_REGS gpioA = GPIOX(A);
	gpioA->CRH = (gpioA->CRH & 0xFFFFF00F) | 0x0890;	//	A9 / A10
}

void _init_usart2() {
	RCC_REGS rcc =RCC();
	rcc->APB2ENR |= 0x04;			//	IOPAEN
	GPIOx_REGS gpioA = GPIOX(A);
	gpioA->CRL = (gpioA->CRL & 0xFFFF00FF) | 0x8900;	//	A2 / A3
	rcc->APB1ENR |= 0x00020000;		//	USART2EN
}

void _init_usart3() {
	RCC_REGS rcc = RCC();
	rcc->APB2ENR |= 0x08;			//	IOPBEN
	GPIOx_REGS gpioB = GPIOX(B);
	gpioB->CRH = (gpioB->CRH & 0xFFFF00FF) | 0x8900;	//	B10 / B11
	rcc->APB1ENR |= 0x00040000;		//	USART3EN
}
/****************************************************************************
 * 						SPI 1, 2
 ****************************************************************************/
void _init_spi1(bool mstr) {
	RCC_REGS rcc = RCC();
	rcc->APB2ENR &= ~0x1000;		//	SPI1 off
	rcc->APB2ENR |= 0x04;			//	GPIOAEN
	(GPIOX(A)->CRL &= 0xFFFF) |= (mstr ? 0x98990000 : 0x89880000);
	rcc->APB2ENR |= 0x1000;			//	SPI1EN
}

void _init_spi2(bool mstr) {
	RCC_REGS rcc = RCC();
	rcc->APB1ENR &= ~0x4000;		//	SPI2 off
	rcc->APB2ENR |= 0x08;			//	GPIOBEN
	(GPIOX(B)->CRH &= 0xFFFF) |= (mstr ? 0x98990000 : 0x89880000);
	rcc->APB1ENR |= 0x4000;			//	SPI2EN
}
/****************************************************************************
 * 							I2C 1, 2
 ****************************************************************************/
void _init_i2c1(bool mstr) {
	RCC_REGS rcc = RCC();
	rcc->APB1ENR &= ~0x00200000;	//	I2C1 off
	rcc->APB2ENR |= 0x08;			//	GPIOBEN
	(GPIOX(B)->CRL &= 0x00FFFFFF) |= (mstr ? 0xDD000000 : 0x44000000);
	rcc->APB1ENR |= 0x00200000;		//	I2C1EN
}

void _init_12c2(bool mstr) {
	RCC_REGS rcc = RCC();
	rcc->APB1ENR &= ~0x00400000;	//	I2C2 off
	rcc->APB2ENR |= 0x08;			//	GPIOBEN
	(GPIOX(B)->CRH &= 0xFFFF00FF) |= (mstr ? 0xDD00 : 0x4400);
	rcc->APB1ENR |= 0x00400000;		//	I2C2EN
}
/****************************************************************************
 * 							TIM 1, 2, 3, 4, .....
 ****************************************************************************/
void _init_tim1() {RCC()->APB2ENR |= 0x0800;}
void _init_tim2() {RCC()->APB1ENR |= 0x01;}
void _init_tim3() {RCC()->APB1ENR |= 0x02;}
void _init_tim4() {RCC()->APB1ENR |= 0x04;}
void _init_tim5() {RCC()->APB1ENR |= 0x08;}
void _init_tim6() {RCC()->APB1ENR |= 0x10;}
void _init_tim7() {RCC()->APB1ENR |= 0x20;}
void _init_tim8() {RCC()->APB2ENR |= 0x2000;}
