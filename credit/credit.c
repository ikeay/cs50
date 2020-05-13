#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    while (true)
    {
        long number = get_long("Number: ");
        long _number = number;
        int count = 0;
        int *array = malloc(sizeof(int) * 16);
        while (true)
        {
            array[count] = _number % 10;
            _number = _number / 10;
            count++;
            if (_number <= 0)
            {
                break;
            }
        }

        if (count < 13 || count > 16)
        {
            printf("INVALID: out of range.\n");
            return -1;
        }

        int sum = 0;
        for (int i = 0; i < count; i++)
        {
            if (i % 2 == 0)
            {
                sum += array[i];
            }
            else
            {
                int _mult = array[i] * 2;
                if (_mult > 9)
                {
					sum += _mult - 9;
                }
                else
                {
                    sum += _mult;
                }
            }
        }

        if (sum % 10 == 0)
        {
            if (array[count - 1] == 3)
            {
                if (array[count - 2] == 4 || array[count - 2] == 7)
                {
                    printf("AMEX\n");
                    return 0;
                }
            }
            else if (array[count - 1] == 5)
            {
                if (array[count - 2] <= 5)
                {
                    printf("MASTERCARD\n");
                    return 0;
                }
            }
            else if (array[count - 1] == 4)
            {
                printf("VISA\n");
                return 0;
            }
        }
        printf("INVALID: bad check sum.\n");
        return -2;
    }
}
