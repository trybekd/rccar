#define F_CPU 8000000

#include "domain/use_cases.hh"

#include "data/uart_repository.hh"
#include "data/pwm_engine_repository.hh"
#include "data/sg90_servo_repository.hh"

int main() {

  Timer1::clk_ctrl_rgstr = Timer1::fast_pwm_icr | Timer1::clr_a_on_compare | Timer1::clr_b_on_compare | Timer1::prescale8;
  Timer1::in_cpt_rgstr = F_CPU / 8 / 50;

  auto recieve_message = [] {
    auto uart_srv = uart_service{};
    uart_srv.init(F_CPU, 9600);
    return receive_message_usecase{uart_repository{uart_srv}};
  }();

  auto set_speed = [] {
    Timer1::enable_b();
    return set_speed_usecase{pwm_engine_repository<timer1_output::OUTPUT_B>{}};
  }();

  auto set_turn = [] {
    Timer1::enable_a();
    return set_turn_usecase{sg90_servo_repository<timer1_output::OUTPUT_A>{}};
  }();

  while(true) {
    message msg = recieve_message();

    switch(msg.command_id) {
    case commands::IS_RUNNING:
    case commands::SHUTDOWN:
      continue;
    case commands::SPEED:
      set_speed(msg.data);
      continue;
    case commands::TURN:
      set_turn(msg.data);
      continue;
    default:
      continue;
    }
  }
}
