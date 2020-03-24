// This software validates a credit card number entered by the user
// Validity checks: 0. Format, 1. Luhn's checksum algorithm*, 2. Number of digits, 3. Starting digit(s)
// Output: It reports whether the card is Amex, Mastercard, Visa or Invalid
// *Luhn's checksum algorithm: https://en.wikipedia.org/wiki/Luhn_algorithm

#include <stdio.h>
#include <cs50.h>

int checkcard(long cardnum);
int morechecks(int len, int first, int second);

int main(void)
{
    // Prompt user for a (positive long) CC number
    long cardnum = 0;
    do
    {
        cardnum = get_long("CC number: ");
    }
    while (cardnum < 0);
    int cardtype = checkcard(cardnum);
    switch (cardtype)
    {
        case 1:
            printf("AMEX\n");
            break;
        case 2:
            printf("MASTERCARD\n");
            break;
        case 3:
            printf("VISA\n");
            break;
        default:
            printf("INVALID\n");
    }
}

// Validity Check - Luhn's Checksum Algorithm
int checkcard(long cardnum)
{
    int cardtype = 0, pos = 1, last_digit = 0, sec_digit = 0;
    long num = cardnum;
    // Right most number and alternate numbers from there moving left are in odd position
    // Second number from right and alternate numbers moving left are in even position
    int prod_even = 1, sum_odd = 0, sum_prod_even = 0;

    while (num > 0)
    {
        // Storing for 2nd digit in more checks function
        sec_digit = last_digit;
        last_digit = num % 10;
        // Alternate numbers from the right
        if (pos % 2 != 0)
        {
            sum_odd += last_digit;
        }
        // Alternate numbers from second from right
        else
        {
            prod_even = last_digit * 2;
            // Adds last digit of product
            sum_prod_even += prod_even % 10;
            // Checks if product output has one more digit
            if (prod_even % 10 != prod_even)
            {
                // Maximum number in the 10s place can only be 1 (9*2=18)
                sum_prod_even += 1;
            }


        }
        num = (num - last_digit) / 10;
        pos++;
    }

    // Test functions
    // printf("\nNumber of digits: %i", pos-1);
    // printf("\nChecksum result: %i + %i = %i\n", sum_prod_even, sum_odd, sum_prod_even + sum_odd);

    // If the card number passes checksum test
    if ((sum_prod_even + sum_odd) % 10 == 0)
    {
        // Validity check: starting digit(s) and total number of digits
        cardtype = morechecks(pos - 1, last_digit, sec_digit);
    }
    else
    {
        // INVALID TYPE: Checksum result failed
        cardtype = 4;
    }
    return cardtype;
}

// To check starting digit(s) and total number of digits
int morechecks(int len, int first, int second)
{
    // printf("First:%i, Second:%i\n", first, second);
    // Total number of digits check
    if (len == 13 || len == 15 || len == 16)
    {
        switch (first)
        {
            case 3:
                if (second == 4 || second == 7)
                {
                    // SUCCESS: AMEX Card Type returned
                    return 1;
                }
                else
                {
                    // INVALID TYPE: Meets all criteria for Amex, except second digit
                    return 4;
                }
            case 4:
                // SUCCESS: VISA Card Type returned
                return 3;
                break;
            case 5:
                if (second >= 1 && second <= 5)
                {
                    // SUCCESS: MASTERCARD Card Type returned
                    return 2;
                }
                else
                {
                    // INVALID TYPE: Meets all criteria for Mastercard, except 2nd digit
                    return 4;
                }
            default:
                // INVALID TYPE: First digit does not meet criteria
                return 4;
        }
    }
    else
    {
        // INVALID TYPE: Card Digit Length
        return 4;
    }
}
