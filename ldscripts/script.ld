MEMORY {
	FLASH (xr) : ORIGIN = 0x08000000, LENGTH = 64K
	SRAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
}

ENTRY (_start)

SECTIONS {
	.vect : ALIGN(4) {
		KEEP(./src/VectorsTable.o (.data.*msp_init*))
		KEEP(./src/VectorsTable.o (.*.*vect_table*))
	} >FLASH
	
	.text 0x08000200 : {
		./src/startup.o(._start)
		*(.text .text.*)
	}  > FLASH
	
	.initialize : ALIGN(4) {
		*(.preinit_array)
		. = ALIGN(4);
		*(.init)
		. = ALIGN(4);
		PROVIDE_HIDDEN(__startup_init_array_start = . );
		KEEP(*(.init_array .init_array.*))
		PROVIDE_HIDDEN(__startup_init_array_end = . );
		. = ALIGN(4);
		*(.fini)
		. = ALIGN(4);
		*(.fini_array)
	} >FLASH
	
	/* .data, .rodata */

	.bss 0x20000000 : {
		*(.bss .bss.*)
	} >SRAM
	
}