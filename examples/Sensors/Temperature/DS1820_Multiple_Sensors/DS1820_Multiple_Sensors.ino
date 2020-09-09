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
 * \brief Erriez DS1820 Multiple Temperature Sensors example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */
 
#include <OneWire.h>
#include <DallasTemperature.h>

// One wire pin
#define ONE_WIRE_BUS    2  // ESP8266: GPIO pin number

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds1820(&oneWire);


void setup(void)
{
    uint8_t addr[8];

    // Startup delay to initialize serial port
    delay(500);
    
    Serial.begin(115200);
    Serial.println(F("\nMultiple DS1820 temperature sensors example"));

    // Initialise bus
    ds1820.begin();
    // Set waitForConversion flag
    ds1820.setWaitForConversion(true);
    // Set global resolution to 9, 10, 11, or 12 bits
    ds1820.setResolution(12);

    // Print addresses
    Serial.println(F("DS1820 devices:"));
    for (int index = 0; index < ds1820.getDeviceCount(); index++) {
        if (ds1820.getAddress(addr, index)) {
            Serial.print(F("  Sensor "));
            Serial.print(index);
            Serial.print(F(": "));
            for (int i = 0; i < sizeof(addr); i++) {
                if (addr[i] < 0x10) { Serial.print(F("0")); }
                Serial.print(addr[i], HEX);
                Serial.print(F(" "));
            }
            Serial.println();
        }
    }
}

void loop(void)
{
    static unsigned long tLast;
    unsigned long tNow;
    
    // Start temperature conversion for all devices on the bus
    ds1820.requestTemperatures();

    // Wait at least conversion time
    delay(1000);
    
    // Print temperatures
    for (uint8_t index = 0; index < ds1820.getDeviceCount(); index++) {
        Serial.print(ds1820.getTempCByIndex(index), 2);
        Serial.print(F(" "));
    }
    Serial.println();
}

