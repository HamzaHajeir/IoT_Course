/*
 MIT License

Copyright (c) 2019 Phil Bowles <H48266@gmail.com>
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
#define H4P_VERSION "0.5.4"

// comment this out to prevent and logging by EVENT( whatever ) messages
#define H4P_LOG_EVENTS
/*
            TWEAKABLES
*/
#ifndef H4PCONFIG_H
#define H4PCONFIG_H

#define H4P_REPLY_BUFFER    512

#define H4ESW_MAX_F         150000
#define H4ESW_MAX_D            100
#define H4ESW_TIMEOUT           50

//#define H4FC_MORSE_SUPPORT

#define H4MQ_RETRY            5000

#define H4P_UDP_JITTER         250
#define H4P_UDP_REFRESH     300000
#define H4P_UDP_REPEAT           2

#define H43F_SLOW              250
#define H43F_MEDIUM            125
#define H43F_FAST               25
#define H43F_TIMEBASE          175
#define H43F_REBOOT           2000
#define H43F_FACTORY          5000

#define H4WF_OTA_RATE         1000

#define H4P_IPPD_RATE         5000
#define H4P_PJ_SPREAD            3

#define H4P_PJ_LO (H4P_IPPD_RATE - (H4_JITTER_LO * H4P_PJ_SPREAD))
#define H4P_PJ_HI (H4P_IPPD_RATE + (H4_JITTER_HI * H4P_PJ_SPREAD))

#define H4P_RUPD_STRETCH         5

#define H4P_TIME_HOLDOFF       500
#define H4P_TIME_RESYNC 60*60*1000

#endif