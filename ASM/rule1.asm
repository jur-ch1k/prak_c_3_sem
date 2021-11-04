section .txt
global rule1
rule1:
	push ebp
	mov ebp, esp
	mov eax, dword[ebp+8]; адрес массива
	mov edx, 0
.cycle:
	;поиск заглавыных букв и их замена
	cmp byte[eax+edx], '.'
	je .fin
	cmp byte[eax+edx], 'A'
	jb .precycle
	cmp byte[eax+edx], 'Z'
	ja .precycle
	sub byte[eax+edx], 'A'
	mov cl, 90
	sub cl, byte[eax+edx]
	mov byte[eax+edx], cl
.precycle:
	inc edx
	jmp .cycle
.fin:
	leave
	ret
