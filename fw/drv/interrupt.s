.cpu cortex-m3
.syntax unified
.thumb

.text
.thumb_func
.globl interrupt_enable
interrupt_enable:
    cpsie   i
    bx      lr

.thumb_func
.globl interrupt_disable
interrupt_disable:
    cpsid   i
    bx      lr

.thumb_func
.globl interrupt_get_state
interrupt_get_state:
    mrs     r0, PRIMASK
    mvn     r0, r0
    and     r0, #1
    bx      lr
