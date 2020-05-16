#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int my_atoi(const char *str, int *out);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key, ret;
    ret = my_atoi(argv[1], &key);
    if (ret == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    char *text = get_string("plaintext: ");
    printf("ciphertext:");
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            printf("%c",  'a' + ((text[i] - 'a' + key) % 26));
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            printf("%c", 'A' + ((text[i] - 'A' + key) % 26));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}

int my_atoi(const char *str, int *out)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        // return 1 if not number
        if (str[i] < '0' || str[i] > '9')
        {
            *out = 0;
            return 1;
        }
    }

    // convert string to int if using only number
    *out = atoi(str);
    return 0;
}
