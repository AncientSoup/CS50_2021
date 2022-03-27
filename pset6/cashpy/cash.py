from cs50 import get_float

# Available coins
change = [25, 10, 5, 1]

# Total coins used.
final = 0

while True:
    money = get_float("Change owed: ")
    if money >= 0:
        break

# Rounds up the money.
cent = int(round(money * 100))

for i in change:
    final += cent // i
    cent %= i
        
print(final)