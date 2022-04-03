GLOBAL  lidtr

lidtr:
	push ebp
	mov ebp, esp
	pushf
	push eax
	mov eax, [ebp+8]
	lidt [eax]
	pop eax
	popf
	pop ebp
	ret