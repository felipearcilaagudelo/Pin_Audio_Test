# Smart Audio Pin - Proyecto de Monitoreo 

Este proyecto consiste en un dispositivo vestible en forma de pin diseñado para el registro de datos. El sistema captura audio de alta calidad mediante protocolo digital y lo transmite vía Wi-Fi a una estación maestra para su visualización en tiempo real y almacenamiento local.

## Caracteristicas Tecnicas
- Microcontrolador: ESP32-C6 (Arquitectura RISC-V).
- Protocolo de Audio: I2S (Inter-IC Sound) mediante micrófono MEMS digital.
- Transmision de Datos:
    - UDP: Transferencia de alta velocidad para generación de archivos .wav mediante Python.
    - WebSockets: Transmisión de baja latencia para visualización en interfaz web.
- Gestion de Energia: Optimizado para baterías Li-Po de 800mAh con una autonomía estimada de 8 horas continuas.

---

## Requisitos de Hardware

| Componente | Especificacion |
| :--- | :--- |
| MCU | ESP32-C6 Super Mini |
| Micrófono | INMP441 (Módulo I2S) |
| Batería | Li-Po 3.7V 800mAh |
| Sujeción | Imanes de Neodimio |

### Diagrama de Conexiones
| INMP441 (Micrófono) | ESP32-C6 (Pin) | Funcion |
| :--- | :--- | :--- |
| VDD | 3V3 | Alimentación 3.3V |
| GND | GND | Tierra |
| L/R | GND | Selección de Canal Mono |
| SCK | GPIO 1 | Reloj de bits (Bit Clock) |
| WS | GPIO 2 | Selección de palabra (Word Select) |
| SD | GPIO 3 | Salida de datos (Serial Data) |

---

## Configuracion del Entorno (PlatformIO)

El desarrollo del firmware se realiza mediante PlatformIO IDE dentro del ecosistema de Visual Studio Code.

### 1. Habilitacion de Rutas Largas en Windows
Debido a la profundidad de los directorios en el framework de Espressif, es obligatorio habilitar el soporte de rutas largas (Long Paths) para evitar errores de compilación críticos como la ausencia de sdkconfig.h:

1. Ejecutar PowerShell como Administrador.
2. Ingresar el siguiente comando:
   ```powershell
   New-ItemProperty -Path 'HKLM:\SYSTEM\CurrentControlSet\Control\FileSystem' -Name 'LongPathsEnabled' -Value 1 -PropertyType DWORD -Force
3. Reiniciar Visual Studio Code.

### 2. Uso de PlatformIO
- **Compilar**: Clic en el icono del Check (✓) en la barra inferior azul.
- **Subir Firmware**: Clic en la Flecha (→).
- **Monitor Serie**: Icono del Enchufe (Configurado a 115200 baudios).

### 3. Definicion de Placa Personalizada
Al ser el ESP32-C6 un chip reciente, el proyecto incluye una carpeta denominada `boards/` con el archivo `c6_arduino.json`. No borre esta carpeta, ya que permite que PlatformIO habilite el soporte de Arduino para esta placa.

---

## Estacion Maestra (Python y Web)

### Grabacion de Audio (receptor.py)
El script de Python actúa como servidor maestro, recibiendo los paquetes UDP y ensamblándolos en un archivo de audio real.
1. Asegurarse de tener Python instalado.
2. Configurar la dirección IP del computador en el código del ESP32.
3. Ejecutar el comando:
   ```bash
   python receptor.py
4. Presionar `Ctrl+C` para detener la grabación y generar el archivo `.wav`.

### Visualizacion Web (index.html)
Interfaz web para monitorear la amplitud del sonido desde cualquier navegador en la red local.
- Abrir el Monitor Serie en VS Code para conocer la dirección IP asignada al Pin.
- Editar la constante `ip` dentro del archivo `index.html`.
- Abrir `index.html` en Chrome o Edge para visualizar la gráfica en tiempo real.

---

### Solucion de Problemas
- **El audio se escucha muy bajo**: Verifique que el pequeño orificio central del micrófono INMP441 no esté obstruido por la carcasa o los cables.
- **Error de compilacion**: Si PlatformIO presenta fallos, elimine la carpeta oculta `.pio` y vuelva a intentar la operación mediante el icono de Check (✓).
- **No aparece el puerto serial**: Asegúrese de que el cable USB-C utilizado sea de transferencia de datos y no únicamente de carga.
