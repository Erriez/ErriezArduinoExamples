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
 * \brief Erriez ESP8266 Email SSL example
 * \details
 *      To retrieve SSL fingerprint:
 *          Tools | Debug level: SSL
 *          Tools | Debug port: Serial
 * 
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char *ssid = "***";
const char *password = "***";
const char *smtpServer = "smtp.myserver.com";
const int smtpPort = 465;
const char *userBase64 = ""; // https://www.base64encode.org
const char *userPasswordBase64 = "";
const char *emailFrom = "MAIL From: your-email@server.com";
const char *emailTo = "RCPT TO: your-email@server.com";
const char *emailSubject = "Subject: Sensor value";

// SHA1 fingerprint of the certificate
const char* fingerprint = "00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00";


byte eRcv(WiFiClientSecure client)
{
    byte respCode;
    byte thisByte;
    int loopCount = 0;

    while (!client.available()) {
        delay(1);
        loopCount++;
        if (loopCount > 10000) {
            client.stop();
            Serial.println(F("Timeout"));
            return 0;
        }
    }

    respCode = client.peek();
    while (client.available()) {
        thisByte = client.read();
        Serial.write(thisByte);
    }
    if (respCode >= '4') {
        return 0;
    }

    return 1;
}

byte sendEmail(int sensorValue)
{
    WiFiClientSecure client;

    // Force timeout
    client.setTimeout(10000);
    // Set fingerprint, or insecure (not recommended)
    client.setFingerprint(fingerprint);
    // client.setInsecure();

    // Connect to SMTP server
    Serial.printf_P(PSTR("Connecting to %s:%d..."), smtpServer, smtpPort);
    if (client.connect(smtpServer, smtpPort) == 1) {
        Serial.println(F("OK"));
    } else {
        Serial.println(F("Failed"));
        return 0;
    }

    // Send email
    if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending EHLO")); client.println("EHLO 1.2.3.4"); if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending login")); client.println("AUTH LOGIN"); if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending User base64")); client.println(userBase64); if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending Password base64")); client.println(userPasswordBase64); if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending From")); client.println(emailFrom); if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending To")); client.println(emailTo); if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending DATA")); client.println(F("DATA")); if (!eRcv(client)) return 0;
    client.println(emailSubject);
    client.println(F("\r\n"));
    client.print(F("Sensor value is now: ")); client.println(sensorValue);
    client.println(F(".")); if (!eRcv(client)) return 0;
    Serial.println(F("--- Sending QUIT"));
    client.println(F("QUIT")); if (!eRcv(client)) return 0;
    client.stop();

    return 1;
}

void connectWifi()
{
    // Connect to WiFi
    Serial.printf_P(PSTR("Connecting to %s"), ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(F("OK"));
}

void setup()
{
    int sensorValue;
    
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);   
    Serial.println(F("\nESP8266 Email SSL example"));

    // Connect with WiFi
    connectWifi();

    // Read sensor value
    sensorValue = analogRead(A0);
    Serial.printf_P(PSTR("Send sensor value: %d\n"), sensorValue);

    // Send email
    if (sendEmail(sensorValue)) {
        Serial.println(F("Email sent"));
    } else {
        Serial.println(F("Send email failed"));
    }
}

void loop()
{
}
