#ifndef UTIL_H
#define UTIL_H

#include <types.h>

void fatal(char*);
void int_to_ascii(int n, char s[]);
void int_to_hexascii(u64 n, char s[]);
void reverse(char s[]);
int strlen(char s[]);
void memset(char* dest, u8 val, u32 len);

#endif
