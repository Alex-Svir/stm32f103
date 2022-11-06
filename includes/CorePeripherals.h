/*
 * CorePeripherals.h
 *
 *  Created on: 11 окт. 2022 г.
 *      Author: shurik
 */
#ifndef __CORE__PERIPHERALS__H__
#define __CORE__PERIPHERALS__H__

#include <inttypes.h>

typedef uint32_t REG_PTR;
//-------------------------------------------------------------------------
/**************************************************************************
 * 								SysTick
 **************************************************************************/
struct __STK_BASE {
	REG_PTR CTRL;
	REG_PTR LOAD;
	REG_PTR VAL;
	REG_PTR CALIB;
};
typedef __STK_BASE* STK_REGS;
const uint32_t __STK_BASE_OFFSET		=	0xE000E010;
inline STK_REGS STK() {return STK_REGS(__STK_BASE_OFFSET);}
/***************************************************************************
 *
 ***************************************************************************/
const uint32_t __SCB_BASE_OFFSET		=	0xE000ED00;
const uint32_t __MPU_BASE_OFFSET		=	0xE000ED90;
//==========================================================================
//---------------------------------------------------------------------------
/****************************************************************************
 * 								NVIC
 ****************************************************************************/
void nvic_setenbl(uint8_t);
void nvic_clrenbl(uint8_t);
void nvic_setpend(uint8_t);
void nvic_clrpend(uint8_t);

#endif
