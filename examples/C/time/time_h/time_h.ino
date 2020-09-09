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
 * \brief Erriez libc time.h example
 * \details
 *    Use https://www.epochconverter.com/ for verification.
 *
 *    Source: https://github.com/Erriez/ErriezArduinoExamples
 */

/* Example output:
      libc time.h example
      
      Convert epoch:
        epoch UTC: 1582983995
        ctime:     Sat Feb 29 13:46:35 2020
        asctime:   Sat Feb 29 13:46:35 2020
        localtime: Sat Feb 29 13:46:35 2020
        tm struct: 6 29-1-120 13:46:35 59 -1
      
      Convert date time:
        tm struct: 29-1-120 13:46:35
        epoch UTC: 1582983995
        ctime:     Sat Feb 29 13:46:35 2020
 */

/* The libc library is not standardized and requires some portability to run the same
 * code on different targets. Major changes differences below:
 *  
 *  AVR:
 *   https://www.nongnu.org/avr-libc/user-manual/group__avr__time.html
 *   
 *   Though not specified in the standard, it is often expected that time_t is a 
 *   signed integer representing an offset in seconds from Midnight Jan 1 1970... i.e. 
 *   'Unix time'. This implementation uses an unsigned 32 bit integer offset from 
 *   Midnight Jan 1 2000. The use of this 'epoch' helps to simplify the conversion 
 *   functions, while the 32 bit value allows time to be properly represented until 
 *   Tue Feb 7 06:28:15 2136 UTC. The macros UNIX_OFFSET and NTP_OFFSET are defined to
 *   assist in converting to and from Unix and NTP time stamps.
 *   
 *   Usage:
 *      time_t t = 1582983995UL; // Unix epoch
 *      t -= UNIX_OFFSET;
 *      struct tm *dt = gmtime(&t);
 *      
 *      time_t t = mktime(&dt);
 *      Serial.println(t + UNIX_OFFSET);
 *      
 *   http://www.cplusplus.com/reference/ctime
 *   
 *   asctime() / ctime()
 *      The string is followed by a new-line character ('\n') and terminated with a 
 *      null-character.
 *      
 *   AVR does not containt the newline, ESP8266 has it.
 *   
 *   Timezene calulation requires lots of flash, for this reason, a different API exists.
 */

#include <time.h>


void convertEpoch()
{
    time_t t;
    struct tm *dt;

    Serial.println(F("\nConvert epoch:"));
  
    // Unix UTC time: "Sat Feb 29 2020 13:46:35"
    t = 1582983995UL;
    Serial.print(F("  epoch UTC: "));
    Serial.println((uint32_t)t);

#ifdef ARDUINO_ARCH_AVR
    t -= UNIX_OFFSET;
#endif

    // UNIX UTC time (including timezone)"
    Serial.print(F("  ctime:     "));
    Serial.println(ctime(&t));

    // Convert time_t to UTC tm struct (no timezone)
    dt = gmtime(&t);

    // Print tm struct
    Serial.print(F("  asctime:   "));
    Serial.println(asctime(dt));

    // Convert time_t with localtime() to tm struct (including timezone)
    dt = localtime(&t);
    
    // Print tm struct
    Serial.print(F("  localtime: "));
    Serial.println(asctime(dt));

    // 0 6-8-120 9:46:40 249 0
    Serial.print(F("  tm struct: "));
    Serial.print(dt->tm_wday); // 0 = Sunday
    Serial.print(" ");
    Serial.print(dt->tm_mday); // 1..31
    Serial.print("-");
    Serial.print(dt->tm_mon);  // 0..11
    Serial.print("-");
    Serial.print(dt->tm_year); // Days since 1900
    Serial.print(" ");
    Serial.print(dt->tm_hour); // 0..23
    Serial.print(":");
    Serial.print(dt->tm_min);  // 0..59
    Serial.print(":");
    Serial.print(dt->tm_sec);  // 0..59
    Serial.print(" ");
    Serial.print(dt->tm_yday); // Days since 1 Jan
    Serial.print(" ");
    Serial.print(dt->tm_isdst); // -1, 0 or 1
    Serial.println();
}

void convertDateTime()
{
    time_t t;
    struct tm dt = { 0 };
  
    Serial.println(F("\nConvert date time:"));
    
    // Configure tm struct "29 Feb 2020 13:46:35" (no day of the week)
    dt.tm_mday = 29;
    dt.tm_mon = 2-1; // February
    dt.tm_year = 2020-1900;
    dt.tm_hour = 13;
    dt.tm_min = 46;
    dt.tm_sec = 35;

    Serial.print(F("  tm struct: "));
    Serial.print(dt.tm_mday); // 1..31
    Serial.print("-");
    Serial.print(dt.tm_mon);  // 0..11
    Serial.print("-");
    Serial.print(dt.tm_year); // Days since 1900
    Serial.print(" ");
    Serial.print(dt.tm_hour); // 0..23
    Serial.print(":");
    Serial.print(dt.tm_min);  // 0..59
    Serial.print(":");
    Serial.print(dt.tm_sec);  // 0..59
    Serial.println();

    // time_t: 1582983995
    t = mktime(&dt);
    Serial.print(F("  epoch UTC: "));
#ifdef ARDUINO_ARCH_AVR
    Serial.println((uint32_t)(t + UNIX_OFFSET));
#else
    Serial.println((uint32_t)t);
#endif

    // time_t: "Sat Feb 29 13:46:35 2020"
    Serial.print(F("  ctime:     "));
    Serial.println(ctime(&t));
}

void setup() 
{
    // Initialize serial
    delay(500);
    Serial.begin(115200);
    Serial.println(F("\nlibc time.h example"));

#if 0 // ARDUINO_ARCH_ESP8266 //For ESP8266
    // Set timezone information Europe/Amssterdam/Netherlands
    setenv("TZ", "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00", 1);
    //                        | month 3, last Sunday at 2:00AM
    //                                        | month 10, last Sunday, at 2:00am  
    //                                                           | overwrite = 1
    tzset();
#endif

    // First test
    convertEpoch();

    // Second test
    convertDateTime();
}

void loop() 
{
}
