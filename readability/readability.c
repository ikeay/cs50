#include <cs50.h>
#include <stdio.h>
#include <math.h>

int coleman_liau_index(int letter_count, int word_count, int sentence_count);

int main(void)
{
    char *text = get_string("Text: ");
    int letter_count = 0;
    int word_count = 0;
    int sentence_count = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z') || (text[i] >= '0' && text[i] <= '9'))
        {
            letter_count++;
        }
        if (i > 0 && text[i] == ' ' && text[i - 1] != ' ')
        {
            word_count++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count++;
        }
    }

    // adds _count of a last word
    word_count++;

    int index = coleman_liau_index(letter_count, word_count, sentence_count);
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

int coleman_liau_index(int letter_count, int word_count, int sentence_count)
{
    // the average number of letters per 100 words in the text
    float l = (float) letter_count / (float)word_count * 100.0f;

    // the average number of sentences per 100 words in the text
    float s = (float) sentence_count / (float)word_count * 100.0f;

    int index = (int) roundf((0.0588f * l) - (0.296f * s) - 15.8f);
    return index;
}
