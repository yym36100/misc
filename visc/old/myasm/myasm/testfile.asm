;define section
define
 	LEDs 00
	val2 10

; data section
data 16	; base address
	; name value(optional)
 	initA	1 
 	incr 	2
 	outval 	03 

;code section
code
; label opcode	address
init:	load 	1
loop:	add 	incr ;some comment here
     	jneg 	skip
     	jump 	loop
skip:	load 	outval
     	add 	incr
     	out 	LEDs
     	store 	outval
     	jump 	init