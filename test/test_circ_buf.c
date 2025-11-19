/**
 * @file test_cb.c
 * @brief Pruebas unitarias para el buffer circular.
 *
 * Este fichero contiene un conjunto de tests automáticos para verificar
 * el correcto funcionamiento de la implementación del buffer circular.
 *
 * Uso:
 *   - Compila y ejecuta este fichero junto con la implementación de circ_buf.c.
 *   - El test se ejecuta automáticamente al iniciar main().
 *   - Si alguna comprobación falla, se ejecuta una instrucción BKPT con un código de error
 *     que permite identificar el test fallido desde el depurador.
 *   - Si todos los tests pasan correctamente, se ejecuta BKPT 0 al final.
 *
 * Tests realizados:
 *   1. Comprobar que el buffer está vacío tras inicialización.
 *   2. Comprobar que el buffer no está lleno tras inicialización.
 *   3. Comprobar que la lectura en vacío devuelve error y pone ceros.
 *   4. Llenar el buffer hasta CIRC_BUF_SIZE-1 (el último push debe fallar).
 *   5. Comprobar que el buffer está lleno.
 *   6. Comprobar que el buffer no está vacío cuando está lleno.
 *   7. Leer todos los elementos y comprobar el orden de salida.
 *   8. Comprobar que el buffer está vacío tras vaciado.
 *   9. Comprobar que el pop en vacío sigue devolviendo error y ceros.
 *   A. Comprobar que el push vuelve a funcionar tras vaciar el buffer.
 *   B. Test adicional: comprobación de wrap-around de head y tail (llenar y vaciar varias veces).
 */
#include <stdint.h>
#include "circ_buf.h"

#include "ARMCM4.h"


// Variables globales
__attribute__((section(".bss.noinit")))
char g_TestN;


int32_t main(void)
{
    g_TestN = '0';
    // Test de buffer circular
    circ_buf_init(&g_tx_buffer, 0, 0);

    // 1. Comprobar que está vacío
    g_TestN = '1';
    if (!circ_buf_is_empty(&g_tx_buffer)) {
        __BKPT(1); // error: el buffer debería estar vacío
    }
    // 2. Comprobar que no está lleno
    g_TestN = '2';
    if (circ_buf_is_full(&g_tx_buffer)) {
        __BKPT(1); // error: el buffer no debería estar lleno
    }

    // 3. Comprobar que la lectura en vacío devuelve error y pone ceros
    g_TestN = '3';
    int16_t sample = 0x5555;
    if (circ_buf_pop(&g_tx_buffer, &sample) == 0) {
        __BKPT(1); // error: no debería poder leer de un buffer vacío
    }
    if (sample != 0) {
        __BKPT(1); // error: el valor leído debe ser 0
    }

    // 4. Llenar el buffer hasta CIRC_BUF_SIZE-1 (el último push debe fallar)
    g_TestN = '4';
    for (int i = 0; i < CIRC_BUF_SIZE; i++) {
        int16_t sample_in = i;

        if (i < CIRC_BUF_SIZE - 1) {
            // Debe poder insertar correctamente
            if (circ_buf_push(&g_tx_buffer, sample_in) != 0) {
                __BKPT(1); // error: el push debería funcionar
            }
        } else {
            // El último push debe fallar (buffer lleno)
            if (circ_buf_push(&g_tx_buffer, sample_in) == 0) {
                __BKPT(1); // error: el push debería fallar
            }
        }
    }

    // 5. Comprobar que está lleno
    g_TestN = '5';
    if (!circ_buf_is_full(&g_tx_buffer)) {
        __BKPT(1); // error: el buffer debería estar lleno
    }

    // 6. Comprobar que no está vacío
    g_TestN = '6';
    if (circ_buf_is_empty(&g_tx_buffer)) {
        __BKPT(1); // error: el buffer no debería estar vacío
    }

    // 7. Leer todos los elementos y comprobar el orden
    g_TestN = '7';
    for (int i = 0; i < CIRC_BUF_SIZE - 1; i++) {
        int16_t sample_out = 0xFFFF;
        if (circ_buf_pop(&g_tx_buffer, &sample_out) != 0) {
            __BKPT(1); // error: el pop debería funcionar
        }
        if (sample_out != i) {
            __BKPT(1); // error: los datos no coinciden con lo insertado
        }
    }

    // 8. Ahora el buffer debe estar vacío
    g_TestN = '8';
    if (!circ_buf_is_empty(&g_tx_buffer)) {
        __BKPT(1); // error: el buffer debería estar vacío
    }

    // 9. Comprobar que el pop en vacío sigue devolviendo error y ceros
    g_TestN = '9';
    int16_t sample_final = 0x1234;
    if (circ_buf_pop(&g_tx_buffer, &sample_final) == 0) {
        __BKPT(1); // error: no debería poder leer de un buffer vacío
    }
    if (sample_final != 0) {
        __BKPT(1); // error: el valor leído debe ser 0
    }

    // A. Comprobar que el push vuelve a funcionar tras vaciar el buffer
    g_TestN = 'A';
    int16_t sample_test = 24;
    if (circ_buf_push(&g_tx_buffer, sample_test) != 0) {
        __BKPT(1); // error: el push debería funcionar
    }
    if (circ_buf_is_empty(&g_tx_buffer)) {
        __BKPT(1); // error: el buffer no debería estar vacío
    }
    if (circ_buf_is_full(&g_tx_buffer)) {
        __BKPT(1); // error: el buffer no debería estar lleno
    }
    int16_t sample_check = 0;
    if (circ_buf_pop(&g_tx_buffer, &sample_check) != 0) {
        __BKPT(1); // error: el pop debería funcionar
    }
    if (sample_check != 24) {
        __BKPT(1); // error: los datos no coinciden
    }

    // B. Test adicional: comprobación de wrap-around de head y tail
    // Llenar y vaciar el buffer varias veces para forzar el avance circular
    g_TestN = 'B';
    circ_buf_init(&g_tx_buffer, 0, 0);

    // Repetimos el ciclo de llenado/vaciado suficiente veces para asegurar el wrap
    for (int ciclo = 0; ciclo < 3; ciclo++) {
        // Llenar el buffer
        for (int i = 0; i < CIRC_BUF_SIZE - 1; i++) {
            int16_t sample_in = ciclo * 100 + i;
            if (circ_buf_push(&g_tx_buffer, sample_in) != 0) {
                __BKPT(1); // error: el push debería funcionar
            }
        }
        // Comprobar que está lleno
        if (!circ_buf_is_full(&g_tx_buffer)) {
            __BKPT(1); // error: el buffer debería estar lleno
        }
        // Vaciar el buffer y comprobar el orden
        for (int i = 0; i < CIRC_BUF_SIZE - 1; i++) {
            int16_t sample_out = 0xFFFF;
            if (circ_buf_pop(&g_tx_buffer, &sample_out) != 0) {
                __BKPT(1); // error: el pop debería funcionar
            }
            if (sample_out != ciclo * 100 + i) {
                __BKPT(1); // error: los datos no coinciden
            }
        }
        // Comprobar que está vacío
        if (!circ_buf_is_empty(&g_tx_buffer)) {
            __BKPT(1); // error: el buffer debería estar vacío
        }
    }

    // Fin del test, todo correcto
    g_TestN = 'F';
    __BKPT(0); // Punto de parada para indicar que todo ha ido bien
}
