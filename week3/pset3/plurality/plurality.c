#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate votedCandidates[candidate_count]; // Creates a new array of candidates sorted in order of most votes
    for (int i = 0; i < candidate_count; i++) // Iterates over array of candidates
    {
        for (int j = 0; j <= i; j++) // Iterates over array of candidates sorted in order of most votes
        {
            // If the current candidates has more votes than the current candidate in the sorted array, it enters the condition
            if (candidates[i].votes > votedCandidates[j].votes)
            {
                if (votedCandidates[j].name != NULL) // If current position in sorted array has a value, space need to be created
                {
                    // Space is created by iterating over sorted array starting at the end and shifting all values to the right
                    for (int k = candidate_count - 1; k > j; k--)
                    {
                        if (votedCandidates[k - 1].name == NULL) // If the value to the left has no value, then no need to shift
                        {
                            continue;
                        }
                    }
                }
                votedCandidates[j] = candidates[i]; // Puts the current candidate in the current position of the sorted array
                break;
            }
        }
    }

    // Print the winner, if there is a draw, all candidates with the highest number of votes are printed
    int maxVotes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (votedCandidates[i].votes >= maxVotes)
        {
            maxVotes = votedCandidates[i].votes;
            printf("%s\n", votedCandidates[i].name);
        }
    }
    return;
}
