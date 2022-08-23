/*
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright (c) 2020 Microsoft, Inc.
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
    This use-after-free example attempts to perform an admin task before performing another user task
		a number of times given by the first argument. It then attempts to perform the admin task again.
		The bug occurs because the repeated user task can be made to overlap with the memory of the "admin"
		object the code checks against. Therefore the user equals admin as the admin now points at the user
		struct. To cause the bug requires the repeat to be at least 26214 on cheri targets. e.g.

		use-after-free-cheri 26214
*/

struct User
{
	volatile char *username;
	volatile char *homeDir;
};

struct User* getUser()
{
	struct User *volatile user = malloc(sizeof(*user));
	user->username = getenv("LOGNAME");
	user->homeDir = getenv("HOME");
	return user;
}

struct User* getAdmin()
{
	struct User *volatile admin = malloc(sizeof(*admin));
	admin->username = "admin";
	admin->homeDir = "/home/admin";
	return admin;
}

void doThing(struct User* user)
{
	// do a thing
}

int main(int argc, char *argv[])
{
	int retryCount = argc == 2 ? atoi(argv[1]) : 2;

	struct User *volatile user;
	struct User *volatile admin;

	user = getUser();
	admin = getAdmin();
	if (strcmp(user->username, admin->username) == 0)
	{
		printf("Performing admin task\n");
		return 0;
	}
	printf("Error, user cannot perform admin tasks\n");
	free(user);
	free(admin); // whoops premature free

	// loop and do a thing as a regular user. For bug to occur this should happen 26214 times
	for (int i = 0; i < retryCount; ++i)
	{
		// do a thing
		struct User *volatile currentUser = getUser();
		doThing(currentUser);
		free(currentUser);
	}

	user = getUser();
	if (strcmp(user->username, admin->username) == 0)
	{
		printf("Performing admin task\n");
		return 0;
	}
	printf("Error, user cannot perform admin tasks\n");
	free(user);
	return 0;
}
