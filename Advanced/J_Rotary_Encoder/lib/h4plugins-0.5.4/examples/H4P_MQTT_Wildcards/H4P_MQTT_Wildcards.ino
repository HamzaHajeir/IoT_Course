#include<H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop
//
//  Callback is given a vector of strings (vs), each contains one component of input topic
//  NB last item is always payload, hence= vs.back()
//
//  If this sounds new, think of it like an array of Arduino Strings, (but with more functionality)
//
//  Assume user publishes cards/hearts with payload of "4"
//  In vector strings vs, you will find:
//  vs[0] = "hearts" - next "part" of topic after "/"
//  vs[1] = "4" - also known as vs.back() becuase its the last item. payload is ALWAYS vs.back()
//  In this case, vs.size() will = 2: a good indication that the input MAY be valid...1 or 3 CERTAINLY can't be
//
//  BUT BE WARNED!!!! 
//    Prepare to cope with nonsense, # will also allow cards/three-piece/with/waistcoat ["and tie"]
//  and you will get
//  In vector strings vs, you will find:
//  vs[0] = "three-piece" - next "part" of topic after "/"
//  vs[1] = "with" - next "part" of topic after "/"
//  vs[2] = "waistcoat" - next "part" of topic after "/"
//  vs[3] = "and tie" - also known as vs.back() becuase its the last item. payload is ALWAYS vs.back()
// In this case, vs.size() will = 4: you know immediatly its junk
//
//  Remember, the "s" in "vs" is "string": if there is  value you want to treat as an int, there are two useful MACROS:
//  PARAM( n ) and H4PAYLOAD_INT
//  So if you subscribe to something/# and someone publishes
//  something/with/an/int/42 and payload of 666 then
//  ...
//  ...
//  vs[4]="42"     in code, use int myInt=PARAM(4);    // 42
//  vs[5]="666"    in code use int myPayload=H4PAYLOAD_INT; // 666
// 
 void onMQTTConnect(){
    Serial.print("USER: MQTT connected\n");
    h4mqtt.subscribeDevice("cards/#",myCallback);
}

void onMQTTDisconnect(){
    Serial.print("USER: MQTT Disconnected\n");
}

H4P_CmdErrors h4ce;
H4P_WiFi h4wifi("XXXXXXXX","XXXXXXXX","testbed");
H4P_AsyncMQTT h4mqtt("192.168.1.4",1883,"","",onMQTTConnect,onMQTTDisconnect); // no username / pword

uint32_t myCallback(vector<string> vs){
  for(auto const& v:vs) Serial.printf("v: %s\n",CSTR(v)); // show input
  if(vs.size()==2){
    string suit=vs[0];
    Serial.printf("Wildcard handler suit is %s, card is %s\n",(CSTR(suit)),CSTR(vs.back()));
    if(suit=="hearts" || suit=="clubs" || suit=="diamonds" || suit=="spades"){
      Serial.printf("You chose the %s of %s\n",CSTR(vs.back()),CSTR(suit));
      h4mqtt.publishDevice("dealt",CSTR(string(vs.back()+" of "+suit)));
      return H4_CMD_OK;
    } 
    else {
      Serial.printf("Invalid suit %s\n",CSTR(suit));
      return H4_CMD_PAYLOAD_FORMAT;        
    }
  } 
  else {
    Serial.printf("Count of %d sub-items is obviously an error\n",vs.size());
    return H4_CMD_PAYLOAD_FORMAT;        
  }
}

#ifdef ARDUINO_ARCH_STM32
  #define U_BOARD_NAME BOARD_NAME
#else
  #define U_BOARD_NAME ARDUINO_BOARD
#endif
/*
    Using any MQTT client MQTTSpy, NODE RED etc etc, subscribe to testbed/# 
    to see all the messages from this device:

    Then, publish topic

    cards/... etc
*/
void h4setup() {
    Serial.println("\nH4 Plugins MQTT example v"H4P_VERSION);
}
