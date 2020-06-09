from cs50 import get_string

# [notice]
# こちらもcredit.py と同様に、== とis の使い分けが気になります。
# C言語の文字列比較(ポインタ同士の比較ではなくstrcmp を使う)や
# Java での文字列比較(== ではなくequals メソッドを使う)にも言えますが、
# 文字列をインスタンスで比較するのか(is を使う)、中身で比較するのか(== を使う）を
# 適切に使い分けるべきです。
# 今回のケースではいずれも文字列を中身で比較するケースですので、== を使った比較の方が適切かと思います。


def is_word_end(c):
    return c is " "

def is_sentence_end(c):
    return c is "." or c is "!" or c is "?"

def is_letter(c):
    return c.isalpha()

def coleman_liau_index(letter_count, word_count, sentence_count):
    l = 100 * letter_count / word_count
    s = 100 * sentence_count / word_count
    result = (0.0588 * l) - (0.296 * s) - 15.8
    return round(result)

text = get_string("Text: ")

count = 0
letter_count = 0
word_count = 0
sentence_count = 0

for c in text:
    if is_word_end(c):
        word_count += 1
    elif is_sentence_end(c):
        sentence_count += 1
    elif is_letter(c):
        letter_count += 1

# added count of last word
word_count += 1

index = coleman_liau_index(letter_count, word_count, sentence_count)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(("Grade {}").format(index))
