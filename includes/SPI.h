/*
 * SPI.h
 *
 *  Created on: 19 окт. 2022 г.
 *      Author: shurik
 */
#ifndef __SPI__H__
#define __SPI__H__
#include "SPI_template.h"
#include "HardwareInit.h"

typedef  __spiTemplate<256, 1, char, _init_spi1, 35> SPI1_T;
typedef  __spiTemplate<256, 2, char, _init_spi2, 36> SPI2_T;

extern SPI1_T SPI1;
extern SPI2_T SPI2;

#endif
