import csv
import sys
from cs50 import SQL

def load_csv(file_name):
    ref = []
    with open(file_name, "r") as csv_file:
        csv_reader = csv.reader(csv_file)
        ref = [row for row in csv_reader]
    return ref[1::]


def is_birth_year(year):
    return year.isnumeric()


def is_house_name(house):
    return house.isalpha()


def is_name(name):
    return name.replace("-", "").isalpha()


def parse_house(house):
    if is_house_name(house):
        return ("\'{}\'").format(house)
    else:
        return "NULL"


def parse_birth(birth):
    if is_birth_year(birth):
        return ("\'{}\'").format(birth)
    else:
        return "NULL"


def parse_name(name):
    if is_name(name):
        return ("\'{}\'").format(name)
    else:
        return "NULL"


def parse_full_name(full_name):
    _sn = full_name.split()
    splitted_name = []
    for name in _sn:
        splitted_name.append(parse_name(name))

    if len(splitted_name) == 2:
        formatted_name = [splitted_name[0], "NULL", splitted_name[1]]
    elif len(splitted_name) == 3:
        formatted_name = [splitted_name[0], splitted_name[1], splitted_name[2]]
    else:
        formatted_name = ["NULL", "NULL", "NULL"]
    return formatted_name


def main():
    try:
        if not len(sys.argv) == 2:
            print("Usage: python import.py csv_file.", file=sys.stderr)
            sys.exit(1)

        csv_file_name = sys.argv[1]
        profiles = load_csv(csv_file_name)

        db = SQL("sqlite:///students.db")

        for profile in profiles:
            name = parse_full_name(profile[0])
            house = parse_house(profile[1])
            birth = parse_birth(profile[2])

            query = (
                "INSERT INTO students(first, middle, last, house, birth) VALUES ({first}, {middle}, {last}, {house}, {birth})"
            ).format(first=name[0], middle=name[1], last=name[2], house=house, birth=birth)
            db.execute(query)

    except Exception as e:
        print(e)
        sys.exit(1)


main()
