# Identifies a person based on their DNA

import csv
from sys import argv


def main(argv):
    if (len(argv) != 3):
        print("Usage: python dna.py database sequence")
        return 1
    else:
        dna_checker(argv[1], argv[2])
        return 0


# Check if the sequence matches the data of an entry in the database
def dna_checker(database, sequence):
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

    # Checking each entry in the database
    for item in entries:
        flag = True

        # Checking if the STR consecutive matches can be found in the sequence
        for count in range(1, len(key)):
            # If the function returns False, then it's not
            if not str_checker(key[count], item[key[count]], seq_str):
                flag = False
                break
        if flag:
            print(item[key[0]])
            return

    print("No match.")
    return


# Checks if key can be found target_value times in a row inside dna
def str_checker(key, target_value, dna):
    seq_size = len(key)
    ran = len(dna)
    times = 0
    longest_streak = 0
    target_value = int(target_value)

    for i in range(0, ran):
        # If a first match is found, record the index value and keep a consecutive flag True
        if "".join(dna[i:i + seq_size]) == key:
            times += 1
            consecutive = True
            # Check for consecutive key patterns right after the first one
            for j in range(i + seq_size, ran - seq_size, seq_size):
                if "".join(dna[j:j + seq_size]) == key:
                    times += 1
                else:
                    consecutive = False
                    # If the current consecutive pattern streak is longer than the one stored, update it and the index
                    if times > longest_streak:
                        longest_streak = times
                    times = 0
                    if not consecutive:
                        break

    if longest_streak == target_value:
        return True
    else:
        return False


main(argv)