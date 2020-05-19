#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    while (true)
    {
        // Note: pay attention to the overflow
        float dollars = get_float("Change owed: ");
        if (dollars > 0)
        {
            int cents = round(dollars * 100);
            int count = 0;
            int coins[] = {25, 10, 5, 1};
            int arrayLength = sizeof(coins) / sizeof(coins[0]);

            for (int i = 0; i < arrayLength; i++)
            {
                int changes = cents / coins[i];
                cents = cents % coins[i];
                count += changes;
            }

            printf("%i\n", count);
            return 0;
        }
    }
}
