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
 * \brief Analog LM35 temperature sensor example for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezLM35
 *      Documentation:  https://erriez.github.io/ErriezLM35
 */

#include <ErriezLM35.h>

// Connect LM35 data pin to Arduino DIGITAL pin
#define LM35_PIN   A0

// This library changes ADC to 1.1V internal reference voltage which affects all analog pins.
LM35 lm35 = LM35(LM35_PIN);


void setup()
{
    // Initialize serial port
    Serial.begin(115200);
    while(!Serial) {
        ;
    }
    Serial.println(F("Analog LM35 temperature sensor example\n"));
}

void loop()
{
    // Read unsigned temperature from sensor
    uint16_t lm35_temp = lm35.readTemperature();

    // Print temperature
    Serial.print(F("LM35: "));
    Serial.print(lm35_temp / 10);
    Serial.print(F("."));
    Serial.print(lm35_temp % 10);

    // Print degree celsius symbols
    // Choose if (1) for normal or if (0) for extended ASCII degree symbol
    if (1) {
        // Print *C characters which are displayed correctly in the serial
        // terminal of the Arduino IDE
        Serial.println(F(" *C"));
    } else {
        // Note: Extended characters are not supported in the Arduino IDE and
        // displays ?C. This is displayed correctly with other serial terminals
        // such as Tera Term.
        // Degree symbol is ASCII code 248 (decimal).
        char buf[4];
        snprintf_P(buf, sizeof(buf), PSTR(" %cC"), 248);
        Serial.println(buf);
    }

    // Wait some time
    delay(2000);
}
