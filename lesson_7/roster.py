# Prints a list of students for a given house in alphabetical order
from cs50 import SQL
from sys import argv

houses = ['gryffindor', 'slytherin', 'ravenclaw', 'hufflepuff']


def main(argv):
    if len(argv) != 2:
        print("Usage: python roster.py house_name")
        return 1
    # Checking if argv[1] is one of the four houses
    elif argv[1].lower() not in houses:
        print(f"Error: {argv[1]} not found.")
        return 2

    print_roster(argv[1])
    return 0


# Print the house's roster
def print_roster(house):

    db = SQL("sqlite:///students.db")

    # Selecting names and year from the table based on house,
    # Sorted by last name first, followed by first name
    entries = db.execute("SELECT first, middle, last, birth FROM students WHERE house=? ORDER BY last ASC, first ASC", house)

    for data in entries:
        # If the middle value exists, print all 3 names, otherwise first and last
        if data['middle'] != None:
            print(data['first'], data['middle'], data['last'] + ", born", data['birth'])
        else:
            print(data['first'], data['last'] + ", born", data['birth'])


main(argv)