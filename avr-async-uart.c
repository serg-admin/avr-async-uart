#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#define ledOn PORTB |= _BV(PINB5)
#define ledOff PORTB &= ~(_BV(PINB5))
#define ledSw PORTB ^= _BV(PINB5)
#define FOSC 16000000 // Clock Speed
#define BAUD 38400
#define USART0_BUFER_SIZE 32
#include "tools/uart_async.h"
// Прерывание переполнения таймера.
ISR (TIMER1_OVF_vect) {
  cli();
  ledSw;
  uart_writeln("Hello World");
  sei();
}

void timer1_init(unsigned char dev) {
  TCCR1B |= _BV(CS12);
  // Включить обработчик прерывания переполнения счетчика таймера.
  TIMSK1 = _BV(TOIE1);
  PRR &= ~(_BV(PRTIM1));
}

int
main(void) {
  // Разрешить светодиод arduino pro mini.
  DDRB |= _BV(DDB5);
  // Делитель счетчика 256 (CS10=0, CS11=0, CS12=1).
  // 256 * 65536 = 16 777 216 (тактов)
  timer1_init(_BV(CS12));
  //Инициализация USART
  uart_async_init();
  // Разрешить прерывания.
  sei();
  // Бесконечный с энергосбережением.
  for(;;){
    /* 
     * Wait for empty transmit buffer
     */
    while ( !( UCSR0A & _BV(UDRE0)) );
   /* 
    * Put data into buffer, sends the data
    */

    sleep_mode();
  }

  return 0;
}

