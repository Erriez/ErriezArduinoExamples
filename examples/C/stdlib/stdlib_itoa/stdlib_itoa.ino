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
 * \brief C stdlib.h itoa example
 * \details
 *      Source:         https://github.com/Erriez/ErriezArduinoExamples
 */

/* Output:
 *   C stdlib itoa() example
 *
 *   Decimal value:12345
 *   Hexadecimal value: 0x3039
 *   Binary value: 0b11000000111001
 */

#include <stdio.h>


void setup() 
{
    char buffer[20];
    int a;

    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial
    Serial.begin(115200);
    Serial.println(F("\nC stdlib itoa() example\n"));

    // Set value
    a = 12345;

    // Print decimal value
    itoa(a, buffer, 10);
    Serial.print(F("Decimal value: "));
    Serial.println(buffer);

    // Print hexadecimal
    itoa(a, buffer, 16);
    Serial.print(F("Hexadecimal value: 0x"));
    Serial.println(buffer);
    
    // Print binary value
    itoa(a, buffer, 2);
    Serial.print(F("Binary value: 0b"));
    Serial.println(buffer);
}

void loop()
{
}
