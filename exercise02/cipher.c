#include <ctype.h>  // for isspace()
#include <stdio.h>  // for printf() and scanf()
#include <string.h> // for various string functions

int main(int argc, char **argv) {

  char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";

  char sub[26];
  printf("Enter substitution pad: ");
  scanf("%s", sub);

  char input[1024];
  char encodedInput[1024];

  // Encoding the inputted string:
  while (1) {
    // Clear input
    for (int i = 0; i < 1024; i++) {
      input[i] = '\0';
    }

    fgets(input, 1024, stdin);
    input[strlen(input) - 1] = '\0';

    // Clearing encodedInput
    memset(encodedInput, '\0', 1024);

    // Encoding the input:
    char letter;
    char *indxptr; // index pointer.
    int index;     // index of the given letter in the alphabet.
    char encodedLetter;
    for (int i = 0; i < strlen(input); i++) {
      letter = input[i];

      if (islower(letter) != 0) {
        indxptr = strchr(alphabet, letter);
        index = indxptr - alphabet;
        encodedLetter = sub[index];
        encodedInput[i] = encodedLetter;
      } else {
        encodedInput[i] = letter;
      }
    }

    printf("%s\n", encodedInput);
  }
}
