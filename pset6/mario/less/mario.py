from cs50 import get_int

while True:
    height = get_int("Height: ")

    if height >= 1 and height <= 8:
        for i in range(1, height + 1):
            print(("{}{}").format(" " * (height - i), "#" * i))
        break
