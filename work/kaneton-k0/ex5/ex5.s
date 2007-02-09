BITS 16
ORG 0x7C00


main:
	mov esp, 0x7C00
	call pmode_enable
BITS 32
switched
	mov eax, 0xb8000
	mov ebx, 4000
	mov ecx, 0xb8300
	call memcpy
	jmp end
	mov eax, 0xb8300
	mov ebx, 4000
	mov cl, 0
	call memset
here	mov si, msg1
	call print_string
end	jmp here

memset	; eax begin ebx size ecx content
.beg	mov byte [eax], cl
	add eax, 1
	sub ebx, 1
	cmp ebx, 0
	jge .beg
	ret

memcpy	; eax begin ebx size ecx where
.beg	mov byte dl, [eax]
	mov byte [ecx], dl
	add eax, 1
	add ecx, 1
	sub ebx, 1
	cmp ebx, 0
	jge .beg
	ret

print_char_fb
	cmp al, 10
	je .cr
	cmp al, 13
	je .lf
	mov ebx, [curpos]
	add ebx, 0xb8000
	mov byte [ebx], al
	mov byte [ebx+1], 7
	add dword [curpos], 2
	jmp .end
.cr	add dword [curpos], 160
	jmp .end
.lf	mov edx, 0
	mov eax, [curpos]
	mov ecx, 160
	div ecx
	sub [curpos], edx
	jmp .end
.end	ret

print_string
.loop   mov al, [si]
        cmp al, 0
        jz .end
        call print_char_fb
        add si, 1
        jmp .loop
.end	ret

BITS 16
pmode_enable
	cli
	lgdt [gdtr]
	mov eax, cr0
	or ax, 1
	mov cr0, eax
;; 32 bts here
	jmp 0x8:.nx	; far jump
BITS 32
.nx:	mov eax, 0x10
	mov ds, eax
	mov ss, eax
	jmp switched

kbd_get
	mov ah, 0
	int 0x16
	ret

msg1	db "haha tu as PAS reussi!!!!!!!!", 10, 13, 0
curpos	dd 0
gdt:
gdt_null:
	db 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
gdt_cs:
	db 0xff, 0xff, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
gdt_ds:
	db 0xff, 0xff, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
eogdt:
gdtr:
	dw eogdt-gdt
	dd gdt

	times 510-($-$$) db 0
	dw    0xAA55
