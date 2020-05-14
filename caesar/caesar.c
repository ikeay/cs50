#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int my_atoi(const char *str, int* out);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

	int key, ret; 
	ret = my_atoi(argv[1], &key); 
    if (ret == -1) 
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

int my_atoi(const char *str, int* out)	
{	
	for (int i = 0; str[i] != '\0'; i++)	
	{	
		// 数字以外が含まれていたら-1 を返す。
		if (str[i] < '0' || str[i] > '9')	
		{
			*out = 0; // 変換できないので未定義になりますが、とりあえず0 を入れておく。
			return -1;	
		}	
	}
	// 数字のみが渡されていたら、数値に変換する。
	*out = atoi(str);
	return 0; 
} 

