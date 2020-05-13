#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int my_atoi(char *str);

int main(int argc, char *argv[])
{
	// [notice] argc != 2 でよくない？（＾＾；
    if (argc > 2 || argc <= 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

	// [notice] 独自でatoi を作られているようですが、何か意図があるのでしょうか？
	// 後述するように、atoi は戻り値が未定義となるケースがあるため、
	// atio ではなくsscanf を使うやり方もあることを覚えておきましょう。
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

int my_atoi(char *str)
{
	// [notice] 今までのコードを見る限り、C99 を前提にコーディングしていると
	// 思います。そうなると、atoi の使い方に注意が必要で、
	// C99 やC11 だと変換できなかった場合の戻り値は未定義になるようです
	// (戻り値が0になるとは限らない。)
    for (int i = 0; str[i] != '\0'; i++)
    {
		// [notice] ここの記述の仕方から、意図が読み取れません…。
		// ポインタの使い方を整理できていないのかもしれません。
        if (atoi(&str[i]) == 0 && strcmp(&str[i], "0") != 0)
        {
            return -1;
        }
    }
    return atoi(str);
}
