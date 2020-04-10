# Imports data from a CSV spreadsheet
import csv
from cs50 import SQL
from sys import argv


def main(argv):
    if len(argv) != 2:
        print("Usage: python import.py spreadsheet")
        return 1

    csv_import(argv[1])
    return 0


def csv_import(csv_file):
    # We're considering the csv file exists and it's not empty.
    file = open(csv_file, "r")
    db = SQL("sqlite:///students.db")

    # Getting the entries in a dictionary
    reader = csv.DictReader(file)

    for rows in reader:
        name = rows['name'].split()
        # If the student doesn't have a middle name, use None as value for that column
        if len(name) == 3:
            db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?)",
                       name[0], name[1], name[2], rows['house'], rows['birth'])
        else:
            db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?)",
                       name[0], None, name[1], rows['house'], rows['birth'])

    file.close()


main(argv)