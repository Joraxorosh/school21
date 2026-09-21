def check_allowed(data):
    allowed = "0123456789.+-e"
    d = 0
    e = 0
    flag = True
    for i in data:
        if not flag:
            break
        if i not in allowed:
            flag = False
        if i == ".":
            if e > 0:
                flag = False
            else:
                d += 1
        if i == "e":
            e += 1

    if d > 1 or e > 1:
        flag = False
    return flag

def check_detieled(data):
    flag = True
    numbers = "0123456789"
    signs = "+-"
    index_start = 0
    index_e = -1
    if data[0] in signs:
        index_start = 1
    if data[index_start] not in numbers:
        flag = False
    for i in data[index_start:]:
        if i == "e":
            index_e = data.index("e")
            break
        elif i not in numbers and i != ".":
            flag = False
            break
    if index_e == len(data)-1:
        flag = False
    if flag and index_e > 0:
        if data[index_e+1] in signs:
            index_e+=1
        for i in data[index_e+1:]:
            if i not in numbers:
                flag = False
                break
    return flag

data = input()
result = 0
flag = check_allowed(data)
if flag:
    flag = check_detieled(data)
if flag:
    sign = 1
    e = 0
    dot = 0
    index_start = 0
    numbers = "0123456789"

    if data[0] == "-":
        sign = -1
        index_start = 1
    elif data[0] == "+":
        index_start = 1
    if "." in data:
        if "e" in data:
            dot = data.index("e") - data.index(".") - 1
        else:
            dot = len(data) - data.index(".") - 1

    for i in data[index_start:]:
        if i == "e":
            e = data.index("e")
            break
        elif i in numbers:
            result*=10
            result+=numbers.index(i)
    
    if e > 0:
        e_sign = 1
        e_res = 0
        e+= 1
        if data[e] == "-":
            e_sign = -1
            e+=1
        elif data[e] == "+":
            e+=1
        for i in data[e:]:
            e_res*=10
            e_res+=numbers.index(i)
        e_res*=e_sign
        result*=10**e_res

    result/=10**dot*sign
    result *=2
    print("%.3f"%result)
else:
    print("Некорректный ввод!")