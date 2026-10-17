    mov rax, 2
    push rax
    mov rax, 5
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    mov rax, 8
    push rax
    mov rax, 3
    push rax
    mov rax, 5
    push rax
    mov rax, 4
    push rax
    pop rbx
    pop rax
    imul rax, rbx
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rax
    mov rdi, rax
    mov rax, 60
    syscall
