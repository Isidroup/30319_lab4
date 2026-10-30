/*
 * ISR.c
 *  Created on: 13 jul. 2020
 *  Last modified: 2025/10/20 09:37:52
 */

#include "FM4_WM8731.h"
#include "HAL_FM4_gpio.h"
#include "HAL_FM4_i2s.h"


#include "s6e2cc.h"
#include "circ_buf.h"




/**
 * @brief  Rutina de servicio de interrupción de I2S
 *
 * @note   Esta rutina se ejecuta cada vez que está libre el buffer de
 *          transmisión de I2S, o cuando se recibe un dato por I2S.
 */

void PRGCRC_I2S_IRQHandler(void)
{

  // 🗲 Si la interrupción se ha producido porque hay hueco
  //      en el buffer de salida de I2S
  if (I2S_isTxBufferFree()) {

    // La condición de interrupción es «la FIFO tiene hueco». Se rellena hasta
    // eliminarla para evitar que la ISR se reactive inmediatamente.

    /*
     *                             ▼
     *                 ╱─────────────────────╲
     *                ╱  ¿I2S TX solicita     ╲ no
     *               ⟨       servicio?         ⟩──────────────────┐
     *                ╲                       ╱                   │
     *                 ╲─────────────────────╱                    │
     *                            │ sí                            │
     *                            ▼                               │
     *                  ╱───────────────────╲                     │
     *                 ╱  ¿Hay espacio en    ╲ no                 │
     *    ┌──────────►⟨       FIFO?           ⟩─────────┐         │
     *    │            ╲                     ╱          │         │
     *    │             ╲───────────────────╱           │         │
     *    │                       │ sí                  │         │
     *    │                       ▼                     │         │
     *    │             ╱───────────────────╲           │         │
     *    │            ╱  ¿g_tx_buffer tiene ╲          │         │
     *    │           ⟨       una muestra?    ⟩         │         │
     *    │            ╲                     ╱          │         │
     *    │             ╲───────────────────╱           │         │
     *    │                ╱             ╲              │         │
     *    │            sí ╱               ╲ no          │         │
     *    │              ▼                 ▼            │         │
     *    │ ┌──────────────┐     ┌─────────────────┐    │         │
     *    │ │ Extraer      │     │ Incrementar     │    │         │
     *    │ │ muestra y    │     │ contador de     │    │         │
     *    │ │ escribirla   │     │ infraflujo      │    │         │
     *    │ │ en FIFO I2S  │     │ software y      │    │         │
     *    │ └──────┬───────┘     │ escribir        │    │         │
     *    │        │             │ silencio        │    │         │
     *    │        │             └────────┬────────┘    │         │
     *    │        │                      │             │         │
     *    │        └──────────┬───────────┘             │         │
     *    │                   │ (Repetir while)         │         │
     *    └───────────────────┴                         ┼─────────┘
     *                                                  │
     *                                                  ▼
     *                                               ╭──────╮
     *                                               │ Fin  │
     *                                               ╰──────╯
     */


  }

  // 🗲 Si la interrupción se ha producido porque hay un dato nuevo
  //       en el buffer de entrada de I2S0
  if (I2S_isRxBufferNotEmpty()) {

    // No se hace nada, se completará en lab5
  }
  // NVIC_ClearPendingIRQ(PRGCRC_I2S_IRQn);
}

// EOF
