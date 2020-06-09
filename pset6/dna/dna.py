import csv
import sys

if not len(sys.argv) is 3:
    print("Usage: python dna.py csv_file txt_file.", file=sys.stderr)
    sys.exit(1)

csv_file_name = sys.argv[1]
txt_file_name = sys.argv[2]

# Load a csv file
try:
    with open(csv_file_name, "r") as csv_file:
        csv_reader = csv.reader(csv_file)
        ref = [row for row in csv_reader]
except (OSError, PermissionError, FileNotFoundError) as e:
    print(e)
    sys.exit(1)

# Load a txt file
try:
    with open(txt_file_name, "r") as txt_file:
        contents = txt_file.read()
        contents_length = len(contents)
except (OSError, PermissionError, FileNotFoundError) as e:
    print(e)
    sys.exit(1)

# [notice]
# ここはこのやり方でも正しく答えを出せていますが、count[i] をリストにしなくてもいけると思います。
# （リスト化することでメモリをかなり浪費しているのが気になります。）
# Create a hash table for counting repeats
count = {}
for i in ref[0][1::]:
    count[i] = [0]

# Count a number of STRs
for key in count.keys():
    key_length = len(key)
    start_count = 0
    for i in range(0, contents_length):
        seq_end = i + key_length
        if seq_end >= contents_length:
            break
        elif key == contents[i:seq_end]:
            count[key][-1] += 1
            start_count = 1
        elif 0 < start_count < key_length:
            start_count += 1
        else:
            start_count = 0
            count[key].append(0)

# STR
max_count = [str(max(v)) for _, v in count.items()]

# Identify whose DNA it is
for r in ref[1::]:
    if r[1::] == max_count:
        print(r[0])
        break
    elif r == ref[-1]:
        print("No match")
