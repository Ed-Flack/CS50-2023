#include <cs50.h>
#include <stdio.h>

char *checksum(long cardNumberLong);
int getLengthOfNumber(long number);
void parseNumber(long numberLong, int *numberArray, int numberLength);
int everyOtherDigitFromEndMultipliedByTwoAndProductsDigitsAddedTogether(int *cardNumber, int cardNumberLength);
int allOtherDigitsAddedTogether(int *cardNumber, int cardNumberLength);
char *findCardType(int *cardNumber, int sizeOfCardNumber);

int main(void)
{
    // Takes card number from user
    long cardNumber = get_long("Number: ");
    printf("%s\n", checksum(cardNumber));
}

char *checksum(long cardNumberLong)
{
    // Works out how many digits are in the number
    int cardNumberLength = getLengthOfNumber(cardNumberLong);

    // If sizeOfCardNumber is not 13, 15, or 16, then the number is invalid
    if (cardNumberLength != 13 && cardNumberLength != 15 && cardNumberLength != 16)
    {
        return "INVALID";
    }

    // Parses card number into array of ints
    int cardNumber[cardNumberLength];
    parseNumber(cardNumberLong, cardNumber, cardNumberLength);

    // Perfroms the checksum
    int total = everyOtherDigitFromEndMultipliedByTwoAndProductsDigitsAddedTogether(cardNumber, cardNumberLength);
    int total2 = allOtherDigitsAddedTogether(cardNumber, cardNumberLength);
    int sum = total + total2;

    // If the last 0 of the sum is not 0, then it is invalid
    if (sum % 10 != 0)
    {
        return "INVALID";
    }

    return findCardType(cardNumber, cardNumberLength);
}

// Parses numbers into array of ints
void parseNumber(long numberLong, int *numberArray, int numberLength)
{
    for (int i = numberLength - 1; i >= 0; i--)
    {
        numberArray[i] = numberLong % 10;
        numberLong /= 10;
    }
}

// Method used calculate the first part of the checksum
int everyOtherDigitFromEndMultipliedByTwoAndProductsDigitsAddedTogether(int *cardNumber, int cardNumberLength)
{
    int total = 0;
    for (int i = cardNumberLength - 2; i >= 0; i -= 2)
    {
        int number = cardNumber[i] * 2;
        int lengthOfNumber = getLengthOfNumber(number);
        if (lengthOfNumber > 1)
        {
            int numberArray[lengthOfNumber];
            parseNumber(number, numberArray, lengthOfNumber);
            for (int j = 0; j < lengthOfNumber; j++)
            {
                total += numberArray[j];
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
int allOtherDigitsAddedTogether(int *cardNumber, int cardNumberLength)
{
    int total = 0;
    for (int i = cardNumberLength - 1; i >= 0; i -= 2)
    {
        int number = cardNumber[i];
        total += number;
    }
    return total;
}

// Works out the card type based on the card number
char *findCardType(int *cardNumber, int sizeOfCardNumber)
{
    int firstNumber = cardNumber[0];
    int secondNumber = cardNumber[1];
    char *cardType = "INVALID";
    if (firstNumber == 3)
    {
        if (secondNumber == 4 || secondNumber == 7)
        {
            cardType = sizeOfCardNumber == 15 ? "AMEX" : "INVALID"; // If number starts with 34 or 37, and is 15 digits in length, it is an American Express
        }
    }
    else if (firstNumber == 5)
    {
        if (secondNumber >= 1 && secondNumber <= 5)
        {
            cardType = sizeOfCardNumber == 16 ? "MASTERCARD" : "INVALID"; // If number starts with 51, 52, 53, 54, or 55, and is 16 digits in length, it is a Mastercard
        }
    }
    else if (firstNumber == 4)
    {
        cardType = sizeOfCardNumber == 13 || sizeOfCardNumber == 16 ? "VISA" : "INVALID"; // If number starts with 4, and is 13 or 16 digits in length, it is a Visa
    }
    return cardType; // Else it is Invalid
}

// Returns the length of a number
int getLengthOfNumber(long number)
{
    int count = 1;
    while (number / 10 > 0)
    {
        count++;
        number /= 10;
    }
    return count;
}
