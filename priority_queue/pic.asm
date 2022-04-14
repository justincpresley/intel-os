GLOBAL  outportb

outportb:
  push ebp
  mov ebp, esp
  push ax
  push dx
  mov dx, [ebp+8]
  mov al, [ebp+12]
  out dx, al
  pop dx
  pop ax
  pop ebp
  ret