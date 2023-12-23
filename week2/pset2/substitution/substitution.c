#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);

int main(int argc, string argv[])
{
    // Checks that there is only one argument and that it is only made up of digits
    if (argc == 1 || argc > 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    // Converts string to an int
    int key = atoi(argv[1]);

    // Takes plaintext to by encrypted from user
    string plaintext = get_string("plaintext: ");

    // Initialize ciphertext char array
    char ciphertext[strlen(plaintext) + 1];
    ciphertext[strlen(plaintext)] = '\0';

    // Loops over each character in the plaintext, if it is an alphabetical value it is rotated 'x' number of times where 'x' is the
    // key
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            int cipherCharPosition;
            if (isupper(plaintext[i]))
            {
                cipherCharPosition = (plaintext[i] - 'A' + key) % 26;
                ciphertext[i] = cipherCharPosition + 'A';
            }
            else
            {
                cipherCharPosition = (plaintext[i] - 'a' + key) % 26;
                ciphertext[i] = cipherCharPosition + 'a';
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // Returns the ciphertext
    printf("ciphertext: %s\n", ciphertext);
}

// Helper method to check a string is only made up of digits
bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}
