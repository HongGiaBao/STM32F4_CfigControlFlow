/*
 * drv_sci.h
 *
 *  Created on: Jul 18, 2025
 *      Author: baohg1
 */

#ifndef INC_APPS_SYSTEM_CONFIG_FRAMEWORK_DRV_SCI_H_
#define INC_APPS_SYSTEM_CONFIG_FRAMEWORK_DRV_SCI_H_

#include "main.h"

#define SCI_BUFFER_SIZE 255

typedef enum
{
	HEADER,
	PAYLOAD,
	CHECKSUM
}SCI_State;

typedef struct
{
	uint16_t data[SCI_BUFFER_SIZE];
	uint16_t header;
	uint16_t state;
	uint16_t index;
	uint16_t checksum;
	uint16_t calCS;
	uint16_t value;
	bool flag;
}_SCIbuffer;

extern _SCIbuffer SCI1buffer;
extern _SCIbuffer SCI2buffer;
extern _SCIbuffer SCI3buffer;

void InitSciGPIO(void);
void InitSci1Gpio(void);
void InitSci2Gpio(void);
void InitSci3Gpio(void);

void InitSciModules(void);
void InitSci1(void);
void InitSci2(void);
void InitSci3(void);

void InitBufferSci1(void);
void InitBufferSci2(void);
void InitBufferSci3(void);

void PreProcessSCI1(void);
void PreProcessSCI2(void);
void PreProcessSCI3(void);

void USART1_ResetQueue(void);
void USART2_ResetQueue(void);
void USART3_ResetQueue(void);


void USART1_Transmit(const uint8_t *, uint16_t);
void USART2_Transmit(const uint8_t *, uint16_t);
void USART3_Transmit(const uint8_t *, uint16_t);

#endif /* INC_APPS_SYSTEM_CONFIG_FRAMEWORK_DRV_SCI_H_ */
