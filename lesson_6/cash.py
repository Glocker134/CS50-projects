# calculates the minimum number of coins required to give a user change

from cs50 import get_float

# Translating my old C code into Python
quarter = 25
dime = 10
nickel = 5
penny = 1

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

fixed = int(change * 100)
coins = 0

while fixed > 0:

    if fixed // quarter > 0:
        fixed -= quarter
    elif fixed // dime > 0:
        fixed -= dime
    elif fixed // nickel > 0:
        fixed -= nickel
    elif fixed // penny > 0:
        fixed -= penny
    coins += 1

print(coins)