#ifndef UART_REPOSITORY_HH
#define UART_REPOSITORY_HH

#include "uart_service.hh"

#include "domain/communication_repository.hh"

class uart_repository {
  uart_service service;

public:
  inline uart_repository(uart_service _service): service(_service) {}

  inline message read_message() {
    uint8_t c = 0;
    do {
      c = service.read_byte();
    } while (c != 0xFF);

    uint8_t cmd_id = service.read_byte();
    uint8_t data_h = service.read_byte();
    uint8_t data_l = service.read_byte();

    return message {.command_id = (commands)cmd_id, .data = uint16_t(data_h << 8) + data_l};
  }
};

static_assert(communication_repository<uart_repository>);

#endif // UART_REPOSITORY_HH
