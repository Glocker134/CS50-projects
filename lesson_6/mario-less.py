# Prints out a half-pyramid of a specified height

from cs50 import get_int

# Adapting my old C code to Python

# Receiving input from user, will repeat until the received value is a value between 1 and 8
while True:
    size = get_int("Height: ")
    # Range can receive an optional starting value to the left of the end value
    if size in range(1, 9):
        break

# Printing each floor and adding whitespace when required
count = size - 1
for i in range(size):
    for j in range(size):
        if j < count:
            print(" ", end="")
        else:
            print("#", end="")
    print()
    count -= 1