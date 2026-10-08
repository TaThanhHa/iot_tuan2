#include <Arduino.h>
#include "LED.h"
#include <OneButton.h>
//dùng nút boot (chân 0) và led ngoài chân 4
LED led(LED_PIN, LED_ACT);

void btnPush();
void btnDoublePush();
OneButton button(BTN_PIN, !BTN_ACT);

void setup()
{
    led.off();
    button.attachClick(btnPush);
    button.attachDoubleClick(btnDoublePush);
}

void loop()
{
    led.loop();
    button.tick();
}

void btnPush()
{
    led.flip();
}

void btnDoublePush()
{
    led.blink(200);
}
