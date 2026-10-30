# 30319 Laboratorio 4: Modulación FSK, modem v.23

Este proyecto implementa un sistema de modulación FSK (Frequency Shift Keying) para microcontroladores FM4, utilizando un codec de audio WM8731.

## Descripción General

El proyecto consiste en un sistema embebido que:
- Genera señales FSK moduladas controladas por pulsaciones de botón
- Utiliza interrupciones para la transmisión de la señal analógica a través de I2S con buffer circular
- Implementa control visual mediante LEDs RGB
- Utiliza un ejecutivo cíclico para la gestión de tareas en tiempo real

### Hardware Utilizado
- Placa FM4 con codec de audio WM8731
- LED RGB para indicación visual del estado
- Pulsador SW2 para control de usuario
- Comunicación I2S para transmisión de audio

## Estructura del Proyecto

```
lab4/
├── src/                    # Código fuente principal
├── shared/                 # Módulos compartidos
├── hal/                    # Capa de abstracción de hardware
├── bsp/                    # Soporte específico de la placa
├── build_keil/             # Archivos del proyecto Keil uVision
├── test/                   # Test
└── _doc/                   # Documentación
```

### Carpeta `src/` - Código Principal
- **`main.c`**: Programa principal con ejecutivo cíclico Round-Robin
- **`ejercicios.c/h`**: Implementación de los ejercicios de laboratorio (lab41, lab42)
- **`circ_buf.c/h`**: Buffer circular para gestión de audio I2S
- **`isr.c`**: Rutinas de interrupción del sistema

### Carpeta `shared/` - Módulos Compartidos
- **`includes/`**:
  - `dds.h`: Definiciones para Direct Digital Synthesis (generación de señales)
  - `pulsaciones.h`: Gestión de pulsaciones de botones
- **`src/`**:
  - `dds.c`: Implementación del DDS de 16 bits
  - `dds_sine_tbl257.dat`: Tabla de lookup para señal sinusoidal
  - `pulsaciones.c`: Detección de pulsaciones cortas y largas

### Carpeta `hal/` - Hardware Abstraction Layer
- **`include/`**:
  - `HAL_FM4_dtimer.h`: Temporizadores dual-timer
  - `HAL_FM4_gpio.h`: Control de pines GPIO
  - `HAL_FM4_i2c.h`: Comunicación I2C
  - `HAL_FM4_i2s.h`: Interfaz I2S para audio
  - `HAL_SysTick.h`: Temporizador del sistema
- **`src/`**: Implementaciones correspondientes de los HAL

### Carpeta `bsp/` - Board Support Package
- **`include/`**:
  - `FM4_leds_sw.h`: Control de LEDs y switches específicos de FM4
  - `FM4_WM8731.h`: Configuración del codec de audio WM8731
- **`src/`**: Implementaciones del BSP

### Carpeta `build_keil/` - Proyecto Keil uVision
- **`lab4.uvprojx`**: Archivo principal del proyecto Keil
- **`lab4.uvoptx`**: Opciones del proyecto
- **`lab4.uvguix.isidr`**: Interfaz de usuario específica
- **`Listings/`**: Archivos de listado generados
- **`Objects/`**: Archivos objeto compilados
- **`RTE/`**: Runtime Environment components

### Carpeta `test/` - Pruebas Unitarias
- **`test_circ_buf.c`**: Pruebas para el buffer circular
- **`test_lab4.c`**: Pruebas específicas del laboratorio


keywords: FSK, I2S, WM8731, DDS, Buffer Circular, Ejecutivo Cíclico, FM4, Modulación.
