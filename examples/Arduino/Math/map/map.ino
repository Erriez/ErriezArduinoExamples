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
 * \brief Arduino map() example
 * \details
 *      Connect a potentiometer middle pin to an ADC pin and outer pins to VCC/GND.
 * 
 *      Source: https://github.com/Erriez/ArduinoLibraries
 */

// Pin defines
#define ANALOG_PIN    A0


void setup(void)
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize Serial
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("\nmap() ADC example"));
}

void loop(void)
{
    int adcValue;
    int mappedValue;

    // Read ADC pin
    adcValue = analogRead(ANALOG_PIN);

    // Map ADC value 0..1023 to values between 100..200
    mappedValue = map(adcValue, 0, 1023, 100, 200);

    // Print value
    Serial.println(mappedValue);

    // Wait some time
    delay(250);
}
