from cs50 import get_string

def is_word_end(c):
    return c is " "

def is_sentence_end(c):
    return c is "." or c is "!" or c is "?"

def is_letter(c):
    return c.isalpha() or c.isdigit()

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

