/*
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright (c) 2022 Microsoft Corporation
 */
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#pragma weak read_buf
char read_buf(char *buf, size_t ix)
{
	return buf[ix];
}

int main(void)
{
	char upper[0x10] = {'u', 'u'};
	char lower[0x10] = {'l', 'l'};

	printf("upper = %p, lower = %p, diff = %zx\n",
				 upper, lower, (size_t)(upper - lower));

	/* Assert that these get placed how we expect */
	assert((ptraddr_t)upper == (ptraddr_t)&lower[sizeof(lower)]);

	char result = read_buf(lower, sizeof(lower));

	printf("lower[2] = %c\n", result);

	return 0;
}
