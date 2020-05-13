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
			// [notice] エラーメッセージは場所に応じて変えた方が良いです。
			// ユーザが原因を判断しやすいので。
			// (Web サーバのように、セキュリティ上エラーの原因を
			// 特定させたくない場合もあります。)
            printf("INVALID\n");
			// [notice] main 関数の返却値のポリシーは統一しておきましょう。
			// よくやるのは、正常終了の時に0 を、異常終了の時には
			// エラーコード（負値）を返すやり方です。
            return 0;
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
					// [notice] array[i] <= 9, _mult <= 18 であることはコード先頭部分で
					// 保証されるので、_mult > 9 ならば _mult / 10 は1であるし、
					// _mult % 10 は_mult - 10 と等しい。
					// 従って、ここはsum += _mult - 9 とする方が
					// シンプル。
                    sum += _mult / 10;
                    sum += _mult % 10;
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
        printf("INVALID\n");
		// [notice] ここも返却値を吟味しましょう。プログラムの仕様を
		// どうするか、仕様策定の時点で決めておく。
        return 0;
    }
}
