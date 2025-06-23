section .text
global _start

_start:
    mov eax, 5      ; Load first number (5) into EAX
    mov ebx, 3      ; Load second number (3) into EBX

    add eax, ebx    ; Add EBX to EAX; EAX = 5 + 3 = 8

    ; Now EAX contains the sum (8)
    
    ; Exit program (Linux syscall)
    mov eax, 1      ; sys_exit
    xor ebx, ebx    ; status 0
    int 0x80
