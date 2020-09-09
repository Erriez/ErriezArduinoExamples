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
 * \brief Assertion example
 * \details
 *      This is a class example.
 *
 *      Source: https://github.com/Erriez/ArduinoLibraries
 */

/* Output:
 *     C++ Class example
 *
 *     Total 2 + 5 = 7
 *     Total 8 + 12 = 20
 */

class MyClass
{
public:
    // Constructor and initialize private variables _a and _b
    MyClass(int a=0, int b=0) : _a(a), _b(b) { }

    // Destructor
    ~MyClass() { }

    // Get private variables via function
    int getA() { return _a; }

    // Print total
    void printTotal() {
        Serial.print(F("Total "));
        Serial.print(getA());
        Serial.print(F(" + "));
        Serial.print(_b); // Access private variable _b directly
        Serial.print(F(" = "));
        Serial.println(getTotal());
    }

private:
    int _a; // Private variables
    int _b;

    // Calculate sum private variables
    int getTotal() {
        return _a + _b;
    }
};

// Create global object with
MyClass myGlobalObject(2, 5);


void setup()
{
    // Initialize serial port
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("\nC++ Class example\n"));

    // Print total of global object
    myGlobalObject.printTotal();

    // Create local object
    MyClass myLocalObject(8, 12);
    
    // Print total of local object
    myLocalObject.printTotal();
}

void loop()
{
}
