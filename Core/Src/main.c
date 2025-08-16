/*
 * main.c
 *
 * Created on: Aug 07, 2025
 * Author: baohg1
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Global flag variables*/
bool isSystemReady = 0;

int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
	SYS_Initialize();

  /* USER CODE BEGIN WHILE */
  while (1)
  {

  	if(trigger_timer2 == true)
  	{
  		trigger_timer2 = false;
  		GPIOD->ODR 			^= (0x1 << 12);
  	}
  }
}
