#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int my_atoi(char *str);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

	int key; 
	int ret = sscanf(argv[1], "%d", &key);
    if (ret != 1) // ret は実際に代入された変数の個数。
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

