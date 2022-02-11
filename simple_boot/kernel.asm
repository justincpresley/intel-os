GLOBAL  k_print

k_print:
        ; set up ebp so we can get to the arguments
        push ebp
        mov ebp, esp

        ; now push any registers you may use during the function, including the flags register
        pushf
        push eax
        push ebx
        push ecx

        ; load for calculating offset
	mov esi, [ebp+8]   ; move string into esi register
	mov eax, 0xB8000   ; base storage addr
	mov ebx, [ebp+16]  ; row
	mov ecx, [ebp+20]  ; column

	; calculate offset
        ; offset = (row * 80 + col) * 2
	; addr = base_storage_addr + offset
	imul ebx,80   ; row * 80
	add ebx,ecx   ; last_val + col
	imul ebx,2    ; last_val * 2
	add ebx, eax  ; last_val + base storage address
	mov edi, ebx  ; move offsetted address into edi

	; set length and see if we need to print
	mov ecx, [ebp+12] ; move length to ecx

_print_loop:   
	cmp edi, (0xB8000 + 2*(24*80+79 + 1)) ; compare to end of screen
	je _reset_address
	jmp _continue_loop
	
_reset_address:
	mov edi, 0xB8000                  ; set edi to base

_continue_loop:
	cmp ecx, 0          ; compare length to zero
	je _done_print      ; if so we are done

	movsb               ;es:[edi], ds:[esi]
	mov BYTE [edi], 31  ; color byte
	inc edi
	dec ecx

	jmp _print_loop

_done_print:
        ; leaving, restore all our registers
	pop ecx        	
	pop ebx
	pop eax
        popf
        pop ebp
        ret


