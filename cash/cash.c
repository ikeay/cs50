#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    while (true)
    {
		// [notice] ここはコメントだけ。
		// お金を扱う時は、扱える値の範囲に注意です。
		// 実運用の時は比較的容易にオーバーフローを起こします。
		// 一部のSQL の中にはmoney型とかいうものもあります。
		// (固定小数で64bit 表現)
        float dollars = get_float("Change owed: ");
        if (dollars > 0)
        {
            int cents = round(dollars * 100);
            int count = 0;
            int coins[] = {25, 10, 5, 1};
            int arrayLength = sizeof(coins) / sizeof(coins[0]);

            for (int i = 0; i < arrayLength; i++)
            {
                int changes = cents / coins[i];
                cents = cents % coins[i];
                count += changes;
            }

            printf("%i\n", count);
            return 0;
        }
    }
}
