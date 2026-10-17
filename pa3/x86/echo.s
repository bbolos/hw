.section .rodata
err_msg:
    .ascii "This command expects exactly one argument.\n"
newline:
    .ascii "\n"

.section .text
.globl _start
_start:
    #kijk of argc gelijk is aan 2
    cmpl    $2, (%esp)
    jne     err

    #pak argv[1]
    movl    8(%esp), %edi

    #lengte van argv[1]
    movb    $0, %al
    movl    $-1, %ecx
    repne   scasb
    notl    %ecx
    decl    %ecx

    #print argv[1] naar stdout
    movl    %ecx, %edx
    movl    8(%esp), %ecx
    movl    $4, %eax
    movl    $1, %ebx
    int     $0x80

    # Print '\n' (enter)
    movl    $4, %eax
    movl    $1, %ebx
    movl    $newline, %ecx
    movl    $1, %edx
    int     $0x80

    # Exit 0
    movl    $1, %eax
    xorl    %ebx, %ebx
    int     $0x80

err:
    # Print error naar stderr (fd=2)
    movl    $4, %eax
    movl    $2, %ebx
    movl    $err_msg, %ecx
    movl    $42, %edx
    int     $0x80

    # Exit 1
    movl    $1, %eax
    movl    $1, %ebx
    int     $0x80
