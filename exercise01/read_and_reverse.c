#include <stdio.h>
#include <string.h>

/* This function reverses a string.
 * Parameters: a string called "a" and the size of the string "len" (an int).
 * Returns: void.
 */
void reverse_string(char a[], int len) {
  char copyWord[80];
  int j = len - 1;
  strcpy(copyWord, a); // copies the contents of a to copyWord.

  for (int i = 0; i < len; i++) {
    a[i] = copyWord[j]; // Taking a letter from the original word (which we keep
                        // track of by using "copyWord") and placing it in its
                        // reversed position.
    j--;
  }
}

int main() {
  char word[80];

  while (1) { // While true (infinite loop).
    // User input:
    printf("Enter a word (ctrl-C to quit): ");
    scanf("%s", word);

    // Printing and reversing the string:
    printf("%s -> ", word); // Printing the original string.
    reverse_string(word, strlen(word));
    printf("%s \n", word); // Printing the reversed string.
  }
}
