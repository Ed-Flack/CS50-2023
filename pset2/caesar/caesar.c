#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool only_digits(char *arg);
char rotate(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1])) // Ensures there are two arguments, the invocation of the file and the key and that the key is numerical
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]); // Converts the key from a string to an int
    char *plaintext = get_string("plaintext: "); // Takes the string to be encrypted from the user
    char cyphertext[strlen(plaintext)];

    // Encrypts the string
    for (int i = 0; i < strlen(plaintext); i++)
    {
        cyphertext[i] = rotate(plaintext[i], key);
    }

    // Prints encrypted string
    printf("ciphertext: ");
    for (int i = 0; i < (int)sizeof(cyphertext); i++)
    {
        printf("%c", cyphertext[i]);
    }
    printf("\n");
}

// Replaces the plaintext character with the encrypted character
char rotate(char c, int key)
{
    if (c >= 'A' && c <= 'Z')
    {
        return ((char)((int)c + key - (int)'A') % 26 + 'A');
    }
    else if (c >= 'a' && c <= 'z')
    {
        return ((char)((int)c + key - (int)'a') % 26 + 'a');
    }
    return c;
}

// Ensures the key is only numerical
bool only_digits(char *arg)
{
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }
    return true;
}
