#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Takes input string from user
    string text = get_string("Text: ");
    int words = 0;     // To count how many words in text
    int sentences = 0; // To count how many sentences in text
    int letters = 0;   // To count how many letters in text
    bool currentWord = false;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i])) // Checks if current character is alphabetical
        {
            letters++;
            if (!currentWord)
            {
                words++;
            }
            currentWord = true;
        }
        else if (text[i] == '?' || text[i] == '!' ||
                 text[i] == '.') // These indicate the end of a sentence and that current word is over
        {
            sentences++;
            currentWord = false;
        }
        else if (text[i] == ' ') // This indicates the current word is over
        {
            currentWord = false;
        }
    }
    double l = (double) letters / (double) words * 100;   // Average number of letters per 100 words
    double s = (double) sentences / (double) words * 100; // Average number of sentences per 100 words
    int grade = round(0.0588 * l - 0.296 * s - 15.8);     // Coleman-Liau index
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}
