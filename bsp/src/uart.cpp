#include "uart.hpp"


uart::uart(USART_HandleTypeDef *p_uart) : husart(p_uart)
{
    husart->Instance = USART1;
    husart->Init.BaudRate = 115200;
    husart->Init.WordLength = USART_WORDLENGTH_8B;
    husart->Init.StopBits = USART_STOPBITS_1;
    husart->Init.Parity = USART_PARITY_NONE;
    husart->Init.Mode = USART_MODE_TX_RX;
    husart->Init.CLKPolarity = USART_POLARITY_LOW;
    husart->Init.CLKPhase = USART_PHASE_1EDGE;
    husart->Init.CLKLastBit = USART_LASTBIT_DISABLE;
    if(HAL_OK != HAL_USART_Init(husart))
    {
        // Do something? 
        // Error handler
    }
    else
    {
        /*
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitTypeDef GPIO_InitStruct = 
        {
            .Pin=GPIO_PIN_8|GPIO_PIN_9,
            .Mode = GPIO_MODE_AF_PP,
            .Speed = GPIO_SPEED_FREQ_HIGH
        };
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct = {
            .Pin = GPIO_PIN_10,
            .Mode = GPIO_MODE_INPUT,    
            .Pull = GPIO_NOPULL,
        };
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        */
    }
}

uart::~uart()
{
     if(USART1 == uart::husart->Instance)
   { 
    __HAL_RCC_USART1_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10);
  }
}
