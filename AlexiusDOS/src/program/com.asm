[bits 16]
[org 0x0100]

start:
    mov dx, msg
    mov ah, 0x09
    int 0x21
    ret

msg db "SOON DOORS OS GONNA EXIST", 13, 10, "$"