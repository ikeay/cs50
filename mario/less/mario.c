#include <cs50.h>
#include <stdio.h>

int main(void)
{
    while (true)
    {
        int number = get_int("Height: ");

		// [notice] 入力が値域外の場合、そのことがわかるようにメッセージを表示した方が
		// 良いです。何がまずかったのかがわかるので。
        if (number >= 1 && number <= 8)
        {
            for (int i = 1; i <= number; i++)
            {
                for (int j = 0; j < (number - i); j++)
                {
                    printf(" ");
                }
                for (int j = 0; j < i; j++)
                {
                    printf("#");
                }
                printf("\n");
            }
            return 0;
        }
		// [notice] 値域外の値が入力された時のreturn がないです。
    }
}
