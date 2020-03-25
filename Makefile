obj-m += soft_uart.o

soft_uart-objs := module.o raspberry_soft_uart.o queue.o

LINUX?=/usr/local/src/kernel

all:
	$(MAKE) -C $(LINUX) M=$(PWD) modules

clean:
	$(MAKE) -C $(LINUX) M=$(PWD) clean

install:
	sudo insmod soft_uart.ko gpio_tx=16 gpio_rx=17
