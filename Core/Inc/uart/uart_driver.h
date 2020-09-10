/*
 * uart_driver.h
 *
 *  Created on: Sep 9, 2020
 *      Author: felipebg
 */

#ifndef INC_UART_UART_DRIVER_H_
#define INC_UART_UART_DRIVER_H_

#include "ring_buffer.h"

uint8_t uart_write(cbuf_handle_t cbuf, uint8_t *data, size_t data_len);
uint8_t uart_read(cbuf_handle_t cbuf, uint8_t *data, size_t data_len);

#endif /* INC_UART_UART_DRIVER_H_ */
