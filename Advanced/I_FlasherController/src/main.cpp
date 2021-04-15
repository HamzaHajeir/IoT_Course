#include <Arduino.h>
#define H4FC_MORSE_SUPPORT
#include<H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop


H4P_FlasherController h4fc;

#include "platform.h"

void h4setup() { // H4 constructor starts Serial
    Serial.println("H4P_FlasherController Basic Example v"H4P_VERSION);
    pinMode(LED_RED,OUTPUT);    // not required if H4P_GPIOManager used
    pinMode(LED_GREEN,OUTPUT);  
    pinMode(LED_YELLOW,OUTPUT);   
    pinMode(ledPin,OUTPUT);         
    pinMode(LED_BUILTIN,OUTPUT);


    h4.everyRandom(5000,10000,[](){
        Serial.print(millis());Serial.println(" RUDE INTERRUPTION");
        h4fc.pulseLED(100,LED_GREEN);
    });

    h4fc.flashLED(250,LED_YELLOW);
    h4fc.flashMorse("... --- ...",150,LED_RED);
    h4fc.flashPattern("01000111000",150,LED_BUILTIN,ACTIVE_LOW);
    h4fc.flashPWM(500,25,ledPin);
}