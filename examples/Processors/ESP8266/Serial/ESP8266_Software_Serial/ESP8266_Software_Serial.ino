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
 * \brief Erriez ESP8266 Software Serial example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include <SoftwareSerial.h>

// Pin defines
#define SW_SERIAL_TX_PIN    D5 // GPIO14
#define SW_SERIAL_RX_PIN    D6 // GPIO12
#define SW_SERIAL_INVERT    false

// Initialize software serial object
SoftwareSerial swSerial(SW_SERIAL_RX_PIN, SW_SERIAL_TX_PIN, SW_SERIAL_INVERT);


void setup() 
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);
    Serial.println(F("\nESP8266 software serial example"));

    // Set baudrate software serial
    swSerial.begin(9600);
}

void loop()
{
    char c;

    // Echo characters back
    if (swSerial.available()) {
        c = swSerial.read();
        Serial.println(c);
    }
}
