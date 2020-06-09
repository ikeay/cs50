import sys
from cs50 import SQL

def is_house_name(house):
    return house.isalpha()


def main():
    try:
        if not len(sys.argv) == 2:
            print("Usage: python roster.py csv_file", file=sys.stderr)
            sys.exit(1)

        if not is_house_name(sys.argv[1]):
            print("Can not input except alphabets.", file=sys.stderr)
            sys.exit(1)

        house = sys.argv[1]
        query = ("SELECT * FROM students WHERE house = \'{}\' ORDER BY last, first;").format(house)
        db = SQL("sqlite:///students.db")

        for row in db.execute(query):
            name = ""
            for item in list(row.values())[1:4]:
                if item:
                    name += item + " "
            name = name.strip()
            print(("{}, born {}").format(name, row["birth"]))

    except Exception as e:
        print(e)
        sys.exit(1)


main()