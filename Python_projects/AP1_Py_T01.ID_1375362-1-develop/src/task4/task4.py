try:
    a = int(input())
except:
    print("Natural number was expected")
else:
    if (a < 1):
        print("Natural number was expected")
    arr = [1]
    for i in range(a):
        print(*arr)
        if len(arr) == 1:
            arr.append(1)
        else:
            arr.insert(0, arr[0])
            for k in range(1, len(arr)-1):
                arr[k] += arr[k+1]