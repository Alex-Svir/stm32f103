/*
 * VectorsTable.cpp
 *
 *  Created on: 11 окт. 2022 г.
 *      Author: shurik
 */
#include "VectorsTable.h"
#include <inttypes.h>

void __reset();

void __ihr_stub_halt__();
void __ihr_stub__();
void ihr_stub_fault() __attribute__((weak, alias("_Z17__ihr_stub_halt__v")));
void ihr_stub_int() __attribute__((weak, alias("_Z12__ihr_stub__v")));

void ihr_NMI() __attribute__((weak, alias("_Z14ihr_stub_faultv")));
void ihr_HardFault() __attribute__((weak, alias("_Z14ihr_stub_faultv")));
void ihr_MemManage() __attribute__((weak, alias("_Z14ihr_stub_faultv")));
void ihr_BusFault() __attribute__((weak, alias("_Z14ihr_stub_faultv")));
void ihr_UsageFault() __attribute__((weak, alias("_Z14ihr_stub_faultv")));

void ihr_SVCall() __attribute__((weak, alias("_Z12ihr_stub_intv")));
void ihr_DebugMonitor() __attribute__((weak, alias("_Z12ihr_stub_intv")));
void ihr_PendSV() __attribute__((weak, alias("_Z12ihr_stub_intv")));
void ihr_SysTick() __attribute__((weak, alias("_Z12ihr_stub_intv")));

void ihr_WWDG() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	0
void ihr_PVD() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	1
void ihr_TAMPER() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	2
void ihr_RTC() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	3
void ihr_FLASH() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	4
void ihr_RCC() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	5
void ihr_EXTI0() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	6
void ihr_EXTI1() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	7
void ihr_EXTI2() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	8
void ihr_EXTI3() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	9
void ihr_EXTI4() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	10
void ihr_DMA1_Channel1() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	11
void ihr_DMA1_Channel2() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	12
void ihr_DMA1_Channel3() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	13
void ihr_DMA1_Channel4() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	14
void ihr_DMA1_Channel5() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	15
void ihr_DMA1_Channel6() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	16
void ihr_DMA1_Channel7() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	17

void ihr_ADC1_2() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	18
void ihr_USB_HP_CAN_TX() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	19
void ihr_USB_LP_CAN_RX0() __attribute__((weak, alias("_Z12ihr_stub_intv")));//	20
void ihr_CAN_RX1() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	21
void ihr_CAN_SCE() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	22
void ihr_EXTI9_5() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	23
void ihr_TIM1_BRK() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	24
void ihr_TIM1_UP() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	25
void ihr_TIM1_TRG_COM() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	26
void ihr_TIM1_CC() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	27
void ihr_TIM2() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	28
void ihr_TIM3() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	29
void ihr_TIM4() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	30
void ihr_I2C1_EV() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	31
void ihr_I2C1_ER() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	32
void ihr_I2C2_EV() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	33
void ihr_I2C2_ER() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	34
void ihr_SPI1() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	35
void ihr_SPI2() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	36
void ihr_USART1() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	37
void ihr_USART2() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	38
void ihr_USART3() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	39
void ihr_EXTI15_10() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	40
void ihr_RTCAlarm() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	41
void ihr_USBWakeup() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	42
void ihr_TIM8_BRK() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	43
void ihr_TIM8_UP() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	44
void ihr_TIM8_TRG_COM() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	45
void ihr_TIM8_CC() __attribute__((weak, alias("_Z12ihr_stub_intv")));		//	46
void ihr_ADC3() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	47
void ihr_FSMC() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	48
void ihr_SDIO() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	49
void ihr_TIM5() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	50
void ihr_SPI3() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	51
void ihr_UART4() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	52
void ihr_UART5() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	53
void ihr_TIM6() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	54
void ihr_TIM7() __attribute__((weak, alias("_Z12ihr_stub_intv")));			//	55
void ihr_DMA2_Channel1() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	56
void ihr_DMA2_Channel2() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	57
void ihr_DMA2_Channel3() __attribute__((weak, alias("_Z12ihr_stub_intv")));	//	58
void ihr_DMA2_Channel4_5() __attribute__((weak, alias("_Z12ihr_stub_intv")));//	59


namespace vtbl {
	const unsigned TABLE_SZ = 75;
	typedef void (*ihr_VECTOR)();
	ihr_VECTOR vect_table[TABLE_SZ] = {&__reset,
					&ihr_NMI,
					&ihr_HardFault,
					&ihr_MemManage,
					&ihr_BusFault,
					&ihr_UsageFault,
					0,0,0,0,		//	reserved
					&ihr_SVCall,
					&ihr_DebugMonitor,
					0,				//	reserved
					&ihr_PendSV,
					&ihr_SysTick,
					&ihr_WWDG,				//	0
					&ihr_PVD,				//	1
					&ihr_TAMPER,			//	2
					&ihr_RTC,				//	3
					&ihr_FLASH,				//	4
					&ihr_RCC,				//	5
					&ihr_EXTI0,				//	6
					&ihr_EXTI1,				//	7
					&ihr_EXTI2,				//	8
					&ihr_EXTI3,				//	9
					&ihr_EXTI4,				//	10
					&ihr_DMA1_Channel1,		//	11
					&ihr_DMA1_Channel2,		//	12
					&ihr_DMA1_Channel3,		//	13
					&ihr_DMA1_Channel4,		//	14
					&ihr_DMA1_Channel5,		//	15
					&ihr_DMA1_Channel6,		//	16
					&ihr_DMA1_Channel7,		//	17
					&ihr_ADC1_2,			//	18
					&ihr_USB_HP_CAN_TX,		//	19
					&ihr_USB_LP_CAN_RX0,	//	20
					&ihr_CAN_RX1,			//	21
					&ihr_CAN_SCE,			//	22
					&ihr_EXTI9_5,			//	23
					&ihr_TIM1_BRK,			//	24
					&ihr_TIM1_UP,			//	25
					&ihr_TIM1_TRG_COM,		//	26
					&ihr_TIM1_CC,			//	27
					&ihr_TIM2,				//	28
					&ihr_TIM3,				//	29
					&ihr_TIM4,				//	30
					&ihr_I2C1_EV,			//	31
					&ihr_I2C1_ER,			//	32
					&ihr_I2C2_EV,			//	33
					&ihr_I2C2_ER,			//	34
					&ihr_SPI1,				//	35
					&ihr_SPI2,				//	36
					&ihr_USART1,			//	37
					&ihr_USART2,			//	38
					&ihr_USART3,			//	39
					&ihr_EXTI15_10,			//	40
					&ihr_RTCAlarm,			//	41
					&ihr_USBWakeup,			//	42
					&ihr_TIM8_BRK,			//	43
					&ihr_TIM8_UP,			//	44
					&ihr_TIM8_TRG_COM,		//	45
					&ihr_TIM8_CC,			//	46
					&ihr_ADC3,				//	47
					&ihr_FSMC,				//	48
					&ihr_SDIO,				//	49
					&ihr_TIM5,				//	50
					&ihr_SPI3,				//	51
					&ihr_UART4,				//	52
					&ihr_UART5,				//	53
					&ihr_TIM6,				//	54
					&ihr_TIM7,				//	55
					&ihr_DMA2_Channel1,		//	56
					&ihr_DMA2_Channel2,		//	57
					&ihr_DMA2_Channel3,		//	58
					&ihr_DMA2_Channel4_5	//	59
	};
	uint32_t msp_init = 0x20005000;
}

void __ihr_stub_halt__() {while(1);}
void __ihr_stub__() {}

