#include "stm32f4xx.h"

#include "spi.h"

volatile uint16_t CCR1_Val = 40961;
volatile uint16_t CCR2_Val = 27309;
volatile uint16_t CCR3_Val = 13654;
volatile uint16_t CCR4_Val = 6826;

void InitializeLEDs()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef gpioStructure;
    gpioStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    gpioStructure.GPIO_Mode = GPIO_Mode_OUT;
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpioStructure);

    GPIO_WriteBit(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, Bit_RESET);
}

void InitializeTimer2()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 40000;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 500;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    TIM_Cmd(TIM2, ENABLE);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void InitializeTimer3()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 1440;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 65535;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &timerInitStructure);

    TIM_OCInitTypeDef  TIM_OCInitStructure;
    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

    /* Output Compare Timing Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);

    /* Output Compare Timing Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);

    /* Output Compare Timing Mode configuration: Channel4 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);

    /* TIM Interrupts enable */
    TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);

    /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);
}

void EnableTimerInterrupt(uint8_t IRQChannel)
{
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = IRQChannel;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}

//void InitializeSPI1(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);
//
//	SPI_InitTypeDef SPI_InitStructure;
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_Init(SPI1, &SPI_InitStructure);
//
//	GPIO_InitTypeDef GPIO_InitStruct;
//
//
//	/*-------- Configuring SCK, MISO, MOSI --------*/
//
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//
//	GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//
//	/*-------- Configuring ChipSelect-Pin PE3 --------*/
//
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//
//	GPIO_Init(GPIOE, &GPIO_InitStruct);
//
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
//
//	GPIO_SetBits(GPIOE, GPIO_Pin_3);
//
//	SPI_Cmd(SPI1, ENABLE);
//}
//
//uint16_t SPI1_SendData(uint16_t word)
//{
//  /*!< Loop while DR register in not emplty */
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//
//  /*!< Send byte through the SPI1 peripheral */
//  SPI_I2S_SendData(SPI1, word);
//
//  /*!< Wait to receive a byte */
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//
//  /*!< Return the byte read from the SPI bus */
//  return SPI_I2S_ReceiveData(SPI1);
//}
//
//uint8_t spi_transfer( uint8_t dane )
//{
//	while( !( SPI1->SR & SPI_SR_TXE ));
//	SPI1->DR = dane;
//	while( !( SPI1->SR & SPI_SR_RXNE ));
//	return SPI1->DR;
//}
//
//void mySPI_SendData(uint8_t adress, uint8_t data)
//{
//GPIO_ResetBits(GPIOE, GPIO_Pin_3);
//
//while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
//SPI_I2S_SendData(SPI1, adress);
//while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
//SPI_I2S_ReceiveData(SPI1);
//
//while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
//SPI_I2S_SendData(SPI1, data);
//while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
//SPI_I2S_ReceiveData(SPI1);
//
//GPIO_SetBits(GPIOE, GPIO_Pin_3);
//}
//
//
//uint8_t mySPI_GetData(uint8_t adress){
//
//GPIO_ResetBits(GPIOE, GPIO_Pin_3);
//
//adress = 0x80 | adress;
//
//while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
//SPI_I2S_SendData(SPI1, adress);
//while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
//SPI_I2S_ReceiveData(SPI1); //Clear RXNE bit
//
//while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
//SPI_I2S_SendData(SPI1, 0x00); //Dummy byte to generate clock
//while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
//
//GPIO_SetBits(GPIOE, GPIO_Pin_3);
//
//return  SPI_I2S_ReceiveData(SPI1);
//}


int main()
{
    InitializeLEDs();
    SPI_initialize();

    uint8_t data = 0xaa;
    SPI_Write(0x20, 0xC4);

    while(1)
        {
        	data = SPI_Read(0x2d);
        }
    while(1)
    {
    }
}
