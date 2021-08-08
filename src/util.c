#include <util.h>
#include <types.h>
#include <display.h> // for "fatal"

/**
 * This function just prints a red error message in the lower left screen corner
 * and loops forever
 */
void fatal(char* msg)
{
  kprint_at(msg, 0, 24, LIGHT_RED);
  while(1);
}

/**
 * int_to_ascii: convert n to characters in s
 * (K&R implementation)
 */
void int_to_ascii(int n, char s[])
{
  int i, sign;
  if ((sign = n) < 0)  // record sign
    n = -n;            // make n positive
  i = 0;
  do {      // generate digits in reverse order
    s[i++] = n % 10 + '0';  // get next digit
  } while ((n /= 10) > 0);  // delete it
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

/**
 * u64 number so that all addresses will fit into it
 */
void int_to_hexascii(u64 n, char s[])
{
  u64 last_digit;
  //n = -n; // for testing
  int i = 0;
  do {      // generate digits in reverse order
    last_digit = n % 16;
    if (last_digit < 0xa)
      s[i++] = last_digit + '0';
    else
      s[i++] = last_digit - 0xa + 'A';
  } while ((n /= 16) > 0);  // delete it
  s[i] = '\0';
  reverse(s);
}

/* K&R implementation */
void reverse(char s[]) 
{
  int c, i, j;
  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = s[i];    
    s[i] = s[j];
    s[j] = c;
  }
}

/* K&R */
int strlen(char s[])
{
  int i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}

void memset(char* dest, u8 val, u32 len)
{
  char* temp = dest;
  for (; len != 0; len--)
    *temp++ = val;
}
