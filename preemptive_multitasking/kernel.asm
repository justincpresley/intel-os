GLOBAL  k_print
GLOBAL  go
GLOBAL  dispatch
GLOBAL  lidtr

EXTERN  enqueue
EXTERN  dequeue
EXTERN  current_pcb

go:
	; dequeue pcb from queue and make it the running process
	call dequeue
	; set esp register to esp value in the current process pcb
	mov [current_pcb], eax	
	mov esp, [eax]
	; restore registers
	pop gs
	pop fs
	pop es
	pop ds
	popad
	iret

dispatch:
	; save registers
	pushad
	push ds
	push es
	push fs
	push gs
	; save esp register in the running processes pcb
	mov edi, [current_pcb]
	mov [edi], esp
	push edi
	; enqueue pcb for the running process
	call enqueue
	; dequeue pcb for the next process and make it running
	call dequeue
	; set the esp register to esp value in the new running process pcb
	mov [current_pcb], eax
	mov esp, [eax]
	; restore registers of new stack
	pop gs
	pop fs
	pop es
	pop ds
	popad
	; unique ret
	iret

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
	movsb               ; es:[edi], ds:[esi]
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
