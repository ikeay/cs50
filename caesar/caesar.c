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

	int key = my_atoi(argv[1]); 
    if (key == -1) 
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

// [notice]
// 1. 変換元の文字列は変更されないことを明示すべきです。つまり、
// char *str ではなく、const char* str とすべきです。
// 
// 2. 読み込みがうまくいったかどうかの結果と、実際に読み込んだ結果とを
// 別々に取得する方が拡張性が高いです。具体的には
//
// int my_atoi(const char* str, int* out)
//
// のように定義します。
//
// 3. int を返すだけの関数だと、負の数を取得できないため。
// 今回の場合、正の整数か０のみを取得するようにすれば実装はシンプルになります。
// 負の数の場合、符号部分があるため、若干面倒です。
// 本気でやるなら正規表現を使いますが、今回のプログラムの本質からは
// 外れるのではないかと思います。
int my_atoi(char *str)	
{	
	for (int i = 0; str[i] != '\0'; i++)	
	{	
		// [notice]
		// ここの意図が不明です。&str[i] はchar のアドレス型なので、
		// 部分文字列を示しています。つまり、部分文字列を徐々に先頭から
		// 縮小していきながら、変換処理＆比較と、"0" との比較処理と、
		// それぞれ実行していっています。
		if (atoi(&str[i]) == 0 && strcmp(&str[i], "0") != 0)	
		{	
			return -1;	
		}	
	}	
	return atoi(str);	
} 

