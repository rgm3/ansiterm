#include <Ansiterm.h>

Ansiterm console(Serial);

void setup() {
  Serial.begin(9600);
  if (100 > console.detectSize(400)) {
    Serial.println(F("\nNO ANSI terminal detected. Try PuTTY, Minicom or 'Screen' (Linux).\n"));
  }
  delay(2000);
}

void loop() {
  console.detectSize(400);
  console.eraseScreen();
  console.xy(1,1);
  int Y = 1;
  while (Y < console.getMaxY()) {
    line(1, 1, console.getMaxX(), Y);
    Y += console.getMaxY()/5;
  }
  Y = 1;
  while (Y < console.getMaxY()) {
    line(1, Y, console.getMaxX(), console.getMaxY());
    Y += console.getMaxY()/5;
  }
  delay(5000);
}

void line(
  int x1, int y1,
  int x2, int y2
  )     
{
  int dx = x2 - x1, 
  dy = y2 - y1, 
  y  = y1, 
  eps = 0,
  x;    

  for ( x = x1; x <= x2; x++ ) {
    console.xy(x,y);
    Serial.write('#');
    eps += dy;  
    if ( (eps << 1) >= dx ) {
      y++;              
      eps -= dx;        
    }           
  }     
}

