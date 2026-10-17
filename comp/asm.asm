global _start:
section .text

yo:
    mov rax, 50
    ret

_start:
    mov rdi, 42
    mov rax, 60
    call yo
    add rdi, rax
    mov rax, 60
    syscall
