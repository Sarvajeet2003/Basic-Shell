include Irvine32.inc

// String & Integer Input.

.data:
    prompt byte "Please enter a String: ",0
    myvar byte 20 DUP(?)
    myvar DWORD ?
    prompt byte "Enter the Integer: ",0
    result byte "This is your value: ",0

.code:
main PROC
    mov edx, offset, prompt
    mov ecx, sizeof, myvar
    call writestring

    mov edx, offset, myvar
    call readstring

    call writestring
    call writedec


    mov edx, offset prompt
    call writestring

    call readint

    mov myvar, eax

    mov edx, offset result
    call writestring

    mov eax, myvar
    call writeint


// Integer Input
; .data
;     myvar DWORD ?
;     prompt byte "Enter the Integer: ",0
;     result byte "This is your value: ",0

; .code
; main PROC 
;     mov edx, offset prompt
;     call writestring

;     call readint

;     mov myvar, eax

;     mov edx, offset result
;     call writestring

;     mov eax, myvar
;     call writeint








; .data:
;     xValue BYTE "Enter a value of x: ", 0
;     cValue BYTE "Enter a value of c: ", 0
;     result BYTE "F(x) = ", 0
;     xx SDWORD ?
;     cc SDWORD ?
;     result SDWORD ?

; .code:
; main PROC
;     mov edx, OFFSET, xcValue 
;     call WriteString
;     call ReadInt
;     mov xx, eax

;     mov edx, OFFSET, cValue
;     call WriteString
;     call ReadInt
;     mov cc, eax
    
;     mov edx, OFFSET, result
;     call WriteString

;     exit:
; END main
