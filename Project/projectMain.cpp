#include <main.h>
#include "projectMain.h"
#include <array>
#include <cstdio>
#include <span>

#include <gpio.hpp>

using namespace std;

void projectMain()
{

    led ledica(GPIOC, GPIO_PIN_13);
 
    // Newer C++ features


    while (true)
    {
        
        ledica.toggle();
        HAL_Delay(500);
    }
}