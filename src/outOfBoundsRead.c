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

    memcpy(PUBLIC_INFORMATION, username, 16);
    memcpy(SECRET_INFORMATION, password, 16);

    for (int i = 16; i < 32; i++)
    {
        printf("index: %d, letter: %c,\n", i, PUBLIC_INFORMATION[i]);
    }
    printf("\n");

    return 0;
}