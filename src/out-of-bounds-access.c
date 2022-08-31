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
    e.g. ./out-of-bounds-access.out root------------123 bla root 123
*/

char *username;
char *password;
char *buffer;

int checkCredentials(char *toMatch, char *successMessage, char *failureMessage)
{
    if (strcmp(buffer, toMatch))
    {
        printf("%s\n", failureMessage);
        return 0;
    }
    else
    {
        printf("%s\n", successMessage);
        return 1;
    }
}

int runAttempt(char *usernameAttempt, char *passwordAttempt)
{
    printf("\nChecking username: %s \n", usernameAttempt);
    memcpy(buffer, usernameAttempt, strlen(usernameAttempt) + 1);

    if (!checkCredentials(username, "Valid user", "Unknown user"))
    {
        return 0;
    }

    printf("\nChecking password... \n");
    memcpy(buffer, passwordAttempt, strlen(passwordAttempt) + 1);

    return (checkCredentials(password, "Correct", "Wrong"));
}

int main(int argc, char *argv[])
{
    if ((argc - 1) % 2 != 0) // argc counts program name as first argument
    {
        printf("Must be supplied an even number of arguments\n");
        return 1;
    }

    username = malloc(16 * sizeof(char));
    buffer = malloc(16 * sizeof(char));
    password = malloc(16 * sizeof(char));

    // check memory allocation is adjacent
    assert((void *)&password[0] == (void *)&buffer[16]);

    // set username and password
    memcpy(username, "root", strlen("root") + sizeof(char));
    memcpy(password, "password", strlen("password") + sizeof(char));

    for (int i = 1; i < argc; i += 2)
    {
        runAttempt(argv[i], argv[i + 1]);
    }

    return 0;
}
