section .data
    array dq 5, 2, 9, 1, 7       ; 5 elements
    array_len equ 5

section .text
    global _start

_start:
    mov rcx, 1              ; i = 1 (start from second element)

outer_loop:
    cmp rcx, array_len
    jge done_sort           ; if i >= length, done

    ; key = array[i]
    mov rax, [array + rcx*8]

    mov rbx, rcx            ; j = i

inner_loop:
    cmp rbx, 0
    je insert_key           ; if j == 0, insert key

    mov rdx, [array + (rbx-1)*8]  ; array[j-1]
    cmp rdx, rax
    jle insert_key          ; if array[j-1] <= key, insert key

    ; shift array[j-1] to array[j]
    mov [array + rbx*8], rdx
    dec rbx
    jmp inner_loop

insert_key:
    mov [array + rbx*8], rax

    inc rcx                 ; i++
    jmp outer_loop

done_sort:
    ; Exit cleanly
    mov rax, 60
    xor rdi, rdi
    syscall
