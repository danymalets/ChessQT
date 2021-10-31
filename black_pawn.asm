global _is_valid_black_pawn_move

section .text

;   ARGS:
;   edi - x1
;   esi - y1
;   edx - x2
;   ecx - y2
;   RESULT: eax

_is_valid_black_pawn_move:

    mov eax, esi

    cmp edi, edx
    je x1_equal_x2
        mov eax, 0
        ret
    x1_equal_x2:

    sub ecx, esi

    cmp ecx, 1
    jne not_one_step
        mov eax, 1
        ret
    not_one_step:

    cmp ecx, 2
    jne not_two_step
        cmp eax, 1
        jne not_two_step
            mov eax, 1
            ret
    not_two_step:

    mov eax, 0
    ret

