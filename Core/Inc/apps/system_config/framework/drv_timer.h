/*
 * drv_timer.h
 *
 *  Created on: Jul 15, 2025
 *      Author: baohg1
 */

#ifndef INC_APPS_SYSTEM_CONFIG_FRAMEWORK_DRV_TIMER_H_
#define INC_APPS_SYSTEM_CONFIG_FRAMEWORK_DRV_TIMER_H_

#include "main.h"

extern uint32_t TIM2InterruptCount;
extern uint32_t TIM3InterruptCount;
extern bool trigger_timer2;

void InitTimer(void);
void InitTimer2(uint32_t);
void InitTimer3(uint32_t);

void InitTimerCounter(void);

#endif /* INC_APPS_SYSTEM_CONFIG_FRAMEWORK_DRV_TIMER_H_ */
