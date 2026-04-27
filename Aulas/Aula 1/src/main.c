#include <avr/io.h>
#include <avr/delay.h>

#define F_CPU 16000000UL

int main()
{
  DDRB = 0x01;  // DEFININDO PINO PB0 COMO OUTPUT
  PORTB = 0x00; // DEFININDO PINO PB0 COMO LOW


  while(1)
  {

    PORTB = 0x01; // DEFININDO PINO PB0 COMO HIGH
    _delay_ms(500);

    PORTB = 0x00; // DEFININDO PINO PB0 COMO LOW
    _delay_ms(500);
  }

  return 0;
}