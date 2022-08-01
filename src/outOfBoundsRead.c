#include <stddef.h>
#include <stdio.h>

//Get value before array by not checking the lower bounds

int getValueFromArray(int *array, int len, int index) {

  int value;

  if (index < len) {
    value = array[index];
  }

  else {
    printf("Value is: %d\n", array[index]);
    value = -1;
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