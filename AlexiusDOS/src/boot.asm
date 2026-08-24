; CODED BY Danoni631, on 08/15/2026

[bits 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov [boot_drive], dl

    cli
    mov word [0x0084], int21_handler
    mov word [0x0086], cs
    sti

    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov dh, 0
    mov cl, 2
    mov dl, [boot_drive]
    mov bx, 0x7E00
    int 0x13
    jnc boot_ok

    mov dx, msg_disk_err
    mov ah, 0x09
    int 0x21
    hlt

times 510 - ($ - $$) db 0x00
dw 0xAA55

%include "AlexiusDOS/src/kernel.inc"

redfat_sector_entry:

db "README.TXT   "
db "Test txt file   "

db "COM.COM    "
db 0xBA, 0x09, 0x01, 0xB4, 0x09, 0xCD, 0x21, 0xC3, "Test program .COM!$", 0x00


times 512 - ($ - redfat_sector_entry) db 0x00