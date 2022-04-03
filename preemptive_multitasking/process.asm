GLOBAL  dispatch

EXTERN  enqueue
EXTERN  dequeue
EXTERN  current_pcb

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