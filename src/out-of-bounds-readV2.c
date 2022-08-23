#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    This out of bounds read example requires 3 pieces of information as parameters to be passed through
    in order to read the supplied data out of bounds. The information required is:
    Data: the secret data entered by the user.
    -32: This is the lower memory bound.
    (-32 - (length of input + 1)): This strips any garbage from the end of the secret.

    The way to use this is out-of-bounds-readV2 (data) -32 (calculation from above)
    I.E example arg1 arg2 arg3
*/

const char data[] = "1415926535897932384626433832795";

int main(int argc, char *argv[])
{

    char *SECRET_INFORMATION = (char *)malloc(32 * sizeof(char));
    char *PUBLIC_INFORMATION = (char *)malloc(32 * sizeof(char));

    printf("Storing Secret...\n");

    memcpy(SECRET_INFORMATION, argv[1], strlen(argv[1]) + sizeof(char));
    memcpy(PUBLIC_INFORMATION, data, strlen(data) + sizeof(char));

    int startIndex = atoi(argv[2]);
    int endIndex = atoi(argv[3]);
    if (endIndex < startIndex)
    {
        printf("End index must be after start index\n");
        return 1;
    }
    if (endIndex > 32)
    {
        printf("This program can only get the first 32 data entries.\n");
        return 1;
    }

    printf("The data between indices %d and %d is: ", startIndex, endIndex);
    for (int i = startIndex; i < endIndex; i++)
    {
        printf("%c", PUBLIC_INFORMATION[i]);
    }
    printf("\n");

    return 0;
}