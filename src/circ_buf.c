/**
 * @file circ_buf.c
 * @date :2026/10/30 08:27:23
 * @brief Implementación de las funciones de gestión del buffer circular.
 */

#include <stdint.h>
#include "circ_buf.h"

// Instanciación de objetos globales
// Buffer de transmisión
volatile circ_buf_t g_tx_buffer;
// Buffer de recepción
volatile circ_buf_t g_rx_buffer;

/* Inicializa el buffer circular y pone todos los datos a cero */
void circ_buf_init(volatile circ_buf_t * self, uint16_t head, uint16_t tail) {

    //TODO: completar codigo

}

/* Devuelve 1 si el buffer está vacío, 0 si no */
uint8_t circ_buf_is_empty(volatile circ_buf_t * self) {

    //TODO: completar codigo

}

/* Devuelve 1 si el buffer está lleno, 0 si no */
uint8_t circ_buf_is_full(volatile circ_buf_t * self) {

    //TODO: completar codigo


}

/* Inserta un elemento en el buffer. Devuelve 0 si OK, -1 si lleno */
int8_t circ_buf_push(volatile circ_buf_t * self, int16_t item) {

    //TODO: completar codigo


}

/* Extrae un elemento del buffer. Devuelve 0 si OK, -1 si vacío. Si vacío, pone ceros en item */
int8_t circ_buf_pop(volatile circ_buf_t * self, int16_t * item) {

    //TODO: completar codigo


}
