//<stdio.h> allows us to use the "printf()" and "scanf()" functions.
#include <stdio.h>

int main() {
  int n;

  while (1) { // While true (i.e. this loop goes on forever).
    printf("Enter a number: ");
    scanf("%d", &n);

    // Verifying if the input is valid (>1).
    if (n < 1) {
      break;
    }

    int j = n;
    int counter = 0; // The counter keeps track of the length of the sequence.

    while (n != 1) {
      if (n % 2 == 0) { // If n is even.
        n = n / 2;
        counter++;
      } else { // If n is odd.
        n = (3 * n) + 1;
        counter++;
      }
    }

    counter++; // Adding an extra number to account for the "1" at the end of
               // the sequence.
    printf("%d -> %d\n", j, counter);
  }
}
