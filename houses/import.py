# import characters.csv into student.db
import sys
import csv
import sqlite3


def main():
    # correct arguments
    if not len(sys.argv) == 2:
        print("Usage: python import.py characters.csv")
        sys.exit(1)
    else:
        loaddb(sys.argv[1])
        sys.exit(0)


def loaddb(csvFile):
    # create new to write on fresh each time
    open("students.db", "w").close()
    # start connection and setup cursor
    conn = sqlite3.connect("students.db")
    db = conn.cursor()

    # create student table
    # db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")
    db.execute("CREATE TABLE students (     \
    id INTEGER PRIMARY KEY AUTOINCREMENT,   \
    first VARCHAR(255),                     \
    middle VARCHAR(255),                    \
    last VARCHAR(255),                      \
    house VARCHAR(10),                      \
    birth INTEGER)")

    # read from csv file
    with open(csvFile) as file:
        reader = csv.DictReader(file)

        # iterate over the rows
        for row in reader:
            # parse the names
            name = row["name"].split(" ")
            # first name
            first = name[0]
            if len(name) == 2:
                # no middle name
                middle = None
                last = name[1]
            else:
                # yes middle name
                middle = name[1]
                last = name[2]

            row_values = [first, middle, last, row["house"], row["birth"]]

            # insert values into the students DB
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", row_values)

    # Save and close
    db.close()
    conn.commit()
    conn.close()


if __name__ == "__main__":
    main()
