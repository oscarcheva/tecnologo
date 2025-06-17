.intel_syntax noprefix
.global _start
.text
    _start:

        lea eax, arrayDesordenado 
        mov ebx, [eax]
        add eax, 2
        mov ecx, [eax]
        add eax, 2
        mov edx, [eax]

        cmp ebx, ecx
        jgt mayor1 

        cmp ecx, edx
        jgt mayor2

        cmp edx, ebx
        jgt mayor3

        

        mov eax, 60 
        xor edi, edi 
        syscall

mayor1:
lea eax, arrayOrdenado
mov ecx, [eax]
add eax, 2
mov ebx, [eax]

mayor2:
lea eax, arrayOrdenado
push ecx
mov edx [eax]
add eax, 2
add eax, 2
pop ecx
mov ecx, [eax]

mayor3:
lea eax, arrayOrdenado
push edx
mov ebx[eax]
add 2
pop edx
mov edx [eax]

.data
 arrayDesordenado:
 .WORD 10, 24, 43
 arrayOrdenado:
 .WORD 0, 0, 0

 # jgt mayor que 
 # jlt menor que
 # je igual que
 # jge mayor o igual
 # jle menor o igual
 