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
 * \brief Erriez Arduino mktime example
 * \details
 *    Source: https://github.com/Erriez/ErriezArduinoExamples
 */

#include <time.h>

// A test epoch "Sunday, September 6, 2020 18:20:30"
#define EPOCH_TEST    1599416430UL


void read(struct tm *dt)
{
    dt->tm_sec = 30;
    dt->tm_min = 20;
    dt->tm_hour = 18;
    dt->tm_wday = 0; // 0=Sunday
    dt->tm_mday = 6;
    dt->tm_mon = 8;  // Month: 0..11
    dt->tm_year = 2020-1900; // Years since 1900
}

void setup() 
{
    struct tm dt = { 0 };
    time_t t;

    delay(500);
    Serial.begin(115200);
    Serial.println();

    // Read time structure
    read(&dt);

    // Convert date/time struct tm to time_t
    t = mktime(&dt);

#ifdef ARDUINO_ARCH_AVR
    t += UNIX_OFFSET;
#endif

    if (t != EPOCH_TEST) {
        Serial.print(F("Expected: "));
        Serial.print(EPOCH_TEST);
        Serial.print(F(" Calculated: "));
        Serial.println((uint32_t)t);
        
        Serial.print(F("Test failed!"));
    } else {
        Serial.println(F("Test passed"));
    }
}

void loop() 
{
}
