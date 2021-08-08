#include <stdint.h>
#include <random.h>
#include <cmos.h> // to read RTC time

static uint32_t next = 0;

uint32_t rand()
{
  next = next * 1103515245 + 12345;
  return (next / 65536) % (RAND_MAX+1);
}

void srand(uint32_t seed)
{
  next = seed;
}

/**
 * This function sets a new random seed which is equal to the
 * sum of the seconds, minutes, hours, weekday, day of month, month and year
 * fields of the RTC in CMOS.
 * Note that here the update in progress flag is ignored which might cause
 * strange time values. However, this is no problem for only getting a seed value.
 */
void rtc_time_rand_seed()
{
  uint32_t seed = 0;
  seed += read_cmos_reg(SECONDS_REG);
  seed += read_cmos_reg(MINUTES_REG);
  seed += read_cmos_reg(HOURS_REG);
  seed += read_cmos_reg(WEEKDAY_REG);
  seed += read_cmos_reg(DAY_OF_MONTH_REG);
  seed += read_cmos_reg(MONTH_REG);
  seed += read_cmos_reg(YEAR_REG);
  srand(seed);
}
