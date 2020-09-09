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
 * \brief Erriez ESP8266 NTP example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */
 
#include <ESP8266WiFi.h>
#include <time.h>

// SSID and Password of your WiFi router
const char *ssid = "***";
const char *password = "***";    


void getNTP()
{
    struct tm timeinfo;
    time_t now;
    char line[40];

    // Configure NTP servers
    configTime(1 * 3600, 0, "pool.ntp.org", "time.nist.gov");

    Serial.print(F("Waiting for NTP time sync"));
    now = time(nullptr);
    while (now < (8 * 3600 * 2)) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println("");

    // Convert time_t to tm as UTC time
    gmtime_r(&now, &timeinfo);

    // Format time as string
    strftime(line, sizeof(line), "%A %d %B %Y  %H:%M:%S", &timeinfo);

    // Print date/time
    Serial.print(F("Epoch: "));
    Serial.println(now);
    Serial.print(F("Current time: "));
    Serial.println(line);
}

void wifiConnect()
{
    Serial.printf_P(PSTR("Connected to %s"), ssid);
    
    // Connect to your WiFi router
    WiFi.begin(ssid, password);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(F("OK"));
}

void setup()
{
    // Startup delay to initialize serial port
    delay(500);
    
    // Initialize serial
    Serial.begin(115200);
    Serial.println(F("\nESP8266 NTP example"));

    // WiFi connect
    wifiConnect();

    // Get NTP
    getNTP();
}

void loop()
{

}
