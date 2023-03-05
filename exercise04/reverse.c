#include <stdio.h>  // for printf() and scanf()
#include <stdlib.h> // for atoi()
#include <string.h> // for various string functions

int main(int argc, char **argv) {

  // Initializing variables:
  int *input_arr = NULL; // pointer to array to populate.
  int arr_size = 0;      // current size of array.
  int num_read = 0;
  char input[8];

  while (num_read != 15) {
    fgets(input, sizeof(input), stdin);

    // Removing the \n at the end of the input
    input[strlen(input) - 1] = '\0';

    // If memory space is too small, reallocate input_arr.
    if (num_read >= arr_size) {
      arr_size = arr_size > 0 ? arr_size * 2 : 1; // Double array size.
      input_arr = realloc(input_arr, arr_size * sizeof(int));
    }

    // Add input to the end of the input array.
    input_arr[num_read] = atoi(input);
    num_read++; // I.e. user typed another input.
  }

  // Print out the reversed inputs:
  for (int i = num_read - 1; i >= 0; i--) {
    printf("%d ", input_arr[i]);
  }
  printf("\n");
}
