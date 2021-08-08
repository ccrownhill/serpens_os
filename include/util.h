#ifndef UTIL_H
#define UTIL_H

void fatal(char*);
void int_to_ascii(int n, char s[]);
void int_to_hexascii(uint64_t n, char s[]);
void reverse(char s[]);
int strlen(char s[]);
void memset(char* dest, uint8_t val, uint32_t len);

#endif
