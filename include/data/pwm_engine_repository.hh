#ifndef PWM_ENGINE_REPOSITORY_H
#define PWM_ENGINE_REPOSITORY_H

#include "domain/engine_repository.hh"

#include "timer1.hh"

template<timer1_output t1_out>
class pwm_engine_repository {
public:
  inline pwm_engine_repository() {}

  inline void set_speed(uint16_t speed) {
    switch (t1_out) {
    case timer1_output::OUTPUT_A:
      Timer1::out_cmp_rgstr_a = speed;
      break;
    case timer1_output::OUTPUT_B:
      Timer1::out_cmp_rgstr_b = speed;
      break;
    }
  }
};

static_assert(engine_repository<pwm_engine_repository<timer1_output::OUTPUT_A>>);
static_assert(engine_repository<pwm_engine_repository<timer1_output::OUTPUT_B>>);

#endif // PWM_ENGINE_REPOSITORY_H
