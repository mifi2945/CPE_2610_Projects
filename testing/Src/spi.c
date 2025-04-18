/**
  ******************************************************************************
  * @file		spi.c
  * @brief		SPI Address File
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/


#include "spi.h"
#include "gpio.h"

volatile SPI *spi2 = (SPI*) SPI2;
//static uint16_t spi2_frame = 0;
//static int sending = 0;

void spi2_init(void) {
	// PB13 -> SCK
	// PB15 -> MOSI

	volatile uint32_t *rcc_apb1enr = (uint32_t*) RCC_APB1_ENR;
	*rcc_apb1enr |= SPI2_EN;
	volatile uint32_t *rcc_ahb1enr = (uint32_t*) RCC_AHB1_ENR;
	*rcc_ahb1enr |= GPIOBEN;

	//clear and set alternate mode 5
	gpiob[MODER_INDEX] &= ~(0b11<<(12*2)) & ~(0b11<<(13*2)) & ~(0b11<<(15*2));
	gpiob[MODER_INDEX] |= (0b01<<(12*2)) | (0b10<<(13*2)) | (0b10<<(15*2));
	gpiob[AFRH_INDEX] &= ~(0xF<<(20)) & ~(0xF<<(28));
	gpiob[AFRH_INDEX] |= (0b0101<<(20)) | (0b0101<<(28));

	// 16 bit frame, clk/2, CPOL 1, CPHA 1 (second edge, rising), master
	spi2->CR1 |= (1<<11) | (0b11) | (1<<2) | (1<<8) | (1<<9);

	// SPI enable
	spi2->CR1 |= (1<<6);
	// set up interrupts
	//spi2->CR2 |= (0b11<<6);
}

void spi2_write(uint16_t frame) {
	while (!(spi2->SR & SPI_TXE)) {}
	spi2->DR = frame;
	while (spi2->SR & (1<<7)) {}
}

//void SPI2_IRQHandler(void) {
//	uint32_t status = spi2->SR;
//	// TXE
//	if ((status & SPI_TXE) && (spi2->CR2 & SPI_TXEIE)) {
//		spi2->DR = spi2_frame;
//		sending = 0;
//		spi2->CR2 &= ~SPI_TXEIE;
//		//spi2->CR1 |= (1<<8);
//	}
//}
