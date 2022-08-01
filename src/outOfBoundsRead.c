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
    int *numbers[100];

    int result = getValueFromArray(*numbers, 100, -50);

    printf("Lower bound pointer: %d, upper bound pointer: %d\n", &numbers[0], &numbers[4]);

    printf("Out of bounds pointer: %d\n", &numbers[-50]);

    printf("Value at first index in array is %d\n", numbers[0]);

    printf("Value 3 indices before array is %d\n", result);

    return 0;
}