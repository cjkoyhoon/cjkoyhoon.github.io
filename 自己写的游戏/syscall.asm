EXTERN FuncIndex : DD


.CODE

Asm_Call PROC

mov r10,rcx
mov eax,dword ptr[FuncIndex]
syscall
ret

Asm_Call ENDP

END