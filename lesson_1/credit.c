#include <cs50.h>
#include <stdio.h>

long cardInput(void);
int luhnCheck(long);
int amexCheck(long, int);
int visaCheck(long, int);
int masterCheck(long, int);

int main(void) 
{
    long card = cardInput();
    if (luhnCheck(card)) 
    {
        if (amexCheck(card, 0)) 
        {
            printf("AMEX\n");
        }
        else if (visaCheck(card, 0)) 
        {
            printf("VISA\n");
        }
        else if (masterCheck(card, 0)) 
        {
            printf("MASTERCARD\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else 
    {
        printf("INVALID\n");
    }
}

long cardInput(void)
{
    long a = get_long("Card number: ");
    return a;
}

// Validate if the number is a valid card number via Luhn's algorithm
int luhnCheck(long card) 
{
    int firstSum = 0;
    int secondMult = 0;
    int aux;
    int aux2;
    int flag = 1;  //1 for odd positions, 0 for even positions
    int answer;
    int digitCount = 0;

    while (card != 0) 
    {
        aux = card % 10;
        if (flag == 1) 
        {
            firstSum += aux;
            flag = 0;
        }
        else 
        {
            aux *= 2;
            if (aux / 10 > 0) 
            {
                while (aux != 0) 
                {
                    aux2 += aux % 10;
                    aux = aux / 10; 
                }
                secondMult += aux2;
            }
            else 
            {
                secondMult += aux;
            }
            flag = 1;
        }
        aux = 0;
        aux2 = 0;
        card = card / 10;
        digitCount++;
    }
    answer = firstSum + secondMult;
    if (answer % 10 == 0 && (digitCount >= 13 && digitCount <= 16)) 
    {
        // This is hard-coded for cards up to 16 digits, 
        // 17+ cards will be considered invalid, even though it
        // can reach 19.
        return 1;
    }
    else 
    {
        return 0;
    }
}

int amexCheck(long card, int count) 
{
    if (card / 10 > 9 && count < 13) 
    {
        return amexCheck(card / 10, count++);
    }
    else 
    {
        int aux = card % 10;
        int aux2 = (card / 10) * 10;
        int ans = aux + aux2;
        if (ans == 34 || ans == 37) 
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }
}

int visaCheck(long card, int count) 
{
    if (card / 10 > 0) 
    {
        return visaCheck(card / 10, count++);
    }
    else 
    {
        if (card / 10 > 0 && count < 16) 
        {
            return (visaCheck(card / 10, count++));
        }
        else if (card / 10 == 0 && count < 16) 
        {
            if (card % 10 == 4) 
            {
                return 1;
            }
            else 
            {
                return 0;
            }
        }
    }
    return 0;
}

int masterCheck(long card, int count) 
{
    if (card / 10 > 9 && count < 14) 
    {
        return masterCheck(card / 10, count++);
    }
    else 
    {
        int aux = card % 10;
        int aux2 = (card / 10) * 10;
        int ans = aux + aux2;
        if (ans >= 51 && ans <= 55) 
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }
}

/*
NOTES:
- AmEx uses 15 digits and start with 34 or 37.
- MasterCard uses 16 digits and start between 51 and 55.
- Visa uses between 13 and 16 digits and always start with 4.
*/
