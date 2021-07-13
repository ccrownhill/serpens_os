; macro for ISRs without an error code
%macro ISR_NOERRCODE 1  ; define a macro, taking one parameter
	[GLOBAL isr%1]        ; %1 accesses the first parameter.
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common
%endmacro

; macro for ISRs with error code
%macro ISR_ERRCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte %1
		jmp isr_common
%endmacro

; TODO write isr_common that calls some isr_handler in src/isr.c
