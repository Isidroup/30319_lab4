/**
 * @file main.c
 * @brief Programa principal del laboratorio 4 - Modulación FSK y gestión de audio.
 * @date :2025/10/28 08:02:18
 * @date Last modified: 2025/10/20 09:37:00
 *
 * Este fichero implementa el programa principal para el laboratorio 4, que incluye:
 * - Configuración de periféricos (I2S, codec de audio WM8731, LEDs, pulsadores).
 * - Ejecutivo cíclico basado en Round-Robin para la gestión de tareas.
 * - Generación de señales FSK moduladas según pulsaciones de botón.
 * - Transmisión de audio a través de I2S mediante buffer circular.
 *
 * Hardware utilizado:
 * - Placa FM4 con codec de audio WM8731.
 * - LED RGB para indicación visual del estado.
 * - LED ETH con efecto breathing.
 * - Pulsador SW2 para control de usuario.
 *
 * Tareas del ejecutivo cíclico (periodo base 1 ms):
 *   Tarea 1: Evalúa el estado del pulsador SW2 (pulsación corta, larga o ninguna).
 *   Tarea 2: Actualiza el contador según la pulsación detectada.
 *            - Pulsación corta: incrementa contador (0-7).
 *            - Pulsación larga: reinicia contador a 0.
 *   Tarea 3: Controla el LED RGB según el valor del contador (8 colores).
 *   Tarea 4: Genera muestras de audio FSK y las almacena en el buffer circular.
 *            - lab41(): Modulación FSK con control por pulsaciones.
 *            - lab42(): Modulación FSK con transmisión de buffer de texto.
 *   Tarea 5: Efecto breathing en LED ETH (se ejecuta continuamente).
 *
 * Configuración del codec WM8731:
 * - Frecuencia de muestreo: 48 kHz.
 * - Entrada de audio: LINE_IN.
 * - Ganancia de salida (auriculares): 0 dB.
 * - Ganancia de entrada (line-in): 0 dB.
 *
 * Comunicación con ISR:
 * - El buffer circular g_tx_buffer se comparte entre main() y la ISR de I2S.
 * - g_tx_buffer se define en circ_buf.c y se declara como extern en circ_buf.h.
 * - Las operaciones de push están protegidas con __disable_irq()/__enable_irq().
 *
 * Arquitectura software: https://tinyurl.com/ysew73ht
 */

// Cabeceras de los módulos propios
#include "circ_buf.h"
#include "dds.h"
#include "ejercicios.h"
#include "pulsaciones.h"

// Cabeceras de los módulos hal y bsp
#include "FM4_WM8731.h"
#include "FM4_leds_sw.h"
#include "HAL_FM4_i2s.h"
#include "HAL_SysTick.h"

// Cabeceras estándar
#include "mcu.h"
#include <stdint.h>


/**
 *  @brief Función main(). Incluye la configuración e inicialización de
 *  periféricos y el "scheduling" de tareas
 */
int32_t main(void)
{
  // Configuración de LEDS y pulsador SW2
  LedsSwInit();

  // Configuración e inicio Systick
  SysTick_Init(SystemCoreClock / 1000); // base de tiempos -> 1ms

  // Inicialización del I2C, Codec e I2S.
  FM4_WM8731_init(FS_48000_HZ,               // Sampling rate (sps)
                  WM8731_LINE_IN,            // Audio input port
                  WM8731_HP_OUT_GAIN_0_DB,   // Output headphone jack Gain (dB)
                  WM8731_LINE_IN_GAIN_0_DB); // Line-in input gain (dB)

  // Puesta en marcha de I2S
  I2S_start();

  // Inicialización del buffer circular de transmisión
  circ_buf_init(&g_tx_buffer, 4, 0);


  // TODO:  Habilita interrupción I2S en NVIC
  ...

  /**
   * Ejecutivo cíclico, utilizamos Round-Robin para la organización de tareas
   * @cite  David E. Simon, "An Embedded Software Primer", Addison-Wesley 2005
   */

  uint8_t pulsacion = 0;
  uint8_t contador = 0;
  int16_t sample = 0;  // Muestra que se envía al códec

  while (1)
  {
    // 🗲 Tareas que se ejecutan cada ~1ms
    if (SysTick_ChkOvf()) {

      // Tarea 1: evalúa pulsación
      uint8_t entrada = Sw2Read(); // Lee SW2
      pulsacion = pulsaciones(entrada, 0);

      // Tarea 2: modifica contador
      if (pulsacion == 1) {
        contador = (contador + 1) & 7;
      }
      if (pulsacion == 2) {
        contador = 0;
      }

      // Tarea 3: Encendido del led RGB
      static const rgb_color_t color[8] = {OFF,    RED,     GREEN, BLUE,
                                           YELLOW, MAGENTA, CYAN,  WHITE};
      LedRGB(color[contador]);
    }

    // Tarea 4: Cálculo de la muestra a enviar por I2S
    /** @note: => Utiliza un buffer circular para compartir información con la ISR
     */

    __disable_irq(); // Proteger acceso a variable compartida
    // TODO: Guarda muestra en el buffer circular
    uint8_t error_push = ...
    __enable_irq();

    // TODO : Si no hay error al guardar la muestra, calcula la siguiente muestra
    ...

    // 🗲 Tareas que se ejecuta siempre
    if (1) {
      // Tarea 5: Encendido del led ETH con efecto breathing
      breath_led(LED_ETH);
    }
  }

  return 0; // nunca alcanzado
}
