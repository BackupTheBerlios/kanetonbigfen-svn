BITS 16
ORG 0x7C00

main
	mov esp, 0xffff
	mov si, mget
	call print_string
	call fscan
	mov si, mhello
	call print_string
	mov si, string
	call print_string
	mov si, mend
	call print_string
end	jmp end

fscan	mov edx, string
.beg	call kbd_get
	cmp ax, 0x1c0d
	je .end
	mov byte [edx], al
	add edx, 1
	call print_char
	jmp .beg
.end	mov byte [edx], 0
	ret


		;; char al
print_char
	mov ah, 0x0E
        mov bh, 0x00
        mov bl, 0xFF
        int 0x10
	ret

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

print_int
	pusha
	mov ebx, 0x2200
	call itoa_hex
	mov si, 0x2200
	call print_string
	popa
	ret

kbd_get
	mov ah, 0
	int 0x16
	ret

		;; string si
print_string
.loop	mov al, [si]
	cmp al, 0
	jz .end
	call print_char
	add si, 1
	jmp .loop
.end	ret

		;; dh for row, dl for column
cursor_set
	mov ah, 0x02
	mov bh, 0
	int 0x10
	ret

mget	db "Enter your name : ",0
mhello	db 13,10,"Hello ",0
mend	db " !",0
string	db "............................"
pos	dw 0
	times 510-($-$$) db 0
	dw    0xAA55
