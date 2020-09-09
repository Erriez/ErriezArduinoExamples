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
 * \brief Arduino JSON example
 * \details
 *    Source: https://github.com/Erriez/ErriezArduinoExamples
 */

/* Output:
    ArduinoJson ESP8266 config file example
    Writing config file...
    {
      "mqtt_server": "test.nl",
      "mqtt_port": "8080",
      "mqtt_token": "YOUR_MQTT_TOKEN"
    }
    Reading config file...
    {
      "mqtt_server": "test.nl",
      "mqtt_port": "8080",
      "mqtt_token": "YOUR_MQTT_TOKEN"
    }
    Parsed JSON:
      mqtt_server: test.nl
      mqtt_port: 8080
      mqtt_token: YOUR_MQTT_TOKEN
 */

#include <FS.h>
#include <ArduinoJson.h> // https://arduinojson.org/

char mqtt_server[40] = "test.nl";
char mqtt_port[6] = "8080";
char mqtt_token[34] = "YOUR_MQTT_TOKEN";

#define CONFIG_FILE   "/config.json"
#define OVERWRITE     false


void writeConfigFile()
{
    Serial.println("Writing config file...");
        
    StaticJsonDocument<256> doc;
    doc["mqtt_server"] = mqtt_server;
    doc["mqtt_port"] = mqtt_port;
    doc["mqtt_token"] = mqtt_token;

    // Open config file with write access
    File configFile = SPIFFS.open(CONFIG_FILE, "w");
    if (!configFile) {
        Serial.println("Failed to open config file for writing");
    }

    // Print the result
    serializeJsonPretty(doc, Serial);
    Serial.println();
    
    // Serialize JSON to file
    if (serializeJson(doc, configFile) == 0) {
        Serial.println("Failed to write to file");
    }

    // Close the file
    configFile.close();
}

void loadConfigFile()
{
    if (!SPIFFS.exists(CONFIG_FILE)) {
        Serial.println("Error: Config file does not exist");
        return;
    }
    
    Serial.println("Reading config file...");

        File configFile = SPIFFS.open(CONFIG_FILE, "r");
    if (!configFile) {
        Serial.println("Failed to open config file");
        return;
    } 

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, configFile);
    configFile.close();
    
    if (error) {
        Serial.println("Failed to load json config");
        return;
    }

    // Print the result
    serializeJsonPretty(doc, Serial);
    Serial.println();

    strcpy(mqtt_server, doc["mqtt_server"]);
    strcpy(mqtt_port, doc["mqtt_port"]);
    strcpy(mqtt_token, doc["mqtt_token"]);

    Serial.println("Parsed JSON:");
    Serial.print("  mqtt_server: ");
    Serial.println(mqtt_server);
    Serial.print("  mqtt_port: ");
    Serial.println(mqtt_port);
    Serial.print("  mqtt_token: ");
    Serial.println(mqtt_token);
}

void setup() 
{
    // Initialize serial
    Serial.begin(115200);
    Serial.println(F("\nArduinoJson ESP8266 config file example"));
    
    // Clean FS, for testing
#if 1
    Serial.println(F("Formatting FS..."));
    SPIFFS.format();
#endif

    // Initialize SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println(F("Failed to mount FS"));
        return;
    }

    // Write config file
    if (OVERWRITE || !SPIFFS.exists(CONFIG_FILE)) {
        writeConfigFile();
    }

    // Load config file
    loadConfigFile();
}

void loop() 
{
}
