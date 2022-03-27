from cs50 import get_int

# Gets input from user and makes sure it is between 1 to 8.
while True:
    num = get_int("Height: ")
    if num >= 1 and num <= 8:
        break

# Prints the triangle.
for i in range(1, num + 1):
    for j in range(1, num + 1):
        if(j <= num - i):
            print(' ', end='')
        else:
            print('#', end='')
    print()