/*
 * control.c
 *
 *  Created on: Aug 10, 2025
 *      Author: baohg1
 */
#include "control.h"

void sendData(uint16_t data)
{
	uint8_t checksum = 0;
	uint8_t dataSend[4];
	uint8_t length = sizeof(dataSend) / sizeof(dataSend[0]);

	dataSend[0] = 0xB6;
	dataSend[1] = (data >> 8) & 0xFF;
	dataSend[2] = data & 0xFF;

	uint16_t count = 0;
	for(count = 0; count < length; count++)
	{
		checksum = checksum + dataSend[count];
	}
	dataSend[3] = checksum;
	USART1_Transmit(dataSend, length);
}

void ControlTasks(void)
{
	uint16_t pan = 5000;
	sendData(pan);
}


