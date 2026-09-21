def paint_square(i, j, figures):
    end_i = i
    end_j = j
    while (end_i < len(figures) and figures[end_i][j]==1):
        end_i += 1
    while (end_j < len(figures[0]) and figures[i][end_j]==1):
        end_j += 1
    for k in range(i, end_i):
        for l in range(j, end_j):
            figures[k][l] += 1

def paint_circle(i, j, figures):
    i_end=i
    while i_end+1 < len(figures) and figures[i_end][j] == 1:
        i_end+=1
    for k in range(i, i_end+1):
        while j < len(figures[0]) and figures[k][j] == 1:
            figures[k][j] += 3
            j += 1
        j-=1
        while k+1 < i_end and figures[k+1][j] == 0:
            j -= 1
        while k+1 < i_end and figures[k+1][j] == 1:
            j -= 1
        j += 1

lst = list(open('/home/joraxorosh/school21/python_backend/AP1_Py_T01.ID_1375362-1/src/task3/input.txt').readlines())
LEN = len(lst)
LEN_ST = len(lst[0])
lst_int = [[0]*(LEN_ST//2) for i in range(LEN)]
circles = 0
squares = 0

for i in range(LEN):
    for k in range (LEN_ST-1):
        if lst[i][k].isdigit():
            lst_int[i][(k)//2] = int(lst[i][k])

for i in range(LEN):
    for j in range(LEN_ST//2):
        if lst_int[i][j] == 1:
            if j == 0:
                squares += 1
                paint_square(i, j, lst_int)
            elif i < LEN-1 and lst_int[i+1][j-1] == 1:
                circles += 1
                paint_circle(i, j, lst_int)
            else:
                squares += 1
                paint_square(i, j, lst_int)

print(squares, circles)