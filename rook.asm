global _is_valid_rook_move

section .text

;   ARGS:
;   edi - x1
;   esi - y1
;   edx - x2
;   ecx - y2
;   RESULT: eax

_is_valid_rook_move:

    cmp edi, edx
    jne x1_not_equal_x2
        mov eax, 1
        ret
    x1_not_equal_x2:

    cmp esi, ecx
    jne y1_not_equal_y2
        mov eax, 1
        ret
    y1_not_equal_y2:

    mov eax, 0
    ret


