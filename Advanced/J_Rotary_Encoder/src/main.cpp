#include <Arduino.h>
#include <H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop

H4P_GPIOManager h4gm;

#include "platform.h"


void h4setup() {
    Serial.println("H4P_GPIOManager EncodeAuto Example v"H4P_VERSION);
    Serial.print("GPIO ");Serial.print(BUTTON_PIN);Serial.print(" ACTIVE ");Serial.println(UB_ACTIVE ? "HIGH":"LOW");

#ifdef ARDUINO_ARCH_ESP32
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(LED_PIN, ledChannel);
#else
    pinMode(LED_PIN, OUTPUT);
#endif


    //
    //  min=0, max=100, 50 means set inital value to default, increment by 2 per click
    //
    h4gm.EncoderAuto(ENCODER_A, ENCODER_B, INPUT, UB_ACTIVE, 0, 1023, 0, 50, [](H4GPIOPin *ptr) {
        H4GM_PIN(EncoderAuto); // Create the correct pointer type in 'pin'
        Serial.print("ENCODER AUTO value ");
        Serial.println(pin->autoValue);
        

#ifdef ARDUINO_ARCH_ESP32
        ledcWrite(ledChannel, pin->autoValue);
#else
        analogWrite(LED_PIN, pin->autoValue);
#endif
    });

}