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
yay:
    push rbp
    mov rbp, rsp
    mov rax, 4
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rax
    call print_number_fast
    pop rax
    jmp .return
.return:
    mov rsp, rbp
    pop rbp
    ret
no:
    push rbp
    mov rbp, rsp
    mov rax, 3
    push rax
    pop rax
    jmp .return
.return:
    mov rsp, rbp
    pop rbp
    ret
lol:
    push rbp
    mov rbp, rsp
    mov rax, 2
    push rax
    call no
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
    call lol
    push rax
    pop rax
    call print_number_fast
    mov rax, 0
    push rax
    pop rax
    mov rdi, rax
    mov rax, 60
    syscall
