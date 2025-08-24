/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "math.h"
#include <stdbool.h>

#include "stm32f4xx_hal.h"
#include "system_config.h"
#include "system_interrupt.h"

#include "app.h"
#include "command_process.h"

#include "drv_digitalGpio.h"
#include "drv_timer.h"
#include "drv_sci.h"
#include "drv_pwm.h"

#include "control.h"

extern bool isSystemReady;

/* Private function prototypes -----------------------------------------------*/
void MX_IWDG_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
