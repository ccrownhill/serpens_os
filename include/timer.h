#ifndef TIMER_H
#define TIMER_H

#define PIT_FREQ 1193182 // in Hz
#define PIT_MODE_REGISTER 0x43
#define PIT_CHANNEL0_PORT 0x40
#define PIT_SQUARE_WAVE_MODE 0b00110110 // channel 0; low and high byte access; mode 3 (square wave)
#define TIMER_IRQ 0

#define TIMER_FREQ 39 // in Hz
// There is a separate FPS plus the TIMER_FREQ value because the frequency
// can't go below 19 Hz
#define FPS 13 // make sure TIMER_FREQ can be divided evenly by this value

extern uint64_t timer_ticks;

void init_timer();
void wait_seconds(uint32_t);

#endif
