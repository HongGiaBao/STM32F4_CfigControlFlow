/*
 * system_config.h
 *
 *  Created on: Jul 8, 2025
 *      Author: baohg1
 */

#ifndef INC_APPS_SYSTEM_CONFIG_H_
#define INC_APPS_SYSTEM_CONFIG_H_

#include "main.h"

/*Define System clock*/

/*Define PWM parameters*/

/*Define SCI parameters*/

/*Define SPI parameters*/

/*Define I2C parameters*/

/*Define Timer parameters*/
#define TIMER2_PERIOD 50 //us
#define TIMER3_PERIOD 1000

void SystemClock_Config(void);
void InitClocks(void);
void SYS_Initialize(void);
void EnAllInterrupt(void);
void HardwareInit(void);
void resetCPU(void);


#endif /* INC_APPS_SYSTEM_CONFIG_H_ */
