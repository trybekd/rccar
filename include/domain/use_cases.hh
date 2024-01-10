#ifndef USE_CASES_H
#define USE_CASES_H

#include <stdint.h>

#include "domain/communication_repository.hh"
#include "domain/engine_repository.hh"
#include "domain/servo_repository.hh"

template <typename CommInterface>
  requires communication_repository<CommInterface>
class receive_message_usecase {
  CommInterface interface;

public:
  inline receive_message_usecase(CommInterface _interface): interface(_interface) {}

  inline message operator()() { return interface.read_message(); }
};

template <typename EngineInterface>
  requires engine_repository<EngineInterface>
class set_speed_usecase {
  EngineInterface interface;

public:
  inline set_speed_usecase(EngineInterface _interface): interface(_interface) {}

  inline void operator()(uint16_t speed) { interface.set_speed(speed); }
};

template <typename ServoInterface>
  requires servo_repository<ServoInterface>
class set_turn_usecase {
  ServoInterface interface;

public:
  inline set_turn_usecase(ServoInterface _interface): interface(_interface) {}

  inline void operator()(uint16_t turn) { interface.set_turn(turn); }
};

#endif // USE_CASES_H
