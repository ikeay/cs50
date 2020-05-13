#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    char *text = get_string("Text: ");
    int letterCount = 0;
    int wordCount = 0;
    int sentenceCount = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z') || (text[i] >= '0' && text[i] <= '9'))
        {
            letterCount++;
        }
        if (i > 0 && text[i] == ' ' && text[i - 1] != ' ')
        {
            wordCount++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceCount++;
        }
    }

    // adds count of a last word
    wordCount++;

    // the average number of letters per 100 words in the text
    float l = (float) letterCount / wordCount * 100;

    // the average number of sentences per 100 words in the text
    float s = (float) sentenceCount / wordCount * 100;

	// [notice] roundf の引数はfloat 型なので、中の式の評価値もfloat の
	// 方が好ましいですが、0.0588 と書くと全体でdouble 型になります。
	// ここはfloat 型で統一するよう、0.0588f と書きましょう。
	// また、必須ではないのですが、こういった公式のような記述は
	// 関数にして然るべき関数名を付与してあげると、コードの可読性が向上します。
    int index = (int) roundf((0.0588 * l) - (0.296 * s) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
