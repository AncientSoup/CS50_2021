import sys
import csv

# To check STR patterns in the sequence text. 


def repeats(str, dnas):
    count = 0
    while str * (count + 1) in dnas:
        count += 1
    return count

# To verify whether an STR is matched with any of the people in the database.


def check(STR, num_of_strs, i):
    for str in STR:
        if num_of_strs[str] != int(i[str]):
            return False
    return True
    
    
num_of_strs = {}

# Checks if user types the correct sequence of arguments.
if len(sys.argv) != 3:
    print("Proper usage: python dna.py database/(large/small).csv sequences(1-20).txt")
    sys.exit()

# To open database and sequence.
file1 = open(sys.argv[1], "r")
file2 = open(sys.argv[2], "r")

# To put file1 in a dictionary so it can be manipulated much easier and to obtain the STR of the opened file.
database = csv.DictReader(file1)
STR = database.fieldnames[1:]

dnas = file2.read()
file2.close()

for str in STR:
    num_of_strs[str] = repeats(str, dnas)
    
for i in database:
    if check(STR, num_of_strs, i):
        print(f"{i['name']}")
        file1.close()
        sys.exit()

# If there's no match.    
print("No match")
file1.close()