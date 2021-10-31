global _is_valid_knight_move

section .text

;   ARGS:
;   edi - x1
;   esi - y1
;   edx - x2
;   ecx - y2
;   RESULT: eax

_is_valid_knight_move:

    cmp edi, edx
    jne x1_not_equal_x2
        mov eax, 0
        ret
    x1_not_equal_x2:

    cmp esi, ecx
    jne y1_not_equal_y2
        mov eax, 0
        ret
    y1_not_equal_y2:

    cmp edi, edx
    jg x1_greater_x2
        mov eax, edi
        mov edi, edx
        mov edx, eax
    x1_greater_x2:

    sub edi, edx

    cmp esi, ecx
    jg y1_greater_y2
        mov eax, esi
        mov esi, ecx
        mov ecx, eax
    y1_greater_y2:

    sub esi, ecx

    add edi, esi

    cmp edi, 3
    je dx_plus_dy_equal_3
        mov eax, 0
        ret
    dx_plus_dy_equal_3:

    mov eax, 1
    ret


