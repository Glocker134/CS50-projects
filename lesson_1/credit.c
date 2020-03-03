#include <cs50.h>
#include <stdio.h>

int main(void) {
  long int card = 378282246310005;
  int firstSum = 0;
  int secondMult = 0;
  int aux;
  int aux2;
  int flag = 1;
  int answer;
  int digitCount = 1;

  while (card != 0) {
    aux = card % 10;
    if (flag == 1) {
      firstSum += aux;
      flag = 0;
    }
    else {
      aux *= 2;
      if (aux / 10 > 0) {
        while (aux != 0) {
          aux2 += aux % 10;
          aux = aux / 10; 
        }
        secondMult += aux2;
      }
      else {
        secondMult += aux;
      }
      flag = 1;
    }
    aux = 0;
    aux2 = 0;
    card = card / 10;
  }
  printf("firstSum value: %i\n", firstSum);
  printf("secondMult value: %i\n", secondMult);
  answer = firstSum + secondMult;
  printf("answer = %i\n", answer);
  if (answer % 10 == 0) {
    printf("Valid Card\n");
  }
  else {
      printf("Not a valid card\n");
  }
}

/*
NOTES:
- AmEx uses 15 digits and start with 34 or 37.
- MasterCard uses 16 digits and start between 51 and 55.
- Visa uses between 13 and 16 digits and always start with 4.

TO DO:
- first-digits validator
-- Visa validator
-- MC validator
-- AmEx validator
*/
