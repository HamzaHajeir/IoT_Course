#ifdef ARDUINO_ARCH_ESP32 

#define LED_RED     2
#define LED_YELLOW  4
#define LED_GREEN   5

constexpr int ledPin = 19;

#elif defined(ARDUINO_ARCH_ESP8266)

#define LED_RED     D8
#define LED_YELLOW  D7
#define LED_GREEN   D6
constexpr int ledPin = D5;
#endif