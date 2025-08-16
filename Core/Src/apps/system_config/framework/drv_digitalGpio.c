/*
 * drv_digitalGpio.c
 *
 *  Created on: Jul 13, 2025
 *      Author: baohg1
 */
#include "drv_digitalGpio.h"


void InitDigitalGPIO(void)
{
	// Configure PD12 as output
	GPIOD->MODER 		&= ~(0x3 << 24);  	// Clear bits 0-1
	GPIOD->MODER 		|= (0x1 << 24);   	// Set PD12 as output
	GPIOD->OTYPER 	&= ~(0x1 << 12); 		// Set push-pull
	GPIOD->OSPEEDR 	&= ~(0x3 << 24); 		// Clear bits 0-1
	GPIOD->OSPEEDR 	|= (0x2 << 24);  		// Set high speed
	GPIOD->PUPDR 		&= ~(0x3 << 0);   	// No pull-up/pull-down
	GPIOD->ODR 			|= (0x1 << 12);     // Set PD12 high initially
}

