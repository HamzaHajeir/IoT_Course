/*
 MIT License

Copyright (c) 2020 Phil Bowles <H48266@gmail.com>
   github     https://github.com/philbowles/H4
   blog       https://8266iot.blogspot.com
   groups     https://www.facebook.com/groups/esp8266questions/
              https://www.facebook.com/H4-Esp8266-Firmware-Support-2338535503093896/


Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#ifndef H4P_MQTTHeapLogger_HO
#define H4P_MQTTHeapLogger_HO

#ifndef ARDUINO_ARCH_STM32
#include <H4PCommon.h>
#include <H4P_AsyncMQTT.h>

class H4P_MQTTHeapLogger: public H4P_MQTTLogger {
        uint32_t _f;
        void _start() override { 
            H4P_MQTTLogger::_start();
            h4.every(_f,[this](){ SYSEVENT(H4P_LOG_MQTT_HEAP,_pName,mqttTag(),"%u",ESP.getFreeHeap()); },nullptr,H4P_TRID_HLOG,true);
            }
        void _stop() override { 
            h4.cancelSingleton(H4P_TRID_HLOG);
            H4P_MQTTLogger::_stop();
        }
    public:
        H4P_MQTTHeapLogger(uint32_t f): _f(f),H4P_MQTTLogger("heap",H4P_LOG_MQTT_HEAP){}
};
#endif
#endif // H4P_MQTTLogger_H