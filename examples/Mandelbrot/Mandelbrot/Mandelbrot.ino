/*
Mandelbrot set inspired by Rosetta-code-AWK:
https://rosettacode.org/wiki/Mandelbrot_set#AWK

A 180x60 character mandelbrot set will be calculated in 10 seconds.

Setting baud rate to 38400 really things up!

Different programs which can show it, and the exit command:
 $ minicom -D /dev/ttyACM0 -b 38400 # ^A x
 $ screen /dev/ttyACM0 38400        # ^A K
 $ cu -l /dev/ttyACM0 -s 38400      # ~.

*/

#include <Ansiterm.h>

#define MAXITER 30

Ansiterm console(Serial);

unsigned char oldColor = 0;

void setup(){
  Serial.begin(9600);
}

void loop() {
  while (!Serial) {}
  console.detectSize(400);
  console.eraseScreen();
  console.xy(1,1);
  unsigned int XSize=console.getMaxX();
  unsigned int YSize=console.getMaxY()-2;

  console.setBackgroundColor(oldColor = 0);
  console.setForegroundColor(7);
  Serial.print(F("Mandelbrot fractal size: "));
  Serial.print(XSize);
  Serial.write('x');
  Serial.print(YSize);
  Serial.print(F(", iterations: "));
  Serial.println(MAXITER);
  
  float MinIm=-1.0, MaxIm=1.0, MinRe=-2.0, MaxRe=1.0;
  float StepX = (MaxRe-MinRe)/XSize;
  float StepY = (MaxIm-MinIm)/YSize;
  unsigned long start = millis();
  for(int y=0; y<YSize; y++) {
    float Im = MinIm+StepY*y;
    for(float x=0; x<XSize; x++) {
      float Re = MinRe+StepX*x;
      float Zr = Re;
      float Zi = Im;
      int n=0;
      float a;
      float b;
      do {
        a = Zr*Zr;
        b = Zi*Zi;
        Zi = 2*Zr*Zi + Im;
        Zr = a-b+Re;
        ++n;
      } 
      while (n<MAXITER && a+b<4.0);
      if (0) {
        Serial.write(62-n);
      } else {
        unsigned char newColor = n == MAXITER ? 0 : n % 7 + 1;
        if (oldColor != newColor) {
          console.setBackgroundColor(newColor);
          oldColor = newColor;
        }
        Serial.write(' ');
      }
    }
    Serial.println();
  }
  console.setBackgroundColor(0);
  console.setForegroundColor(7);
  Serial.print(F("Calculation time in milli seconds: "));
  Serial.print(millis()-start);
  delay(3000);
}

