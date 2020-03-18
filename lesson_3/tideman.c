#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// Setting a flag to initialize the preferences array on first run
bool preferences_initialized = false;

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// My added prototypes
void initialize_preferences(void);
void merge_sort(pair array[], int left, int middle, int right);
void merge_setup(pair array[], int left, int right);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    if (!preferences_initialized)
    {
        initialize_preferences();
        preferences_initialized = true;
    }

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int count = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[count].winner = i;
                pairs[count].loser = j;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[count].winner = j;
                pairs[count].loser = i;
            }
            count++;
            pair_count++
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_setup(pairs, 0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

void initialize_preferences(void)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            preferences[i][j] = 0;
        }
    }
}

void merge_sort(pair array[], int left, int middle, int right)
{
    int left_index, right_index, array_index;
    int left_size = middle - left + 1;
    int right_size = right - middle;
    pair leftA[left_size];
    pair rightA[right_size];

    for (int i = 0; i < left_size; i++)
    {
        leftA[i] = array[left + i];
    }

    for (int j = 0; j < right_size; j++)
    {
        rightA[j] = array[middle + 1 + j];
    }

    left_index = 0;
    right_index = 0;
    array_index = left;

    while (left_index < left_size && right_index < right_size)
    {
        int left_value = preferences[leftA[left_index].winner][leftA[left_index].loser] - preferences[leftA[left_index].loser][leftA[left_index].winner];
        int right_value = preferences[rightA[right_index].winner][rightA[right_index].loser] - preferences[rightA[right_index].loser][rightA[right_index].winner];

        if (left_value >= right_value)
        {
            array[array_index] = leftA[left_index];
            left_index++;
        }
        else
        {
            array[array_index] = rightA[right_index];
            right_index++;
        }
        array_index++;
    }

    while (left_index < left_size)
    {
        array[array_index] = leftA[left_index];
        left_index++;
        array_index++;
    }

    while (right_index < right_size)
    {
        array[array_index] = rightA[right_index];
        right_index++;
        array_index++;
    }

}

void merge_setup(pair array[], int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        merge_setup(array, left, middle);
        merge_setup(array, middle + 1, right);

        merge_sort(array, left, middle, right);
    }
}