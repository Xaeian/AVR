#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define LED_ON (PORTD |= (1 << 2))
#define LED_OFF (PORTD &= ~(1 << 2))

int main(void)
{
  // init();
  DDRD |= (1 << 2); // PD2 Output
  DDRB &= ~(1 << 1); // PB1 Input
  PORTB |= (1 << 1); // PB1 Pull up

  int i;
  bool blink = false;

  while(1)
  {
    if(!(PINB & (1 << 1))) {
      blink = !blink;
    }
    //------------------------
    if(blink) {
      PORTD ^= (1 << 2);
    }
    else {
      PORTD &= ~(1 << 2);
    }
    _delay_ms(100);
  }
}