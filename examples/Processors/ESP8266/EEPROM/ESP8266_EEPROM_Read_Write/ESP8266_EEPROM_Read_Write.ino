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
 * \brief Erriez ESP8266 EEPROM Read Write example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */
 
#include <ESP8266WiFi.h>
#include <EEPROM.h>

typedef struct {
    char ssid[64];
    char password[64];
} WiFiCredentials_t;

WiFiCredentials_t credentialsWrite = { "myssid", "mypassword" };


void eepromInit(uint16_t eepromSize)
{
    // Initialize EEPROM
    EEPROM.begin(eepromSize);
}

void eepromRead(uint16_t addr, void *buffer, uint16_t bufferLength)
{
    // Read from EEPROM
    for (uint8_t i = 0; i < bufferLength; i++) {
        ((uint8_t *)buffer)[i] = EEPROM.read(addr + i);
    }
}

void eepromWrite(uint16_t addr, const void *buffer, uint16_t bufferLength)
{
    // Write to EEPROM buffer
    for (uint8_t i = 0; i < bufferLength; i++) {
        EEPROM.write(addr + i, ((uint8_t *)buffer)[i]);
    }
    
    // Commit to EEPROM
    EEPROM.commit();
}

void setup()
{
    WiFiCredentials_t credentialsRead;
  
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial
    Serial.begin(115200);
    Serial.println("\nESP8266 EEPROM example");

    // Initialize EEPROM
    Serial.println("Initializing EEPROM...");
    eepromInit(sizeof(credentialsWrite));

    // Write WiFi credentials to EEPROM
    Serial.println("Writing credentials to EEPROM...");
    eepromWrite(0, &credentialsWrite, sizeof(credentialsWrite));

    // Read WiFi credentials from EEPROM
    eepromRead(0, &credentialsRead, sizeof(credentialsRead));
    Serial.println("Wifi credentials from EEPROM:");
    Serial.printf("  SSID: %s\n", credentialsRead.ssid);
    Serial.printf("  PASSWORD: %s\n", credentialsRead.password);
}

void loop()
{
}
