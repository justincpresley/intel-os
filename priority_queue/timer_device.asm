GLOBAL  init_timer_device

init_timer_device:
  ; 1) Do the normal preamble for assembly functions (set up ebp and save any registers
  ; that will be used). The first arg is time in ms
  ; 2) move the ms argument value into a register (say, edx)
  ; 3) Multiply dx (only the bottom 16 bits will be used) by 1193.
  ; Why? because the timer cycles at 1193180 times a second, which is 1193 times a ms
  ; note: The results must fit in 16 bits, so ms can't be more than 54.
  ; So, put your code for steps 1 - 3 HERE:
  push ebp
  mov ebp, esp
  pushad
  mov edx, [ebp+8]
  imul dx, 1193

  ; The code for steps 4-6 is given to you for free below...
  ; 4) Send the command word to the PIT (Programmable Interval Timer) that initializes Counter 0
  ; (there are three counters, but you will only use counter 0).
  ; The PIT will be initalized to mode 3, Read or Load LSB first then MSB, and
  ; Channel (counter) 0 with the following bits: 0b00110110 =
  ; Counter 0 |Read then load|Mode 3|Binary. So, the instructions will be:
  mov al, 0b00110110 ; 0x43 is the Write control word
  out 0x43, al

  ; 5) Load the LSB first then the MSB.
  ; 0x40 = Load counter 0 with the following code:
  mov ax, dx
  out 0x40, al ; LSB first
  xchg ah, al
  out 0x40, al ; MSB second

  ; 6) clean up (pop ebp and other regs used) and return
  popad
  pop ebp
  ret