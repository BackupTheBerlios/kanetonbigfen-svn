include ../Makefile.rules

all:
	nasm ex3.s -f bin -o iso
	$(QEMU) -fda iso
