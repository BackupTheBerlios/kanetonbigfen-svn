floppy_read_sector
	mov ah, 2
	mov al, 1
	mov ecx, 1		; track 0 * 1024 + cyl 1
	mov dh, 0
	mov dl, 1
	mov ebx, 0		; es buffer
	mov es, ebx		; es buffer
	mov ebx, 0xa000		; bx buffer
	int 0x13
	ret
