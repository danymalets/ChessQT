global _is_valid_king_move

section .text

;   ARGS:
;   edi - x1
;   esi - y1
;   edx - x2
;   ecx - y2
;   RESULT: eax

_is_valid_king_move:

    sub edi, edx
    add edi, 1

    cmp edi, 2
    jbe abs_dx_bellow_or_equal_2
        mov eax, 0
        ret
    abs_dx_bellow_or_equal_2:

    sub esi, ecx
    add esi, 1

    cmp esi, 2
    jbe abs_dy_bellow_or_equal_2
        mov eax, 0
        ret
    abs_dy_bellow_or_equal_2:

    mov eax, 1
    ret


