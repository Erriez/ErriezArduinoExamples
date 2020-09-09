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
 * \brief Erriez ESP8266 Wifi scan example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */
 
#include <ESP8266WiFi.h>


void setup() 
{
    String ssid;
    uint8_t encryptionType;
    int32_t RSSI;
    uint8_t* BSSID;
    int32_t channel;
    bool isHidden;
    int netcount;
    int n;

    // Startup delay to initialize serial port
    delay(500);
   
    // Initialize serial
    Serial.begin(115200);
    Serial.println(F("\nESP8266 WiFi scan example"));

    netcount = WiFi.scanNetworks();

    for (n = 0; n < netcount; n++) {
        WiFi.getNetworkInfo(n, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
        Serial.println();
        Serial.println(String("SSID:            ") + ssid);
        Serial.print  (String("Encryption type: "));
        switch (encryptionType) {
            case ENC_TYPE_WEP:
                Serial.println(F("WEP"));
                break;
            case ENC_TYPE_TKIP:
                Serial.println(F("WPA PSK"));
                break;
            case ENC_TYPE_CCMP:
                Serial.println(F("WPA2 PSK"));
                break;
            case ENC_TYPE_NONE:
                Serial.println(F("Open"));
                break;
            case ENC_TYPE_AUTO:
                Serial.println(F("WPA WPA2 PSK"));
                break;
            default:
                Serial.println(String("Unknown: ") + encryptionType);
        }
        Serial.println(String("RSSI:            ") + RSSI);
        Serial.println(String("Channel:         ") + channel);
        Serial.println(String("Hidden:          ") + isHidden);
    }
}

void loop() 
{
}
