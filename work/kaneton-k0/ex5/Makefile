include ../Makefile.rules

all:
	nasm ex5.s -f bin -o iso
	$(QEMU) -fda iso
