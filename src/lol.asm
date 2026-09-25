global _start
_start:
    mov rax, 2
    push rax
    mov rax, 5
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rbx
    pop rax
