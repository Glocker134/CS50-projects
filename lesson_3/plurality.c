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
    // Check the candidate struct for a name matching the ballot's.
    // We know the max amount of candidates is 9, but we don't know how many
    // Candidates there'll be on a given election, so we default to either finding a
    // Name value of '\0' within the array, or reaching the end of the array.
    for (int i = 0; candidates[i].name != '\0' && i < MAX; i++)
    {
        // If it's found, add one to its tally, return true to the main function
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // The exact name was not found, the ballot is invalid, return false to the main function
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int topVotes = 0;

    // Checking for the highest vote count across all candidates
    for (int i = 0; candidates[i].name != '\0' && i < MAX; i++)
    {
        if (candidates[i].votes > topVotes)
        {
            // Storing the index of the candidate with the highest number of votes
            topVotes = candidates[i].votes;
        }
    }

    // Printing all winners
    for (int j = 0; candidates[j].name != '\0' && j < MAX; j++)
    {
        if (candidates[j].votes == topVotes)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}