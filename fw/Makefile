CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
GIT_VERSION := $(shell git rev-parse --short HEAD)
OBJDUMP = arm-none-eabi-objdump
CFLAGS = -g -c -nostdlib -nostartfiles -ffreestanding -mthumb -mcpu=cortex-m3 -march=armv7-m
LDFLAGS = -T link.ld

all: image.elf

image.elf: boot.o main.o rpc.o drv/gpio.o drv/usart.o drv/interrupt.o drv/flash.o drv/rtc.o drv/dac.o drv/pwm.o drv/adc.o
	$(LD) $(LDFLAGS) -o image.elf boot.o main.o rpc.o drv/gpio.o drv/usart.o drv/interrupt.o drv/flash.o drv/rtc.o drv/dac.o drv/pwm.o drv/adc.o
	$(OBJDUMP) -D image.elf > image.list

boot.o: boot.s
	$(AS) -o boot.o boot.s

main.o: main.c
	$(CC) $(CFLAGS) main.c

rpc.o: rpc.c
	$(CC) $(CFLAGS) rpc.c

gpio.o: gpio.c
	$(CC) $(CFLAGS) drv/gpio.c

dac.o: dac.c
	$(CC) $(CFLAGS) drv/dac.c

adc.o: adc.c
	$(CC) $(CFLAGS) drv/adc.c

pwm.o: pwm.c
	$(CC) $(CFLAGS) drv/pwm.c

usart.o: usart.c
	$(CC) $(CFLAGS) drv/usart.c

flash.o: flash.c
	$(CC) $(CFLAGS) drv/flash.c

rtc.o: rtc.c
	$(CC) $(CFLAGS) drv/rtc.c

interrupt.o: interrupt.s
	$(AS) -o drv/interrupt.o drv/interrupt.s

clean:
	rm -f *.o
	rm -f drv/*.o
	rm -f *.elf
	rm -f *.list
