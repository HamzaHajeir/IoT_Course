#ifdef ARDUINO_ARCH_ESP32 
#define BUTTON_PIN      23
#define UB_ACTIVE       ACTIVE_LOW

#define ENCODER_A       18
#define ENCODER_B       19

#define LED_PIN          4

const int freq          = 5000;
const int ledChannel    = 0;
const int resolution    = 10;
#elif defined(ARDUINO_ARCH_ESP8266)

#define USER_BTN        D3
#define UB_ACTIVE       ACTIVE_LOW

#define ENCODER_A       D7
#define ENCODER_B       D6

#define LED_PIN          D8

#endif