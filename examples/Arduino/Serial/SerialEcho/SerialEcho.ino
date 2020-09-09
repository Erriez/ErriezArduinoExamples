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
 * \brief Arduino Serial Echo example
 * \details
 *      Arduino IDE | Tools | Serial Monitor:
 *          - Set baudrate to "115200 baud"
 *          - Type some text and click "Send"
 *
 *      Source: https://github.com/Erriez/ArduinoLibraries
 */

#include <Wire.h>


void setup(void)
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize Serial
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("\nSerial echo example"));
}

void loop() 
{
    char c;

    // Check if data received
    while (Serial.available()) {
        // Read Byte
        c = Serial.read();

        // Write Byte
        Serial.write(c);
    }
}
