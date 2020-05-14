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
	if(argc - 1 > MAX) {
		fprintf(stderr, "too many parameters. number of parameters must be less than %d\n", MAX); 
		return -1; 
	}

	candidate_count = argc - 1;
		
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voters_num = get_int("Number of voters: ");
	if(voters_num <= 0) {
		fprintf(stderr, "invalid number of voters: %d\n", voters_num); 
		return -2; 
	}
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
    int max = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
		}
	}

	for (int i = 0; i < candidate_count; i++)
	{
		if(candidates[i].votes == max) {
			printf("%s\n", candidates[i].name);
		}
	}
}
