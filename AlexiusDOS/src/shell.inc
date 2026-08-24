shell_loop:
    mov dx, msg_prompt
    mov ah, 0x09
    int 0x21

    mov di, cmd_buffer
    call read_line

    cmp byte [cmd_buffer], 0
    je shell_loop

    mov si, cmd_buffer
    mov di, cmd_cls
    call strcmp
    jz do_cls

    mov si, cmd_buffer
    mov di, cmd_ver
    call strcmp
    jz do_ver

    mov si, cmd_buffer
    mov di, cmd_help
    call strcmp
    jz do_help

    mov si, cmd_buffer
    mov di, cmd_reboot
    call strcmp
    jz do_reboot

    mov si, cmd_buffer
    mov di, cmd_shutdown
    call strcmp
    jz do_shutdown

    mov si, cmd_buffer
    mov di, cmd_run
    call strcmp
    jz do_run

    mov si, cmd_buffer
    mov di, cmd_doors
    call strcmp
    jz run_doors

    mov dx, msg_err
    mov ah, 0x09
    int 0x21
    jmp shell_loop

do_cls:
    mov ax, 0x0003
    int 0x10
    jmp shell_loop

do_ver:
    mov dx, msg_ver_out
    mov ah, 0x09
    int 0x21
    jmp shell_loop

do_help:
    mov dx, msg_help
    mov ah, 0x09
    int 0x21
    jmp shell_loop

do_reboot:
    call reboot

do_shutdown:
    call shutdown

do_run:
    call execute

run_doors:
    extern _DoorsMain
    call _DoorsMain
    jmp $