/*
 * MemoryMap.h
 *
 *  Created on: 11 окт. 2022 г.
 *      Author: shurik
 */

#ifndef __MEMORYMAP__H__
#define __MEMORYMAP__H__

#include <inttypes.h>

typedef uint32_t REG_PTR;
const uint32_t __REGS_DELTA = 0x400;
//-------------------------------------------------------------------
///*****************************************************************
///*****************************************************************
/// 				Reset and clock control RCC
/// ****************************************************************
/// ****************************************************************
struct __RCC_BASE {
	REG_PTR CR;
	REG_PTR CFGR;
	REG_PTR CIR;
	REG_PTR APB2RSTR;
	REG_PTR APB1RSTR;
	REG_PTR AHBENR;
	REG_PTR APB2ENR;
	REG_PTR APB1ENR;
	REG_PTR BDCR;
	REG_PTR CSR;
};
typedef __RCC_BASE* RCC_REGS;
const uint32_t __RCC_BASE_OFFSET	=	0x40021000;
inline RCC_REGS RCC() {return RCC_REGS(__RCC_BASE_OFFSET);}
/*********************************************************************
 *********************************************************************
 * 							GPIO Port A - G
 *********************************************************************
 *********************************************************************/
struct __GPIOx_BASE {
	REG_PTR CRL;
	REG_PTR CRH;
	REG_PTR IDR;
	REG_PTR ODR;
	REG_PTR BSRR;
	REG_PTR BRR;
	REG_PTR LCKR;
};
typedef enum {A, B, C, D, E, F, G} GPIO_PORT;
typedef __GPIOx_BASE* GPIOx_REGS;
const uint32_t __GPIOA_BASE_OFFSET	=	0x40010800;
const uint32_t __GPIOs_DELTA	=	0x400;
inline GPIOx_REGS GPIOX(GPIO_PORT p)
		{return GPIOx_REGS(__GPIOA_BASE_OFFSET + (p - A) * __GPIOs_DELTA);}
/************************************************************************
 ************************************************************************
 *									TIMER
 ************************************************************************
 ************************************************************************/
struct __TIM_BASE {
	REG_PTR CR1;			//	0
	REG_PTR CR2;			//	4
	REG_PTR SMCR;			//	8
	REG_PTR DIER;			//	C
	REG_PTR SR;				//	10
	REG_PTR EGR;			//	14
	REG_PTR CCMR1;			//	18
	REG_PTR CCMR2;			//	1C
	REG_PTR CCER;			//	20
	REG_PTR CNT;			//	24
	REG_PTR PSC;			//	28
	REG_PTR ARR;			//	2C
	REG_PTR RCR;			//	30
	REG_PTR CCR1;			//	34
	REG_PTR CCR2;			//	38
	REG_PTR CCR3;			//	3C
	REG_PTR CCR4;			//	40
	REG_PTR BDTR;			//	44
	REG_PTR DCR;			//	48
	REG_PTR DMAR;			//	4C
};
typedef __TIM_BASE* TIMx_REGS;
const uint32_t __TIM2_BASE_OFFSET	=	0x40000000;
const uint32_t __TIM1_BASE_OFFSET	=	0x40012C00;
const uint32_t __TIM8_BASE_OFFSET	=	0x40013400;
const uint32_t __TIM9_BASE_OFFSET	=	0x40014C00;
inline TIMx_REGS TIMX(unsigned i) {
	return TIMx_REGS(	(i == 1) ? __TIM1_BASE_OFFSET
			:	(i == 8)	?	__TIM8_BASE_OFFSET
			:	(i < 8) 	?	__TIM2_BASE_OFFSET + (i - 2) * __REGS_DELTA
			:	(i < 12)	?	__TIM9_BASE_OFFSET + (i - 9) * __REGS_DELTA
			:	__TIM2_BASE_OFFSET + (i - 6) * __REGS_DELTA);}
enum {
	TIM_CEN			=	1 << 0,			//	TIMx_CR1	0x00
	TIM_UDIS		=	1 << 1,
	TIM_URS			=	1 << 2,
	TIM_OPM			=	1 << 3,
	TIM_DIR			=	1 << 4,
	TIM_ARPE		=	1 << 7,
	TIM_CCPC		=	1 << 0,			//	TIMx_CR2	0x04
	TIM_CCUS		=	1 << 2,
	TIM_CCDS		=	1 << 3,
	TIM_TI1S		=	1 << 7,
	TIM_OIS1		=	1 << 8,
	TIM_OIS1N		=	1 << 9,
	TIM_OIS2		=	1 << 10,
	TIM_OIS2N		=	1 << 11,
	TIM_OIS3		=	1 << 12,
	TIM_OIS3N		=	1 << 13,
	TIM_OIS4		=	1 << 14,
	TIM_MSM			=	1 << 7,			//	TIMx_SMCR	0x08
	TIM_ECE			=	1 << 14,
	TIM_ETP			=	1 << 15,
	TIM_UIE			=	1 << 0,			//	TIMx_DIER	0x0C
	TIM_CC1IE		=	1 << 1,
	TIM_CC2IE		=	1 << 2,
	TIM_CC3IE		=	1 << 3,
	TIM_CC4IE		=	1 << 4,
	TIM_COMIE		=	1 << 5,
	TIM_TIE			=	1 << 6,
	TIM_BIE			=	1 << 7,
	TIM_UDE			=	1 << 8,
	TIM_CC1DE		=	1 << 9,
	TIM_CC2DE		=	1 << 10,
	TIM_CC3DE		=	1 << 11,
	TIM_CC4DE		=	1 << 12,
	TIM_COMDE		=	1 << 13,
	TIM_TDE			=	1 << 14,
	TIM_UIF			=	1 << 0,			//	TIMx_SR		0x10
	TIM_CC1IF		=	1 << 1,
	TIM_CC2IF		=	1 << 2,
	TIM_CC3IF		=	1 << 3,
	TIM_CC4IF		=	1 << 4,
	TIM_COMIF		=	1 << 5,
	TIM_TIF			=	1 << 6,
	TIM_BIF			=	1 << 7,
	TIM_CC1OF		=	1 << 9,
	TIM_CC2OF		=	1 << 10,
	TIM_CC3OF		=	1 << 11,
	TIM_CC4OF		=	1 << 12,
	TIM_UG			=	1 << 0,			//	TIMx_EGR	0x14
	TIM_CC1G		=	1 << 1,
	TIM_CC2G		=	1 << 2,
	TIM_CC3G		=	1 << 3,
	TIM_CC4G		=	1 << 4,
	TIM_COMG		=	1 << 5,
	TIM_TG			=	1 << 6,
	TIM_BG			=	1 << 7,
	TIM_OC1FE		=	1 << 2,			//	TIMx_CCMR1	0x18
	TIM_OC1PE		=	1 << 3,
	TIM_OC1CE		=	1 << 7,
	TIM_OC2FE		=	1 << 10,
	TIM_OC2PE		=	1 << 11,
	TIM_OC2CE		=	1 << 15,
	TIM_OC3FE		=	1 << 2,			//	TIMx_CCMR2	0x1C
	TIM_OC3PE		=	1 << 3,
	TIM_OC3CE		=	1 << 7,
	TIM_OC4FE		=	1 << 10,
	TIM_OC4PE		=	1 << 11,
	TIM_OC4CE		=	1 << 15,
	TIM_CC1E		=	1 << 0,			//	TIMx_CCER	0x20
	TIM_CC1P		=	1 << 1,
	TIM_CC1NE		=	1 << 2,
	TIM_CC1NP		=	1 << 3,
	TIM_CC2E		=	1 << 4,
	TIM_CC2P		=	1 << 5,
	TIM_CC2NE		=	1 << 6,
	TIM_CC2NP		=	1 << 7,
	TIM_CC3E		=	1 << 8,
	TIM_CC3P		=	1 << 9,
	TIM_CC3NE		=	1 << 10,
	TIM_CC3NP		=	1 << 11,
	TIM_CC4E		=	1 << 12,
	TIM_CC4P		=	1 << 13,
	TIM_CC4NP		=	1 << 15,
	TIM_OSSI		=	1 << 10,		//	TIMx_BDTR	0x44
	TIM_OSSR		=	1 << 11,
	TIM_BKE			=	1 << 12,
	TIM_BKP			=	1 << 13,
	TIM_AOE			=	1 << 14,
	TIM_MOE			=	1 << 15
};
/************************************************************************
 ************************************************************************
 * 									SPI
 ************************************************************************
 ************************************************************************/
struct __SPI_BASE {
	REG_PTR CR1;
	REG_PTR CR2;
	REG_PTR SR;
	REG_PTR DR;
	REG_PTR CRCPR;
	REG_PTR RXCRCR;
	REG_PTR TXCRCR;
	REG_PTR I2SCFGR;
	REG_PTR I2SPR;
};
typedef __SPI_BASE* SPI_REGS;
const uint32_t __SPI_1_BASE			=	0x40013000;
const uint32_t __SPI_2_BASE			=	0x40003800;
inline SPI_REGS SPI(unsigned i) { return SPI_REGS( (i == 1) ? __SPI_1_BASE
					: __SPI_2_BASE + (i - 2) * __REGS_DELTA ); }
enum {
	SPI_CPHA		=	1 << 0,				//	SPI_CR1
	SPI_CPOL		=	1 << 1,
	SPI_MSTR		=	1 << 2,
	SPI_SPE			=	1 << 6,
	SPI_LSBFIRST	=	1 << 7,
	SPI_SSI			=	1 << 8,
	SPI_SSM			=	1 << 9,
	SPI_RXONLY		=	1 << 10,
	SPI_DFF			=	1 << 11,
	SPI_CRCNEXT		=	1 << 12,
	SPI_CRCEN		=	1 << 13,
	SPI_BIDIOE		=	1 << 14,
	SPI_BIDIMODE	=	1 << 15,
	SPI_RXDMAEN		=	1 << 0,				//	SPI_CR2
	SPI_TXDMAEN		=	1 << 1,
	SPI_SSOE		=	1 << 2,
	SPI_ERRIE		=	1 << 5,
	SPI_RXNEIE		=	1 << 6,
	SPI_TXEIE		=	1 << 7,
	SPI_RXNE		=	1 << 0,				//	SPI_SR
	SPI_TXE			=	1 << 1,
	SPI_CHSIDE		=	1 << 2,
	SPI_UDR			=	1 << 3,
	SPI_CRCERR		=	1 << 4,
	SPI_MODF		=	1 << 5,
	SPI_OVR			=	1 << 6,
	SPI_BSY			=	1 << 7,
	SPI_CHLEN		=	1 << 0,				//	SPI_I2SCFGR
	SPI_CKPOL		=	1 << 3,
	SPI_PCMSYNC		=	1 << 7,
	SPI_I2SE		=	1 << 10,
	SPI_I2SMOD		=	1 << 11,
	SPI_ODD			=	1 << 8,				//	SPI_I2SPR
	SPI_MCKOE		=	1 << 9
};
/****************************************************************************
 ****************************************************************************
 * 									USART
 ****************************************************************************
 ****************************************************************************/
struct __USART_BASE {
	REG_PTR SR;
	REG_PTR DR;
	REG_PTR BRR;
	REG_PTR CR1;
	REG_PTR CR2;
	REG_PTR CR3;
	REG_PTR GTPR;
};
typedef __USART_BASE* USART_REGS;
const uint32_t __USART_1_BASE		=	0x40013800;
const uint32_t __USART_2_BASE		=	0x40004400;
const uint32_t __USART_DELTA	=	0x400;
inline USART_REGS USART(int i) { return USART_REGS( (i == 1) ? __USART_1_BASE
							: __USART_2_BASE + (i - 2) * __USART_DELTA ); }
/************************************************************************
 ************************************************************************
 *								I2C
 ************************************************************************
 ************************************************************************/
struct __IIC_BASE {
	REG_PTR CR1;
	REG_PTR CR2;
	REG_PTR OAR1;
	REG_PTR OAR2;
	REG_PTR DR;
	REG_PTR SR1;
	REG_PTR SR2;
	REG_PTR CCR;
	REG_PTR TRISE;
};
typedef __IIC_BASE* IIC_REGS;
const uint32_t __IIC_1_BASE			=	0x40005400;
inline IIC_REGS IIC(unsigned i) {return IIC_REGS(__IIC_1_BASE + (i - 1) * __REGS_DELTA);}
enum {
	IIC_PE					=	1 << 0,			//	IIC_CR1
	IIC_SMBUS				=	1 << 1,
	IIC_SMBTYPE				=	1 << 3,
	IIC_ENARP				=	1 << 4,
	IIC_ENPEC				=	1 << 5,
	IIC_ENGC				=	1 << 6,
	IIC_NOSTRETCH			=	1 << 7,
	IIC_START				=	1 << 8,
	IIC_STOP				=	1 << 9,
	IIC_ACK					=	1 << 10,
	IIC_POS					=	1 << 11,
	IIC_PEC					=	1 << 12,
	IIC_ALERT				=	1 << 13,
	IIC_SWRST				=	1 << 15,
	IIC_ITERREN				=	1 << 8,			//	IIC_CR2
	IIC_ITEVTEN				=	1 << 9,
	IIC_ITBUFEN				=	1 << 10,
	IIC_DMAEN				=	1 << 11,
	IIC_LAST				=	1 << 12,
	IIC_ADD0				=	1 << 0,			//	IIC_OAR1
	IIC_ADDMODE				=	1 << 15,
	IIC_ENDUAL				=	1 << 0,			//	IIC_OAR2
	IIC_SB					=	1 << 0,			//	IIC_SR1
	IIC_ADDR				=	1 << 1,
	IIC_BTF					=	1 << 2,
	IIC_ADD10				=	1 << 3,
	IIC_STOPF				=	1 << 4,
	IIC_RXNE				=	1 << 6,
	IIC_TXE					=	1 << 7,
	IIC_BERR				=	1 << 8,
	IIC_ARLO				=	1 << 9,
	IIC_AF					=	1 << 10,
	IIC_OVR					=	1 << 11,
	IIC_PECERR				=	1 << 12,
	IIC_TIMEOUT				=	1 << 14,
	IIC_SMBALERT			=	1 << 15,
	IIC_MSL					=	1 << 0,			//	IIC_SR2
	IIC_BUSY				=	1 << 1,
	IIC_TRA					=	1 << 2,
	IIC_GENCALL				=	1 << 4,
	IIC_SMBDEFAULT			=	1 << 5,
	IIC_SMBHOST				=	1 << 6,
	IIC_DUALF				=	1 << 7,
	IIC_DUTY				=	1 << 14,		//	IIC_CCR
	IIC_FS					=	1 << 15
};
//===============================================================


#endif
