section .data
    message db "Hello world"
    msg_len equ  $ - message 
    
section .text
    global _start
    
_start:
    mov eax, 4          ; We must tell the OS **which system call** we want to execute. Sys_write is number 4, so we load 4 into eax to select the write operation.
    mov ebx, 1          ; The write syscall needs to know **where to send the data**. File descriptor 1 means standard output (the screen), so we put 1 in ebx.
    mov ecx, message    ; The OS needs to know **what data** to write. We provide the memory address of the message string so the kernel knows where to read the data from.
    mov edx, msg_len    ; We must specify **how much data** to write, so the kernel knows how many bytes to output.
    int 0x80            ; This triggers the actual system call with all the info we set up in registers. Without this, nothing happens.
    
    mov eax, 1          ; After writing, we need to exit cleanly. Sys_exit is syscall 1, so we load 1 into eax to tell the OS we want to terminate.
    xor ebx, ebx        ; We need to specify an **exit status code**. Zero means success. This informs the OS and any parent process about the program’s result.
    int 0x80            ; Finally, this triggers the exit syscall, ending the program.
