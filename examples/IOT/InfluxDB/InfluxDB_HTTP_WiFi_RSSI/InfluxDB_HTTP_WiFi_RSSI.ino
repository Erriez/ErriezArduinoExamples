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
 * \brief Erriez InfluxDB1 ESP8266/ESP32 WiFi Status example
 * \details
 *      This example uses InfluxDBClient library for Arduino to log WiFi RSSI 
 *      (Received Signal Strength Indicator).
 *      
 *      This example supports only InfluxDB running from unsecure (http://...).
 *      
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include <ESP8266WiFi.h>

#if defined(ESP32)
  #define DEVICE "ESP32"
#elif defined(ESP8266)
  #define DEVICE "ESP8266"
#else
#error "Unknown target"
#endif

#include <InfluxDbClient.h> // https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino

// WiFi connection
#define WIFI_SSID "***"
#define WIFI_PASSWORD "***"

// InfluxDB connection
#define INFLUXDB_URL "http://192.168.0.1:8086"
#define INFLUXDB_USER "iot"
#define INFLUXDB_PASSWORD "iot123"
#define INFLUXDB_DB_NAME "data"

// InfluxDB client instance for InfluxDB 1
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);

// Data point
Point sensor("wifi_status");


void connectWifi()
{
    // Connect to WiFi
    Serial.printf_P(PSTR("Connecting to %s"), WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
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
    Serial.println(F("\nInfluxDB1 ESP8266/ESP32 WiFi RSSI example"));
  
    // Connect WiFi
    connectWifi();
  
    // Set InfluxDB 1 authentication params
    client.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD);
  
    // Add constant tags - only once
    sensor.addTag("device", DEVICE);
    sensor.addTag("SSID", WiFi.SSID());
  
    // Check server connection
    if (client.validateConnection()) {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(client.getServerUrl());
    } else {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(client.getLastErrorMessage());
    }
}

void loop() 
{
    // Store measured value into point
    sensor.clearFields();
    
    // Report RSSI of currently connected network
    sensor.addField("rssi", WiFi.RSSI());
    
    // Print what are we exactly writing
    Serial.print("Writing: ");
    Serial.println(sensor.toLineProtocol());
    
    // If no Wifi signal, try to reconnect it
    if ((WiFi.RSSI() == 0) && (WiFi.status() != WL_CONNECTED)) {
        Serial.println("Wifi connection lost");
    }
    
    // Write point
    if (!client.writePoint(sensor)) {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    }
    
    // Wait 10s
    Serial.println("Wait 10s");
    delay(10000);
}
