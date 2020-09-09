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
 * \brief Erriez ESP8266 SPI example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include <SPI.h>

// Create SPI object
SPISettings settings(1 * 1000000UL, LSBFIRST, SPI_MODE0);


void setup() 
{
  // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);
    Serial.println(F("\nESP8266 SPI pins:"));
    Serial.print(F("  SS:   GPIO")); Serial.println(SS);
    Serial.print(F("  SCK:  GPIO")); Serial.println(SCK);
    Serial.print(F("  MOSI: GPIO")); Serial.println(MOSI);
    Serial.print(F("  MISO: GPIO")); Serial.println(MISO);
    
//    pinMode(SS, OUTPUT);
//    pinMode(SCK, OUTPUT);
//    pinMode(MOSI, OUTPUT);
//    pinMode(MISO, OUTPUT);
//    
//    while (1) {
//        digitalWrite(SS, HIGH);
//        digitalWrite(SS, LOW);
//        digitalWrite(SCK, HIGH);
//        digitalWrite(SCK, LOW);
//        digitalWrite(MOSI, HIGH);
//        digitalWrite(MOSI, LOW);
//        digitalWrite(MISO, HIGH);
//        digitalWrite(MISO, LOW);
//        delay(1);
//    }

    // Initialize chip select
    digitalWrite(SS, HIGH);
    pinMode(SS, OUTPUT);

    // Initialize SPI
    SPI.begin();
}

void loop() 
{
    // Transfer a character over SPI
    digitalWrite(SS, LOW);
    SPI.beginTransaction(settings);
    SPI.transfer('A');
    SPI.endTransaction();
    digitalWrite(SS, HIGH);

    // Wait some time
    delay(100);
}
