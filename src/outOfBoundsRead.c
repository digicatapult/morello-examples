#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{

    char *PUBLIC_INFORMATION;
    char *SECRET_INFORMATION;

    PUBLIC_INFORMATION = (char *)malloc(16 * sizeof(char));
    SECRET_INFORMATION = (char *)malloc(16 * sizeof(char));

    char password[16] = "ThisIsMyPassword";
    char username[16] = "username";

    memcpy(SECRET_INFORMATION, password, 16);
    memcpy(PUBLIC_INFORMATION, username, 16);

    // printf("Secret pointer: %d, public pointer: %d\n", &SECRET_INFORMATION, &PUBLIC_INFORMATION);

    char secretInfo;

    for (int i = 0; i < 32; i++)
    {
        int index = i;
        // printf("index: %d, letter: %d,", index, PUBLIC_INFORMATION[index]);

        // Prints out the username and password from the SECRET_INFORMATION
        printf("%c", PUBLIC_INFORMATION[i]);
    }

    return 0;
}