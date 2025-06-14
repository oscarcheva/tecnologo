.intel_syntax noprefix
.global _start
.text
    _start:

        mov eax, 1 
        mov edi, 1 
        lea esi, hello_string 
        mov edx, 14 
        syscall 

        mov eax, 60 
        xor edi, edi 
        syscall

.data

    hello_string:
    .asciz "Hello, world!\n"