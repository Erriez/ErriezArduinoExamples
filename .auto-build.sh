#/bin/bash

# Automatic build script
#
# To run locally, execute:
# sudo apt install doxygen graphviz texlive-latex-base texlive-latex-recommended texlive-pictures texlive-latex-extra

# Exit immediately if a command exits with a non-zero status.
set -e

echo "Starting auto-build script..."


function autobuild()
{
    # Set environment variables
    BOARDS_AVR="--board uno --board leonardo"
    BOARDS_ARM="--board due"
    ESP8266="--board d1_mini"
    ESP32="--board lolin_d32"

    echo "Installing library dependencies"
    platformio lib --global install https://github.com/adafruit/Adafruit_NeoPixel
    platformio lib --global install https://github.com/bblanchon/ArduinoJson
    platformio lib --global install https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino
    platformio lib --global install https://github.com/knolleary/pubsubclient
    platformio lib --global install "paulstoffregen/OneWire@^2.3.5"
    platformio lib --global install "bitbucket-fmalpartida/LiquidCrystal"
    platformio lib --global install https://github.com/milesburton/Arduino-Temperature-Control-Library
    platformio lib --global install https://github.com/Erriez/ErriezBH1750
    platformio lib --global install https://github.com/Erriez/ErriezBMX280
    platformio lib --global install https://github.com/Erriez/ErriezDHT22
    platformio lib --global install https://github.com/Erriez/ErriezDS1302
    platformio lib --global install https://github.com/Erriez/ErriezDS1307
    platformio lib --global install https://github.com/Erriez/ErriezDS3231
    platformio lib --global install https://github.com/Erriez/ErriezINA219
    platformio lib --global install https://github.com/Erriez/ErriezLM35
    platformio lib --global install https://github.com/Erriez/ErriezMHZ19B
    platformio lib --global install https://github.com/Erriez/ErriezRobotDyn4DigitDisplay

    echo "Install ESPSoftwareSerial into framework-arduinoespressif32 to prevent conflicts with generic name SoftwareSerial"
    mkdir -p ~/.platformio/packages/framework-arduinoespressif32/libraries
    platformio lib --storage-dir ~/.platformio/packages/framework-arduinoespressif32/libraries install "ESPSoftwareSerial"

    echo "Building cross-platform examples..."
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/ADC/ADCSerialPlotter/ADCSerialPlotter.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/Build/BuildMarcos/BuildMarcos.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/ExternalInterrupts/InterruptPin/InterruptPin.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/I2C/I2C_Probe/I2C_Probe.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/IO/digitalRead/digitalRead.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/IO/digitalWrite/digitalWrite.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/LED/Blink/Blink.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/Math/map/map.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266}          examples/Arduino/PWM/PWM/PWM.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/Serial/Print32BitVariables/Print32BitVariables.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Arduino/Serial/SerialEcho/SerialEcho.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/C++/Assert/Assert.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/C++/Class/Class.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/C/stdlib/stdlib_itoa/stdlib_itoa.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/C/time/mktime/mktime.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/C/time/time_h/time_h.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/DataProcessing/JSON/ArduinoJson/ArduinoJson.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/DataProcessing/JSON/ArduinoJson_Filtered/ArduinoJson_Filtered.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Display/Character/LCD2004_I2C/LCD2004_I2C.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/CO2/MH-Z19B_CO2_Sensor/MH-Z19B_CO2_Sensor.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/Humidity/DHT22/DHT22.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/Light/BH1750_Light_Sensor/BH1750_Light_Sensor.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/Movement/PIR/PIR.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/Temperature/DS1820_Basic/DS1820_Basic.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/Temperature/DS1820_Multiple_Sensors/DS1820_Multiple_Sensors.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/Temperature/LM35/LM35.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/Voltage/INA219_Power_Sensor/INA219_Power_Sensor.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Sensors/Weather/BMX280/BMX280.ino
    platformio ci --lib="." ${BOARDS_AVR}               ${ESP8266} ${ESP32} examples/Timing/RTC/DS1302/DS1302.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Timing/RTC/DS1307/DS1307.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${ESP8266} ${ESP32} examples/Timing/RTC/DS3231/DS3231.ino

    echo "Building ESP8266 examples..."
    platformio ci --lib="." ${ESP8266} examples/IOT/InfluxDB/InfluxDB_HTTP_WiFi_RSSI/InfluxDB_HTTP_WiFi_RSSI.ino
    platformio ci --lib="." ${ESP8266} examples/IOT/MQTT/MQTT_Publish_WiFi_RSSI/MQTT_Publish_WiFi_RSSI.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/ADC/ESP8266_ADC_VCC/ESP8266_ADC_VCC.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/ChipID/ESP8266_Chip_ID/ESP8266_Chip_ID.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/EEPROM/ESP8266_EEPROM_Clear/ESP8266_EEPROM_Clear.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/EEPROM/ESP8266_EEPROM_Read_Write/ESP8266_EEPROM_Read_Write.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/IO/ESP8266_Interrupt_Pin/ESP8266_Interrupt_Pin.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/JSON/ArduinoJson_Configfile/ArduinoJson_Configfile.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/LED/ESP8266_LED_Blink/ESP8266_LED_Blink.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/LowPower/ESP8266_Low_Power_Blink/ESP8266_Low_Power_Blink.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Reset/ESP8266_CPU_Reset/ESP8266_CPU_Reset.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Reset/ESP8266_Reset_Cause/ESP8266_Reset_Cause.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Serial/ESP8266_Software_Serial/ESP8266_Software_Serial.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Serial/ESP8266_Swap_Pins/ESP8266_Swap_Pins.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Sleep/ESP8266_Normal_Sleep/ESP8266_Normal_Sleep.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/SPI/ESP8266_SPI/ESP8266_SPI.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/SPIFS/ESP8266_SPIFS/ESP8266_SPIFS.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Timer/ESP8266_Hardware_Timer_Interval/ESP8266_Hardware_Timer_Interval.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Timer/ESP8266_Ticker/ESP8266_Ticker.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Watchdog/ESP8266_Watchdog_Refresh/ESP8266_Watchdog_Refresh.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/Webserver/ESP8266_Webserver_Access_Point/ESP8266_Webserver_Access_Point.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/WiFiClientSecure/Email/ESP8266_Email_SSL/ESP8266_Email_SSL.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/WiFi/ESP8266_MAC_Address/ESP8266_MAC_Address.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/WiFi/ESP8266_NTP/ESP8266_NTP.ino
    platformio ci --lib="." ${ESP8266} examples/Processors/ESP8266/WiFi/ESP8266_WiFi_Scan/ESP8266_WiFi_Scan.ino

    platformio ci --lib="." ${ESP8266} examples/Projects/ESP8266/MHZ19B-NeoPixel-TM1637/MHZ19B-NeoPixel-TM1637.ino

    echo "Building ATMega328 examples..."
    platformio ci --lib="." ${BOARDS_AVR} examples/Projects/ATMega328/DS1820_SDCard_Logger/DS1820_SDCard_Logger.ino
    platformio ci --lib="." ${BOARDS_AVR} examples/Projects/ATMega328/PIR_LED_Strip/PIR_LED_Strip.ino
}

autobuild
