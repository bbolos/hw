  .section .rodata

hello:
  # Constant holding the message string to print.
  .ascii "Hello World\n"

  .section .text

  .globl _start
_start:
  ## Print message to standard output.

  movl  $4, %eax
  # Select the 'sys_write' syscall.
  # ===============================
  # The value in %eax determines which syscall the kernel will execute when
  # interrupt 0x80 is triggered by our code.

  movl  $1, %ebx
  # Set the output to file descriptor #1 (standard output).
  # =======================================================
  # The value in %ebx is the first argument to the syscall. In the case of
  # sys_write, that first argument is the file descriptor (fd) number to which
  # the string should be written.

  movl  $hello, %ecx
  # Set the target string to our message.
  # =====================================
  # The value in %ecx is the second argument to the syscall. In the case of
  # sys_write, that second argument is the address in memory of the string to
  # print. Since we defined 'hello' as our message string constant in the
  # .rodata section above, this will place its address in memory into %ecx.

  movl  $12, %edx
  # Set the length of the string to print.
  # ======================================
  # The value in %edx is the third argument to the syscal. In the case of
  # sys_write, that third argument is the length of the string to print. Our
  # message is 12 characters long, including the trailing newline.

  int   $0x80
  # Invoke the syscall and print the message string.
  # ===================
  # This triggers interrupt number 0x80, which the Linux kernel intercepts to
  # run the syscall we select in the %eax register, using the %ebx-%edx
  # registers as its arguments.

  ## Exit the program with code 0 (success).
  movl  $1, %eax      # Select the 'sys_exit' syscall
  movl  $0, %ebx      # Set the exit code to 0
  int   $0x80         # Invoke the syscall
