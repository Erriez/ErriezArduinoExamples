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
 * \brief Arduino I2C Probe example
 * \details
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
    Serial.println(F("\nI2C Probe example"));

    // Initialize I2C
    Wire.begin();

    // Set I2C clock speed
    Wire.setClock(100000);
}

void loop(void)
{
    byte error, address;
    int nDevices;
    
    Serial.println(F("Scanning..."));
    
    nDevices = 0;
    for (address = 1; address < 127; address++) {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if (error == 0) {
            Serial.print(F("I2C device found at address 0x"));
            if (address < 16) {
               Serial.print("0");
            }
            Serial.print(address,HEX);
            Serial.println(" !");
            
            nDevices++;
        } else if (error==4) {
            Serial.print(F("Unknow error at address 0x"));
            if (address < 16) {
                Serial.print(F("0"));
            }
            Serial.println(address,HEX);
        }
    }
    if (nDevices == 0) {
        Serial.println(F("No I2C devices found\n"));
    } else {
        Serial.println(F("done\n"));
    }
    
    delay(1000); // wait 5 seconds for next scan
}

