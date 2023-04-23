#include <stdio.h>  // for printf() and scanf()
#include <stdlib.h> // for atoi()
#include <string.h> // for various string functions

int main(int argc, char **argv) {
  while (1) { // Infinite loop

    char num[10]; // Max of 10 digits.

    printf("Enter a number: ");
    scanf("%s", num);

    // Turning the string into an array of ints:
    int digit_list[10];
    for (int i = 0; i < strlen(num); i++) {
      char smaller = num[i];
      digit_list[i] = atoi(&smaller); // '&' required because we're using a
                                      // char and not a string.
    }

    // 3 rows, 10 cols, and each element is 4 chars (3 plus '/0'):
    char num_format[3][10][4];

    for (int i = 0; i < strlen(num); i++) { // i is column number.
      // Creating row 0 of num_format:
      if (digit_list[i] == 1 || digit_list[i] == 4) {
        strcpy(num_format[0][i], "   ");
      } else {
        strcpy(num_format[0][i], " _ ");
      }

      // Creating row 1 of num_format:
      if (digit_list[i] == 0) {
        strcpy(num_format[1][i], "| |");
      } else if (digit_list[i] == 1 || digit_list[i] == 7) {
        strcpy(num_format[1][i], "  |");
      } else if (digit_list[i] == 2 || digit_list[i] == 3) {
        strcpy(num_format[1][i], " _|");
      } else if (digit_list[i] == 5 || digit_list[i] == 6) {
        strcpy(num_format[1][i], "|_ ");
      } else {
        strcpy(num_format[1][i], "|_|");
      }

      // Creating row 2 of num_format:
      if (digit_list[i] == 2) {
        strcpy(num_format[2][i], "|_ ");
      } else if (digit_list[i] == 3 || digit_list[i] == 5) {
        strcpy(num_format[2][i], " _|");
      } else if (digit_list[i] == 6 || digit_list[i] == 8 ||
                 digit_list[i] == 0) {
        strcpy(num_format[2][i], "|_|");
      } else {
        strcpy(num_format[2][i], "  |");
      }
    }

    // Printing the numbers out:
    for (int i = 0; i < 3; i++) {             // row
      for (int j = 0; j < strlen(num); j++) { // col
        printf("%s", num_format[i][j]);
      }
      printf("\n");
    }

    printf("\n");
  }
}
