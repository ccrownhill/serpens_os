#ifndef MEMORY_H
#define MEMORY_H

typedef struct {
  uint64_t base_addr;
  uint64_t size;
  uint32_t type;
} mem_map_entry_t;

void print_mem_map(int, mem_map_entry_t*);
void init_mem_management(int, mem_map_entry_t*);
void* kalloc(uint32_t);
void kfree(void*);
#endif
