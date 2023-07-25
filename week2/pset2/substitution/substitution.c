#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Ensures theres only one argument
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    // Ensures that arguments is made up of 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }

    // Ensures each character is alphabetical and does not appear more than once
    int key[26];
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        char keyChar = toupper(argv[1][i]);
        if (!isalpha(keyChar))
        {
            printf("Key may only contain alphabetical characters");
            return 1;
        }
        for (int j = 0; j <= i; j++)
        {
            if (key[j] == keyChar)
            {
                printf("Each letter can only appear once");
                return 1;
            }
        }
        key[i] = keyChar;
    }

    // Takes plaintext input from user
    string plaintext = get_string("plaintext: ");

    // Initializes array of characters for ciphertext
    char ciphertext[strlen(plaintext) + 1];
    ciphertext[strlen(plaintext)] = '\0';

    // Loops over each character and substitutes it
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i])) // Only substitutes alphabetical characters
        {
            ciphertext[i] = islower(plaintext[i]) ? tolower(key[plaintext[i] - 'a']) : key[plaintext[i] - 'A'];
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // Prints ciphertext
    printf("ciphertext: %s\n", ciphertext);
}
