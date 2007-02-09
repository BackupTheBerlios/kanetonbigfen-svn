include ../Makefile.rules

all:
	nasm wrong.s -f bin -o wrong
	nasm ex4.s -f bin -o iso -I ../libs/
	$(QEMU) -fda iso -fdb wrong
	$(QEMU) -fda iso -fdb iso
	$(QEMU) -fda iso
