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

lib_deps =
    mathertel/OneButton @ ^2.6.1

*/


