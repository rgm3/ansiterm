#include <Ansiterm.h>

Ansiterm console(Serial);

void setup() {
  Serial.begin(9600);
  console.setBackgroundColor(MAGENTA);
  console.setForegroundColor(YELLOW);
  console.boldOn();
  console.eraseScreen();
  console.xy(1,1);
}

char line = 1;

void loop() {
  Serial.print(F("\tHello, world!"));
  console.down(1);
  console.backward(10);
  delay(500);
  if (++line > 25) {
    line = 1;
    console.xy(1,line);
  }
}
