/*
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright (c) 2022 Microsoft Corporation
 */
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#pragma weak write_buf
void write_buf(char *buf, size_t ix, char c)
{
	buf[ix] = c;
}

int main(void)
{
	char upper[0x10] = {'u', 'u'};
	char lower[0x10] = {'l', 'l'};

	printf("upper = %p, lower = %p, diff = %zx\n",
				 upper, lower, (size_t)(upper - lower));

	/* Assert that these get placed how we expect */
	assert((ptraddr_t)upper == (ptraddr_t)&lower[sizeof(lower)]);

	printf("upper[0] = %c\n", upper[0]);

	write_buf(lower, sizeof(lower), 'l');

	printf("upper[0] = %c\n", upper[0]);

	return 0;
}
