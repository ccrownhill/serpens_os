#ifndef MEMORY_H
#define MEMORY_H

#include <types.h>

typedef struct {
  u64 base_addr;
  u64 size;
  u32 type;
} mem_map_entry_t;

void print_mem_map(int, mem_map_entry_t*);
void init_mem_management(int, mem_map_entry_t*);
void* kalloc(u32);
void kfree(void*);
#endif
