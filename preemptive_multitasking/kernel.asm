GLOBAL  go

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