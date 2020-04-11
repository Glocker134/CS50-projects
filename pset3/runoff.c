// Implement a program that runs a runoff election.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Name was found, update preferences for voter i, return true
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    // Name was not found, invalid vote, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        bool flag = false;
        int rank = 0;
        while (!flag)
        {
            // If voter's option is not eliminated, update that candidate's vote count
            if (!(candidates[preferences[i][rank]].eliminated))
            {
                candidates[preferences[i][rank]].votes++;
                flag = true;
            }
            // If voter's option is eliminated, move to the next option
            else
            {
                rank++;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int top_votes_index = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        // If there is a candidate that's not eliminated and has over half the total vote count, save the index
        if (candidates[i].votes >= (voter_count / 2) + 1 && !(candidates[i].eliminated))
        {
            top_votes_index = i;
        }
    }

    // If there is a winner, print its name, return true
    if (top_votes_index > -1)
    {
        printf("%s\n", candidates[top_votes_index].name);
        return true;
    }

    // No candidate has the minimum amount of votes to be considered winner, return false
    else
    {
        return false;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        // Looking for the lowest vote count, store its value when found
        if (candidates[i].votes < min && !(candidates[i].eliminated))
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool flag = true;
    int count = 0;
    int value = 0;

    // First we need to find a candidate that's still in the election and store its vote count
    while (flag)
    {
        if (candidates[count].votes > 0 && !(candidates[count].eliminated))
        {
            value = candidates[count].votes;
            flag = false;
        }
        else
        {
            count++;
        }
    }

    // Checking if other participating candidates have the same vote count
    for (int j = count + 1; j < candidate_count; j++)
    {
        // If there is another participating candidate with a higher/lower vote count, there is no tie
        if (!(candidates[j].eliminated) && candidates[j].votes != value)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // Finding all participating candidates with a vote count equal to "min"
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && !(candidates[i].eliminated))
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}