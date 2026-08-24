boot_ok:
    call kernel_main

do_rft_dir:
    mov dx, msg_dir_head
    mov ah, 0x09
    int 0x21

    mov si, 0x7E00
    mov cx, 4

.loop_entries:
    cmp byte [si], 0
    je .next_entry

    push cx
    push si

    mov cx, 12

.print_name:
    lodsb
    mov ah, 0x0E
    int 0x10
    loop .print_name

    mov dx, msg_sep
    mov ah, 0x09
    int 0x21

    pop si
    push si
    add si, 12
    mov cx, 20
.print_content:
    lodsb
    cmp al, 0
    je .done_content
    mov ah, 0x0E
    int 0x10
    loop .print_content

.done_content:
    mov dx, msg_nl
    mov ah, 0x09
    int 0x21

    pop si
    pop cx

.next_entry:
    add si, 32
    loop .loop_entries

    jmp shell_loop

execute:
    mov ax, 0x2000
    mov es, ax
    mov di, 0x0100

    mov si, 0x7E00 + 32
    add si, 12

    mov cx, 20
    rep movsb

    push ds
    push es

    mov ax, 0x2000
    mov ds, ax
    mov es, ax

    call 0x2000:0100

    pop es
    pop ds

    jmp shell_loop