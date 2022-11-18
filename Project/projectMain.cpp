#include <main.h>
#include "projectMain.h"
#include <array>
#include <cstdio>
#include <span>

#include <gpio.hpp>

using namespace std;
namespace
{
    const led_template<uintptr_t, uint16_t, GPIOC_BASE, GPIO_PIN_13> ledica;
}

void projectMain()
{
    ledica.toggle();
    //led ledica(GPIOC, GPIO_PIN_13);
//Led led(GPIOC, GPIO_PIN_13);
    // Newer C++ features
    constexpr auto arr = std::to_array({1, 2, 3, 4, 5});
    auto view = std::span(arr);

    while (true)
    {
        
        //ledica.toggle();
        HAL_Delay(500);
    }
}