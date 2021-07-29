#ifndef MEMORY_H
#define MEMORY_H

#include <types.h>

typedef struct {
  u64 base_addr;
  u64 length;
  u32 type;
} mem_map_entry_t;

#endif
