try:
    N, time = map(int, input().split())
    machines = [[0]*3]*N
    if time <= 0 or N <= 0:
        raise Exception("Ошибка!")
    for i in range(N):
        machines[i] = list(map(int, input().split()))
    
    for i in machines:
        for j in i:
            if j <= 0:
                raise Exception("Ошибка!")
    machines.sort()
    min_price = -1
    for i in range(N):
        for j in machines[i+1:]:
            if j[0] == machines[i][0] and j[2] + machines[i][2] == time and (j[1] + machines[i][1] < min_price or min_price == -1):
                min_price = j[1] + machines[i][1]


    print(min_price)
except:
    print("Ошибка!")