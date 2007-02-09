include ../Makefile.rules

all: bs ld iso run

bs:	ex6.s
	nasm ex6.s -f bin -o bootstrap -I ../libs/

ld:	kernel.c script.ld
	$(GCC) -c kernel.c -o kernel.o
	ld -T script.ld kernel.o -o kernel
	readelf -l kernel

iso: bootstrap kernel
	cat bootstrap kernel /dev/zero | dd bs=512 count=2880 of=iso

run: iso
	$(QEMU) -fda iso
