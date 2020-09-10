/*
 * ring_buffer.c
 *
 *  Created on: Sep 7, 2020
 *      Author: felipebg
 */
#include <stdlib.h>

#include "uart/ring_buffer.h"

// The hidden definition of our circular buffer structure
struct ring_buf_t {
	uint8_t * buffer;
	size_t head;
	size_t tail;
	size_t max; //of the buffer
	bool full;
};

cbuf_handle_t ring_buf_init(uint8_t* buffer, size_t size)
{
	assert(buffer && size);

	cbuf_handle_t cbuf = malloc(sizeof(ring_buf_t));
	assert(cbuf);

	cbuf->buffer = buffer;
	cbuf->max = size;
	ring_buf_reset(cbuf);

	assert(ring_buf_empty(cbuf));

	return cbuf;
}

void ring_buf_reset(cbuf_handle_t cbuf)
{
    assert(cbuf);

    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = false;
}

void ring_buf_free(cbuf_handle_t cbuf)
{
	assert(cbuf);
	free(cbuf);
}

bool ring_buf_full(cbuf_handle_t cbuf)
{
	assert(cbuf);

    return cbuf->full;
}

bool ring_buf_empty(cbuf_handle_t cbuf)
{
	assert(cbuf);

    return (!cbuf->full && (cbuf->head == cbuf->tail));
}

size_t ring_buf_capacity(cbuf_handle_t cbuf)
{
	assert(cbuf);

	return cbuf->max;
}

size_t ring_buf_size(cbuf_handle_t cbuf)
{
	assert(cbuf);

	size_t size = cbuf->max;

	if(!cbuf->full)
	{
		if(cbuf->head >= cbuf->tail)
		{
			size = (cbuf->head - cbuf->tail);
		}
		else
		{
			size = (cbuf->max + cbuf->head - cbuf->tail);
		}
	}

	return size;
}

static void advance_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	if(cbuf->full)
   	{
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
	}

	cbuf->head = (cbuf->head + 1) % cbuf->max;
	cbuf->full = (cbuf->head == cbuf->tail);
}

static void retreat_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->max;
}

void ring_buf_put(cbuf_handle_t cbuf, uint8_t data)
{
	assert(cbuf && cbuf->buffer);

    cbuf->buffer[cbuf->head] = data;

    advance_pointer(cbuf);
}

int ring_buf_get(cbuf_handle_t cbuf, uint8_t * data)
{
    assert(cbuf && data && cbuf->buffer);

    int r = -1;

    if(!ring_buf_empty(cbuf))
    {
        *data = cbuf->buffer[cbuf->tail];
        retreat_pointer(cbuf);

        r = 0;
    }

    return r;
}

size_t ring_buf_free_space(cbuf_handle_t cbuf)
{
	return cbuf->max - ring_buf_size(cbuf);
}
