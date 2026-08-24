print:
    mov si, dx
.loop:
    lodsb
    cmp al, '$'
    je .done
    mov ah, 0x0e
    int 0x10
    jmp .loop
.done:
    popa
    iret