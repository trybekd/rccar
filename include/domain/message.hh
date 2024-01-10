#ifndef MESSAGE_HH
#define MESSAGE_HH

#include <stdint.h>

enum struct commands: uint8_t {
  SPEED = 0x11,
  TURN = 0x12,
  IS_RUNNING = 0x13,
  SHUTDOWN = 0x14
};

struct message {
  commands command_id;
  uint16_t data;
};

#endif // MESSAGE_HH
