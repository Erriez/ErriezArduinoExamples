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
 * \brief Erriez ESP8266 SPIFS example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

/*
ESP8266 SPIFS example
Mounting FS...
SPIFFS info:
  totalBytes: 2949250
  usedBytes: 1506
  blockSize: 8192
  pageSize: 256
  maxOpenFiles: 5
  maxPathLength: 32
Files in /:
  /test/hello.txt    12
Reading from /test/hello.txt: Hello world!
Unmount completed
*/

#include "FS.h"


static void printFSInfo(void)
{
    FSInfo fs_info;

    Serial.println(F("SPIFFS info:"));

    // Get SPI Flash Filesystem info
    SPIFFS.info(fs_info);

    Serial.print(F("  totalBytes: "));
    Serial.println(fs_info.totalBytes);

    Serial.print(F("  usedBytes: "));
    Serial.println(fs_info.usedBytes);

    Serial.print(F("  blockSize: "));
    Serial.println(fs_info.blockSize);

    Serial.print(F("  pageSize: "));
    Serial.println(fs_info.pageSize);

    Serial.print(F("  maxOpenFiles: "));
    Serial.println(fs_info.maxOpenFiles);

    Serial.print(F("  maxPathLength: "));
    Serial.println(fs_info.maxPathLength);
}

static void formatFS(void)
{
    Serial.print(F("Formatting flash..."));
    if (SPIFFS.format() != true) {
        Serial.print(F("Failed"));
    } else {
        Serial.print(F("OK"));
    }
}

static void printDirectory(char *path)
{
    File f;
    Dir d;

    Serial.print(F("Files in "));
    Serial.print(path);
    Serial.println(F(":"));

    d = SPIFFS.openDir(path);
    while (d.next()) {
        Serial.print(F("  "));
        Serial.print(d.fileName());
        f = d.openFile("r");
        Serial.print("\t\t");
        Serial.println(f.size());
    }
}

static void printFile(char *filename)
{
    File f;

    Serial.print(F("Reading from "));
    Serial.print(filename);
    Serial.print(F(": "));

    f = SPIFFS.open(filename, "r");
    if (f == false) {
        Serial.println(F("Failed"));
        return;
    }

    while (f.available()) {
        Serial.write(f.read());
    }
    f.close();

    Serial.println("");
}

static void writeFile(char *filename, char *str)
{
    File f;

    Serial.print(F("Writing string to "));
    Serial.print(filename);
    Serial.print(F("..."));

    f = SPIFFS.open(filename, "w");
    if (f == false) {
        Serial.println(F("Failed"));
        return;
    }

    f.print(str);
    f.close();

    Serial.println(F("OK"));
}

void setup(void)
{
    char *filename = "/test/hello.txt";
    File root;

    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);
    Serial.println(F("\nESP8266 SPIFS example"));

    // Mount FS
    Serial.println(F("Mounting FS..."));
    if (!SPIFFS.begin()) {
        Serial.println(F("Failed to mount file system"));
        return;
    }

    printFSInfo();
    //formatFS();

    printDirectory("/");

    if (SPIFFS.exists(filename) == false) {
        writeFile(filename, "Hello world!");
    }
    printFile(filename);

    SPIFFS.end();

    Serial.println(F("Unmount completed"));
}

void loop()
{
}
