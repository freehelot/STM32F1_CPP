/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : uart.hpp
  * @brief          : Header for uart.cpp file.
  *                  UART initializations and use
  ******************************************************************************
  * @attention

 ******************************************************************************
*/
#pragma once
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_HPP
#define __UART_HPP

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_usart.h>
/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#include <array>
#include <cstdio>
#include <span>

class uart
{
private:
    USART_HandleTypeDef * husart;
public:
    uart(USART_HandleTypeDef *p_uart);
    ~uart();
};





#endif /* __UART_HPP */