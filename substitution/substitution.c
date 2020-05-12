#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int my_atoi(char *str);

int main(int argc, char *argv[])
{
    if (argc > 2 || argc <= 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *keys = argv[1];
    int keyNums[26];
    for (int i = 0; i < 26; i++)
    {
        if (keys[i] >= 'a' && keys[i] <= 'z')
        {
            keyNums[i] = keys[i] - ('a' + i);
        }
        else if (keys[i] >= 'A' && keys[i] <= 'Z')
        {
            keyNums[i] = keys[i] - ('A' + i);
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        for (int j = 0; j < 26; j++)
        {
            if (keys[i] == keys[j] && i != j)
            {
                printf("Duplicate characters in key.\n");
                return 1;
            }
        }
    }

    char *text = get_string("plaintext: ");
    printf("ciphertext:");
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            int index = text[i] - 'a';
            printf("%c", text[i] + keyNums[index]);
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            int index = text[i] - 'A';
            printf("%c", text[i] + keyNums[index]);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}