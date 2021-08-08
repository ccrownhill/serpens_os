/**
 * Code for getting the main game loop running at a certain frame rate
 * using the Programmable Interval Timer PIT.
 */

#include <timer.h>
#include <irq.h>
#include <ports_io.h>

// in main.c
void game_main_loop();

u64 ticks = 0;

void timer_irq_handler()
{
  ticks++;
}

/**
 * Set the frequency at which interrupts on IRQ 0 will occur
 * to the game frame rate FPS
 */
void set_timer_frequency(u32 freq)
{
  u16 divisor = PIT_FREQ / freq;

  // set the frequency divisor
  port_byte_out(PIT_CHANNEL0_PORT, (u8)(divisor & 0xff)); // low byte
  port_byte_out(PIT_CHANNEL0_PORT, (u8)((divisor >> 8) & 0xff)); // high byte
}

void init_timer()
{
  install_irq_handler(TIMER_IRQ, timer_irq_handler);
  port_byte_out(PIT_MODE_REGISTER, PIT_SQUARE_WAVE_MODE);
  set_timer_frequency(FREQ);
}
