/*
 * uart_driver.c
 *
 *  Created on: Sep 9, 2020
 *      Author: felipebg
 */
#include "uart/uart_driver.h"
#include "stm32l4xx_hal.h"

void uart_write(cbuf_handle_t cbuf, uint8_t *data, size_t data_len)
{
	//if (ring_buf_write(cbuf, data, data_len) == )
}

void uart_read(cbuf_handle_t cbuf, uint8_t *data, size_t data_len)
{
	ring_buf_read(cbuf, data, data_len);
}

