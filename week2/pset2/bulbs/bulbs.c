#include <cs50.h>
#include <stdio.h>
#include <string.h>

// The amount of bits in one byte - i.e the amount of bits in one character
const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
char *charToBinary(char c);
void binaryToBulbSequence(char *binary);

int main(void)
{
    // Takes in string from user
    char *message = get_string("Message: ");

    // Loops over each character in the string to convert to a sequence of bulbs
    for (int i = 0; i < strlen(message); i++)
    {
        char *binary = charToBinary(message[i]);
        binaryToBulbSequence(binary);
        printf("\n");
    }

}

// Converts a character to a string of binary
char *charToBinary(char c)
{
    static char binary[BITS_IN_BYTE + 1];
    binary[BITS_IN_BYTE] = '\0';
    for (int i = BITS_IN_BYTE - 1; i >= 0; i--)
    {
        if (c % 2 == 0)
        {
            binary[i] = '0';
        }
        else
        {
            binary[i] = '1';
        }
        c /= 2;
    }
    return binary;
}

// Takes the string and prints the bulb based on if the character is '0' or '1'
void binaryToBulbSequence(char *binary)
{
    for (int j = 0; j < BITS_IN_BYTE; j++)
    {
        if (binary[j] == '0')
        {
            print_bulb(0);
        }
        else
        {
            print_bulb(1);
        }
    }
}

// Method to print the bulb
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
