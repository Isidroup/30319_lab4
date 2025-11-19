/**
 * @file circ_buf.c
 * @date :2025/10/22 08:11:31
 * @brief Implementación de las funciones de gestión del buffer circular.
 */

#include <stdint.h>
#include "circ_buf.h"

// Instanciación de objetos globales
// Buffer de transmisión
circ_buf_t g_tx_buffer;
// Buffer de recepción
circ_buf_t g_rx_buffer;

/* Inicializa el buffer circular y pone todos los datos a cero */
void circ_buf_init(circ_buf_t * const cb, const uint16_t head, const uint16_t tail) {

    //TODO: completar codigo

}

/* Devuelve 1 si el buffer está vacío, 0 si no */
uint8_t circ_buf_is_empty(circ_buf_t * const cb) {

    //TODO: completar codigo

}

/* Devuelve 1 si el buffer está lleno, 0 si no */
uint8_t circ_buf_is_full(circ_buf_t * const cb) {

    //TODO: completar codigo


}

/* Inserta un elemento en el buffer. Devuelve 0 si OK, -1 si lleno */
int8_t circ_buf_push(circ_buf_t * const cb, int16_t item) {

    //TODO: completar codigo


}

/* Extrae un elemento del buffer. Devuelve 0 si OK, -1 si vacío. Si vacío, pone ceros en item */
int8_t circ_buf_pop(circ_buf_t * const cb, int16_t * const item) {

    //TODO: completar codigo


}
