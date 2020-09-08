# Fetch the roster of students in a house
# Ordered alphabetically by last name, then first name

import sys
import sqlite3

def main():
    # correct arguments
    if not len(sys.argv) == 2:
        print("Usage: python roster.py Gryffindor")
        sys.exit(1)
    else:
        roster(sys.argv[1])
        sys.exit(0)


# fetch_house is the input from user
def roster(fetch_house):
    # open database in read mode
    open("students.db", "r").close()
    # start connection
    conn = sqlite3.connect("students.db")

    # set row factory property of connection object to sqlite3.Row
    conn.row_factory = sqlite3.Row
    # this is to return list of dictionaries instead of tuples

    # set cursor object
    cur = conn.cursor()

    # query DB to fetch students ordered by name in each house
    cur.execute("SELECT * FROM students WHERE house = ? ORDER BY last ASC, first ASC", [fetch_house])

    # convert sqlite3.Row objects to dictionary
    result = [dict(row) for row in cur.fetchall()]

    # # check dictionary
    # for i in result:
    #     print(i)

    for row in result:
        print(row["first"], end=" ")
        if not row["middle"] == None:
            print(row["middle"], end=" ")
        print(row["last"] + ", born " + str(row["birth"]))

    # close db
    cur.close()
    conn.commit()
    conn.close()


if __name__ == "__main__":
    main()
