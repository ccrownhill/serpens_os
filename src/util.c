#include <util.h>

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

void memset(u8* dest, u8 val, u32 len)
{
	u8* temp = dest;
	for (; len != 0; len--)
		*temp++ = val;
}
