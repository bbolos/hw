import sys

sid = b"0593729"

payload = sid + b"\x00" + b"A" * 2 + b"A+\x00"

sys.stdout.buffer.write(payload + b"\n")
