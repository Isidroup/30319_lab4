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
#include "ejercicios.h"



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

    // Lee datos del buffer circular
    int16_t txdata;
    // TODO : Lee muestra del buffer circular
    uint8_t error = ...
    
    if ( error != 0) {
       // Si no hay datos en el buffer de transmisión, detiene la ejecución
        __BKPT(2); // ERROR, no debería pasar por aquí
    }
    // TODO:Envía muestra al canal izquierdo del codec, silencio en derecho
    ...
  }

  // 🗲 Si la interrupción se ha producido porque hay un dato nuevo
  //       en el buffer de entrada de I2S0
  if (I2S_isRxBufferNotEmpty()) {
    // No se hace nada, se completará en lab5
  }
  // NVIC_ClearPendingIRQ(PRGCRC_I2S_IRQn);
}

// EOF
