# identifies the person based on their DNA sequence
import sys
import csv
import re


def main():
    if not len(sys.argv) == 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    else:
        name = match(sys.argv[1], sys.argv[2])
        print(name)
        sys.exit(0)


def match(database, sequence):
    # open and read DNA sequence input file
    with open(sequence, "r") as f1:
        seq = f1.read().strip()

    # open DNA database CSV file into a list of lists
    data = []
    with open(database, "r") as f2:
        db = csv.reader(f2)
        for row in db:
            data.append(row)

    # STR types in first row from second column of DB
    # Ex: AGATC,TTTTTTCT,AATG,TCTAG,GATA,TATC,GAAA,TCTG
    pattern = data[0][1:]

    # count longest run of each STR pattern in same order
    check_pat = []

    for p in pattern:
        # extract longest run using regex and max
        res = max(re.findall('((?:' + p + ')*)', seq), key=len)
        # count occurences in the longest run of that STR
        check_pat.append(str(res.count(p)))

    # find matching sequence in DB and return name
    i = 0
    for row in data:
        if check_pat == data[i][1:]:
            # match found, return name
            return data[i][0]
        else:
            i += 1
    # if not found in db
    return "No match"


main()
