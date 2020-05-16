#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *keys = argv[1];

    // checks the number of keys, the number is 26
    if (strlen(keys) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        // converts a key to lowercase
        char key = tolower(keys[i]);
        if (key < 'a' || key > 'z')
        {
            printf("The key %c is not alphabet. \n", key);
            return 1;
        }

        for (int j = 0; j < 26; j++)
        {
            char key2 = tolower(keys[j]);
            if (i != j && key == key2)
            {
                printf("Duplicate characters in key.\n");
                return 1;
            }
        }
    }

    // maps each char code
    char convert_map[256];
    for (int i = 0; i < 256; i++)
    {
        char c = (char)i;
        int index;
        if (c >= 'a' && c <= 'z')
        {
            // index: Alphabetical order number from 'a'
            index = (int)(c - 'a');
            convert_map[i] = tolower(keys[index]);
        }
        else if (c >= 'A' && c <= 'Z')
        {
            // index: Alphabetical order number from 'A'
            index = (int)(c - 'A');
            convert_map[i] = toupper(keys[index]);
        }
        else
        {
            convert_map[i] = c;
        }
    }

    char *text = get_string("plaintext: ");

    // converts plaintext to a ciphertext
    printf("ciphertext:");
    for (int i = 0; text[i] != '\0'; i++)
    {
        int index = (int)text[i]; // index is 0-255
        printf("%c", convert_map[index]);
    }
    printf("\n");
    return 0;
}
