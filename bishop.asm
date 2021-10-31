global _is_valid_bishop_move

section .text

;   ARGS:
;   edi - x1
;   esi - y1
;   edx - x2
;   ecx - y2
;   RESULT: eax

_is_valid_bishop_move:

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

    cmp edi, esi
    je dx_equal_dy
        mov eax, 0
        ret
    dx_equal_dy:

    mov eax, 1
    ret

