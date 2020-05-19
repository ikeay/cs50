#include <cs50.h>
#include <stdio.h>

int main(void)
{
    while (true)
    {
        int number = get_int("Height: ");
        if (number >= 1 && number <= 8)
        {
            for (int i = 1; i <= number; i++)
            {
                for (int j = 0; j < (number - i); j ++)
                {
                    printf(" ");
                }
                for (int j = 0; j < i; j ++)
                {
                    printf("#");
                }
                printf("  ");
                for (int j = 0; j < i; j ++)
                {
                    printf("#");
                }
                printf("\n");
            }
            return 0;
        }
    }
    return 0; 
}
