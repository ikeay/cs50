#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int my_atoi(char *str);

int main(int argc, char *argv[])
{
	// [notice] argc != 2でいいんじゃ…（以下略）
    if (argc > 2 || argc <= 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *keys = argv[1];
    int keyNums[26];
	// [notice] バッファオーバーランを起こすので、事前に文字列長を
	// チェックしておいた方が良いです。
	// (今回の場合はkeys に対しては読み込みアクセスだけですので、
	// メモリを破壊することはないとは思いますが、チェックはしておいた方が良いです。)
    for (int i = 0; i < 26; i++)
    {
		// [notice] 大文字と小文字を区別していますが、keyNums を求めるためだけに区別
		// する必要はないですので、事前にすべて大文字または小文字に変換すると
		// 少しすっきりします。
		// 大文字・小文字への変換は標準関数で用意されています。
		// toupper, tolower 関数です。
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
		// [notice] 単純にアルファベットから他のアルファベットへのマップであれば
		// もう少し短く書けるのではないかと思います。
		// 配列を上手に使いましょう。
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
