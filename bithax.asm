; See bithax.h for explanations!
; Only the main x86_64 assembly code here (intel syntax), no real procs or anything else because they depend on the assembler syntax.
; But it should be easy as pie to translate this to your favourite assembler.
; We assume that 64-bit GPR 'rax' always contains x! 'rsi' and 'rdi' are for additional params. Also rax it the return register!

;;;;;;;;;; set_x_to_zero ;;;;;;;;;;
xor rax, rax

;;;;;;;;;; multiply_by_2 ;;;;;;;;;;
shl rax, 1

;;;;;;;;;; divide_by_2 ;;;;;;;;;;
shr rax, 1

;;;;;;;;;; is_event_or_odd ;;;;;;;;;;
and rax, 1
not rax

;;;;;;;;;; is_power_of_2 ;;;;;;;;;;
mov rbx, rax
dec rbx
and rax, rbx
not rax

;;;;;;;;;; to_uppercase ;;;;;;;;;;
and rax, '_'

;;;;;;;;;; to_lowercase ;;;;;;;;;;
or rax, ' '

;;;;;;;;;; invert_case ;;;;;;;;;;
xor rax, ' '

;;;;;;;;;; set_rightmost_bit ;;;;;;;;;;
mov rbx, rax
inc rbx
and rax, rbx

;;;;;;;;;; clear_rightmost_bit ;;;;;;;;;;
mov rbx, rax
dec rbx
and rax, rbx

;;;;;;;;;; set_bit ;;;;;;;;;;
mov rbx, 1
shl rbx, rdi
or rax, rbx

;;;;;;;;;; clear_bit ;;;;;;;;;;
mov rbx, 1
shl rbx, rdi
not rbx
and rax, rbx

;;;;;;;;;; flip_bit ;;;;;;;;;;
mov rbx, 1
shl rbx, rdi
xor rax, rbx

;;;;;;;;;; extract_bitfield ;;;;;;;;;;
and rax, rdi
shr rax, rsi

;;;;;;;;;; insert_bitfield ;;;;;;;;;;
shl r8, rsi
not rdi
and rax, rdi
or rax, r8

;;;;;;;;;; xor_swap ;;;;;;;;;;
xor rax, rbx
xor rbx, rax
xor rax, rbx

