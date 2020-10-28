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
 * \brief Erriez MQTT PubSubClient BME280 example
 * \details
 *      Source: https://github.com/Erriez/ErriezArduinoExamples
 */

#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ErriezBMX280.h>

#define WIFI_SSID               ""
#define WIFI_PASSWORD           ""
#define WIFI_TIMEOUT_MS         6000

#define MQTT_SERVER             ""
#define MQTT_PORT               1883
#define MQTT_USER               ""
#define MQTT_PASSWORD           ""

// WiFi client
WiFiClient wifiClient;

// MQTT
PubSubClient mqttClient(MQTT_SERVER, MQTT_PORT, wifiClient);

// Create BMX280 object I2C address 0x76 or 0x77
ErriezBMX280 bmx280 = ErriezBMX280(0x76);


void setup()
{
    uint32_t tStart;
    char deviceID[20];
    char topic[30];
    char payload[75];
    float temperature;
    float humidity;
    float pressure;
    float batteryVoltage;

    // Initialize serial
    Serial.begin(115200);
    Serial.println();

    // Initialize I2C bus
    Wire.begin();
    Wire.setClock(400000);

    // Initialize sensor
    if (!bmx280.begin()) {
        Serial.println(F("Error: Could not detect sensor"));
        ESP.deepSleep(5 * 1000000UL);
    }

    // Set sampling - Recommended modes of operation
    //
    // Weather
    //  - forced mode, 1 sample / minute
    //  - pressure ×1, temperature ×1, humidity ×1
    //  - filter off
    //
    // Humidity sensing
    //  - forced mode, 1 sample / second
    //  - pressure ×0, temperature ×1, humidity ×1
    //  - filter off
    //
    // Indoor navigation
    //  - normal mode, t standby = 0.5 ms
    //  - pressure ×16, temperature ×2, humidity ×1
    //  - filter coefficient 16
    //
    // Gaming
    //  - forced mode, t standby = 0.5 ms
    //  - pressure ×1, temperature ×1, humidity ×1
    //  - filter off
    bmx280.setSampling(BMX280_MODE_FORCED,    // SLEEP, FORCED, NORMAL
                       BMX280_SAMPLING_X16,   // Temp:  NONE, X1, X2, X4, X8, X16
                       BMX280_SAMPLING_X16,   // Press: NONE, X1, X2, X4, X8, X16
                       BMX280_SAMPLING_X16,   // Hum:   NONE, X1, X2, X4, X8, X16 (BME280)
                       BMX280_FILTER_X16,     // OFF, X2, X4, X8, X16
                       BMX280_STANDBY_MS_500);// 0_5, 10, 20, 62_5, 125, 250, 500, 1000

    // Read temperature from sensor (blocking)
    temperature = bmx280.readTemperature();

    // Read humidity from sensor (blocking)
    humidity = bmx280.readHumidity();

    // Read pressure from sensor (blocking)
    pressure = bmx280.readPressure() / 100.0F;

    if ((temperature < -50.0) || (temperature > 80.0)) {
        Serial.println(F("Temperature error"));
        ESP.deepSleep(60 * 1000000UL);
    }
    if ((humidity < 0.0) || (humidity > 100.0)) {
        Serial.println(F("Humidity error"));
        ESP.deepSleep(60 * 1000000UL);
    }
    if ((pressure < 0.0) || (pressure > 10000.0)) {
        Serial.println(F("Pressure error"));
        ESP.deepSleep(60 * 1000000UL);
    }

    // Create MQTT unique device ID
    snprintf_P(deviceID, sizeof(deviceID), PSTR("ESP8266-%06X"), ESP.getChipId());

    // Create MQTT topic
    snprintf_P(topic, sizeof(topic), PSTR("%s/BME280"), deviceID);

    // Print info on power-on
    if (ESP.getResetInfoPtr()->reason != REASON_DEEP_SLEEP_AWAKE) {
        delay(500);
        Serial.println(F("Erriez ESP8266 MQTT BME280 example"));

        if (bmx280.getChipID() != CHIP_ID_BME280) {
            Serial.println(F("Error: BME280 not found"));
            ESP.deepSleep(5 * 1000000UL);
        }

        Serial.printf(PSTR("WiFi: %s, %s\n"), WIFI_SSID, WIFI_PASSWORD);
        Serial.printf(PSTR("MQTT server: %s:%d, %s\n"), MQTT_SERVER, MQTT_PORT, topic);

        // Set persistent on
        //WiFi.persistent(true);

        // WiFi station
        WiFi.mode(WIFI_STA);

        // Connect to WiFi
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }

    tStart = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (((millis() - tStart) > WIFI_TIMEOUT_MS)) {
            Serial.println(F("WiFi connect timeout"));
            ESP.deepSleep(60 * 1000000UL);
        }

        yield();
    }

    // MQTT connect
    if (!mqttClient.connect(deviceID, MQTT_USER, MQTT_PASSWORD)) {
        Serial.println(F("MQTT connect failed"));
        ESP.deepSleep(60 * 1000000UL);
    }

    if (!mqttClient.connected()) {
        Serial.println(F("MQTT disconnected"));
        ESP.deepSleep(60 * 1000000UL);
    }

    // Measure battery voltage (220k 1% resistor between battery and A0)
    batteryVoltage = map(analogRead(A0), 0, 1024, 0, 529) / 100.0;

    // Publish
    snprintf_P(payload, sizeof(payload),
               PSTR("{\"temperature\":%.02f,\"humidity\":%.02f,\"pressure\":%.02f,\"battery\":%.2f}"),
               temperature, humidity, pressure, batteryVoltage);

    Serial.println();
    Serial.print(payload);

    if (!mqttClient.publish(topic, payload, false)) {
        Serial.println(F(" FAILED"));
    }

    // MQTT disconnect
    mqttClient.disconnect();

    // Sleep 60 seconds
    ESP.deepSleep(60 * 1000000UL);
}

void loop()
{
}