#ifndef TIMER1_HH
#define TIMER1_HH

#include <avr/io.h>

struct Timer1 {

private:
  static constexpr uint8_t byte_offset = 8;

  struct CCR {
    inline CCR& operator = (const uint16_t val) {
      TCCR1A = val & 0xFF;
      TCCR1B = (val >> 8) & 0xFF;
      return *this;
    }
  };

public:
  static inline decltype(TCCR1A)& ClockControlRegisterA = TCCR1A;
  static inline decltype(TCCR1B)& ClockControlRegisterB = TCCR1B;

  static inline decltype(OCR1A)& out_cmp_rgstr_a = OCR1A;
  static inline decltype(OCR1B)& out_cmp_rgstr_b = OCR1B;

  static inline decltype(ICR1)& in_cpt_rgstr = ICR1;

  static inline CCR clk_ctrl_rgstr;

  static inline void enable_a() {
#if defined (__AVR_ATmega16__)
    DDRD |= (1<<PD4);
#elif defined (__AVR_ATtiny2313A__)
    DDRB |= (1<<PB3);
#endif
  }

  static inline void enable_b() {
#if defined (__AVR_ATmega16__)
    DDRD |= (1<<PD5);
#elif defined (__AVR_ATtiny2313A__)
    DDRB |= (1<<PB4);
#endif
  }

  enum {
    force_compare_a = 1 << FOC1A,
    force_compare_b = 1 << FOC1B,

    // waveform generation mode
    phase_correct_pwm_8bit = 1 << WGM10,
    phase_correct_pwm_9bit = 1 << WGM11,
    phase_correct_pwm_10bit = (1 << WGM11) | (1 << WGM10),
    clr_timer_on_compare = 1 << WGM12 << byte_offset,
    fast_pwm_8bit = (1 << WGM12 << byte_offset) | (1 << WGM10),
    fast_pwm_9bit = (1 << WGM12 << byte_offset) | (1 << WGM11),
    fast_pwm_10bit = (1 << WGM12 << byte_offset) | (1 << WGM11) | (1 << WGM10),
    phase_freq_correct_pwm_ocr = 1 << WGM13 << byte_offset,
    phase_freq_correct_pwm_icr = (1 << WGM13 << byte_offset) | (1 << WGM10),
    phase_correct_pwm_ocr = (1 << WGM13 << byte_offset) | (1 << WGM11),
    phase_correct_pwm_icr = (1 << WGM13 << byte_offset) | (1 << WGM11) | (1 << WGM10),
    clr_timer_on_compare_icr = (1 << WGM13 << byte_offset) | (1 << WGM12 << byte_offset),
    fast_pwm_icr = (1 << WGM13 << byte_offset) | (1 << WGM12 << byte_offset) | (1 << WGM11),
    fast_pwm_ocr = (1 << WGM13 << byte_offset) | (1 << WGM12 << byte_offset) | (1 << WGM11) | (1 << WGM10),

    // compare output mode
    toggle_a_on_compare = 1 << COM1A0,
    clr_a_on_compare = 1 << COM1A1,
    set_a_on_compare = (1 << COM1A0) | (1 << COM1A1),

    toggle_b_on_compare = 1 << COM1B0,
    clr_b_on_compare = 1 << COM1B1,
    set_b_on_compare = (1 << COM1B0) | (1 << COM1B1),

    // clock set
    no_prescale = 1 << CS10 << byte_offset,
    prescale8 = 1 << CS11 << byte_offset,
    prescale64 = (1 << CS10 << byte_offset) | (1 << CS11 << byte_offset),
    prescale256 = 1 << CS12 << byte_offset,
    prescale1024 = (1 << CS10 << byte_offset) | (1 << CS12 << byte_offset),
    ext_clk_falling_edge = (1 << CS11 << byte_offset) | (1 << CS12 << byte_offset),
    ext_clk_rising_edge = (1 << CS10 << byte_offset) | (1 << CS11 << byte_offset) | (1 << CS12 << byte_offset),
  };
};

enum struct timer1_output {
  OUTPUT_A,
  OUTPUT_B
};

#endif // TIMER1_HH
