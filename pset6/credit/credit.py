from cs50 import get_int

# [notice]
# 全体的に気になりますが、== とis の使い分けは意識してされていますか？
# is はオブジェクトidの比較で、== は等価であるかどうかの判定です。
# したがって、左辺と右辺の数値が同じでも、is での比較を行うと比較結果が
# True になることもFalse になることもあります（環境依存？）。
#
# 例えば、cs50 IDE の環境だと以下のようになります。

'''
>>> a0=1
>>> b0=1
>>> a0 is b0
True
>>> a0 == b0
True
>>> a1 = 2000
>>> b1 = 2000
>>> a1 is b1
False
>>> a1 == b1
True
'''


# 一部の数値に対してはシングルトンオブジェクトが内部的に生成されているため、
# is での比較が== での比較と同じ結果になるようですが、
# それ以外の数値に対してはＮＧのようです。
#
# 比較処理自体はis の方が高速ではありますが、比較する数値によって比較の振舞が変わるため、
# 数値の比較にはis を使うべきではないでしょう。


def list_number(number):
    array = []
    while True:
        array.append(number % 10)
        number = number // 10
        if number <= 0:
            break
    return array[::-1]


def is_amex(list_number):
    if list_number[0] is 3:
        if list_number[1] is 4 or list_number[1] is 7:
            return True
    return False


def is_master(list_number):
    if list_number[0] is 5:
        if list_number[0] <= 5:
            return True
    return False


def is_visa(list_number):
    if list_number[0] is 4:
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

    if sum % 10 is 0:
        if is_amex(numbers):
            print("AMEX")
        elif is_master(numbers):
            print("MASTERCARD")
        elif is_visa(numbers):
            print("VISA")
        else:
            print("INVALID")
        break
