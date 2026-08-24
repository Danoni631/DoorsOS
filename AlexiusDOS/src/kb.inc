int21_handler:
    pusha
    cmp ah, 0x09
    je print
    popa
    iret

read_line:
    mov ah, 0x01
    int 0x16
    jz .start_read          ; Buffer limpo, pode ler
    mov ah, 0x00
    int 0x16                ; Consome tecla residual
    jmp read_line

.start_read:
    xor cx, cx

.loop:
    mov ah, 0x00
    int 0x16
    cmp al, 13
    je .done
    mov ah, 0x0E
    int 0x10
    mov [di], al
    inc di
    jmp .loop
.done:
    mov byte [di], 0
    mov dx, msg_nl
    mov ah, 0x09
    int 0x21
    ret