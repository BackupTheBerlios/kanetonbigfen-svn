BITS 16
ORG 0x7C00
	mov esp, 0xffff
	call floppy_read_sector
	mov si, mload
	call print_string
	cmp eax, 0
	je ok
	mov si, mno
	call print_string
	jmp end
ok	mov si, mok
	call print_string
	mov si, mmnum
	call print_string
	mov si, 0xa000
	mov ebx, 0x2200
	mov eax, 0
	mov ax, [0xa1fe]
	call itoa_hex
	mov si, 0x2200
	call print_string
end	jmp end

print_int
	pusha
	mov ebx, 0x2200
	call itoa_hex
	mov si, 0x2200
	call print_string
	popa
	ret

%include "floppy_read_sector.s"

itoa_hex
	mov edx, 0		; A
	mov ecx, 16		; C
	mov dword [pos], ebx
.loop	mov ecx, 16
	mov edx, 0
	div ecx			; quotien eax / reste edx
	cmp edx, 10		;
	jge .conv2		;
.conv1	add edx, '0'
	jmp .endconv		;
.conv2	add edx, 'a'		;
	sub edx, 10
.endconv			;
	mov ecx, [pos]
	mov [ecx], edx
	add dword [pos], 1
	cmp eax, 0
	jnz .loop
	mov ecx, [pos]		;
	mov byte [ecx], 'x'	;
	add dword [pos], 1	;
	mov ecx, [pos]		;
	mov byte [ecx], '0'	;
	add dword [pos], 1	;
.rev	mov eax, ebx
	mov edx, [pos]
	sub edx, 1
.loop2	mov cl, [eax]
	mov ch, [edx]
	mov byte [eax], ch
	mov byte [edx], cl
	add eax, 1
	sub edx, 1
	cmp eax, edx
	jl .loop2
	ret

print_char
	pusha
	mov ah, 0x0E
        mov bh, 0x00
        mov bl, 0xFF
        int 0x10
	popa
	ret

print_string
.loop	mov al, [si]
	cmp al, 0
	jz .end
	call print_char
	add si, 1
	jmp .loop
.end	ret

mload	db "Loading floppy bootsector ... ", 0
mno	db "ERROR",10,13,0
mok	db "OK",10,13,0
mmnum	db "magic found: ", 0
pos	dw 0
	times 510-($-$$) db 0
	dw 0xAA55
