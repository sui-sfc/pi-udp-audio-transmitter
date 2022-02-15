import pyaudio
import wave
import time
from socket import socket, AF_INET, SOCK_DGRAM

CHUNK = 256
HOST = ''
PORT = 60000
ADDRESS = '192.168.0.29'

s = socket(AF_INET, SOCK_DGRAM)

p = pyaudio.PyAudio()


stream = p.open(format=pyaudio.paInt16,
                channels=2,
                rate=44100,
                input=True,
                frames_per_buffer = CHUNK*2
                )
empty = b''

for i in range (CHUNK*4):
    empty += b'\x00'
data = stream.read(CHUNK)
print('Now streaming')
while data != b'':
    s.sendto(data, (ADDRESS,PORT))
    data = b''
    data = stream.read(CHUNK)
s.close()

stream.stop_stream()
stream.close()
wf.close()
p.terminate()

