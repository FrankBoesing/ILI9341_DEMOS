/* Mandelbrot ILI9341, Teensy 3.1
 * Copyright (c) 2015, Frank Bösing, f.boesing(at)gmx.de,
 * 31.10.2015
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

#ifndef mandelbrotILI9341_t3_h_
#define mandelbrotILI9341_t3_h_

#define MAX_X 320
#define MAX_Y 240

#define ITERATIONS  255

#define FIXSIZE 25
#define mul(a,b) ((((long long)a)*(b))>>FIXSIZE)
#define fixpt(a) ((long)(((a)*(1<<FIXSIZE))))
#define integer(a) (((a)+(1<<(FIXSIZE-1)))>>FIXSIZE)


//un-protect some functions:
class mandelbrotILI9341_t3: public ILI9341_t3
{
public:

 mandelbrotILI9341_t3(uint8_t _CS, uint8_t _DC, uint8_t _RST = 255, uint8_t _MOSI=11, uint8_t _SCLK=13, uint8_t _MISO=12): ILI9341_t3(_CS,_DC,_RST,_MOSI,_SCLK,_MISO) {init();}

 FASTRUN void mandelbrot(void) {

  int x0,y0,p,q,xn;
  float xmin=-2.5,ymin=-1.5,xmax=1.5,ymax=1.5,xs,ys;
  int i,x,y;
  uint16_t col;
  uint16_t line[MAX_X];
  int maxIT = ITERATIONS;
  
  xs=(xmax-xmin)/320.0;
  ys=(ymax-ymin)/240.0;

  for (y=0; y < MAX_Y/2; y++) {
   SPI.beginTransaction(SPISettings(30000000, MSBFIRST, SPI_MODE0));
   setAddr(0, y, MAX_X-1, y);
   writecommand_cont(ILI9341_RAMWR);
   for (x=0;x < MAX_X; x++) {
         p=fixpt(xmin+x*xs);
         q=fixpt(ymin+y*ys);
         xn=0;
         x0=0;
         y0=0;
         i=0;
         while ((mul(xn,xn)+mul(y0,y0))<fixpt(4) && ++i < maxIT )  {
            xn=mul((x0+y0),(x0-y0)) +p;
            y0=mul(fixpt(2),mul(x0,y0)) +q;
            x0=xn;
            }
         if (i==maxIT ) col=ILI9341_BLUE;
         else col = color565(i*2,y,i*16);
         line[x]=col;
         writedata16_cont(col);
      }
   i = MAX_Y-1-y;   
   setAddr(0, i, MAX_X-1, i);
   writecommand_cont(ILI9341_RAMWR);
   for (x=0;x < MAX_X;x++) {
      writedata16_cont(line[x]);
   }
   SPI.endTransaction();
   }

  }
private:
  void init(){}
};
#endif
