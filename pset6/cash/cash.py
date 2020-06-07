from cs50 import get_float

while True:
    dollars = get_float("Change owed: ")
    if dollars > 0:
        cents = round(dollars * 100)
        count = 0
        coins = [25, 10, 5, 1]

        for i in coins:
            count += cents // i
            cents = cents % i

        print(count)
        break
