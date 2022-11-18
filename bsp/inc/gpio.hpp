/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : gpio.hpp
  * @brief          : Header for gpio.cpp file.
  *                   GPIO initializations and use
  ******************************************************************************
  * @attention

 ******************************************************************************
*/
#pragma once
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_HPP
#define __GPIO_HPP

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

#define LED_PIN GPIO_PIN_13
#define LED_GPIO_PORT GPIOC

/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#include <array>
#include <cstdio>
#include <span>



class led
{

private:
    GPIO_TypeDef* gpio;
    uint16_t pin;
public:

    // The led constructor
    explicit led(GPIO_TypeDef * t_gpio, uint16_t t_pin);
    // Constructor
    ~led();
    // Toggle LED
    void toggle();
    // Get State of LED
    bool state();
    // LED OFF
    void off();
    // LED ON
    void on();
};



#endif /* __GPIO_HPP */