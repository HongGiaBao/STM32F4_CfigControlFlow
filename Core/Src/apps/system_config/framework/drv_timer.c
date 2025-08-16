/*
 * drv_timer.c
 *
 *  Created on: Jul 15, 2025
 *      Author: baohg1
 */

#include "drv_timer.h"

/* Global variables ---------------------------------------------------------*/
uint32_t TIM2InterruptCount;
uint32_t TIM3InterruptCount;
bool trigger_timer2;

void InitTimer()
{
	InitTimer2(TIMER2_PERIOD);
	InitTimer3(TIMER3_PERIOD);
}

void InitTimer2(uint32_t period)
{
	/*Step 1: Configure prescaler*/
	TIM2->PSC = 83; //1MHz

	/*Step 2: Auto-reload register*/
	TIM2->ARR = period; //us

	/*Step 3: Configure TIMx_CR1*/
	TIM2->CR1 = 0;
	TIM2->CR1 |= TIM_CR1_ARPE;
	TIM2->CR1 &= ~TIM_CR1_DIR;

	/*Step 4: Interrupt TIMER2*/
	TIM2->DIER |= TIM_DIER_UIE; //Start interrupt when update event happens
	NVIC_SetPriority(TIM2_IRQn, 0);
	NVIC_EnableIRQ(TIM2_IRQn);

	/*Step 5: Turn on TIMER*/
	TIM2->CR1 |= TIM_CR1_CEN;
}

void InitTimer3(uint32_t period)
{

}

void InitTimerCounter(void)
{
	TIM2InterruptCount = 0;
	TIM3InterruptCount = 0;
}

