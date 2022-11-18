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


/*
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
*/

template <typename port_type, typename bval_type, const port_type port, const bval_type bval>
class led_template
{
    public:
    led_template(port_type * t_gpio, bval_type t_pin) : gpio(t_gpio), pin(t_pin)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
        HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
        GPIO_InitTypeDef GPIO_InitStruct = 
        {
            .Pin = pin,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_LOW
        };
        HAL_GPIO_Init(gpio, &GPIO_InitStruct); 
    }
    ~led_template()
    {
    //Configure GPIO pin Output Level 
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
    //Deinitialize gpio/pin
    HAL_GPIO_DeInit(gpio, pin);
    }

    void toggle()
    {
        HAL_GPIO_TogglePin(gpio, pin);
    }

    bool state()
    {
    return HAL_GPIO_ReadPin(gpio, pin);
    }   
    void off()
    {
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
    }

    void on()
    {
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
    }

    private:
    port_type * gpio;
    bval_type pin;

};

#endif /* __GPIO_HPP */