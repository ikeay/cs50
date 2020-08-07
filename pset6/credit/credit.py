from cs50 import get_int

def list_number(number):
    array = []
    while True:
        array.append(number % 10)
        number = number // 10
        if number <= 0:
            break
    return array[::-1]


def is_amex(list_number):
    if list_number[0] == 3:
        if list_number[1] == 4 or list_number[1] == 7:
            return True
    return False


def is_master(list_number):
    if list_number[0] == 5:
        if list_number[0] <= 5:
            return True
    return False


def is_visa(list_number):
    if list_number[0] == 4:
        return True
    return False


while True:
    data = get_int("Number: ")
    numbers = list_number(data)
    reverse_numbers = numbers[::-1]
    numbers_length = len(numbers)

    if numbers_length < 13 or numbers_length > 16:
        print("INVALID")
        break

    sum = 0
    for i in reverse_numbers[1::2]:
        sum += i * 2
        if i >= 5:
            sum -= 9

    for i in reverse_numbers[0::2]:
        sum += i

    if sum % 10 == 0:
        if is_amex(numbers):
            print("AMEX")
        elif is_master(numbers):
            print("MASTERCARD")
        elif is_visa(numbers):
            print("VISA")
        else:
            print("INVALID")
        break
