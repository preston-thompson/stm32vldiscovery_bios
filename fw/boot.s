.cpu cortex-m3
.syntax unified
.thumb

// Stack pointer
.word 0x20002000

// Program start
.word   _start

// Fault handlers
.word   nmi_handler
.word   hardfault_handler
.word   memmanage_handler
.word   busfault_handler
.word   usagefault_handler

// Interrupt vectors
.rept   4
.word   hang
.endr

.word   svc_handler
.word   debugmon_handler

.word   hang

.word   pendsv_handler
.word   systick_handler

.rept   37
.word   hang
.endr

.word   usart1_isr

.text
.thumb_func
.global _start
_start:
    movs    r1, #0
    b       _loopcopydatainit

_copydatainit:

    ldr r3, =_sidata
    ldr r3, [r3, r1]
    str r3, [r0, r1]

    // Move to the next word.
    adds    r1, r1, #4

_loopcopydatainit:

    // _sdata contains the beginning of the data section.
    ldr r0, =_sdata
    // _edata contains the end of the data section.
    ldr r3, =_edata

    // Check if this is the end of the data section and branch if it isn't.
    adds    r2, r0, r1
    cmp     r2, r3
    bcc     _copydatainit

    // _sbss contains the beginning of the bss section.
    ldr     r2, =_sbss

    b       _loopfillzerobss

_fillzerobss:

    movs    r3, #0
    str     r3, [r2], #4

_loopfillzerobss:

    // _ebss contains the end of the bss section.
    ldr     r3, =_ebss

    cmp     r2, r3
    bcc     _fillzerobss

    bl      main

    // Should never get here.
    b hang

.thumb_func
hang:
    ldr     r0, uhoh
    b       hang

.thumb_func
nmi_handler:
    b       .

.thumb_func
hardfault_handler:
    b       .

.thumb_func
memmanage_handler:
    b       .

.thumb_func
busfault_handler:
    b       .

.thumb_func
usagefault_handler:
    b       .

.thumb_func
svc_handler:
    b       .

.thumb_func
debugmon_handler:
    b       .

.thumb_func
pendsv_handler:
    b       .

.thumb_func
systick_handler:
    b       .

.align
uhoh: .word 0xdeadbeef          // canary value

.end
