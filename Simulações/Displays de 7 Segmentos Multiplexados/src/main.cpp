#include <Arduino.h>

volatile uint8_t digits[4] = {0, 0, 0, 0};
volatile uint8_t current_digit = 0;

void write_display(uint8_t number)
{
  if(number>9) number = 0x0A;
  PORTD = number;
}

void select_display(uint8_t disp)
{
  uint8_t aux;
  switch(disp)
  {
    case 0: aux = 0x01; break;
    case 1: aux = 0x02; break;
    case 2: aux = 0x04; break;
    case 3: aux = 0x08; break;
    default: aux = 0x01; break;
  }
  PORTC = aux;
}

ISR(TIMER1_COMPA_vect)
{
  // Desliga todos os displays (evita ghosting)
  PORTC = 0x00;

  // Seleciona próximo display
  select_display(current_digit);

  // Escreve o valor correspondente
  write_display(digits[current_digit]);

  // Próximo dígito
  current_digit++;
  if(current_digit > 3) current_digit = 0;
}


void setup()
{
  DDRD = 0x0F;
  DDRC = 0x0F;

  PORTC = 0x00;
  PORTD = 0x00;

  // 🔧 Configuração do Timer1 (CTC)
  TCCR1A = 0x00;
  TCCR1B = 0x00;

  TCCR1B |= (1 << WGM12); // modo CTC

  // Prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // 16MHz / 64 = 250kHz → 1ms = 250 contagens
  OCR1A = 249;

  TIMSK1 |= (1 << OCIE1A); // habilita interrupção

  sei(); // habilita interrupções globais
}

void implement_counter_in_digits(uint8_t counter)
{
  digits[0] = counter % 10;
  digits[1] = (counter / 10) % 10;
  digits[2] = (counter / 100) % 10;
  digits[3] = (counter / 1000) % 10;
}

void loop()
{
  static uint16_t counter = 0;
  implement_counter_in_digits(counter);

  delay(250);

  counter++;
  if(counter > 9999) counter = 0;
}