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
 * \brief Erriez MHZ19B CO2 sensor example for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezMHZ19B
 *      Documentation:  https://erriez.github.io/ErriezMHZ19B
 */

/* Possible output:
    Erriez MH-Z19B CO2 Sensor example
    Warming up...
    ...
    Warming up...
      Firmware: 0443
      Range: 5000ppm
      Auto calibrate: On
    695 ppm
    696 ppm
    696 ppm
    ...
*/

#include <Adafruit_NeoPixel.h>
#include <ErriezRobotDyn4DigitDisplay.h>
#include <ErriezMHZ19B.h>
#include <SoftwareSerial.h>

#include "ESP8266WiFi.h"
extern "C" {
#include "user_interface.h"
}

// Pin defines MH-Z19B
#define MHZ19B_TX_PIN       D5
#define MHZ19B_RX_PIN       D6
SoftwareSerial mhzSerial(MHZ19B_TX_PIN, MHZ19B_RX_PIN);

// Create MHZ19B object
ErriezMHZ19B mhz19b(&mhzSerial);

// NeoPixel pins
#define NEO_PIXEL_PIN       D2
#define NUM_NEO_PIXELS      1
#define NEO_BRIGHTNESS      40

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEO_PIXELS, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// 7segment display
#define TM1637_BRIGHTNESS   2   // 0..7
#define TM1637_CLK_PIN      D3
#define TM1637_DIO_PIN      D4
RobotDyn4DigitDisplay display(TM1637_CLK_PIN, TM1637_DIO_PIN);

// FAN control (on/off)
#define FAN_PIN             D7
#define FAN_ON()            { digitalWrite(FAN_PIN, HIGH); }
#define FAN_OFF()           { digitalWrite(FAN_PIN, LOW); }


void setLED(uint16_t co2)
{
    if (co2 < 800) {
        strip.setPixelColor(0, strip.Color(0, 255, 0));
        strip.show();
    } else if (co2 < 1000) {
        strip.setPixelColor(0, strip.Color(128, 150, 0));
        strip.show();
    } else if (co2 < 1200) {
        strip.setPixelColor(0, strip.Color(255, 100, 0));
        strip.show();
    } else {
        for (uint8_t blink = 0; blink < 10; blink++) {
            strip.setPixelColor(0, strip.Color(0, 0, 0));
            strip.show();
            delay(200);
            strip.setPixelColor(0, strip.Color(255, 0, 0));
            strip.show();
            delay(200);
        }
    }
}

void printErrorCode(int16_t result)
{
    // Print error code
    switch (result) {
        case MHZ19B_RESULT_ERR_CRC:
            Serial.println(F("CRC error"));
            break;
        case MHZ19B_RESULT_ERR_TIMEOUT:
            Serial.println(F("RX timeout"));
            break;
        default:
            Serial.print(F("Error: "));
            Serial.println(result);
            break;
    }

    // Turn blue LED on
    strip.setPixelColor(0, strip.Color(0, 0, 255));
    strip.show();

    // Display error
    display.dec(result);
}

void setup()
{
    char firmwareVersion[5];

    // Initialize serial port to print diagnostics and CO2 output
    Serial.begin(115200);
    Serial.println(F("\nErriez MH-Z19B CO2 Sensor example"));

    // WiFi disconnect
    WiFi.disconnect();
    // Mode off 
    WiFi.mode(WIFI_OFF);
    // Turn off ESP8266 RF
    WiFi.forceSleepBegin();
    // Give RF section time to shutdown             
    delay(1);

    // Initialize senor software serial at fixed 9600 baudrate
    mhzSerial.begin(9600);

    // Initialize LED blue
    strip.begin();
    strip.setBrightness(NEO_BRIGHTNESS);
    strip.setPixelColor(0, strip.Color(0, 0, 255));
    strip.show();

    // Initialize TM1637
    display.begin();
    display.clear();
    display.setBrightness(TM1637_BRIGHTNESS);
    display.overflow();

    // Optional: Detect MH-Z19B sensor (check wiring / power)
    while ( !mhz19b.detect() ) {
        Serial.println(F("Detecting MH-Z19B sensor..."));
        delay(2000);
    };

    // Sensor requires 3 minutes warming-up after power-on
    while (mhz19b.isWarmingUp()) {
        Serial.println(F("Warming up..."));
        strip.setPixelColor(0, strip.Color(0, 0, 255));
        strip.show();
        delay(1000);
        strip.setPixelColor(0, strip.Color(0, 0, 0));
        strip.show();
        delay(1000);
    };

    // Optional: Print firmware version
    Serial.print(F("  Firmware: "));
    mhz19b.getVersion(firmwareVersion, sizeof(firmwareVersion));
    Serial.println(firmwareVersion);

    // Optional: Set CO2 range 2000ppm or 5000ppm (default) once
    // Serial.print(F("Set range..."));
    // mhz19b.setRange2000ppm();
    // mhz19b.setRange5000ppm();

    // Optional: Print operating range
    Serial.print(F("  Range: "));
    Serial.print(mhz19b.getRange());
    Serial.println(F("ppm"));

    // Optional: Set automatic calibration on (true) or off (false) once
    // Serial.print(F("Set auto calibrate..."));
    // mhz19b.setAutoCalibration(true);

    // Optional: Print Automatic Baseline Calibration status
    Serial.print(F("  Auto calibrate: "));
    Serial.println(mhz19b.getAutoCalibration() ? F("On") : F("Off"));

    // Initialize fan pin
    pinMode(FAN_PIN, OUTPUT);
}

void loop()
{
    int16_t result;

    // Minimum interval between CO2 reads is required
    if (mhz19b.isReady()) {
        // Read CO2 concentration from sensor
        result = mhz19b.readCO2();

        // Print result
        if (result < 0) {
            // An error occurred
            printErrorCode(result);
        } else {
            // Print CO2 concentration in ppm
            Serial.print(result);
            Serial.println(F(" ppm"));

            // Display CO2
            display.dec(result);

            // Set color LED with CO2
            setLED(result);

            // Turn fan on or off
            if (result > 775) {
                FAN_ON();
            } else {
                FAN_OFF();
            }
        }
    }
}
