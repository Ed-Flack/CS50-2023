import cs50

text = cs50.get_string("Text: ")
words = 0
sentences = 0
letters = 0
currentWord = False

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
        if not currentWord:
            words += 1
        currentWord = True
    elif text[i] == "?" or text[i] == "!" or text[i] == ".":
        sentences += 1
        currentWord = False
    elif text[i] == " ":
        currentWord = False

l = letters / words * 100  # Average number of letters per 100 words
s = sentences / words * 100  # Average number of sentences per 100 words
grade = round(0.0588 * l - 0.296 * s - 15.8)  # Coleman-Liau index
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print("Grade", grade)
