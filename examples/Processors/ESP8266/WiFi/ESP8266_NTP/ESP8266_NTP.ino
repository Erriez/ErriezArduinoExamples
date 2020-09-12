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
 * \brief Erriez ESP8266 NTP UTC example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Udp.h>
#include <time.h>

// SSID and Password of your WiFi router
#define WIFI_SSID           ""
#define WIFI_PASSWORD       ""

// "pool.ntp.org", "time.nist.gov" or IP address
#define NTP_SERVER          "pool.ntp.org"
// Receive timeout
#define NTP_RX_TIMEOUT      2000

// NTP time stamp is in the first 48 bytes of the message
#define NTP_PACKET_SIZE     48
// UDP listen port
#define LOCAL_PORT          2390

// WiFi UDP object
WiFiUDP udp;


void initWifi()
{
    Serial.print(F("Connecting to '"));
    Serial.print(WIFI_SSID);
    Serial.print(F("'"));

    // Connect to your WiFi router
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // If connection successful show IP address in serial monitor
    Serial.println("OK");
}

void sendNTPpacket(const char *ntpServer)
{
    static bool initialized  = false;
    uint8_t txBuffer[NTP_PACKET_SIZE];

    // Initialize UDP
    if (!initialized) {
        udp.begin(LOCAL_PORT);
        initialized = true;
    }

    // Clear transmit buffer
    memset(txBuffer, 0, NTP_PACKET_SIZE);

    // Initialize values needed to form NTP request
    txBuffer[0] = 0b11100011; // LI, Version, Mode
    txBuffer[1] = 0;          // Stratum, or type of clock
    txBuffer[2] = 6;          // Polling Interval
    txBuffer[3] = 0xEC;       // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    txBuffer[12]  = 49;
    txBuffer[13]  = 0x4E;
    txBuffer[14]  = 49;
    txBuffer[15]  = 52;

    // Send NTP packet to port 123
    udp.beginPacket(ntpServer, 123);
    udp.write(txBuffer, NTP_PACKET_SIZE);
    udp.endPacket();
}

time_t getEpoch(const char *ntpServer, uint16_t timeoutMs=1000)
{
    static uint32_t tPacketSent = 0;
    uint8_t rxBuffer[NTP_PACKET_SIZE];
    time_t t = 0;

    // Send packet
    tPacketSent = millis();
    sendNTPpacket(ntpServer);

    do {
        // Check if packet received
        if (udp.parsePacket()) {
            // Read data from received UDP packet
            udp.read(rxBuffer, NTP_PACKET_SIZE);


            // NTP time in seconds since Jan 1 1900
            t = (rxBuffer[40] << 24) | (rxBuffer[41] << 16) |
                (rxBuffer[42] << 8) | (rxBuffer[43] << 0);

            // Unix time starts on Jan 1 1970. In seconds, that's 2208988800
            t -= 2208988800UL;

            break;
        }
    } while ((millis() - tPacketSent) < timeoutMs);

    return t;
}

void setup()
{
    time_t t;

    // Initialize serial
    delay(500);
    Serial.begin(115200);
    Serial.println(F("\nErriez ESP8266 NTP example"));

    // Initialize WiFi
    initWifi();

    // Get epoch
    t = getEpoch(NTP_SERVER, NTP_RX_TIMEOUT);

    // Print result
    if (t > 0) {
        Serial.print(F("Epoch: "));
        Serial.println((uint32_t)t);
        Serial.print(F("UTC:   "));
        Serial.println(ctime(&t));
    } else {
        Serial.println(F("Timeout"));
    }
}

void loop()
{
}