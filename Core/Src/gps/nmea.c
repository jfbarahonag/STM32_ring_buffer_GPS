/*
 * nmea.c
 *
 *  Created on: Sep 15, 2020
 *      Author: felipebg
 */

#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "gps/nmea.h"

/**
 * @brief: Parse data from buffer
 */

void nmea_parse_data(uint8_t *buff, uint8_t *keyword, size_t len)
{
	uint8_t *start, *end;

	const char *comma = ",";

	start = (uint8_t *)strnstr((const char *)buff, (const char *)keyword, len);
	end = (uint8_t *)strnstr((const char *)start, comma, len);
	assert(start && end);
	start = end+1;





}

