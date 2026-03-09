import socket
import wave
import struct

# Configuración - LA MISMA QUE EN EL ESP32
UDP_IP = "0.0.0.0" # Escucha en todas las interfaces
UDP_PORT = 4444
FILE_NAME = "grabacion_niño_1.wav"

# Configuración del archivo WAV (16kHz, Mono, 16-bit)
audio_file = wave.open(FILE_NAME, 'wb')
audio_file.setnchannels(1)
audio_file.setsampwidth(2) # 2 bytes = 16 bits
audio_file.setframerate(16000)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(f"Escuchando en el puerto {UDP_PORT}... Presiona Ctrl+C para detener y guardar.")

try:
    while True:
        data, addr = sock.recvfrom(2048) # Recibe paquetes de audio
        audio_file.writeframes(data)
except KeyboardInterrupt:
    print("\nGrabación finalizada y guardada.")
finally:
    audio_file.close()
    sock.close()