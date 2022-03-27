from cs50 import get_string

# Letter, sentence and word counter.
letter = 0
sentence = 0
words = 1

text = get_string("Text: ")

for i in text:
    # Checks for number of letters
    if i.isalpha():
        letter += 1
    # Checks for spaces which means a word has been passed by.
    if i == " ":
        words += 1
    # Checks for end of sentence.
    if i == "." or i == "!" or i == "?":
        sentence += 1

# Coleman liau index formula
L = (letter / words) * 100
S = (sentence / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

# Checks if grade is 16+, below 1 or in between.
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")