# SQLite Database

### Project
- Import dataset of Harry Potter characters into a Student DB (SQLite)
- Fetch roster of students and their details by house

**Usage**:

    python import.py characters.csv
    python roster.py Gryffindor


---
#### Non-specified
Use python's SQLite3 package instead of CS50 libraries

Workflow:

1. Import sqlite3 and set up the DB connection
2. Create and use a cursor object to run the SQL queries to create table, insert values, fetch details etc.
3. Commit changes and close connection


#### References
- [FOSS Sqlite Databases in Python](https://www.fosslinux.com/42798/basics-of-working-with-the-sqlite-databases-in-python.htm)
- [Stack Overflow - Dictionary from Sqlite Query](https://stackoverflow.com/questions/3300464/how-can-i-get-dict-from-sqlite-query)