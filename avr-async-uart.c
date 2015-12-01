#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#define ledOn PORTB |= _BV(PINB5)
#define ledOff PORTB &= ~(_BV(PINB5))
#define ledSw PORTB ^= _BV(PINB5)
#include "tools/uart_async.h"
// Прерывание переполнения таймера.
ISR (TIMER1_OVF_vect) {
  cli();
  ledSw;
  //uart_writeln("Hello World");
  sei();
}

void timer1_init(unsigned char dev) {
  TCCR1B |= _BV(CS12);
  // Включить обработчик прерывания переполнения счетчика таймера.
  TIMSK1 = _BV(TOIE1);
  PRR &= ~(_BV(PRTIM1));
}

void inputCallBack(char* str) {
  uart_write("cmd <");
  uart_write(str);
  uart_writeln(">");
}

int
main(void) {
  DDRB |= _BV(DDB5);
  // Делитель счетчика 256 (CS10=0, CS11=0, CS12=1).
  // 256 * 65536 = 16 777 216 (тактов)
  timer1_init(_BV(CS12));
  uart_async_init();
  uart_readln(&inputCallBack);
  sei();
  uart_writeln("start->");
  for(;;){
    sleep_mode();
  }
  return 0;
}

