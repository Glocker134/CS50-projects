# Identifies a person based on their DNA

import csv
from sys import argv

# csv reader and dictreader
def main():
    if (len(argv) != 3):
        print("Usage: python dna.py database sequence")
        return 1
    else:
        dna_checker(argv[1], argv[2])
        return 0

def dna_checker (database, sequence):
    # Setting up database dictionary & key list
    db = open(database, "r")
    reader = csv.DictReader(db)
    line_count = 0

    entries = []

    for row in reader:
        if line_count == 0:
            # Key list for future reference
            key = list(row.keys())
            line_count += 1
        entries.append(row)

    db.close()

    # Setting up the sequence string
    seq = open(sequence, "r")
    # Removing the line break at the end of the string
    seq_str = str.rstrip(seq.read())

    seq.close()

    # Call check function
    # Write check function


main()




