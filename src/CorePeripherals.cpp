/*
 * CorePeripherals.cpp
 *
 *  Created on: 12 окт. 2022 г.
 *      Author: shurik
 */
#include "CorePeripherals.h"

const uint32_t NVIC_BASE_OFFSET		=	0xE000E100;
const uint32_t NVIC_STIR_OFFSET		=	0xE000EF00;
const uint32_t NVIC_ISER_OFFSET = 0;
const uint32_t NVIC_ICER_OFFSET = 0x80;
const uint32_t NVIC_ISPR_OFFSET = 0x100;
const uint32_t NVIC_ICPR_OFFSET = 0x180;
const uint32_t NVIC_IABR_OFFSET = 0x200;

inline void setbit(uint8_t i, uint32_t b) {
	REG_PTR *ptr = (REG_PTR*)(NVIC_BASE_OFFSET + b + ((i >> 5) << 2));
	*ptr = 1 << (i & 0x1F);
}

void nvic_setenbl(uint8_t i) {setbit(i, NVIC_ISER_OFFSET);}
void nvic_clrenbl(uint8_t i) {setbit(i, NVIC_ICER_OFFSET);}
void nvic_setpend(uint8_t i) {setbit(i, NVIC_ISPR_OFFSET);}
void nvic_clrpend(uint8_t i) {setbit(i, NVIC_ICPR_OFFSET);}


