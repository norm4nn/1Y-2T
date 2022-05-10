from zad1ktesty import runtests

def recursive(s,t,m,n,steps):
    if m == -1 or n == -1:
        return steps + 1 + max(n,m)

    if s[m] == t[n]:
        return recursive(s,t,m-1,n-1,steps)
    else:
        return min(recursive(s,t,m-1,n-1,steps+1),recursive(s,t,m-1,n,steps+1),recursive(s,t,m,n-1,steps+1))

def napraw ( s, t ):
    F = [[0 for _ in range(len(s))] for __ in range(len(t))]
    for i in range(len(s)):
        for j in range(len(t)):
            if t[j] != s[i]:
                insert_cost = 0
                delete_cost = 0
                replace_cost = 0
                if j == 0:
                    insert_cost = 2 + i
                    replace_cost = 1 + i
                else:
                    insert_cost = 1 + F[j-1][i]


                if i == 0:
                    delete_cost = 2 + j
                    replace_cost = 1 + j
                else:
                    delete_cost = 1 + F[j][i-1]

                if i != 0 and j != 0:
                    replace_cost = 1 + F[j-1][i-1]

                F[j][i] = min(replace_cost,delete_cost,insert_cost)
            else:
                if j != 0 and i != 0:
                    F[j][i] = F[j-1][i-1]
                elif i == 0:
                    F[j][i] = j
                elif j == 0:
                    F[j][i] = i

    print(s,t)

    return F[len(t) - 1][len(s) - 1]

    #return recursive(s,t,len(s)-1,len(t)-1,0)

runtests ( napraw )
