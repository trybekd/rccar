#ifndef UART_SERVICE_HH
#define UART_SERVICE_HH

#include <avr/io.h>

class uart_service {
public:

  inline void init(long fcpu, long baudrate) {
    UCSRB |= (1 << RXEN) | (1 << TXEN);/* Turn on transmission and reception */
//    UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

#if defined (__AVR_ATmega16__)
    UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit character sizes */
#elif defined (__AVR_ATtiny2313A__)
    UCSRC |= (1 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit character sizes */
#endif

    unsigned long baud_prescale = ((fcpu / (baudrate * 16UL)) - 1);

    UBRRL = baud_prescale;		/* Load lower 8-bits of the baud rate value */
    UBRRH = (baud_prescale >> 8);	/* Load upper 8-bits*/
  }

  inline void transmit_byte(uint8_t data) {
    while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
    UDR = data;
  }

  inline uint8_t read_byte() {
    while ((UCSRA & (1 << RXC)) == 0);/* Wait till data is received */
    return(UDR);			/* Return the byte*/
  }
};

#endif // UART_SERVICE_HH
