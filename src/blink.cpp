#include <Arduino.h>
#include "LED.h"
#include <OneButton.h>

//dùng chân số 4 để điều khiển LED

LED led(LED_PIN, LED_ACT);

void setup()
{
    led.off();
}

void loop()
{
    led.blink(500);
    led.loop();
    //button.tick();
}


