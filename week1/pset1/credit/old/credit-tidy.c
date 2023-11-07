#include <cs50.h>
#include <stdio.h>

int getSizeOfNumber(long number);

int getNumberFromPosition(long cardNumber, int position, int sizeOfCardNumber);

int everyOtherDigitFromEndMultipliedByTwoAndProductsDigitsAddedTogether(long cardNumber, int sizeOfCardNumber);

int allOtherDigitsAddedTogether(long cardNumber, int sizeOfCardNumber);

char *findCardType(long cardNumber, int sizeOfCardNumber);

int main(void)
{
    // Takes card number from user
    long cardNumber = get_long("Number: ");

    // Works out how many digits are in the number
    int sizeOfCardNumber = getSizeOfNumber(cardNumber);

    // If sizeOfCardNumber is not 13, 15, or 16, then the number is invalid
    if (sizeOfCardNumber < 13 || sizeOfCardNumber > 16 || sizeOfCardNumber == 14)
    {
        printf("INVALID\n");
        return 0;
    }

    // Perfroms the checksum
    int total = everyOtherDigitFromEndMultipliedByTwoAndProductsDigitsAddedTogether(cardNumber, sizeOfCardNumber);
    int total2 = allOtherDigitsAddedTogether(cardNumber, sizeOfCardNumber);
    int sum = total + total2;

    // If the last 0 of the sum is not 0, then it is invalid
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Finds the card type based on the card number
    char *cardType = findCardType(cardNumber, sizeOfCardNumber);
    printf("%s\n", cardType);

    return 0;
}

// Works out the card type based on the card number
char *findCardType(long cardNumber, int sizeOfCardNumber)
{
    int firstNumber = getNumberFromPosition(cardNumber, 0, sizeOfCardNumber);
    int secondNumber = getNumberFromPosition(cardNumber, 1, sizeOfCardNumber);
    if (firstNumber == 3)
    {
        if (secondNumber == 4 || secondNumber == 7)
        {
            return "AMEX"; // If number starts with 34 or 37, it is an American Express
        }
    }
    else if (firstNumber == 5)
    {
        if (secondNumber == 1 || secondNumber == 2 || secondNumber == 3
            || secondNumber == 4 || secondNumber == 5)
        {
            return "MASTERCARD"; // If number starts with 51, 52, 53, 54, or 55, it is a Mastercard
        }
    }
    else if (firstNumber == 4)
    {
        return "VISA"; // If number starts with 4, it is a Visa
    }
    return "INVALID"; // Else it is Invalid
}

// Method used calculate the first part of the checksum
int everyOtherDigitFromEndMultipliedByTwoAndProductsDigitsAddedTogether(long cardNumber, int sizeOfCardNumber)
{
    int total = 0;
    for (int i = sizeOfCardNumber - 2; i >= 0; i -= 2)
    {
        int number = getNumberFromPosition(cardNumber, i, sizeOfCardNumber) * 2;
        int sizeOfNumber = getSizeOfNumber(number);
        if (sizeOfNumber > 1)
        {
            for (int j = 0; j < sizeOfNumber; j++)
            {
                total += getNumberFromPosition(number, j, sizeOfNumber);
            }
        }
        else
        {
            total += number;
        }
    }
    return total;
}

// Method used to calculate the second part of the checksum
int allOtherDigitsAddedTogether(long cardNumber, int sizeOfCardNumber)
{
    int total = 0;
    for (int i = sizeOfCardNumber - 1; i >= 0; i -= 2)
    {
        int number = getNumberFromPosition(cardNumber, i, sizeOfCardNumber);
        total += number;
    }
    return total;
}

// Returns the length of a number
int getSizeOfNumber(long number)
{
    int count = 1;
    while (number / 10 > 0)
    {
        count++;
        number /= 10;
    }
    return count;
}

// Returns a number based on a position within a larger number, i.e position 2 in 653748 would be 3
int getNumberFromPosition(long cardNumber, int position, int sizeOfCardNumber)
{
    for (int j = sizeOfCardNumber - 1 - position; j > 0; j--)
    {
        cardNumber /= 10;
    }
    return (int)(cardNumber % 10);
}
