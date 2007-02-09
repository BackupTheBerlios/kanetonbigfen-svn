BITS 16
ORG 0x7C00

main	mov esp, 0xffff
	mov dword [heap], 0x2200
	mov dword [break], 0x2200
;;;
	mov si, str1
	call print_string

;;;
	mov eax, 20
	call malloc
	mov [string], eax

	mov ebx, [string]
	mov eax, 0
	mov ax, sp
	call itoa

	mov si, [string]
	call print_string
;;;
	mov si, str2
	call print_string
;;;
	mov eax, 20
	call malloc
	mov [string], eax

	mov ebx, [string]
	mov eax, 0
	mov ax, sp
	call itoa_hex

	mov si, [string]
	call print_string
;;;
	mov eax, 20
	call malloc
	mov [string], eax

	mov ebx, [string]
	mov eax, 0
	mov ax, 123
	call itoa

	mov si, [string]
	call print_string
;;;
end	jmp end

malloc
	mov dword ebx, [break]
	mov dword ecx, [break]
	add dword ebx, eax
	mov dword [break], ebx
	mov eax, 0
	mov ax, cx
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

itoa
	mov edx, 0		; A
	mov ecx, 10		; C
	mov dword [pos], ebx
.loop	mov ecx, 10
	mov edx, 0
	div ecx			; quotien eax / reste edx
	add edx, '0'
	mov ecx, [pos]
	mov [ecx], edx
	add dword [pos], 1
	cmp eax, 0
	jnz .loop
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

heap	dw 0
break	dw 0
string	dw 0
pos	dw 0
tmp	dw 0
str1	db "sp = ", 0
str2	db " = ", 0
	times 510-($-$$) db 0
	dw    0xAA55
