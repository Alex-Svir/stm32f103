/*
 * SPI.cpp
 *
 *  Created on: 19 окт. 2022 г.
 *      Author: shurik
 */
#include "SPI.h"

SPI1_T SPI1;
SPI2_T SPI2;

void ihr_SPI1() {
	SPI1.interrupt();
}

void ihr_SPI2() {
	SPI2.interrupt();
}
