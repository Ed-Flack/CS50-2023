#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2) // Ensures there are two arguments, the invocation of the file and the key
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i])) // Ensures the key is only numerical
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]); // Converts the key from a string to an int
    char *plaintext = get_string("plaintext: "); // Takes the string to be encrypted from the user
    char cyphertext[strlen(plaintext)];

    // Encrypts the string
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            char character = ((char)((int)plaintext[i] + key - (int)'A') % 26 + 'A');
            cyphertext[i] = character;
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            char character = ((char)((int)plaintext[i] + key - (int)'a') % 26 + 'a');
            cyphertext[i] = character;
        }
        else
        {
            cyphertext[i] = plaintext[i];
        }
    }

    // Prints encrypted string
    printf("ciphertext: ");
    for (int i = 0; i < (int)sizeof(cyphertext); i++)
    {
        printf("%c", cyphertext[i]);
    }
    printf("\n");
}
