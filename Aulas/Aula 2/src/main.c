#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void set_bit(volatile uint8_t *reg, uint8_t bit)
{
  *reg |= (1 << bit);
}

void clear_bit(volatile uint8_t *reg, uint8_t bit)
{
  *reg &= ~(1 << bit);
}

int main()
{

  set_bit(&DDRD, PD0);
  clear_bit(&PORTD, PD0);

  while(1)
  {
    set_bit(&PORTD, PD0);
    _delay_ms(500);

    clear_bit(&PORTD, PD0);
    _delay_ms(500);
  }

  return 0;
}