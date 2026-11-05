section .text
global _start
print_number_fast:
; === PROLOGUE ===
push rbp
mov rbp, rsp
; Allocate 16 bytes on the stack for our string buffer
sub rsp, 16
; Track if the number was negative using a register we won't break (R8)
mov r8, 0
; Check if the number is negative
cmp rax, 0
jge prepare_buffer       ; If it's positive, skip to buffer setup
neg rax
mov r8, 1
prepare_buffer:
; Start filling our buffer from the VERY END (right to left)
mov byte [rbp - 1], 10
mov rsi, rbp             ; Use RSI to track where our string starts
dec rsi                  ; Move pointer to the newline
mov rcx, 1               ; RCX counts total string length (starts
convert_loop:
mov rdx, 0               ; Clear RDX for division
mov rbx, 10
div rbx                  ; RAX = quotient, RDX = remainder
add rdx, 48              ; Convert remainder digit to ASCII
dec rsi                  ; Move our string pointer one byte to the left
mov [rsi], dl            ; Store the ASCII character
inc rcx                  ; Increase our character count
cmp rax, 0               ; Are we out of digits?
jne convert_loop         ; If not, keep going
; Check our flag: Do we need to slap a minus sign on the front?
cmp r8, 1
jne do_syscall           ; If not negative, go straight to printing
dec rsi                  ; Move pointer one more byte to the left
mov byte [rsi], 45
inc rcx
do_syscall:
mov rax, 1
mov rdi, 1
mov rdx, rcx
syscall
; === EPILOGUE ===
mov rsp, rbp
pop rbp
ret
uwu:
    push rbp
    mov rbp, rsp
    mov rax, 10
    push rax
    mov rax, rdi
    push rax
    pop rbx
    pop rax
    cmp rax, rbx
    setg al
    movzx rax, al
    push rax
    pop rax
    cmp rax, 0
    je .endif_0
    mov rax, 9
    push rax
    pop rax
    jmp .return
.endif_0:
    mov rax, 2
    push rax
    mov rax, 4
    push rax
    pop rbx
    pop rax
    imul rax, rbx
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rax
    call print_number_fast
    mov rax, 5
    push rax
    pop rax
    call print_number_fast
    mov rax, 0
    push rax
    pop rax
    jmp .return
.return:
    mov rsp, rbp
    pop rbp
    ret
yo:
    push rbp
    mov rbp, rsp
    mov rax, 1
    push rax
    pop rax
    call print_number_fast
    mov rax, 2
    push rax
    pop rax
    call print_number_fast
    mov rax, 3
    push rax
    pop rax
    jmp .return
    mov rax, 6
    push rax
    pop rax
    call print_number_fast
.return:
    mov rsp, rbp
    pop rbp
    ret
fact:
    push rbp
    mov rbp, rsp
    mov rax, 1
    push rax
    mov rax, rdi
    push rax
    pop rbx
    pop rax
    cmp rax, rbx
    sete al
    movzx rax, al
    push rax
    pop rax
    cmp rax, 0
    je .endif_1
    mov rax, 1
    push rax
    pop rax
    jmp .return
.endif_1:
    mov rax, 3
    push rax
    mov rdi, 1
    call fact
    push rax
    pop rbx
    pop rax
    imul rax, rbx
    push rax
    pop rax
    jmp .return
.return:
    mov rsp, rbp
    pop rbp
    ret
_start:
    mov rdi, 5
    call fact
    push rax
    pop rax
    call print_number_fast
    mov rax, 0
    push rax
    pop rax
    mov rdi, rax
    mov rax, 60
    syscall
