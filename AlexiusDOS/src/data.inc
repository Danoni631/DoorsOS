boot_drive  db 0
cmd_buffer  times 32 db 0
cmd_cls      db "CLS", 0
cmd_ver      db "VER", 0
cmd_dir      db "DIR", 0
cmd_reboot   db "RBT", 0
cmd_shutdown db "SDW", 0
cmd_help     db "HLP", 0
cmd_run      db "RUN", 0
cmd_doors    db "DRS", 0

msg_welcome  db "AlexiusDOS", 13, 10, "$"
msg_prompt   db "Local Disk:\> $", 0
msg_ver_out  db "AlexiusDOS - Version 1.0", 13, 10, "$"
msg_dir_head db "Disk content:", 13, 10, "$"
msg_sep      db " : ", "$"
msg_err      db "Invalid command", 13, 10, "$"
msg_disk_err db "Error reading RedFat sector", 13, 10, "$"
msg_help     db "HLP, CLS, VER, DIR, RBT, SDW, RUN", 13, 10, "$"
msg_nl       db 13, 10, "$"