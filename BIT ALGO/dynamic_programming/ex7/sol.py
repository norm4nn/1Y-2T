import collections
from zad1ktesty import runtests


def count_liters(T,x):
    full_sum = 0
    max_depth = len(T) - 1
    max_width = len(T[0]) - 1
    que = collections.deque()
    que.append((0,x))
    while que:
        coordinates = que.popleft()
        full_sum += T[ coordinates[0] ][ coordinates[1] ]
        T[ coordinates[0] ][ coordinates[1] ] = 0
        if coordinates[0] < max_depth and T[ coordinates[0] + 1 ][ coordinates[1] ] != 0:
            que.append(( coordinates[0] + 1, coordinates[1] ))
        if coordinates[1] > 0 and T[ coordinates[0] ][ coordinates[1]-1 ] != 0:
            que.append(( coordinates[0], coordinates[1] - 1 ))
        if coordinates[1] < max_width and T[ coordinates[0] ][ coordinates[1] + 1 ] != 0:
            que.append(( coordinates[0], coordinates[1] + 1 ))
        if coordinates[0] > 0 and T[ coordinates[0] - 1 ][ coordinates[1] ] != 0:
            que.append((coordinates[0]-1, coordinates[1]))

    return full_sum


# def recursive(W,Z,l,i,best):
#     if i == len(W):
#         return best
#     inc = 0
#     if l - W[i] >= 0:
#         inc = recursive(W,Z,l-W[i],i+1,best+Z[i])
#
#     exc = recursive(W,Z,l,i+1,best)
#
#     return max(inc,exc)

def ogrodnik (T, D, Z, l):
    n = len(D)

    # all_liters = 0
    # for i in range(len(T)):
    #     all_liters += sum(T[i])

    W = [0 for _ in range(n)]

    # all_i_counted = 0
    for i in range(n):
        W[i] = count_liters(T,D[i])
        # all_i_counted += W[i]

    #print(all_i_counted, "/", all_liters)
    #just knapsack
    F  = [[0 for _ in range(l+1)] for __ in range(n)]
    for i in range(W[0],l+1):
        F[0][i] = Z[0]


    for i in range(1,n):
        for j in range(l + 1):
            F[i][j] = F[i-1][j]
            if j - W[i] >= 0:
                F[i][j] = max(Z[i] + F[i-1][j-W[i]], F[i][j])

    #gettin result
    # y = n - 1
    # x = l
    # L = []
    # while y >= 0:
    #     if y > 0 and F[y][x] != F[y-1][x]:
    #         L.append(y)
    #         x -= W[y]
    #     elif y == 0:
    #         if F[0][x] != 0:
    #             L.append(0)
    #     y -= 1

    #checkin
    # taken_liters = 0
    # for i in range(len(L)):
    #     taken_liters += W[L[i]]
    # print(taken_liters,"/",l,end=" ")
    # if taken_liters <= l:
    #     print("jest ok jesli chodzi o litry")
    # else:
    #     print("nie jest ok jesli chodzi o litry")


    return F[n-1][l]

    #return recursive(W,Z,l,0,0)

runtests( ogrodnik, all_tests=True )
