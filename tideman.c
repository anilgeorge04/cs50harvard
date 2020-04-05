// TIDEMAN Elections: Ranked Pair voting system

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    // int strength; // <- cleaner solution for downstream functions
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

// Function Prototypes for Unit Tests
void test_record_preferences();
void test_pairs();
void test_lock_pairs();

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
    // Initiate preferences between candidates to zero
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
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
    // test_record_preferences();

    add_pairs();
    // test_pairs();
    sort_pairs();
    // test_pairs();
    lock_pairs();
    // test_lock_pairs();
    print_winner();

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // i is the candidate index from 0 to candidate_count
            // Order of candidate name index mapping is as entered in command line
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Flag true when candidate vote count updated
    bool filled[candidate_count];
    // Initiate to false, update to true when filled
    for (int i = 0; i < candidate_count; i++)
    {
        filled[i] = false;
    }

    for (int i = 0; i < candidate_count - 1; i++)
    {
        // Current updates vote preference for 1 candidate at a time in rank order
        int current = ranks[i];
        for (int j = 0; j < candidate_count; j++)
        {
            // Updates vote count in rank order
            // Skips the columns who were ranked higher, using filled[]
            if (j != current && filled[j] == false)
            {
                preferences[current][j] += 1;
            }
        }
        filled[current] = true;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Flag true if candidate row is covered in rank pair
    bool filled[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        filled[i] = false;
    }

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && filled[j] == false)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    // pairs[pair_count].strength = preferences[i][j];
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    // pairs[pair_count].strength = preferences[j][i];
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
        filled[i] = true;
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bool swap = false;
    for (int i = 0; i < pair_count - 1; i++)
    {
        swap = false;
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            // Cleaner code will be to use strength variable within struct pair
            // Following checks the strength of victory and sorts the pair array in descending order
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair temp_pair = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp_pair;
                swap = true;
            }
        }
        if (swap == false)
        {
            // Array is sorted, no need to run the loop further
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool closed_for_entry[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        closed_for_entry[i] = false;
    }

    // To avoid cycle, form graph only when closed_for_entry for that candidate is False
    for (int i = 0; i < pair_count; i++)
    {
        if (closed_for_entry[pairs[i].loser] == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            closed_for_entry[pairs[i].winner] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool source_status[candidate_count];
    for (int j = 0; j < candidate_count; j++)
    {
        // j is the column here
        source_status[j] = false;
        for (int i = 0; i < candidate_count; i++)
        {
            // If any incoming arrow, source_status becomes >0
            source_status[j] += locked[i][j];
        }
        if (source_status[j] == false)
        {
            printf("\n%s\n", candidates[j]);
            break;
        }
    }
    return;
}

// TESTING Functions
void test_record_preferences()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i  ", preferences[i][j]);
        }
        printf("\n");
    }
}

void test_pairs()
{
    printf("\nTest Case: Print Ranked Pairs\n");
    for (int i = 0; i < pair_count; i++)
    {
        // printf("%s beat %s with strength %i.\n", candidates[pairs[i].winner], candidates[pairs[i].loser], pairs[i].strength);
        printf("%s beat %s with strength %i.\n", candidates[pairs[i].winner], candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
    }
}

void test_lock_pairs()
{
    printf("\nTest Case: Print Locked Pairs\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i  ", locked[i][j]);
        }
        printf("\n");
    }
}