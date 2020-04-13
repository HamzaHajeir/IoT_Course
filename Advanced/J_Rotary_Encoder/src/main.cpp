#include<H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop

H4P_GPIOManager h4gm;


#define USER_BTN D3
#define UB_ACTIVE ACTIVE_LOW

#define ENCODER_A D7
#define ENCODER_B D6

void h4setup() { // H4 constructor starts Serial
    Serial.println("H4P_GPIOManager EncodeAuto Example v"H4P_VERSION);
    Serial.print("GPIO ");Serial.print(USER_BTN);Serial.print(" ACTIVE ");Serial.println(UB_ACTIVE ? "HIGH":"LOW");
//
//  min=0, max=100, 50 means set inital value to default, increment by 2 per click
//
    h4gm.EncoderAuto(ENCODER_A,ENCODER_B,INPUT,UB_ACTIVE,0,1023,50,10,[](H4GPIOPin* ptr){
        H4GM_PIN(EncoderAuto); // Create the correct pointer type in 'pin'
        Serial.print("ENCODER AUTO value ");Serial.println(pin->autoValue);
        analogWrite( D5,  pin->autoValue );
    });

    pinMode(D5,OUTPUT);

}