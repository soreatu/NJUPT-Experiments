.486
DATA SEGMENT USE16
    BUF DB 'ABCDEFGHIJKLMNOPQRSTUVWXYZZYXWVUTSRQPONMLKJIHGFEDCBA$'
    BIN DB 0, 0, 0, 0, 0, 0, 0, 0, '$'
DATA ENDS

CODE    SEGMENT USE16
        ASSUME CS:CODE, DS:DATA
START:
        MOV AX, DATA
        MOV DS, AX

        MOV BX, OFFSET BUF
        MOV CX, 52                  ; 字符串长度
        MOV AH, 0                   ; AH用于计数

    LOOP1:                          ; 循环判断字符是否在0x42~0x45内
        MOV AL, BYTE PTR [BX]
        CMP AL, 42H
        JC NEXT
        CMP AL, 45H
        JA NEXT
        INC AH                      ; 计数+1
    NEXT:
        INC BX
        loop LOOP1
                                    ; 循环结束
        CALL DEC2BIN                ; 将AX中的十进制数转化为二进制

        MOV AH, 9                   ; 输出二进制结果
        MOV DX, OFFSET BIN
        INT 21H

        MOV AH, 4CH
        INT 21H


DEC2BIN  PROC                       ; 将十进制数转化为二进制
LAST:
        MOV DX, OFFSET BIN          ; 字符串基地址
        MOV CX, 8                   ; 字符串偏移量

    LOOP2:
        MOV AL, AH
        AND AL, 01H                 ; 取AH最低位
        SHR AH, 1                   ; AH右移一位

        MOV BX, DX
        ADD BX, CX
        SUB BX, 1                   ; 定位字符串地址
        MOV BYTE PTR [BX], AL
        ADD BYTE PTR [BX], 30H      ; 将对应数字进行ascii编码
        loop LOOP2

        RET
DEC2BIN ENDP

CODE ENDS
    END START
