OUTPUT_FORMAT("binary")
ENTRY(_start)
SECTIONS
{
  . = 0x10000;

  .text ALIGN(4K) :
  {
    *(.text)
  }

  /* Read-only data. */
  /* commented out because it is not necessary
  .rodata ALIGN(4K) :
  {
    *(.rodata)
  }
  */

  /* Data (initialized) */
  .data ALIGN(4K) :
  {
    *(.data) /* read-write */
    *(.rodata) /* read-only */
  }

  /* Read-write data (uninitialized) and stack */
  .bss ALIGN(4K) :
  {
    *(.bss)
  }

  /* to find out kernel end address in kernel */
  _kernelend = .;
}
