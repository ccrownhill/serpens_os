OUTPUT_FORMAT("binary")
ENTRY(_start)
SECTIONS
{
  . = 0x10000; /* kernel will be loaded at this address */

  .text : ALIGN(0x1000) /* Align to 4096 bytes */
  {
    *(.text)
  }

  /* Data (initialized) */
  .data : ALIGN(0x1000)
  {
    *(.data) /* read-write */
    *(.rodata) /* read-only */
  }

  /* Read-write data (uninitialized) and stack */
  .bss : ALIGN(0x1000)
  {
    *(.bss)
  }

  /* to find out kernel end address in kernel */
  _kernelend = .;
}
