MEMORY {
    flash (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    ram (rwx)   : ORIGIN = 0x20000000, LENGTH = 8K
}

SECTIONS {
    .text : {
        _stext = .;
        *(.text*)
        *(.rodata*)
        _sidata = .;
    } > flash
    .data : AT (_sidata) {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > ram
    .bss : {
        _sbss = .;
        *(.bss*)
        _ebss = .;
    } > ram
}
