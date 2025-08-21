/*
 * system_config.c
 *
 *  Created on: Jul 8, 2025
 *      Author: baohg1
 */

#include "system_config.h"

void SYS_Initialize(void)
{
	/*1. Initialize system and hardware*/
	HardwareInit();
//	/*2. Initialzie the application*/
//	AppsInit();
//	/*3. Enable all interrupt*/
//	EnAllInterrupt();
}


void HardwareInit(void)
{
  /*1. Reset of all peripherals, Initializes the Flash interface and the Systick*/
  HAL_Init();

  /*2. Configure the system clock*/
  SystemClock_Config();

  /*3. Initialize Hardware Interfaces*/
  InitClocks();
  InitDigitalGPIO();
  InitSciGPIO();
//  InitXintGPIO();

  /*4. Initialize all the device peripherals*/
  InitSciModules();

  /*5. Configure TIMERs*/
  InitTimer();
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; //max 168 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  //max 42 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  //max 84 MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

void InitClocks(void)
{
	/*According to Reset Clock Control registers*/
	/* GPIO Ports Clock Enable (A, C, D, E, F) */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
	HAL_Delay(1);

	/*TIMER2, TIMER3 Clock Enable*/
	RCC->APB1ENR |= 0x00000003;

	/*USART1 Clock Enable*/
//	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	HAL_Delay(1);
}








