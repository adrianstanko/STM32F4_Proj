// spi.h
//This is a header file containing functions for SPI communication services


#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"

void SPI_initialize(void);

uint8_t SPI_transmit(uint8_t data);

void SPI_Write(uint8_t address, uint8_t data);

uint8_t SPI_Read(uint8_t address);