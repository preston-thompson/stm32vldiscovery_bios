.cpu cortex-m3
.syntax unified
.thumb

.word 0x20002000
.word   _start
.word   nmi_handler
.word   hardfault_handler
.word   memmanage_handler
.word   busfault_handler
.word   usagefault_handler

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
    adds    r1, r1, #4

_loopcopydatainit:
    ldr r0, =_sdata
    ldr r3, =_edata
    adds    r2, r0, r1
    cmp     r2, r3
    bcc     _copydatainit
    ldr     r2, =_sbss
    b       _loopfillzerobss

_fillzerobss:
    movs    r3, #0
    str     r3, [r2], #4

_loopfillzerobss:
    ldr     r3, =_ebss
    cmp     r2, r3
    bcc     _fillzerobss

    bl      main
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
uhoh: .word 0xdeadbeef
//stacktop: .word 0x20002000

.end
