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
 * \brief Erriez ESP8266 Normal Sleep example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include <ESP8266WiFi.h>

// SSID and Password of your WiFi router
const char *ssid = "***";
const char *password = "***";  

// Time to sleep in seconds
#define SLEEP_TIME_SEC    15


void setup(void)
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);
    Serial.println(F("\nESP8266 normal sleep example"));
}

void loop(void)
{
    Serial.print(F("Connecting to "));
    Serial.print(ssid);
    
    // Connect to local Wifi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println(F("OK"));

    // Do something

    // Time to let the WiFi go to sleep!
    Serial.print(F("Sleeping "));
    Serial.print(SLEEP_TIME_SEC);
    Serial.println(F("seconds..."));
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin(SLEEP_TIME_SEC * 1000000L); // In uS. Must be same length as your delay
    delay(SLEEP_TIME_SEC * 1000); // Hang out at 15mA for 10 seconds
    WiFi.mode(WIFI_STA);

    // Wakeup after sleep time
    Serial.println(F("Awake!"));
}

