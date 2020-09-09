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
 * \brief Erriez Arduino build macro example
 * \details
 *    Source: https://github.com/Erriez/ErriezArduinoExamples
 */

/*
The following build-macro's can be used in Arduino libraries and sketches:
    // Architecture:
     __AVR__
    ARDUINO_ARCH_AVR
    ARDUINO_ARCH_SAM
    ARDUINO_ARCH_ESP8266
    ARDUINO_ARCH_ESP32

    // Board:
    ARDUINO_AVR_UNO
    ARDUINO_AVR_NANO
    ARDUINO_AVR_MICRO
    ARDUINO_AVR_MINI
    ARDUINO_AVR_PRO
    ARDUINO_AVR_MEGA2560
    ARDUINO_AVR_LEONARDO
    ARDUINO_SAM_DUE
    ARDUINO_ESP8266_WEMOS_D1MINI
    ARDUINO_ESP8266_NODEMCU
    ARDUINO_LOLIN32

    // CPU:
    __AVR_ATmega328P__
    __AVR_ATmega2560__
    __AVR_ATmega32U4__
 */

void setup()
{
    // Initialize serial
    Serial.begin(115200);

    // Print target
#if defined(ARDUINO_ARCH_AVR)
    Serial.println(F("I'm built for an AVR target!"));
#elif defined(ARDUINO_SAM_DUE)
    Serial.println(F("I'm built for an ARM Cortex M0 target!"));
#elif defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
    Serial.println(F("I'm built for an ESP8266 or ESP32 target!"));
#else
#error "Unknown build macro )-;"
#endif
}

void loop()
{
}