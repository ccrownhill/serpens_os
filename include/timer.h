#ifndef TIMER_H
#define TIMER_H

#include <snake.h> // for SNAKE_SPEED

#define PIT_FREQ 1193182 // in Hz
#define PIT_MODE_REGISTER 0x43
#define PIT_CHANNEL0_PORT 0x40
#define PIT_SQUARE_WAVE_MODE 0b00110110 // channel 0; low and high byte access; mode 3 (square wave)
#define TIMER_IRQ 0

#define FPS (SNAKE_SPEED*6) // in 1/s / Hz

extern uint64_t timer_ticks;

void init_timer();
void wait_seconds(uint32_t);

#endif
