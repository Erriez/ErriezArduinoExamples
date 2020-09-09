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
 * \brief Erriez ESP8266 Ticker example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include <Ticker.h>

// LED pin define
#define LED_PIN   BUILTIN_LED

// Create ticker object
Ticker ticker;


void blink()
{    
    // Toggle LED
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup() 
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);   
    Serial.println(F("\nESP8266 Ticker example"));
    
    // Set led pin as output
    pinMode(LED_PIN, OUTPUT);

    // Start ticker with 0.5 seconds
    ticker.attach(0.5, blink);

    // Stop ticker
    //ticker.detach();
}

void loop() 
{
}
