/**
 * @file test_lab4.c
 * @brief Test de integración para las funciones de laboratorio 4 (modulación FSK).
 *
 * Este fichero contiene tests para verificar el funcionamiento de las funciones
 * de modulación FSK implementadas en ejercicios.c, simulando pulsaciones de botón
 * que activan y desactivan la modulación.
 *
 * Uso:
 *   - Compila y ejecuta este fichero junto con ejercicios.c.
 *   - El test simula una secuencia de pulsaciones cortas y largas del botón.
 *   - La función bajo prueba (lab41 o lab42) genera muestras
 *     basadas en las pulsaciones detectadas.
 *   - Al finalizar, se ejecuta BKPT #0 para inspeccionar las variables con el debugger.
 *
 * Secuencia de test simulada (2448 muestras @ 48kHz ≈ 51ms):
 *   - Muestras 0-499:     Sin pulsación (g_pls = 0)
 *   - Muestras 500-547:   Pulsación corta (g_pls = 1, duración = 1ms)
 *   - Muestras 548-999:   Sin pulsación (g_pls = 0)
 *   - Muestras 1000-1047: Pulsación corta (g_pls = 1, duración = 1ms)
 *   - Muestras 1048-1299: Sin pulsación (g_pls = 0)
 *   - Muestras 1300-1347: Pulsación larga (g_pls = 2, duración = 1ms) - INICIA modulación
 *   - Muestras 1348-1999: Sin pulsación (g_pls = 0) - Modulación activa
 *   - Muestras 2000-2047: Pulsación larga (g_pls = 2, duración = 1ms) - FINALIZA modulación
 *   - Muestras 2048-2447: Sin pulsación (g_pls = 0)
 *
 * Funciones probadas:
 *   - lab41(): Modulación FSK con control por pulsaciones.
 *              - Pulsación corta: conmuta entre tono de 1300 Hz y 2100 Hz.
 *              - Pulsación larga: inicia/termina la modulación de la secuencia 101010101... a 1200 bps.
 *   - lab42(): Modulación FSK con transmisión de buffer de texto.
 *              - Sin pulsación o pulsación corta: genera tono de 1300 Hz ('1').
 *              - Pulsación larga: inicia la modulación del buffer de texto a 1200 bps.
 *              - No utiliza la pulsación corta.
 *
 * Variables globales inspeccionables:
 *   - g_sample: Última muestra de audio generada.
 *   - g_pls: Estado de la pulsación en el momento actual.
 *   - time: Tiempo transcurrido en la simulación (en segundos).
 */
#include "pulsaciones.h"
#include "ejercicios.h"
#include <stdint.h>

// Variables globales para el test
__attribute__((section(".bss.noinit")))
int16_t g_sample;           // Muestra de audio calculada en cada iteración
uint8_t g_pls;              // Estado de pulsación (0=ninguna, 1=corta, 2=larga)
const float period = 1.0/48000;  // Período de muestreo (20.83 μs @ 48 kHz)
float time = 0.0;           // Tiempo acumulado de simulación

int main() {
  // Cadena de prueba para lab42 (transmisión de buffer de texto)
  char frase[] = "1";

  // Estado inicial: sin pulsación
  g_pls = 0;

  // Bucle principal de simulación (2448 muestras ≈ 51 ms)
  for (uint16_t i = 0; i < 2448; i++) {

    // --- Generación del patrón de pulsaciones ---

    // Primera pulsación corta: muestras 500-547 (1 ms)
    if ((i >= 500) && (i < 548)) {
      g_pls = 1;
    }
    // Segunda pulsación corta: muestras 1000-1047 (1 ms)
    else if ((i >= 1000) && (i < 1048)) {
      g_pls = 1;
    }
    // Primera pulsación larga: muestras 1300-1347 (1 ms) - Inicia modulación
    else if ((i >= 1300) && (i < 1348)) {
      g_pls = 2;
    }
    // Segunda pulsación larga: muestras 2000-2047 (1 ms) - Finaliza modulación
    else if ((i >= 2000) && (i < 2048)) {
      g_pls = 2;
    }
    // Sin pulsación en el resto del tiempo
    else {
      g_pls = 0;
    }

    // Actualizar el tiempo transcurrido
    time = time + period;

    // --- Ejecutar la función bajo prueba ---
    g_sample = lab41(g_pls);
    // Alternativa: probar lab42 con transmisión de buffer de texto
    // g_sample = lab42(g_pls, frase);
  }

  // --------------------------------------------------------------------------
  // Fin del test - Punto de inspección con debugger
  __asm volatile ("BKPT #0");

  // Bucle infinito (nunca se alcanza en depuración)
  while(1);
}
