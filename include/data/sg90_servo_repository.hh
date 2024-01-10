#ifndef SG90_SERVO_REPOSITORY_HH
#define SG90_SERVO_REPOSITORY_HH

#include "domain/servo_repository.hh"

#include "timer1.hh"

template<timer1_output t1_out>
class sg90_servo_repository {
public:
  inline sg90_servo_repository() {}

  inline void set_turn(uint16_t _turn) {
    uint16_t turn = _turn / 10 + Timer1::in_cpt_rgstr / 40;

    switch (t1_out) {
    case timer1_output::OUTPUT_A:
      Timer1::out_cmp_rgstr_a = turn;
      break;
    case timer1_output::OUTPUT_B:
      Timer1::out_cmp_rgstr_b = turn;
      break;
    }
  }
};

static_assert(servo_repository<sg90_servo_repository<timer1_output::OUTPUT_A>>);
static_assert(servo_repository<sg90_servo_repository<timer1_output::OUTPUT_B>>);

#endif // SG90_SERVO_REPOSITORY_HH
