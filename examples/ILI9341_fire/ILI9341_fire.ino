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
#include "font_ChanceryItalic.h"

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
  tft.setTextColor(ILI9341_PINK);
  tft.setFont(Chancery_40_Italic);
  tft.setCursor(50,60);
  tft.println("Teensy 3.1");
  tft.setCursor(60,120);
  tft.println("ILI9341");  
  tft.setFont(Chancery_20_Italic);
  tft.setTextColor(ILI9341_CYAN);
  tft.setCursor(20,180);
  tft.println("Greetings to all members @");
  tft.setCursor(60,200);
  tft.println("forum.pjrc.com");    

  //add some Stars
  int i,y;
  for (i=0;i<200;i++) {
    y =  random(200);
    tft.drawPixel(random(cols), y, tft.color565(200-y,200-y,200-y));
  }
}


void loop(void) {
 tft.fire();
}
