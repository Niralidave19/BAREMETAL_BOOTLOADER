/* Entry point for Debugger */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM); /* end of "RAM" Ram type memory */

_Min_Heap_Size = 0x200; /* required amount of heap */
_Min_Stack_Size = 0x400; /* required amount of stack */
/* name(attr) : ORIGIN/org = 0x... , LENGTH/len = 0x....; */
/* attributes are R readonly, W readwrite, X executable, A allocated */

MEMORY {
    FLASH(rx) : org = 0x08060000, len = 128K
    SRAM(rwx) : org = 0x20000000, len = 128K
}

/* >(VMA) AT>(LMA) - VMA where loader loads data to execute */
/* location counter . always tracks VMA not LMA */
/* ALIGN aligns address to boundary */

SECTIONS {
    .text : {
        KEEP (*(.vector_table))
        KEEP(*(.text*))
        KEEP(*(.rodata))
        . = ALIGN(4);
        _etext = .;
    }>FLASH

    /* LOADADDR returns the LMA address, unlike . operator that returns VMA
       Hence, _la_data is pointing to start of data in flash */
    .data : {
        _la_data = LOADADDR(.data);
        _sdata = .;
        KEEP(*(.data*))
        . = ALIGN(4);
        _edata = .;
    }>SRAM AT>FLASH

    .bss : {
        _sbss = .;
        __bss_start__ = .;
        KEEP(*(.bss*))
        KEEP(*(COMMON))
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = .;
    } > SRAM
    
    . = ALIGN(8);
     end  = .;
    _end =  .;
}