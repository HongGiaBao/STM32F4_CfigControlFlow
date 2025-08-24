/*
 * drv_pwm.c
 *
 *  Created on: Aug 25, 2025
 *      Author: baohg1
 */

#include "drv_pwm.h"

void InitPWMGPIO(void)
{
	// 2. Configure PA8 as Alternate Function PWM (AF1) - TIM1_CH1
	GPIOA->MODER 	&= ~(0x3 << (2*8));  // Clear MODER8
	GPIOA->MODER 	|=  (0x2 << (2*8));  // Set AF mode (10)

	// 3. Configure output type as Push-Pull
	GPIOA->OTYPER 	&= ~(1 << 8);        // 0 = Push-Pull

	// 4. Configure speed as High speed
	GPIOA->OSPEEDR 	&= ~(0x3 << (2*8));
	GPIOA->OSPEEDR 	|=  (0x2 << (2*8)); // 10 = High speed

	// 5. Configure no pull
	GPIOA->PUPDR 	&= ~(0x3 << (2*8));

	// 6. Select Alternate Function = AF7 (USART2) cho PA2/PA3
	GPIOA->AFR[1] &= ~(0xF); // Clear AFRH8
	GPIOA->AFR[1] |=   0x1;  // AF1 = TIM1
}


void InitPWMModules(void)
{}

