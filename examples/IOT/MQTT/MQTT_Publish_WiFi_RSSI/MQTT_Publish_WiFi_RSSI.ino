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
 * \brief Erriez MQTT Publish WiFi RSSI example
 * \details
 *      This example uses PubSubClient library for Arduino to log WiFi RSSI 
 *      (Received Signal Strength Indicator).
 *      
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi connection
#define WIFI_SSID "***"
#define WIFI_PASSWORD "***"

// MQTT connection
#define MQTT_SERVER             "192.168.0.1"
#define MQTT_USER               "admin"
#define MQTT_PASSWORD           "admin"

// MQTT topics
#define MQTT_TOPIC_RSSI         "esp8266/rssi"
#define MQTT_CLIENT_ID          "ESP8266"
#define MQTT_PUBLISH_DELAY_SEC  30

// Create objects
WiFiClient espClient;
PubSubClient mqttClient(espClient);


void deepSleep(uint16_t sec)
{
    Serial.print("Deepsleep ");
    Serial.print(sec);
    Serial.println("s...");
    Serial.flush();

    ESP.deepSleep(sec * 1000000UL); 
}

void mqttPublish(long rssi)
{
    // Publish
    char data[60];
    
    snprintf(data, sizeof(data), "{\"rssi\": %ld}", rssi);

    Serial.print("MQTT data: ");
    Serial.println(data);

    Serial.print("MQTT publish...");    
    if (mqttClient.publish(MQTT_TOPIC_RSSI, data, false)) {
        Serial.println("OK");
    } else {
        Serial.println("failed");
    }

    // Wait until all data transmitted
    delay(500);
}

void printMQTTError(int8_t code)
{
    switch (code) {
        case MQTT_CONNECTION_TIMEOUT:
            Serial.print("timeout");
            break;
        case MQTT_CONNECTION_LOST:
            Serial.print("connection lost");
            break;
        case MQTT_CONNECT_FAILED:
            Serial.print("connect failed");
            break;
        case MQTT_DISCONNECTED:
            Serial.print("disconnected");
            break;
        case MQTT_CONNECTED:
            Serial.print("connected");
            break;
        case MQTT_CONNECT_BAD_PROTOCOL:
            Serial.print("bad protocol");
            break;
        case MQTT_CONNECT_BAD_CLIENT_ID:
            Serial.print("bad client ID");
            break;
        case MQTT_CONNECT_UNAVAILABLE:
            Serial.print("unavailable");
            break;
        case MQTT_CONNECT_BAD_CREDENTIALS:
            Serial.print("bad credentials");
            break;
        case MQTT_CONNECT_UNAUTHORIZED:
            Serial.print("unauthorized");
            break;
        default:
            Serial.print("unknown");
    }

    Serial.print(": ");
    Serial.println(code);
}

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

void initMQTT()
{
    // Setup MQTT server
    mqttClient.setServer(MQTT_SERVER, 1883);

    // Connect
    if (!mqttClient.connected()) {
        Serial.print("Connecting MQTT...");
    
        // Attempt to connect
        if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("OK");
        } else {
            printMQTTError(mqttClient.state());
            deepSleep(MQTT_PUBLISH_DELAY_SEC);
        }
    }

    // Process MQTT receive
    mqttClient.loop();    
}

void setup() 
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial
    Serial.begin(115200);
    Serial.println(F("\nMQTT ESP8266 WiFi RSSI example"));
  
    // Connect WiFi
    connectWifi();

    // Initialize MQTT
    initMQTT();

    // Publish sensor values
    mqttPublish(WiFi.RSSI());

    // Deep sleep
    deepSleep(MQTT_PUBLISH_DELAY_SEC);
}

void loop()
{

}
