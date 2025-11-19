# Laboratorio 4 - Modulación FSK y Gestión de Audio

Este proyecto implementa un sistema de modulación FSK (Frequency Shift Keying) y gestión de audio para microcontroladores FM4, utilizando un codec de audio WM8731 y un ejecutivo cíclico basado en Round-Robin.

## Descripción General

El proyecto consiste en un sistema embebido que:
- Genera señales FSK moduladas controladas por pulsaciones de botón
- Gestiona audio a través de I2S con buffer circular
- Implementa control visual mediante LEDs RGB
- Utiliza un ejecutivo cíclico para la gestión de tareas en tiempo real

### Hardware Utilizado
- Placa FM4 con codec de audio WM8731
- LED RGB para indicación visual del estado
- LED ETH con efecto breathing
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

## Funcionalidad del Sistema

### Ejecutivo Cíclico (Base de tiempo: 1ms)

El sistema implementa 5 tareas principales:

1. **Tarea 1**: Evaluación del estado del pulsador SW2
   - Detecta pulsaciones cortas, largas o ninguna

2. **Tarea 2**: Control del contador
   - Pulsación corta: incrementa contador (0-7)
   - Pulsación larga: reinicia contador a 0

3. **Tarea 3**: Control del LED RGB
   - 8 colores diferentes según el valor del contador
   - Estados: OFF, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE

4. **Tarea 4**: Generación de muestras FSK
   - `lab41()`: Modulación FSK controlada por pulsaciones
   - `lab42()`: Modulación FSK para transmisión de texto
   - Almacenamiento en buffer circular protegido por interrupciones

5. **Tarea 5**: Efecto breathing en LED ETH
   - Se ejecuta continuamente para crear efecto visual

### Configuración del Audio

- **Frecuencia de muestreo**: 48 kHz
- **Entrada de audio**: LINE_IN
- **Ganancia de salida**: 0 dB (auriculares)
- **Ganancia de entrada**: 0 dB (line-in)

### Comunicación ISR

El buffer circular `g_tx_buffer` se comparte entre `main()` y la ISR de I2S, con operaciones protegidas mediante `__disable_irq()/__enable_irq()`.

## Compilación y Uso

1. Abrir el proyecto en Keil uVision 5
2. Cargar `build_keil/lab4.uvprojx`
3. Compilar y cargar en la placa FM4
4. Utilizar el pulsador SW2 para controlar la modulación FSK
5. Observar los cambios en el LED RGB según el estado del contador

## Referencias

- David E. Simon, "An Embedded Software Primer", Addison-Wesley 2005
  (Diseño del ejecutivo cíclico Round-Robin)

## Notas de Desarrollo

- El proyecto utiliza ARM Cortex-M4 como procesador objetivo
- Implementa protección de variables compartidas en contexto de interrupciones
- Diseño modular con separación clara entre HAL, BSP y lógica de aplicación