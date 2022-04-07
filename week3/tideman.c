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
pair pairs[MAX * (MAX - 1) / 2]; //custom struct

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs();
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

//My Functions
void print_preferences(void);
void printNewArrays(int array1[], int array2[]);
void printPairs();

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
        candidates[i] = argv[i + 1]; //candiates is a string array
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false; // set all locked pairs to false
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++) // 5 loops here
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count]; // in example this is three

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) //three loops here
        {
            string name = get_string("Rank %i: ", j + 1); //Collects name in for loops each time

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        print_preferences();

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

    for (int i = 0; i < sizeof(candidates); i++){
        if (strcmp(candidates[i], name) == 0){
            ranks[i] = rank;
            return true;
        }
    }
    // Ranks correspond to inputed list of candidates
    // candidates = [Alice, Bob, Charlie]
    //                (0)   (1)    (2)
    //Uses this postion to then input their selected rank 0-2 within their respective rank slot
    // ie if voter votes
    // Rank 1: Charlie
    // Rank 2: Alice
    // Rank 3: Bob

    // Ranks will look like this Ranks = [ 1, 2, 0]
    // Alice is first but ranked "2nd"
    // Bob is second but ranked "3rd"
    // Charlie is last but ranked "1st"


    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    printf("candiadate count: %d \n", candidate_count);

    int cand_1 = 0;
    int cand_2 = 0;

    for (int i = 0; i < candidate_count-1; i++){
        for (int j = 1+i; j < candidate_count; j++){

            cand_1 = ranks[i];
            cand_2 = ranks[j];

            preferences[ranks[i]][ranks[j]] += 1;

        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs()
{
    //compare alice to bob
        // run through all votes
    //compare alice to charlie
        // run throgh all votes   -> votes is a constant here of

    for (int i = 0; i < candidate_count-1; i++){
        for (int j = 1+i; j < candidate_count; j++){

            if(preferences[i][j] > preferences[j][i]){
                    pairs[i].winner = i;
                    pairs[i].loser  = j;
                    pair_count += 1;
            }
            else if(preferences[i][j] < preferences[j][i]){
                    pairs[i].winner = j;
                    pairs[i].loser  = i;
                    pair_count += 1;
            }

            printf("Candidate 1: %s %i\n", candidates[i], preferences[i][j]);
            printf("Candidate 2: %s %i\n", candidates[j], preferences[j][i]);
            printf("pairs[i].winner: %d \n", pairs[i].winner);
            printf("pairs[i].loser: %d \n\n", pairs[i].loser);
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int sorted = 0;

    pair holder = pairs[0];
    //printf("pairs[i].winner: %d \n", pairs[0].winner);
    //printf("pairs[i].loser: %d \n\n", pairs[0].loser);
    //printf("holder.winner: %d \n", holder.winner);
    //printf("holder.loser: %d \n", holder.loser);

    while(sorted != 1){

        sorted = 1;

        for (int i = 0; i < pair_count-1; i++){

            printPairs();

            //Getting the win margin between pairs
            int set_1 = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            int set_2 = preferences[pairs[i+1].winner][pairs[i+1].loser] - preferences[pairs[i+1].loser][pairs[i+1].winner];

            if (set_2 > set_1){

                holder = pairs[i];
                pairs[i] = pairs[i+1];
                pairs[i+1] = holder;

                sorted = 0;
            }


        }




    }


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

void print_preferences(void)
{
    for (int a = 0; a < MAX; a++){
        for(int b = 0; b < MAX; b++){
            printf("%d ", preferences[a][b]);
        }
        printf("\n");
    }

}

void printNewArrays(int array1[], int array2[]){

    for (int a = 0; a < MAX; a++){
        printf("%d ", array1[a]);
    }
    printf("\n");

    for (int a = 0; a < MAX; a++){
        printf("%d ", array2[a]);
    }
    printf("\n");
}

void printPairs(){
    for (int i = 0; i < pair_count; i++){
        printf("%d ", pairs[i].winner);
    }
    printf("\n");

    for (int i = 0; i < pair_count; i++){
        printf("%d ", pairs[i].loser);
    }
    printf("\n\n");

}