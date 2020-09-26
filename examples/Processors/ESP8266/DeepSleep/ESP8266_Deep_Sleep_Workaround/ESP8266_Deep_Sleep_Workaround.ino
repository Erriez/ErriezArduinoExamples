/*
 * MIT License
 *
 * Copyright (c) 2020 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \brief Erriez ESP8266 deepSleep() workaround
 * \details
 *      deepSleep() does not wake up correctly on some counterfeit ESP8266.
 *      A workaround is created on GitHub, unfortunately without documentation:
 *          https://github.com/esp8266/Arduino/issues/6007
 *      Note: Use ESP.deepSleep() for genuine ESP8266 devices.
 *
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include "ESP8266WiFi.h"
extern "C" {
#include <user_interface.h>
}

#define ets_wdt_disable ((void (*)(void))0x400030f0)
#define ets_delay_us ((void (*)(int))0x40002ecc)

#define _R (uint32_t *)0x60000700


void nk_deep_sleep(uint64_t time)
{
    ets_wdt_disable();
    *(_R + 4) = 0;
    *(_R + 17) = 4;
    *(_R + 1) = *(_R + 7) + 5;
    *(_R + 6) = 8;
    *(_R + 2) = 1 << 20;
    ets_delay_us(10);
    *(_R + 39) = 0x11;
    *(_R + 40) = 3;
    *(_R) &= 0xFCF;
    *(_R + 1) = *(_R + 7) + (45*(time >> 8));
    *(_R + 16) = 0x7F;
    *(_R + 2) = 1 << 20;
    __asm volatile ("waiti 0");
}

void setup()
{
    delay(1000);

    nk_deep_sleep(2000000);
}

void loop()
{
}