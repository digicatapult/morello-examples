#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// An example of a user gaining access, despite entering an incorrect password, as long as it's long enough to go out of bounds of the allocated buffer.

const char password[] = "password";

void checkPassword(char buff[], int access[])
{
    buff[strcspn(buff, "\n")] = '\0'; // strip \n from fgets
    if (strcmp(buff, password))
    {
        printf("Wrong password\n");
    }
    else
    {
        printf("Correct password\n");
        access[0] = 1;
    }
}

void checkAccess(int access[])
{
    if (access[0])
    {
        printf("You have root access \n\n");
    }
    else
    {
        printf("You DO NOT have root access \n\n");
    }
}

void logout(int access[2])
{
    access[0] = 0;
}

void runAttempt(char buff[], int access[])
{
    printf("Enter password: \n");
    fgets(buff, 16, stdin);
    printf("\nAttempt: %s", buff);
    checkPassword(buff, access);
    checkAccess(access);
    logout(access);
}

int main(void)
{
    int access[2] = {0, 0};
    char buff[8];

    // printf("%p\n", &access[0]);
    // printf("%p\n", &buff[8]);

    // check memory allocation is adjacent
    assert((void *)&access[0] == (void *)&buff[sizeof(buff)]);

    printf("Password is: %s\n\n", password);

    while (1)
    {
        runAttempt(buff, access);
    }

    return 0;
}
