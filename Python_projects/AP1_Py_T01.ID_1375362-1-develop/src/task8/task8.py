a = int(input())
arr = [int(input())]
count = 1
for i in range(1, a):
    b = int(input())
    if b not in arr:
        count += 1
        arr.append(b)
print(count)