include ../Makefile.rules

all:
	nasm ex1.s -f bin -o iso
	$(QEMU) -fda iso
