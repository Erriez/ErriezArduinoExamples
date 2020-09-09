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
 * \brief Erriez ESP8266 WiFi Webserver Access Point example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// SSID and password (Empty password for no password or at least 8 chars)
#define AP_SSID       "ESP8266_AP"
#define AP_PASSWORD   "thereisnospoon"
#define AP_PORT       80

// Create webserver object
ESP8266WebServer server(80);


// Visit http://192.168.4.1 in a web browser connected to this access point
void handleRoot() 
{
    // Print connected HTML message
    server.send(200, "text/html", "<h1>You are connected</h1>");
}

void setup() 
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);
    Serial.println("\nESP8266 WiFi Client Access Point example");

    // Configure access point
    Serial.print(F("Configuring access point..."));
    WiFi.softAP(AP_SSID, AP_PASSWORD);

    // Get access point IP
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // Set / request
    server.on("/", handleRoot);

    // Initialize HTTP server
    server.begin();
    Serial.println("HTTP server started");
}

void loop() 
{
    // Handle webserver in a loop
    server.handleClient();
}
