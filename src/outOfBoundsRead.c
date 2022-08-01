#include <stddef.h>
#include <stdio.h>

// Get value before array by not checking the lower bounds

int getValueFromArray(int *array, int len, int index)
{

    int value = -1;

    if (index < len)
    {
        value = array[index];
    }

    return value;
}

int main(void)
{
    int *numbers[5];

    int result = getValueFromArray(*numbers, 5, -3);

    printf("Value before is %d\n", result);

    return 0;
}