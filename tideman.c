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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair sorted[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void mergeSort(pair temp);
int compare(pair pair1, pair pair2);

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
            ranks[rank - 1] = i;
            return true;
        }
    }
    ranks[rank - 1] = -1; // if invalid, make it -1 so easier to compare in record_preferences
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 2; i++)
    {
        if (ranks[i] == -1)
        {
            continue;
        }
        for (int j = i + 1; j < candidate_count - 1; j++)
        {
            if (ranks[j] == -1)
            {
                continue;
            }
            
            preferences[ranks[i]][ranks[j]]++; 
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    
    for (int i = 0; i < candidate_count - 2; i++)
    {
        
        for (int j = i + 1; j < candidate_count - 1; j++)
        {
            if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }
            
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    
    sorted = mergeSort(pairs);

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

void mergeSort(pair arrayOfPairs)
{
    if (pair_count > 1)
    {
        int L_count = pair_count / 2;
        int R_count = pair_count - L_count;
        
        pair L_pairs[L_count];
        pair R_pairs[R_count];
        
        for (int i = 0; i < L_count; i++)
        {
            L_pairs[i] = pairs[i];
        }
        
        for (int i = 0; i < R_count; i++)
        {
            R_pairs[i] = pairs[i + L_count];
        }
        
        mergeSort(L_pairs);
        mergeSort(R_pairs);
        
        int index;
        pair sortedArray[];
        
        for (int i = 0; i < L_count; i++)
            {
            for (int j = 0; i < R_count; j++)
            {
                if (compare(L_pairs[i], R_pairs[j]) == 1 || compare(L_pairs[i], R_pairs[j]) == 0)
                {
                    sortedArray[index] = L_pairs[i];
                    index++;
                    break;
                }
                else
                {
                    sortedArray[index] = R_pairs[j];
                    index++;
                }
            }
        }
        
        arrayOfPairs = sortedArray;
        
        return;
        
    }
    else
    {
        return;
    }
}

int compare(pair pair1, pair pair2)
{
    int difference1 = preferences[pair1.winner][pair1.loser] - preferences[pair1.loser][pair1.winner];
    int difference2 = preferences[pair2.winner][pair2.loser] - preferences[pair2.loser][pair2.winner];
    
    if (difference1 > difference2)
    {
        return 1;
    }
    else if (difference2 > difference1)
    {
        return 2;
    }
    else
    {
        return 0;
    }
        
