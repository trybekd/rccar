#ifndef SERVO_REPOSITORY_HH
#define SERVO_REPOSITORY_HH

#include <stdio.h>

template <typename T>
concept servo_repository = requires(T t, uint16_t value, uint8_t byte) {
  {t.set_turn(value)};
};

#endif // SERVO_REPOSITORY_HH
