# Determines whether a provided credit card number is valid according to Luhn’s algorithm.

# AmEx uses 15 digits and start with 34 or 37.
# MasterCard uses 16 digits and start between 51 and 55.
# Visa uses between 13 and 16 digits and always start with 4.

from cs50 import get_int

# Translating my old C code into Python

# Main function
def main():
    while True:
        card = get_int("Number: ")
        if len(str(card)) >= 9 and len(str(card)) <= 16:
            break

    if luhn_check(card):
        if amex_check(card, 0):
            print("AMEX")
        elif visa_check(card, 0):
            print("VISA")
        elif master_check(card, 0):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


# Luhn algorithm checker
def luhn_check(card):
    first_sum = 0
    second_mult = 0
    aux = 0
    aux2 = 0
    # Flag 1 is for odd positions. Flag 0 is for even positions
    flag = 1
    answer = 0
    digit_count = 0

    # Adding up the odd and even positions
    while card != 0:
        aux = card % 10
        # Odd positions
        if flag == 1:
            first_sum += aux
            flag = 0
        # Even positions
        else:
            aux *= 2
            # If aux is a 2-digit number, add both digits and then add them to second_mult
            if aux // 10 > 0:
                while aux != 0:
                    aux2 += (aux % 10)
                    aux //= 10
                second_mult += aux2
            # Otherwise, just add aux to second_mult
            else:
                second_mult += aux
            flag = 1
        aux = 0
        aux2 = 0
        card //= 10
        digit_count += 1

    # Adding the totals in first_sum and second_mult to check if the last digit is zero
    # If it is zero, the card number is valid as per Luhn's algorithm
    answer = first_sum + second_mult
    if answer % 10 == 0:
        return True
    else:
        return False

# Checks if the card is American Express:
# First two digits are 34 or 37, card length must be 15
def amex_check(card, count):
    if card // 10 > 9 and count < 13:
        return amex_check(card // 10, count + 1)
    else:
        aux = card % 10
        aux2 = (card // 10) * 10
        ans = aux + aux2
        if ans == 34 or ans == 37:
            return True
        else:
            return False

# Checks if the card is Visa:
# First digit is 4
def visa_check(card, count):
    if card // 10 > 0:
        return visa_check(card // 10, count + 1)
    else:
        if card // 10 > 0 and count < 16:
            return visa_check(card // 10, count + 1)
        elif card // 10 == 0 and count < 16:
            if card % 10 == 4:
                return True
            else:
                return False

# Checks if the card is Mastercard:
# First two digits are between 51 and 55, length must be 16
def master_check(card, count):
    if card // 10 > 9 and count < 14:
        return master_check(card // 10, count + 1)
    else:
        aux = card % 10
        aux2 = (card // 10) * 10
        ans = aux + aux2
        if ans >= 51 and ans <= 55:
            return True
        else:
            return False

main()