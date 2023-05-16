#include <avr/io.h>
#include <TM1638.h>

void setup() {
  // put your setup code here, to run once:
    pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  // create LedControl object
  TM1638 module = TM1638(8, 9, 7);

  // setup lmk1638
  module.test();
}

void loop() {
  // put your main code here, to run repeatedly:

}
