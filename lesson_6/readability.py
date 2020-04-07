#  Computes the approximate grade level needed to comprehend some text.

from cs50 import get_string

# Translating my old C code into Python

# Defining a list of punctuation that denotes a new sentence
punctuation = ["!", "?", "."]
sentence_count = 0
letter_count = 0

text = get_string("Text: ")

# Separating the string by whitespaces, and placing it in a list
checker = text.split()

# Since string.split() separates the text by whitespace, check the size of the list
# To get word count
word_count = len(checker)
for item in checker:
    for char in item:
        # If the character is alphanumeric, increase the letter count by one
        if char.isalnum():
            letter_count += 1
        # Else if it's a character inside the punctuation list, increase sentence count by one
        elif char in punctuation:
            sentence_count += 1

# Calculating the letter and sentence average per 100 words
letter_avg = round((letter_count * 100) / word_count, 4)
sentence_avg = round((sentence_count * 100) / word_count, 4)

# Calculating the reading level
index = round(0.0588 * letter_avg - 0.296 * sentence_avg - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade", index)