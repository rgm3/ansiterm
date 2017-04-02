#include <Ansiterm.h>

Ansiterm console(Serial);

void setup() {
  Serial.begin(9600);
  if (100 > console.detectSize(400)) {
    Serial.print(F("NO ANSI terminal detected. Try PuTTY, Minicom or 'Screen' (Linux).\n"));
  } else {
    console.eraseScreen();
    console.xy(4,2);
    Serial.print(F("ANSI terminal detected, maxX: "));
    Serial.print(console.getMaxX());
    Serial.print(F(", maxY: "));
    Serial.print(console.getMaxY());
  }
  delay(2000);
}

void loop() {
  int y = 0;
  int x = console.getMaxX()/console.getMaxY() - 1;
  console.eraseScreen();
  console.xy(1,1);
  while (++y < console.getMaxY()) {
    Serial.write('.');
    console.down(1);
    console.forward(x);
    delay(100);
  }
  delay(500);
}
