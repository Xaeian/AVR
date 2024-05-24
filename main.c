#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  // init();
  DDRD |= (1 << 3); // PD3 Output

  while (1)
  {
    // loop();
    _delay_ms(200);
    PORTD |= (1 << 3); // PD3 High
    _delay_ms(200);
    PORTD &= ~(1 << 3); // PD3 Low
  }
}
