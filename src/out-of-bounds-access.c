#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
    An example of a user changing the root password by attempting to login with a username that's
    long enough (>16 characters) to go out of bounds of the allocated buffer array.
    The password is replaced with the out of bounds characters e.g. if `root------------123` is
    attempted for a username, the password is now `123`.

    Requires an even number of arguments as 'username password' pairs. Attempts to login with each sequentially.
    e.g. ./out-of-bounds-access root------------123 bla root 123
*/

char *username;
char *usernameBuffer;
char *password;
char *passwordBuffer;

int loginAttempt()
{
    if (strcmp(usernameBuffer, username))
    {
        printf("%s\n", "Login failed");
        return 1;
    }

    if (strcmp(passwordBuffer, password))
    {
        printf("%s\n", "Login failed");
        return 1;
    }

    printf("%s\n", "Login succeeded");
    return 0;
}

int main(int argc, char *argv[])
{
    if ((argc - 1) % 2 != 0) // argc counts program name as first argument
    {
        printf("Must be supplied an even number of arguments\n");
        return 1;
    }

    username = malloc(16 * sizeof(char));
    usernameBuffer = malloc(16 * sizeof(char));
    password = malloc(16 * sizeof(char));
    passwordBuffer = malloc(16 * sizeof(char));

    // check memory allocation is adjacent
    assert((void *)&password[0] == (void *)&usernameBuffer[16]);

    // set username and password
    strcpy(username, "root");
    strcpy(password, "password");

    for (int i = 1; i < argc; i += 2)
    {
        char *usernameAttempt = argv[i];
        char *passwordAttempt = argv[i + 1];
        strcpy(usernameBuffer, usernameAttempt);
        strcpy(passwordBuffer, passwordAttempt);
        loginAttempt();
    }

    return 0;
}
