#ifndef ENGINE_REPOSITORY_HH
#define ENGINE_REPOSITORY_HH

#include <stdio.h>

template <typename T>
concept engine_repository = requires(T t, uint16_t value, uint8_t byte) {
  {t.set_speed(value)};
};

#endif // ENGINE_REPOSITORY_HH
