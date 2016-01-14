#include <avr/io.h>
/*
VER - 14-01-2016
   Содержит функции для асинхронной записи в UART.
   Перед использованием необходимо установить:
     F_CPU  - Тактовая частота
     BAUND - Желаемая скорость порта. На некоторых частотах возможно возникновении 
             погрешности несущей частоты что делает невозможной работу порта.
             Смотрите документацию на микропроцессор
     Для инициализации прерываний необходимо вызвать
*    void uart_async_init(void);            
*    sei();
*/

#ifndef __UART_ASYNC_H_
#define __UART_ASYNC_H_ 1

#if defined (__AVR_ATmega128__)
#  define F_CPU 8000000 // Clock Speed
#elif defined (__AVR_ATmega8515__)
#  define F_CPU 8000000 // Clock Speed
#else
#  define F_CPU 16000000 // Clock Speed
#endif

//#define BAUD 2400
#define BAUD 38400
//#define BAUD 57600
//#define BAUD 115200

#define MYBDIV (F_CPU / 16 / BAUD - 1)
#define UART0_BUFER_SIZE 128
#define UART0_READ_BUFER_SIZE 32

/**
 * @brief Отправляет один байт в очередь вывода в USART.
 * @param c -  байт данных
 */
void uart_putChar(char c);

/**
 * @brief Отправляет 0 терменированную строку в очередь USART.
 * @param s - 0 терминатная строка.
 */
void uart_write(char* s);

/**
 * @brief Отправляет 0 терменированную строку + символ переноса в очередь USART.
 * @param s - 0 терминатная строка.
 */
void uart_writeln(char* s);

/**
 * @brief Инициализация прерываний USART.
 */
void uart_async_init(void);

/**
 * @brief Выводит в USART два HEX символа.
 * @param c - байт данных.
 */
void _uart_writeHEX(unsigned char c);

/**
 * @brief Выводит в порт массив байт в ввиде HEX строки - 0xXX XX XX XX.
 * @param c - массив байт.
 * @param size - длинна массива.
 */

void uart_writelnHEXEx(unsigned char* c, unsigned char size);

/**
 * @brief Отправляет в UART один байт в ввиде HEX строки - 0xXX.
 * @param c - байт данных
 */
/
void uart_writelnHEX(unsigned char c);

/**
 * @brief Обявляет callBack функцию для данных поступающих с UART
 *   в качастве параметра функция будет получать строку до символа переноса.
 * @param callback ссылка на функцию обработки входящих данных.
 */
void uart_readln(void (*callback)(char*));

/**
 * @brief Формирует и выводит в UART строку вида E-XXXX
 * @param code - двух байтный код ошибки
 */
void _log(uint16_t code);

#endif