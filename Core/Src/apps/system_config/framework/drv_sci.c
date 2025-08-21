/*
 * drv_sci.c
 *
 *  Created on: Jul 18, 2025
 *      Author: baohg1
 */

#include "drv_sci.h"

_SCIbuffer SCI1buffer;
_SCIbuffer SCI2buffer;
_SCIbuffer SCI3buffer;

/*Init GPIOs for SCI (UART) interface */
void InitSciGPIO(void)
{
//	InitSci1Gpio();
	InitSci2Gpio();
//	InitSci3Gpio();
}


/*Init GPIOs for SCI1 */
void InitSci1Gpio(void)
{

	// 2. Configure PA9 (TX) and PA10 (RX) as Alternate Function (AF7)
	GPIOA->MODER &= ~((0x3 << (2*9)) | (0x3 << (2*10)));  // Clear MODER9 and MODER10
	GPIOA->MODER |=  ((0x2 << (2*9)) | (0x2 << (2*10)));  // Set to 10: Alternate Function mode

	// 3. Configure output type as Push-Pull
	GPIOA->OTYPER &= ~((1 << 9) | (1 << 10));             // 0 = Push-Pull

	// 4. Configure speed as High speed
	GPIOA->OSPEEDR &= ~((0x3 << (2*9)) | (0x3 << (2*10)));
	GPIOA->OSPEEDR |=  ((0x2 << (2*9)) | (0x2 << (2*10))); // 10 = High speed

	// 5. Configure Pull-up/Pull-down
	// TX: No pull; RX: Pull-Up to avoid floating line
	GPIOA->PUPDR &= ~((0x3 << (2*9)) | (0x3 << (2*10)));
	GPIOA->PUPDR |=  (0x1 << (2*10));                     // PA10 = Pull-Up

	// 6. Select Alternate Function = AF7 (USART1) for PA9/PA10
	GPIOA->AFR[1] &= ~((0xF << (4*1)) | (0xF << (4*2))); // Clear AFRH9, AFRH10
	GPIOA->AFR[1] |=  ((0x7 << (4*1)) | (0x7 << (4*2))); // AF7 for USART1
}


/*Init GPIOs for SCI2 */
void InitSci2Gpio(void)
{
	// 2. Configure PA2 (TX) and PA3 (RX) as Alternate Function (AF7)
	GPIOA->MODER &= ~((0x3 << (2*2)) | (0x3 << (2*3)));  // Clear MODER2, MODER3
	GPIOA->MODER |=  ((0x2 << (2*2)) | (0x2 << (2*3)));  // Set AF mode (10)

	// 3. Configure output type as Push-Pull
	GPIOA->OTYPER &= ~((1 << 2) | (1 << 3));             // 0 = Push-Pull

	// 4. Configure speed as High speed
	GPIOA->OSPEEDR &= ~((0x3 << (2*2)) | (0x3 << (2*3)));
	GPIOA->OSPEEDR |=  ((0x2 << (2*2)) | (0x2 << (2*3))); // 10 = High speed

	// 5. Configure Pull-up/Pull-down
	// TX: No pull; RX: Pull-Up để tránh floating line
	GPIOA->PUPDR &= ~((0x3 << (2*2)) | (0x3 << (2*3)));
	GPIOA->PUPDR |=  (0x1 << (2*3));                     // PA3 = Pull-Up

	// 6. Select Alternate Function = AF7 (USART2) cho PA2/PA3
	GPIOA->AFR[0] &= ~((0xF << (4*2)) | (0xF << (4*3))); // Clear AFRL2, AFRL3
	GPIOA->AFR[0] |=  ((0x7 << (4*2)) | (0x7 << (4*3))); // AF7 = USART2
}


/*Init GPIOs for SCI3 */
void InitSci3Gpio(void)
{

}


/*Init SCI Modules */
void InitSciModules(void)
{
//	InitSci1();
//	InitBufferSci1();
	InitSci2();
	InitBufferSci2();
//	InitSci3();
}


/*Init Sci1 Modules*/
void InitSci1(void)
{
//	//fclk = 84MHz -> USARTDIV = 11.391 (for baudrate 460.8Kbs)
//	USART1->BRR = 0xB6;

	//fclk = 84MHz -> USARTDIV = 45.593 (for baudrate 115.2Kbs)
	USART1->BRR = 0x2D9;

	USART1->SR = 0;

	USART1->CR1 = 0;
	USART1->CR2 = 0;
	USART1->CR2 |= USART_CR2_STOP_1;

	USART1->CR3 = 0;
	/*- UE = 1 (USART enable)
	 	- TE = 1 (Transmitter enable)
	 	- RE = 1 (Receiver enable)
	 	- RXNEIE = 1 (RX not empty interrupt enable)
	 	- TXEIE = 1 (TX empty interrupt enable)
	 	- 8 data bits, no parity (M = 0, PCE = 0)
	 	- Oversampling 16 (OVER8 = 0) */
	USART1->CR1 = (1 << 13) |  // UE
								(1 << 3)  |  // TE
								(1 << 2)  |  // RE
								(1 << 5); // RXNEIE
	//Enable USART1 interrupt in NVIC
	NVIC_EnableIRQ(USART1_IRQn);
}


/*Init Sci2 Modules*/
void InitSci2(void)
{
	// fclk = 42 MHz (APB1)
	// Baudrate = 115200 bps
	// USARTDIV = 42MHz / (16 * 115200) = 22.786 -> BRR = 0x16D
	USART2->BRR = 0x16D;

	// Clear status register
	USART2->SR = 0;

	// CR1/CR2/CR3 reset
	USART2->CR1 = 0;
	USART2->CR2 = 0;
	USART2->CR2 |= USART_CR2_STOP_1;  // 1 stop bit

	USART2->CR3 = 0;

	/* CR1 configuration
		- UE = 1 (USART enable)
		- TE = 1 (Transmitter enable)
		- RE = 1 (Receiver enable)
		- RXNEIE = 1 (RX not empty interrupt enable)
		- 8 data bits, no parity (M = 0, PCE = 0)
		- Oversampling 16 (OVER8 = 0)
	*/
	USART2->CR1 = (1 << 13) |  // UE
				  (1 << 3)  |  // TE
				  (1 << 2)  |  // RE
				  (1 << 5);    // RXNEIE

	// Enable USART2 interrupt in NVIC
	NVIC_EnableIRQ(USART2_IRQn);
}


/*Init Sci3 Modules*/
void InitSci3(void)
{

}


/*Init Sci1 Buffer*/
void InitBufferSci1(void)
{
	uint16_t count = 0;
	for (count = 0; count < SCI_BUFFER_SIZE; count ++)
	{
		SCI1buffer.data[count] = 0;
	}
	SCI1buffer.header = 0x00;
	SCI1buffer.index = 0;
	SCI1buffer.checksum = 0;
	SCI1buffer.flag = 0;
}


/*Init Sci2 Buffer*/
void InitBufferSci2(void)
{
	uint16_t count = 0;
	for (count = 0; count < SCI_BUFFER_SIZE; count ++)
	{
		SCI2buffer.data[count] = 0;
	}
	SCI2buffer.header = 0x00;
	SCI2buffer.index = 0;
	SCI2buffer.checksum = 0;
	SCI2buffer.flag = 0;
}


/*Init Sci3 Buffer*/
void InitBufferSci3(void)
{
	uint16_t count = 0;
	for (count = 0; count < SCI_BUFFER_SIZE; count ++)
	{
		SCI3buffer.data[count] = 0;
	}
	SCI3buffer.header = 0x00;
	SCI3buffer.index = 0;
	SCI3buffer.checksum = 0;
	SCI3buffer.flag = 0;
}


/*Reset USART1 Queue*/
extern uint16_t txBuffer_head;
extern uint16_t txBuffer_tail;
extern uint16_t tx_ready;
extern uint8_t tx_buffer[256];
void USART1_ResetQueue(void)
{
	USART1->CR1 &= ~USART_CR1_TXEIE;
	txBuffer_head = 0;
	txBuffer_tail = 0;
	tx_ready = 0;
}


/*Fucntion send packet through USART1*/
void USART1_Transmit(const uint8_t *data, uint16_t length)
{
	USART1->CR1 &= ~USART_CR1_TXEIE;; // Block interrupt when update Queue
	if (tx_ready + length > 256)
	{
			USART1_ResetQueue();
			return;
	}

	for (uint16_t i = 0; i < length; i++)
	{
			tx_buffer[txBuffer_tail] = data[i];
			txBuffer_tail = (txBuffer_tail + 1) % 256;
			tx_ready++;
	}

	// Turn on USART Interrupt
	USART1->CR1 |= USART_CR1_TXEIE;
}

/* Reset USART2 Queue */
extern uint16_t tx2Buffer_head;
extern uint16_t tx2Buffer_tail;
extern uint16_t tx2_ready;
extern uint8_t tx2_buffer[256];

void USART2_ResetQueue(void)
{
    USART2->CR1 &= ~USART_CR1_TXEIE;
    tx2Buffer_head = 0;
    tx2Buffer_tail = 0;
    tx2_ready = 0;
}

/* Function send packet through USART2 */
void USART2_Transmit(const uint8_t *data, uint16_t length)
{
	if (tx2_ready != 0)
	{
		return;
	}
	if (tx2_ready + length > 256)
    {
        USART2_ResetQueue();
        return;
    }

    for (uint16_t i = 0; i < length; i++)
    {
        tx2_buffer[tx2Buffer_tail] = data[i];
        tx2Buffer_tail = (tx2Buffer_tail + 1) % 256;
        tx2_ready++;
    }

    USART2->CR1 |= USART_CR1_TXEIE;
}











