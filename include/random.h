#ifndef RANDOM_H
#define RANDOM_H

#define RAND_MAX 32767

#define SECONDS_REG 0x0
#define MINUTES_REG 0x2
#define HOURS_REG 0x4
#define WEEKDAY_REG 0x6
#define DAY_OF_MONTH_REG 0x7
#define MONTH_REG 0x8
#define YEAR_REG 0x9

uint32_t rand();
void srand(uint32_t);
void rtc_time_rand_seed();

#endif
