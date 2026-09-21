N, M = map(int, input().split())
a = [list(map(int, input().split())) for i in range (N)]
b = a.copy()

for i in range (1, N):
    b[i][0] += b[i-1][0]
    for j in range (1, M):
        b[i][j]+= max(b[i-1][j], b[i][j-1])

print(b[N-1][M-1]) 