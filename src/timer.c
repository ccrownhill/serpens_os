/**
 * Code for getting the main game loop running at a certain frame rate
 * using the Programmable Interval Timer PIT.
 */

#include <stdint.h>
#include <timer.h>
#include <irq.h>
#include <ports_io.h>

// in main.c
void game_main_loop();

uint64_t timer_ticks = 0;

void timer_irq_handler()
{
  timer_ticks++;
}

/**
 * Set the frequency at which interrupts on IRQ 0 will occur
 * to the game frame rate FPS
 */
void set_timer_frequency(uint32_t freq)
{
  uint16_t divisor = PIT_FREQ / freq;

  // set the frequency divisor
  port_byte_out(PIT_CHANNEL0_PORT, (uint8_t)(divisor & 0xff)); // low byte
  port_byte_out(PIT_CHANNEL0_PORT, (uint8_t)((divisor >> 8) & 0xff)); // high byte
}

void init_timer()
{
  install_irq_handler(TIMER_IRQ, timer_irq_handler);
  port_byte_out(PIT_MODE_REGISTER, PIT_SQUARE_WAVE_MODE);
  set_timer_frequency(TIMER_FREQ);
}

void wait_seconds(uint32_t seconds)
{
  uint32_t first_tick = (uint32_t)timer_ticks; // this is a 32 bit OS so cast it to 32 bit
  while( ((uint32_t)timer_ticks-first_tick) / TIMER_FREQ < seconds);
}
