        ORG 1000H
TABLA   DB 5 DUP (1, 2, 3, 4)
FIN_TAB DB ?
DATO    DB 2
CANT    DW ?

        ORG 2000H
        MOV BX, OFFSET TABLA
        MOV CL, OFFSET FIN_TAB - OFFSET TABLA
        MOV CANT, 0
LAZO:   MOV AL, [BX]
        CMP AL, DATO
        JNZ SIG
        INC CANT
SIG:    INC BX
        DEC CL
        JNZ LAZO
        HLT
        END
