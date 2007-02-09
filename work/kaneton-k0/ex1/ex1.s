BITS 16
ORG 0x7C00

main
	mov esp, 0xffff
end	mov dh, 20
	mov dl, 10
	call cursor_set
	mov si, msg1
	call print_string
	jmp end

		;; char al
print_char
	mov ah, 0x0E
        mov bh, 0x00
        mov bl, 0xFF
        int 0x10
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

msg1	db "coin", 13, 10, 0
	times 510-($-$$) db 0
	dw    0xAA55
