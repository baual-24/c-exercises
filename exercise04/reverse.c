#include <stdio.h>  // for printf() and scanf()
#include <stdlib.h> // for atoi()
#include <string.h> // for various string functions

int main(int argc, char **argv) {

  // Initializing variables:
  int *input_arr = NULL; // pointer to array to populate.
  int arr_size = 0;      // current size of array.
  int num_read = 0;      // how many inputs have been read thus far.
  char input[13]; // Size is 13 to account for the 10 digits that could be in
                  // the largest unsigned int, 1 for the possibility of a
                  // minus sign, 1 for the null terminator, and 1 for the
                  // newline character at the end (a result of using fgets)..

  while (1) {

    // NOTE: this if-statement simultaneously executes fgets() and evaluates
    // its return value.
    if (fgets(input, sizeof(input), stdin) == NULL) {
      break;
    }

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

  // Print out the reversed inputs in a line:
  for (int i = num_read - 1; i >= 0; i--) {
    printf("%d ", input_arr[i]);
  }
  printf("\n");
}
