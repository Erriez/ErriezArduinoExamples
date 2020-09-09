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
 * \brief Erriez ESP8266 EERPOM Clear example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */
 
#include <EEPROM.h>

// LED pin define
#define LED_PIN       LED_BUILTIN

// EEPROM size
#define EEPROM_SIZE   512


void setup() 
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);   
    Serial.print(F("\nESP8266 clearing EEPROM..."));
    
    // Turn LED on
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Initialize EEPROM
    EEPROM.begin(EEPROM_SIZE);
    
    // Write a 0xff to all Bytes of the EEPROM
    for (int i = 0; i < EEPROM_SIZE; i++) {
        EEPROM.write(i, 0xff);
    }

    // Commit, and release EEPROM contents RAM copy
    EEPROM.end();

    // Turn LED off
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    // Print done message
    Serial.println(F("Done!"));
}

void loop() 
{
}
