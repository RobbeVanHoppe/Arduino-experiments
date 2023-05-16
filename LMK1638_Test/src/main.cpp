#include <Arduino.h>
#include <avr/io.h>
#include <TM1638.h>

// Map the arduino pins to the names on the LMK1638
#define CLK_PIN 8
#define DIO_PIN 9
#define STB0_PIN 7

void testLED(TM1638 module) {

    for (size_t i = 0; i < 9; i++)
    {
      module.setLED(1, i);
      _delay_ms(20);
    }
    for (size_t i = 0; i < 9; i++)
    {
      module.setLED(2, i);
      _delay_ms(20);
    }
    for (size_t i = 0; i < 9; i++)
    {
      module.setLED(0, i);
      _delay_ms(20);
    }
}

void testDisplay(TM1638 module) {
  for (int i = 0; i < 99; i++)
  {
      module.setDisplayToDecNumber(i,0,false);
      _delay_ms(20);
  }
  
}

int main(void)
{
  // Set all pins as outputs

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  // create LedControl object
  TM1638 module = TM1638(DIO_PIN, CLK_PIN, STB0_PIN);

  // setup lmk1638
  module.clearDisplay();
  module.setupDisplay(true, 7);

  while (1)
  {
    testLED(module);
    testDisplay(module);
  }
}