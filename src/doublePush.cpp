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

/*------------------------------------------------------------------------------
[env:esp32-s3-devkitc-1]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino

board_build.arduino.memory_type = qio_opi
board_upload.flash_size = 16MB

upload_speed = 921600

build_flags = 
    ;-DARDUINO_USB_CDC_ON_BOOT=1 
    ;-DARDUINO_USB_MODE=1 
    -DBOARD_HAS_PSRAM
    '-D LED_PIN=4U'
    '-D LED_ACT=HIGH'
    '-D BTN_PIN=0U'
    '-D BTN_ACT=LOW'

lib_deps =
    mathertel/OneButton @ ^2.6.1

*/