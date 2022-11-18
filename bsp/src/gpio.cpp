#include "gpio.hpp"

#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_gpio.h>

led::led(GPIO_TypeDef * t_gpio, uint16_t t_pin): gpio(t_gpio), pin(t_pin)
{
        // GPIO Ports Clock Enable 
        // Remove this part and make it port specific
        __HAL_RCC_GPIOC_CLK_ENABLE();
        //Configure GPIO pin Output Level
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

led::~led()
{
    //Configure GPIO pin Output Level 
    HAL_GPIO_WritePin(led::gpio, led::pin, GPIO_PIN_RESET);
    //Deinitialize gpio/pin
    HAL_GPIO_DeInit(led::gpio, led::pin);
}

void led::toggle()
{
        HAL_GPIO_TogglePin(gpio, pin);
}

bool led::state()
{
    return HAL_GPIO_ReadPin(led::gpio, led::pin);
}

void led::off()
{
    HAL_GPIO_WritePin(led::gpio, led::pin, GPIO_PIN_RESET);
}

void led::on()
{
    HAL_GPIO_WritePin(led::gpio, led::pin, GPIO_PIN_SET);
}


