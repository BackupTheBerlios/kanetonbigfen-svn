include ../Makefile.rules

all:
	nasm ex2.s -f bin -o iso
	$(QEMU) -fda iso
