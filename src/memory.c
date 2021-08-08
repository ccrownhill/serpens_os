#include <memory.h>
#include <display.h> // for print_mem_map
#include <util.h>

#define MEM_FREE 1
#define MEM_ARR_MAX_SIZE 3000 // entries not bytes

enum mem_space_type {EMPTY, ALLOCATED};

typedef struct {
  u32 base_addr;
  u32 size;
  enum mem_space_type space_type;
} mem_space_t;

// in link.ld
extern u32 _kernelend;

mem_space_t* mem_arr;
int mem_arr_size;

/**
 * This function is for debugging
 * so that you can quickly view the memory map
 */
void print_mem_map(int mem_map_len, mem_map_entry_t* mem_map)
{
  char mmap_string[15];
  int i;
  for (i = 0; i < mem_map_len; i++) {
    memset(mmap_string, 0, 15);
    int_to_hexascii(mem_map[i].base_addr, mmap_string);
    kprint_at(mmap_string, i*2, i*3, WHITE);
    memset(mmap_string, 0, 15);
    int_to_hexascii(mem_map[i].size, mmap_string);
    kprint_at(mmap_string, i*2, i*3+1, WHITE);
    memset(mmap_string, 0, 15);
    int_to_hexascii(mem_map[i].type, mmap_string);
    kprint_at(mmap_string, i*2, i*3+2, WHITE);
  }
}

/**
 * Setup ordered list of empty and allocated memory needed for kalloc and kfree functions
 */
void init_mem_management(int mem_map_len, mem_map_entry_t* mem_map)
{
  int i;

  // memory management array is put right after the kernel end
  mem_arr = (mem_space_t*)&_kernelend;

  // the memory area in which allocation will take place should
  // the first free area after the kernel end in the memory map
  for (i = 0; i < mem_map_len; i++) {
    if (mem_map[i].base_addr > (u32)&_kernelend && mem_map[i].type == MEM_FREE) {
      memset((char*)mem_arr, 0, MEM_ARR_MAX_SIZE * sizeof(mem_space_t));
      mem_arr[0].base_addr = mem_map[i].base_addr;

      // this might be too much memory but since there will nothing else
      // but my little snake game to allocate memory it should not matter
      mem_arr[0].size = mem_map[i].size;
      mem_arr[0].space_type = EMPTY;
      mem_arr_size = 1;
      return; // only 1 free area needs to be found
    }
  }
  fatal("No free memory area found");
}

void insert_mem_arr_element(mem_space_t element, int index)
{
  if (mem_arr_size + 1 > MEM_ARR_MAX_SIZE)
    fatal("Can't add new element to memory management array");

  if (index == mem_arr_size) {
    // just append the item
    mem_arr[mem_arr_size] = element;
  } else {
    // now it needs to be inserted somewhere in the middle
    mem_space_t tmp = mem_arr[index];
    mem_arr[index] = element;
    for (; index < mem_arr_size; index++) {
      mem_space_t tmp2 = mem_arr[index+1];
      mem_arr[index+1] = tmp;
      tmp = tmp2;
    }
  }
  mem_arr_size++; // array is now bigger by 1 element
}

void remove_mem_arr_element(int index)
{
  for (; index < mem_arr_size; index++)
    mem_arr[index] = mem_arr[index+1];
  mem_arr_size--;
}

void* kalloc(u32 size)
{
  void* ret_addr;
  int i;
  for (i = 0; i < mem_arr_size; i++) {
    // find suitable empty entry with first fit algorithm
    if (mem_arr[i].size >= size && mem_arr[i].space_type == EMPTY) {
      ret_addr = (void*)mem_arr[i].base_addr;
      if (mem_arr[i].size > size) {
        // if the empty entry is bigger than needed just adjust its base_addr and size
        mem_arr[i].base_addr += size;
        mem_arr[i].size -= size;
        // and insert a new entry of type ALLOCATED before it
        mem_space_t insert_element = {.base_addr=(u32)ret_addr, .size=size, .space_type=ALLOCATED};
        insert_mem_arr_element(insert_element, i);
      } else if (mem_arr[i].size == size) {
        // if it is just the same size just convert it to an "ALLOCATED" type entry
        mem_arr[i].space_type = ALLOCATED;
      }
      return ret_addr;
    }
  }
  fatal("No memory for allocation found");
}

void kfree(void* addr)
{
  int i;
  for (i = 0; i < mem_arr_size; i++) {
    // find mem_arr entry of addr
    if (mem_arr[i].base_addr == (u32)addr) {
      // set it to be a hole now
      mem_arr[i].space_type = EMPTY;

      // check for adjacent empty entry after current one
      if (i+1 < mem_arr_size && mem_arr[i+1].space_type == EMPTY) {
        // merge these empty entries
        mem_arr[i].size += mem_arr[i+1].size;
        remove_mem_arr_element(i+1);
      }
      
      // check for adjacent empty prior to current hole
      if (i-1 >= 0 && mem_arr[i-1].space_type == EMPTY) {
        // if this is the case merge them
        mem_arr[i-1].size += mem_arr[i].size;
        remove_mem_arr_element(i);
      }
    }
  }
}
