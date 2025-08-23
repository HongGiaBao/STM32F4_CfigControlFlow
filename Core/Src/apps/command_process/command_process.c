/*
 * command_process.c
 *
 *  Created on: Aug 16, 2025
 *      Author: baohg1
 */

#include "command_process.h"

_SCIbuffer DrvSciRcv;

void initDrvUSART(void)
{
	uint16_t count = 0;
	for (count = 0; count < SCI_BUFFER_SIZE; count ++)
	{
		DrvSciRcv.data[count] = 0;
	}
	DrvSciRcv.header = 0x00;
	DrvSciRcv.index = 0;
	DrvSciRcv.checksum = 0;
	DrvSciRcv.flag = 0;
}


void preProcessUSART1(void)
{
	if(SCI1buffer.flag == 1)
	{
		DrvSciRcv = SCI1buffer;
		InitBufferSci1();
	}
}


void preProcessUSART2(void)
{
	if(SCI2buffer.flag == 1)
	{
		DrvSciRcv = SCI2buffer;
		InitBufferSci2();
	}
}


void preProcessUSART3(void)
{
	if(SCI3buffer.flag == 1)
	{
		DrvSciRcv = SCI3buffer;
		InitBufferSci3();
	}
}

