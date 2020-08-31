# Outputs the READABILITY GRADE LEVEL of a passage provided by the user
# Grade Level calculated by the following Coleman-Liau Index formula (rounded to nearest whole number)
# Index = 0.0588 * L - 0.296 * S - 15.8
# L - avg no of letters per 100 words, S - avg no of sentences per 100 words

# Input Passage ASSUMPTIONS & DEFINITIONS made for this software version
# a letter is any Engligh alphabet from 'a' to 'z' or 'A' to 'Z'
# a word is a sequence of characters separated by " "
# a hyphenated word is considered to be 1 word, ex: "sister-in-law" is one word with 11 letters
# a sentence shall not start or end with a space, it must only end with "?" or "." or "!"
# a sentence must not have multiple spaces in a row
# Known version limitation: any period used within one grammatical sentence will also be considered as the end of a sentence
# Ex: "Mr. and Mrs. George are out of town." will be considered as 3 sentences

import re

passage = input("Text: ")

# Count number of letters
l = len(re.findall("[a-z]", passage, re.IGNORECASE))

# Count number of words
w = passage.count(" ") + 1

# Count number of sentences
s = len(re.findall(r"\?|\.|!", passage))

# Coleman-Liau index calculation
L = l * 100 / w
S = s * 100 / w
index = (0.0588 * L) - (0.296 * S) - 15.8

# Print grade according to index
if round(index) < 1:
    print("Before Grade 1")
elif round(index) > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")