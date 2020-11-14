#include <Arduino.h>

#include<H4.h>

H4 h4(115200); // Automatically starts Serial for you if speed provided

void myCallback(){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // invert pin state
}

void h4setup(){ // do the same type of thing as the standard setup
    pinMode(LED_BUILTIN,OUTPUT);

#if 1
    h4.nTimes(10,//Times
        200,//Interval time in ms
        myCallback
    );
#else
    h4.nTimes(10,//Times
        200,//Interval time in ms
        myCallback,
        [](){
            h4.every(1000,myCallback); // All times are milliseconds, 1000=1 second
        }
    );
#endif
}