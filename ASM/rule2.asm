section .bss
	a resb 102; массив цифр
	b resb 102; массив остальных символов
section .txt
global rule2
rule2:
	push ebp
	mov ebp, esp
	push ebx
	push edi
	mov eax, dword[ebp+8]; адресс массива text
	
	;разделение массива на цифры и не цифры
	xor edx, edx
	xor edi, edi
	xor ebx, ebx
.cycle1:
	cmp byte[eax+edx], '.'
	je .fin1
	cmp byte[eax+edx], '0'
	jb .altarr
	cmp byte[eax+edx], '9'
	ja .altarr
	mov cl, byte[eax+edx]
	mov byte[a+edi], cl
	inc edi
	jmp .altcycle
.altarr:
	mov cl, byte[eax+edx]
	mov byte[b+ebx], cl
	inc ebx
.altcycle:
	inc edx
	jmp .cycle1
.fin1:
	
	;вставка в основной массив НЕ цифр
	mov byte[a+edi], '.'
	mov byte[b+ebx], '.'
	xor edx, edx
.cycle2:
        cmp byte[a+edx], '.'
        je .fin2
        mov cl, byte[a+edx]
        mov byte[eax+edx], cl
        inc edx
        jmp .cycle2
.fin2:

	;вставка в основной массив цифр
	xor edi, edi
.cycle3:
	cmp byte[b+edi], '.'
        je .fin3
        mov cl, byte[b+edi]
        mov byte[eax+edx], cl
        inc edx
        inc edi
        jmp .cycle3
.fin3:
	
	pop edi
	pop ebx
	pop ebp
	ret