/*
 * HardwareInit.h
 *
 *  Created on: 20 окт. 2022 г.
 *      Author: shurik
 */

#ifndef __HARDWARE__INIT__H__
#define __HARDWARE__INIT__H__

void _init_usart1();
void _init_usart2();
void _init_usart3();
void _init_spi1(bool);
void _init_spi2(bool);
//void _init_spi3(bool);
void _init_i2c1(bool);
void _init_i2c2(bool);

void _init_tim1();
void _init_tim2();
void _init_tim3();
void _init_tim4();
void _init_tim5();
void _init_tim6();
void _init_tim7();
void _init_tim8();

#endif

