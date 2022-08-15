/*
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright (c) 2020 Microsoft, Inc.
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void fn1(uintptr_t arg)
{
	fprintf(stderr, " First function: %#p\n", (void *)arg);
}

static void fn2(uintptr_t arg)
{
	fprintf(stderr, " Second function: %#p\n", (void *)arg);
}

struct obj
{
	char buf[32];
	void (*volatile fn)(uintptr_t);
	volatile uintptr_t arg;
};

int main(void)
{
	struct obj *volatile obj1 = malloc(sizeof(*obj1));

	fprintf(stderr, "Installing function pointer in obj1 at %#p\n", obj1);
	obj1->fn = fn1;
	obj1->arg = (uintptr_t)obj1;

	free(obj1);

	fprintf(stderr, "Demonstrating use after free:\n");
	obj1->fn(obj1->arg);

	// allocated obj2 asserting that it's address matches obj1
	struct obj *volatile obj2 = malloc(sizeof(*obj2));
	for (int i = 0; obj2 != obj1 && i < 1000000; ++i)
	{
		free(obj2);
		obj2 = malloc(sizeof(*obj2));
	}
	assert(obj1 == obj2);

	fprintf(stderr, "Assigning function pointer through obj2 at %#p\n",
					obj2);
	obj2->fn = fn2;

	fprintf(stderr, "Calling function pointer through obj1 (now %#p):\n",
					obj1);
	obj1->fn(obj1->arg);

	return (0);
}
