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
 * \brief Arduino JSON filtered example
 * \details
 *    Source: https://github.com/Erriez/ErriezArduinoExamples
 */

/* Output:
    ArduinoJson filtered example
    RAW:
    {
      "cod": "200",
      "message": 0,
      "list": [
        {
          "dt": 1581498000,
          "main": {
            "temp": 3.23,
            "feels_like": -3.63,
            "temp_min": 3.23,
            "temp_max": 4.62,
            "pressure": 1014,
            "sea_level": 1014,
            "grnd_level": 1010,
            "humidity": 58,
            "temp_kf": -1.39
          },
          "weather": [
            {}
          ]
        }
      ]
    }
    Filtered:
    {
      "list": [
        {
          "dt": 1581498000,
          "main": {
            "temp": 3.23
          }
        },
        {
          "dt": 1581508800,
          "main": {
            "temp": 6.09
          }
        }
      ]
    }
 */

#include <ArduinoJson.h> // https://arduinojson.org


void setup() 
{
    // The huge input: an extract from OpenWeatherMap response
    const __FlashStringHelper* input_json = F(
        "{\"cod\":\"200\",\"message\":0,\"list\":[{\"dt\":1581498000,\"main\":{"
        "\"temp\":3.23,\"feels_like\":-3.63,\"temp_min\":3.23,\"temp_max\":4.62,"
        "\"pressure\":1014,\"sea_level\":1014,\"grnd_level\":1010,\"humidity\":"
        "58,\"temp_kf\":-1.39},\"weather\":[{\"id\":800,\"main\":\"Clear\","
        "\"description\":\"clear "
        "sky\",\"icon\":\"01d\"}],\"clouds\":{\"all\":0},\"wind\":{\"speed\":6."
        "19,\"deg\":266},\"sys\":{\"pod\":\"d\"},\"dt_txt\":\"2020-02-12 "
        "09:00:00\"},{\"dt\":1581508800,\"main\":{\"temp\":6.09,\"feels_like\":-"
        "1.07,\"temp_min\":6.09,\"temp_max\":7.13,\"pressure\":1015,\"sea_"
        "level\":1015,\"grnd_level\":1011,\"humidity\":48,\"temp_kf\":-1.04},"
        "\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"clear "
        "sky\",\"icon\":\"01d\"}],\"clouds\":{\"all\":9},\"wind\":{\"speed\":6."
        "64,\"deg\":268},\"sys\":{\"pod\":\"d\"},\"dt_txt\":\"2020-02-12 "
        "12:00:00\"}],\"city\":{\"id\":2643743,\"name\":\"London\",\"coord\":{"
        "\"lat\":51.5085,\"lon\":-0.1257},\"country\":\"GB\",\"population\":"
        "1000000,\"timezone\":0,\"sunrise\":1581492085,\"sunset\":1581527294}}");
  
    // Initialize serial port
    Serial.begin(115200);
    Serial.println(F("\nArduinoJson filtered example"));
    
    // Print the result
    StaticJsonDocument<400> raw;
    deserializeJson(raw, input_json);
    Serial.println("RAW:");
    serializeJsonPretty(raw, Serial);
    Serial.println();
  
    // The filter: it contains "true" for each value we want to keep
    StaticJsonDocument<200> filter;
    filter["list"][0]["dt"] = true;
    filter["list"][0]["main"]["temp"] = true;
  
    // Deserialize the document
    StaticJsonDocument<400> doc;
    deserializeJson(doc, input_json, DeserializationOption::Filter(filter));
  
    // Print the result
    Serial.println("Filtered:");
    serializeJsonPretty(doc, Serial);
}

void loop() 
{
}
