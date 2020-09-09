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
 * \brief Erriez ESP8266 low power LED blink example
 * \details
 *      Connect wire between pins D0 and RST
 *
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */
 
#include <ESP8266WiFi.h>
extern "C" {
#include <user_interface.h>
}

// LED pin NodeMCU
#define LED_PIN             LED_BUILTIN

// Sleep time in seconds
#define SLEEP_TIME_SEC      1

// RTC RAM SIZE
#define RTC_RAM_SIZE        512

// RTC RAM data
typedef struct {
    uint16_t wakeCount;
    bool toggle;
} RTCRamData;

static_assert(sizeof(RTCRamData) <= RTC_RAM_SIZE, "RTC RAM size exceeded");

RTCRamData ramData;


void readRtcRam()
{
    if (ESP.getResetInfoPtr()->reason != REASON_DEEP_SLEEP_AWAKE) {
        Serial.println("Clear RTC RAM");
        memset(&ramData, 0, sizeof(ramData));
    } else {
        Serial.println("Read from RTC RAM");
        ESP.rtcUserMemoryRead(0, (uint32_t *)&ramData, sizeof(ramData));
    }
}

void writeRtcRam()
{
    Serial.println("Write to RTC RAM");
    ESP.rtcUserMemoryWrite(0, (uint32_t *)&ramData, sizeof(ramData));
}

void setup()
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);
    Serial.println("\nESP8266 Low Power Blink example");
    
    // Turn LED on
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Turn WiFi off
    WiFi.mode(WIFI_OFF);

    // Initialize RTC RAM
    readRtcRam();
    ramData.wakeCount++;
    ramData.toggle ^= true;
    writeRtcRam();

    // Print RTC RAM
    Serial.printf("Wake count: %d\n", ramData.wakeCount);
    if (ramData.toggle) {
        Serial.println("Toggle: true");
    } else {
        Serial.println("Toggle: false");
    }

    Serial.println("Normal sleep");
    WiFi.forceSleepBegin(SLEEP_TIME_SEC * 1000000L); // Must be the same sleep time as delay()
    delay(SLEEP_TIME_SEC * 1000);

    // Sleep one second deep power down
    // LED is turned off during deep sleep
    Serial.println("Deep sleep");
    ESP.deepSleep(SLEEP_TIME_SEC * 1000000UL, WAKE_RF_DISABLED);
}

void loop()
{
}
