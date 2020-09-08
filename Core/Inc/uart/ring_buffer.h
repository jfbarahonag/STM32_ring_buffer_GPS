/*
 * ring_buffer.h
 *
 *  Created on: Sep 7, 2020
 *      Author: felipebg
 */

#ifndef INC_UART_RING_BUFFER_H_
#define INC_UART_RING_BUFFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Opaque circular buffer structure
typedef struct ring_buf_t ring_buf_t;

// Handle type, the way users interact with the API
typedef ring_buf_t* cbuf_handle_t;

/// Pass in a storage buffer and size
/// Returns a circular buffer handle
cbuf_handle_t ring_buf_init(uint8_t* buffer, size_t size);

/// Free a circular buffer structure.
/// Does not free data buffer; owner is responsible for that
void ring_buf_free(cbuf_handle_t cbuf);

/// Reset the circular buffer to empty, head == tail
void ring_buf_reset(cbuf_handle_t cbuf);

/// Put version 1 continues to add data if the buffer is full
/// Old data is overwritten
void ring_buf_put(cbuf_handle_t cbuf, uint8_t data);

/// Retrieve a value from the buffer
/// Returns 0 on success, -1 if the buffer is empty
int ring_buf_get(cbuf_handle_t cbuf, uint8_t * data);

/// Returns true if the buffer is empty
bool ring_buf_empty(cbuf_handle_t cbuf);

/// Returns true if the buffer is full
bool ring_buf_full(cbuf_handle_t cbuf);

/// Returns the maximum capacity of the buffer
size_t ring_buf_capacity(cbuf_handle_t cbuf);

/// Returns the current number of elements in the buffer
size_t ring_buf_size(cbuf_handle_t cbuf);

#endif /* INC_UART_RING_BUFFER_H_ */
