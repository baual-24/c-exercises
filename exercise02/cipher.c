#include <stdio.h>  // for printf() and scanf()
#include <string.h> // for various string functions

int main(int argc, char **argv) {
  // char sub[26];
  // printf("Enter substitution pad: ");
  // scanf("%s", sub);

  // char input[1026];
  // scanf("%s", input);

  char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
  // char shortAlph[3] = "abc";

  // char encodedInput[1026];

  char sub[26] = "qwertyuiopasdfghjklzxcvbnm";
  printf("Enter substitution pad: qwertyuiopasdfghjklzxcvbnm\n");

  char input[1024];
  scanf("%s", input);

  // 1) we're comparing the letter at input[i] (ex: input[0] = 'h')
  // 2) check where that letter is in the location of alphabet. (ex: h  =
  // alphabet[7]). 3) find the letter that's at that index in sub (ex: sub[7] =
  // 'i'). 4) add that letter to editedInput

  char letter = 'h';
  char *indxptr = strchr(alphabet, 'h');
  int index = indxptr - alphabet;
  printf("Letter: %c\n", letter);
  printf("Index in alphabet (should be 7): %d\n", index);

  /*  for (int i = 0; i < 26; i++) {
      if (sub[i] >= 'a') { // if character at position 'i' is a letter "greater
        // printf("%c is greater than a", sub[0]);
      }
    }
  */

  // Caveman approach:
  /*  for (int i = 0; i < strlen(input); i++) {
      if (input[i] == 'a') {
        input[i] = 'q';
      } else if (input[i] == 'b') {
        input[i] = 'w';
      } else if (input[i] == 'c') {
        input[i] = 'e';
      } else if (input[i] == 'd') {
        input[i] = 'r';
      } else if (input[i] == 'e') {
        input[i] = 't';
      } else {
        input[i] = 'O';
      }
    }
  */

  printf("%s", input);
}
