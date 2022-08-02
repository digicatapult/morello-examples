#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// An example of a user changing the root password by entering a username that's long enough to go out of bounds of the allocated input array.

int checkInput(char input[], char toMatch[])
{
    input[strcspn(input, "\n")] = '\0'; // strip \n from fgets
    if (strcmp(input, toMatch))
    {
        printf("Wrong input\n");
        return 0;
    }
    else
    {
        printf("Correct input\n");
        return 1;
    }
}

void runAttempt(char input[], char username[], char password[])
{
    printf("\nEnter username: \n");
    fgets(input, 20, stdin);
    if (!checkInput(input, username))
    {
        return;
    }

    printf("\nEnter password: \n");
    fgets(input, 20, stdin);
    checkInput(input, password);
}

int main(void)
{
    char username[] = "root";
    char password[] = "password";

    char input[10];

    // printf("%p\n", &access[0]);
    printf("%x\n", &input[sizeof(input)]);
    printf("%x\n", &password);

    // check memory allocation is adjacent
    assert((void *)&password[0] == (void *)&input[sizeof(input)]);

    printf("Password is: %s\n\n", password);

    while (1)
    {
        runAttempt(input, username, password);
    }

    return 0;
}
