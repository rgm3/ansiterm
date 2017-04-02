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
  float s = 0.0;
  int y;
  int x = 0;
  while (++x < console.getMaxX()-5) {
    y = (sin(s)+1)*(console.getMaxY()/2.2)+2;
    console.xy(x,y);
    Serial.write('#');
    s += 0.09;
  }
  delay(5000);
}
