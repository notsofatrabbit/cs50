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
void printPairsScores();
void print_locked(void);

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

        printf("\n");
    }

    //User Func
    //print_preferences();

    //Standard Funcs
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++){

        if (strcmp(candidates[i], name) == 0){
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    /*printf("Ranks: ");
    for (int i = 0; i < candidate_count; i++){
        printf("%i ", ranks[i]);
    }
    printf("\n");*/

    for (int i = 0; i < candidate_count-1; i++){
        for (int j = 1+i; j < candidate_count; j++){

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
    int a = 0; //Stable counter, due to sub loops continous adding was an issues

    for (int i = 0; i < candidate_count-1; i++){
        for (int j = 1+i; j < candidate_count; j++){

            if(preferences[i][j] > preferences[j][i]){
                    pairs[a].winner = i;
                    pairs[a].loser  = j;
                    pair_count += 1;
                    a += 1;
                    //printf("1st wins\n");
            }
            else if(preferences[i][j] < preferences[j][i]){
                    pairs[a].winner = j;
                    pairs[a].loser  = i;
                    pair_count += 1;
                    a+= 1;
                    //printf("2nd wins\n");
            }

            //printf("Candidate 1: %s %i\n", candidates[i], preferences[i][j]);
            //printf("Candidate 2: %s %i\n", candidates[j], preferences[j][i]);
            //printf("pairs[i].winner: %d \n", pairs[a].winner);
            //printf("pairs[i].loser: %d \n\n", pairs[a].loser);
            //printPairs();
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

    //printf("Start sort\n");

    while(sorted != 1){

        sorted = 1;

        for (int i = 0; i < pair_count-1; i++){

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

        //printPairs();
        //printPairsScores();

    }

    //printPairs();
    //printPairsScores();

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int closeCount;
    int countNum = 0;

    do{
        closeCount = 0;

        locked[pairs[countNum].loser][pairs[countNum].winner] = 1;
        if (countNum > pair_count){
            break;
        }

        for (int i = 0; i < candidate_count; i++){
            int zeroRows = 0;

            for (int j = 0; j < candidate_count; j++){
                if (locked[i][j] == 0){
                    zeroRows += 1;
                }
            }

            if (zeroRows == candidate_count){
                closeCount += 1;
                //printf("Whose the winner: %d\n", i);
            }
        }

        //printf("Close Count: %d\n", closeCount);
        //print_locked();
        countNum +=1;
    }
    while(closeCount > 1);
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++){
            int zeroRows = 0;

            for (int j = 0; j < candidate_count; j++){
                if (locked[i][j] == 0){
                    zeroRows += 1;
                }
            }

            if (zeroRows == candidate_count){
                printf("%s\n", candidates[i]);
            }
        }
    return;
}

void print_preferences(void)
{
    for (int a = 0; a < candidate_count; a++){
        for(int b = 0; b < candidate_count; b++){
            printf("%d ", preferences[a][b]);
        }
        printf("\n");
    }

    printf("\n");
}

void printNewArrays(int array1[], int array2[]){

    for (int a = 0; a < MAX; a++){
        printf(" %d  ", array1[a]);
    }
    printf("\n");

    for (int a = 0; a < MAX; a++){
        printf(" %d  ", array2[a]);
    }
    printf("\n");
}

void printPairsScores(){
    for (int i = 0; i < pair_count; i++){
        printf("[%d] ", preferences[pairs[i].winner][pairs[i].loser]);
    }
    printf("\n");

    for (int i = 0; i < pair_count; i++){
        printf("[%d] ", preferences[pairs[i].loser][pairs[i].winner]);
    }
    printf("\n\n");

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

void print_locked(void)
{
    for (int a = 0; a < candidate_count; a++){
        for(int b = 0; b < candidate_count; b++){
            printf("%d ", locked[a][b]);
        }
        printf("\n");
    }

}

