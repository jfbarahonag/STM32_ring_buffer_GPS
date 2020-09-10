/*
 * uart_driver.c
 *
 *  Created on: Sep 9, 2020
 *      Author: felipebg
 */
#include "uart/uart_driver.h"

uint8_t uart_write(cbuf_handle_t cbuf, uint8_t *data, size_t data_len)
{
	assert(cbuf);

	if(ring_buf_full(cbuf))
	{
		return 1;
	}

	if(ring_buf_free_space(cbuf) < data_len)
	{
		return 2;
	}

	size_t data_counter = 0;

	while (data_counter < data_len)
	{
		ring_buf_put(cbuf, data[data_counter++]);
	}

	return 0;

}

uint8_t uart_read(cbuf_handle_t cbuf, uint8_t *data, size_t data_len)
{
	assert(cbuf && data);

	size_t data_counter = 0;

	while (data_counter < data_len)
	{
		if (!ring_buf_get(cbuf, &data[data_counter++]))
		{
			return 0;
		}
	}

	return 1;
}

