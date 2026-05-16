[bits 16]
[ORG 0x7C00]

start:
    mov ax, 0
    mov ds, ax
    mov es, ax
    
    mov si, msg_loading
    call print_string

    jmp $

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0e
    int 0x10
    jmp print_string
.done:
    ret

msg_loading db "Starting DoorsOS...", 0

times 510-($-$$) db 0
dw 0xaa55