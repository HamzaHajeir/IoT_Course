#include <Arduino.h>


#include<H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop


uint32_t myCallback(vector<string> vs);
void onMQTTConnect();
void onMQTTDisconnect();


#define SSID ""
#define PASS ""


H4P_CmdErrors h4ce;
H4P_GPIOManager h4gm;
H4P_WiFi h4wifi(SSID,PASS,"H4-Mqtt Test");
H4P_AsyncMQTT h4mqtt("192.168.1.4",1883,"","",onMQTTConnect,onMQTTDisconnect); // no username / pword

H4P_BinaryThing h4bt([](bool b){ 
    Serial.print("I am now ");Serial.println(b ? "ON":"OFF");
    h4gm.logicalWrite(LED_BUILTIN, b ? ON : OFF);
 });



void onMQTTConnect(){
    Serial.print("USER: MQTT connected\n");
    h4mqtt.subscribeDevice("mytopic",myCallback);
}

void onMQTTDisconnect(){
    Serial.print("USER: MQTT Disconnected\n");
    h4mqtt.unsubscribeDevice("mytopic");
}

uint32_t myCallback(vector<string> vs){

  Serial.printf("USER: Msg received with payload=%s\n",H4PAYLOAD.c_str()); // convert payload to C-style string

  if(H4PAYLOAD=="good") {
      h4mqtt.publishDevice("goodpayload","Thank You!");
      return H4_CMD_OK;
  }
  else {
      h4mqtt.publishDevice("badpayload",H4PAYLOAD);
      return H4_CMD_PAYLOAD_FORMAT;
  }

}

// thing variableSpeedBlinky([](bool on) {
//     if (on)
//         Esparto.flashLED(Esparto.getConfigInt("blinkrate"));
//     else
//         Esparto.stopLED();
// });


void h4setup(){
    Serial.printf("Start the flashing one of many ways:\n");
    Serial.printf(" * Serial console: switch/0 or switch/1\n");
    Serial.printf(" * Button on GPIO0 (short press)\n");
    
    
    h4gm.Output(LED_BUILTIN,
        ACTIVE_LOW,
        OFF
    );
}

