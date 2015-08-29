/* Fire ILI9341, Teensy 3.1
 * Copyright (c) 2015, Frank Bösing, f.boesing(at)gmx.de,
 * 29.8.2015
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "SPI.h"
#include "ILI9341_t3.h"
#include "ILI9341_fire.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 20
#define TFT_CS 21
fireILI9341_t3 tft = fireILI9341_t3(TFT_CS, TFT_DC);

void setup() {

//CS Flash-Chip
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);

//CS SD-Karte
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  SPI.setSCK(14);
  SPI.setMOSI(7);
  SPI.setMISO(12);
  SPI.begin();


  tft.begin();
  tft.setRotation(3);

  tft.fillScreen(ILI9341_BLACK);
#if 0
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_GREENYELLOW);
  tft.println("Waiting for Arduino Serial Monitor...");
  tft.fillScreen(ILI9341_BLACK);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.print("Start..");
#endif
}


void loop(void) {
 tft.fire();
}

