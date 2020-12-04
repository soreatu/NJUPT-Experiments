.486
DATA SEGMENT USE16
        PROMT_USERNAME DB 'username: ', '$'
        PROMT_PASSWORD DB 'password: ', '$'
        PROMT_SUCCESS  DB 'login success!', 0DH, 0AH, '$'
        PROMT_INVALID DB 'Invalid username or password!', 0DH, 0AH, '$'
        PRMOT_TRY_AGAIN DB 'Please try again...', 0DH, 0AH, '$'
        NEWLINE  DB 0DH, 0AH, '$'

        USERNAME DB 'root$'
        PASSWORD DB '123456$'

        BUFFER1 DB 64 dup (?)
        BUFFER2 DB 64 dup (?)
DATA ENDS


CODE SEGMENT USE16
START:
        MOV AX, DATA
        MOV DS, AX

    LOGIN:
        ; 输出提示，读取用户名
        MOV AH, 9
        MOV DX, OFFSET PROMT_USERNAME
        INT 21H                             ; 提示输入用户名

        MOV BX, OFFSET BUFFER1
    INPUT_USERNAME:
        MOV AH, 1
        INT 21H                             ; 从键盘输入一个字符（有回显）

        MOV BYTE PTR [BX], AL               ; 将读取到的字符放入缓冲区中
        INC BX

        CMP AL, 0DH                         ; 如果是非换行符，就继续读取
        JNZ INPUT_USERNAME

        CALL PRINT_NEWLINE


        ; 输出提示，读取密码
        MOV AH, 9
        MOV DX, OFFSET PROMT_PASSWORD
        INT 21H                             ; 提示输入密码

        MOV BX, OFFSET BUFFER2
    INPUT_PASSWORD:
        MOV AH, 7
        INT 21H                             ; 从键盘输入一个字符（无回显）

        MOV BYTE PTR [BX], AL               ; 将读取到的字符放入缓冲区中
        INC BX

        CMP AL, 0DH                         ; 如果是非换行符，就继续读取
        JNZ INPUT_PASSWORD

        CALL PRINT_NEWLINE


        ; 与硬编码的用户名进行比较
        MOV CX, 4                           ; 用户名长度
        MOV DX, 0
    COMPARE_USERNAME:
        MOV BX, OFFSET USERNAME
        ADD BX, DX
        MOV AL, BYTE PTR[BX]                ; 硬编码的一个字符

        MOV BX, OFFSET BUFFER1
        ADD BX, DX
        MOV AH, BYTE PTR[BX]                ; 输入的一个字符

        CMP AH, AL                          ; 逐字符比较
        JNZ FAIL

        INC DX
        LOOP COMPARE_USERNAME


        ; 与硬编码的密码进行比较
        MOV CX, 6                           ; 密码长度
        MOV DX, 0
    COMPARE_PASSWORD:
        MOV BX, OFFSET PASSWORD
        ADD BX, DX
        MOV AL, BYTE PTR[BX]                ; 硬编码的一个字符

        MOV BX, OFFSET BUFFER2
        ADD BX, DX
        MOV AH, BYTE PTR[BX]                ; 输入的一个字符

        CMP AH, AL                          ; 逐字符比较
        JNZ FAIL

        INC DX
        LOOP COMPARE_PASSWORD

        ; 检测均通过
        MOV AH, 9
        MOV DX, OFFSET PROMT_SUCCESS
        INT 21H                             ; 登录成功！

        MOV AH, 4CH
        INT 21H


    FAIL:
        MOV AH, 9
        MOV DX, OFFSET PROMT_INVALID
        INT 21H

        MOV AH, 9
        MOV DX, OFFSET PRMOT_TRY_AGAIN
        INT 21H

        CALL PRINT_NEWLINE

        JMP LOGIN


PRINT_NEWLINE PROC
        MOV AH, 9
        MOV DX, OFFSET NEWLINE
        INT 21H

        RET
PRINT_NEWLINE ENDP

CODE ENDS
    END START