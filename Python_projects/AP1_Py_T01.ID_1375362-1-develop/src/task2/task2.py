res = True
a = int(input())
start = 10
end = 10
while (a//start > 0):
    start *= 10
start //=10
if a < 0:
    res = False
while (start>end):
    if (a//start != a%end):
        res = False
    a %= start
    a //= 10
    start //=100
print(res)