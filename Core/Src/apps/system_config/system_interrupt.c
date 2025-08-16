/*
 * system_interrupt.c
 *
 *  Created on: Jul 17, 2025
 *      Author: baohg1
 */

#include "system_interrupt.h"

void TIM2_IRQHandler(void)
{
	/*Check register TIM2_SR and Update Event flag*/
	if (TIM2->SR & TIM_SR_UIF)
	{
		// delete Update Event flag
		TIM2->SR &= ~TIM_SR_UIF;

		if(TIM2InterruptCount % 100 == 0)
		{
			trigger_timer2 = true;
		}
		TIM2InterruptCount++;
	}
}

/*------Interrupts SCI Modules-----*/
volatile uint8_t tx_ready = 0;
volatile uint8_t tx_buffer[256];
volatile uint16_t txBuffer_head = 0;
volatile uint16_t txBuffer_tail = 0;
double 	scic_t = 0;
double 	scic_f = 0;
void USART1_IRQHandler(void)
{
	// TXE interrupt: transmit data register is empty
	if(USART1->SR & USART_SR_TXE)
	{
		if(tx_ready == 0)
		{
			//No more data to send -> disable TXE interrupt
			USART1->CR1 &= ~USART_CR1_TXEIE;
		}
		else
		{
			//Send the next byte from tx_buffer
			USART1->DR = tx_buffer[txBuffer_head];
			txBuffer_head = (txBuffer_head + 1) % 256;
			tx_ready--;
		}
	}

	// RXNE interrupt: new data received
	if(USART1->SR & USART_SR_RXNE)
	{
		SCI1buffer.value = USART1->DR;
		switch (SCI1buffer.state)
		{
				case HEADER:
						if (SCI1buffer.value == 0xA6)
						{
								SCI1buffer.header = SCI1buffer.value;
								SCI1buffer.index = 0;
								SCI1buffer.calCS = 0;
								SCI1buffer.state = PAYLOAD;
						}
						break;

				case PAYLOAD:
						SCI1buffer.data[SCI1buffer.index++] = SCI1buffer.value;
						if (SCI1buffer.index >= 4)
						{
								SCI1buffer.calCS = SCI1buffer.header;
								for (int i = 0; i < 4; i++)
								{
										SCI1buffer.calCS += SCI1buffer.data[i];
								}
								SCI1buffer.calCS &= 0xFF;
								SCI1buffer.state = CHECKSUM;
						}
						break;

				case CHECKSUM:
						SCI1buffer.checksum = SCI1buffer.value;
						if (SCI1buffer.checksum == SCI1buffer.calCS)
						{
								SCI1buffer.flag = true;
								scic_t++;
						}
						else
						{
								SCI1buffer.flag = false;
								scic_f++;
						}
						SCI1buffer.state = HEADER;
						break;

				default:
						SCI1buffer.state = HEADER;
						break;
		}
	}
}










