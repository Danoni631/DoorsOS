kernel_main:
    mov dx, msg_welcome
    mov ah, 0x09
    int 0x21

    call shell_loop

%include "AlexiusDOS/src/shell.inc"
%include "AlexiusDOS/src/kb.inc"
%include "AlexiusDOS/src/print.inc"
%include "AlexiusDOS/src/mem.inc"
%include "AlexiusDOS/src/apm.inc"
%include "AlexiusDOS/src/redfat.asm"
%include "AlexiusDOS/src/data.inc"

times 1024-($-kernel_main) db 0