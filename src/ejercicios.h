/**
 * @file ejercicios.h
 * @brief Prototipos de funciones
 *
 * @details Este archivo contiene las declaraciones de las funciones que implementan
 *          los ejercicios de modulación FSK (Frequency Shift Keying) para el laboratorio 4.
 *          Las funciones generan muestras de audio moduladas en FSK según diferentes
 *          estrategias de control y transmisión de datos.
 * @date 2025/10/20
 */

#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include <stdint.h>


/**
 * @brief Genera muestras de audio con modulación FSK controlada por pulsaciones.
 *
 * @details Esta función implementa el ejercicio 1 del laboratorio. Genera una señal
 *          modulada en FSK donde la frecuencia de la portadora cambia según el estado
 *          de pulsación del botón SW2. Utiliza DDS (Direct Digital Synthesis) para
 *          generar las diferentes frecuencias correspondientes a bits '0' y '1'.
 *
 *          Comportamiento según pulsación:
 *          - **Pulsación corta**: Conmuta entre tonos de 1300 Hz y 2100 Hz
 *          - **Pulsación larga**: Inicia o termina la modulación de la secuencia
 *                                  alternante 101010101... a una velocidad de 1200 bps
 *          - **Sin pulsación**: Mantiene el estado actual de transmisión
 *
 *          Especificaciones FSK (estándar V.23):
 *          - Frecuencia para bit '0': 2100 Hz (espacio)
 *          - Frecuencia para bit '1': 1300 Hz (marca)
 *          - Velocidad de transmisión: 1200 bps (bits por segundo)
 *          - Muestras por bit: fs/1200 (ej: 48000/1200 = 40 muestras/bit)
 *
 * @param[in] pulsacion Estado de pulsación del botón SW2:
 *                      - 0: Sin pulsación detectada
 *                      - 1: Pulsación corta detectada
 *                      - 2: Pulsación larga detectada
 *
 * @return int16_t Muestra de audio de 16 bits con signo, lista para transmisión I2S.
 *                 El valor representa la amplitud instantánea de la señal FSK modulada
 *                 en el rango [-32768, 32767].
 */
int16_t lab41(uint8_t pulsacion);

/**
 * @brief Genera muestras de audio con modulación FSK para transmisión de texto.
 *
 * @details Esta función implementa el ejercicio 2 del laboratorio. Genera una señal
 *          modulada en FSK que transmite un buffer de caracteres de texto. Cada carácter
 *          se codifica en sus bits individuales (típicamente 8 bits por carácter ASCII)
 *          y se transmite usando diferentes frecuencias para representar '0' y '1'.
 *          Utiliza DDS (Direct Digital Synthesis) para la generación de las portadoras FSK.
 *
 *          Comportamiento según pulsación:
 *          - **Sin pulsación/Pulsación corta**: Genera tono continuo de 1300 Hz (bit '1')
 *          - **Pulsación larga**: Inicia la modulación y transmisión del buffer de texto
 *                                  a una velocidad de 1200 bps
 *          - **Durante transmisión**: Continúa hasta finalizar el mensaje completo
 *
 *           Proceso de transmisión:
 *             1. Al recibir pulsación larga, comienza la transmisión
 *             2. Para cada carácter se transmite una trama de 10 bits:
 *                - **Bit de START**: 1 bit con valor '0' (2100 Hz)
 *                - **Datos**: 8 bits del carácter ASCII (LSB primero)
 *                - **Bit de STOP**: 1 bit con valor '1' (1300 Hz)
 *             3. Cada bit se transmite durante N muestras (fs/1200 para 1200 bps)
 *             4. Bit '0' → frecuencia de 2100 Hz (espacio)
 *             5. Bit '1' → frecuencia de 1300 Hz (marca)
 *             6. Al finalizar el mensaje, retorna al estado de reposo (tono de 1300 Hz)
 *
 *             Formato de trama asíncrona (10 bits por carácter):
 *             ```
 *             [START] [D0] [D1] [D2] [D3] [D4] [D5] [D6] [D7] [STOP]
 *                0    LSB                                 MSB     1
 *             ```
 *
 *          Especificaciones FSK:
 *          - Frecuencia para bit '0': 2100 Hz
 *          - Frecuencia para bit '1': 1300 Hz
 *          - Velocidad de transmisión: 1200 bps
 *          - Codificación: ASCII estándar (8 bits por carácter)
 *
 * @param[in] pulsacion Estado de pulsación del botón SW2:
 *                      - 0: Sin pulsación
 *                      - 1: Pulsación corta (genera tono continuo 1300 Hz)
 *                      - 2: Pulsación larga (inicia transmisión del mensaje)
 *
 * @param[in] frase Puntero a cadena de caracteres terminada en '\0' que se transmitirá
 *                  mediante modulación FSK. El buffer debe permanecer válido y constante
 *                  durante toda la transmisión.
 *                  Ejemplo: "SEMP 30319" o "HOLA MUNDO"
 *
 * @return int16_t Muestra de audio de 16 bits con signo, lista para transmisión I2S.
 *                 Representa la amplitud instantánea de la señal FSK correspondiente
 *                 al bit actual que se está transmitiendo, en el rango [-32768, 32767].
 *
 * @warning El puntero 'frase' debe apuntar a memoria válida durante toda la
 *          ejecución del programa. No copiar en buffer local.
 *
 */
int16_t lab42(uint8_t pulsacion, char frase[]);

#endif // EJERCICIOS_H
