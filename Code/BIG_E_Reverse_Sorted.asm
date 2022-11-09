; BIG_E_Reverse_Sorted.asm

; Name:Dylan Carroll
; Student Numbers: -------------------------
; Date: 2021-07-29

; Purpose       Copy and Convert Little Endian data to a new Big Endian data array, Reverse then Sort Bid Endian
        org     $1000
Little_Endian                   ; Array of 16 bit Little Endian words
        dw      $1234, $2888, $AA55, $00FF, $FF00, $55AA, $0101,$FF00
End_Little_Endian
        org     $1010
Big_Endian
        ds   End_Little_Endian-Little_Endian    ; defines storage dynamically as the same size of little endian at right location using org
End_Big_Endian
        org     $1020
Reverse
        ds    End_Little_Endian-Little_Endian
End_Reverse
        org     $1030
Sorted
        ds    End_Little_Endian-Little_Endian
End_Sorted
        org     $2000
        lds     #$2000
        ldx     #Little_Endian      ; point x and y to start of the arrays to iterate through
        ldy     #Big_Endian
Back
        ldd     0,x  ; load d with the current 16 bit value
        exg     a,b  ; swaps values for the proper display in memory with offset
        std     16,x ; as the value to be entered will always be 16 away from x true value
        inx          ; double increment for the 16 bit
        inx
        iny
        cpx     #End_Little_Endian ; compares pointer to last location in array to determine when finished
        blo     Back               ;will loop until it is equal
 ;END OF ENDIAN CODE
 
        ldx     #Big_Endian-1    ; sets pointer to write from end of reverse into start of big Endian
        ldy     #End_Reverse
Back2
        ldaa     1,x+           ; Load in current value to
        staa     1,y-
        cpx     #End_Big_Endian ; Is x at end of Big Endian?
        bne     Back2
 ;END OF REVERSE CODE
         ldx    #Reverse+1
Loop1
                        cpx     #End_Reverse ;Compare to determine if at end of array
                        beq     EndLoop
                        ldab    0,x  ;Hold first unsorted value
                        leay    0,x   ;Point y to the value
Loop2
                        cpy     #Reverse ;Compare to see if at start
                        bls     Endif  ;end loop when at start
                        ldaa    -1,y
                        cba             ;Compare to sorted value
                        bls     Endif
                        staa    0,y
                        dey               ;Continute while greater than
                        bra     Loop2
Endif
                        stab    0,y

                        inx
                        
                        bra     Loop1  ;Begin iteration with next unsorted value
EndLoop

Done    swi
        end                                    ;end program