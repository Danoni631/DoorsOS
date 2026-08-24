strcmp:
.loop:
    mov al, [si]
    mov bl, [di]
    cmp al, bl
    jne .diff
    cmp al, 0
    je .equal
    inc si
    inc di
    jmp .loop
.diff:
    mov ax, 1
    ret
.equal:
    xor ax, ax
    ret