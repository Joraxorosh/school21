poww, x = map(float, input().split())
poww = int(poww)
res = 0
for i in reversed(range(poww)):
    temp = float(input())
    res += (i+1)*temp*x**i
float(input())
print("%.3f"%res)