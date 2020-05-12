#define MAX 9
#define NULL ((void *)0)
#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool vote(char *name);
void print_winner(void);

typedef struct
{
    char *name;
    int votes;
} candidate;

candidate candidates[MAX];

int candidate_count;

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc - 1; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    candidate_count = argc - 1;

    int voters_num = get_int("Number of voters: ");
    for (int i = 0; i < voters_num; i++)
    {
        char *name = get_string("Vote: ");
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }

    }
    print_winner();
}

bool vote(char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    char *winner_names[candidate_count];
    int count = 0;
    int max = 0;

    for (int i = 0; candidates[i].name != '\0'; i++)
    {
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
            for (int j = 0; j < candidate_count; j++)
            {
                winner_names[j] = NULL;
            }
            winner_names[0] = candidates[i].name;
            count = 0;
        }
        else if (candidates[i].votes == max)
        {
            count++;
            winner_names[count] = candidates[i].name;
        }
    }

    for (int i = 0; i < candidate_count && winner_names[i] != NULL; i++)
    {
        printf("%s\n", winner_names[i]);
    }
}