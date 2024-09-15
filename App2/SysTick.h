/*
 * SysTick.h
 *
 *  Created on: Jul 27, 2024
 *      Author: Radwan
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include "std_types.h"


#define RELOAD_VALUE_PER_1_SECOND 15999999

void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
void SysTick_Handler(void);
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
void SysTick_Stop(void);
void SysTick_Start(void);
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
