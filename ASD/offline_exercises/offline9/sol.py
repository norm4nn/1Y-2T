#Szymon Mamoń
# reprezentacja macierzowa, algorytm przechodzi po kazdej parze miast, 'merguje' je jesli sa rozne od S oraz suma wag
# krawedzi ktore do nich wchodza nie jest mniejsza od aktualnego resulta (zeby dalo sie w oogle go polepszyc)
# oraz jesli result jest rowny sumie wag wychodzacych ze zrodla S wtedy program jest zatrzymywany i zwracany odrazu
# result (bo nie da sie go polepszyc), kazda spelniajaca te warunki para miast tworzy jedno nowe miasto-ujscie T i odpalany na
# takim grafie jest algorytm forda-fulkersona
# O(v^4)
import collections

from zad9testy import runtests


def merge(C,x,y):
    for i in range(len(C)):
        C[i][y] += C[i][x]

def sum_input(G,x,y):
    result = 0
    for i in range(len(G)):
        result += G[i][x] + G[i][y]

    return result


def maxflow( G,s ):
    # tu prosze wpisac wlasna implementacje

    n = 0
    result = 0

    for i in range(len(G)):
        n = max(G[i][0],G[i][1],n)
    n += 1
    sum_of_output = 0
    for i in range(len(G)):
        if G[i][0] == s:
            sum_of_output += G[i][2]

    for x in range(n):
        for y in range(x+1,n):
            if x == s or y == s:
                continue
            if result == sum_of_output:
                return result
            C = [[0 for _ in range(n)] for __ in range(n)]

            for i in range(len(G)):
                C[G[i][0]][G[i][1]] += G[i][2]
            if sum_input(C,x,y) <= result:
                continue
            merge(C,x,y)


            flow = 0

            end_it = False
            while not end_it:#DFS moze bedzie lepszy
                parent = [None for _ in range(n)]
                c2out = [float('inf') for _ in range(n)]
                Q = collections.deque()
                Q.append(s)
                found = False
                #print(x," ",y)
                while Q:

                    curr = Q.popleft()
                    c_min = c2out[curr]
                    for i_temp in range(n):
                        i = i_temp
                        if i == x:
                            i = y
                        if parent[i] != None:
                            continue
                        c = C[curr][i]

                        if c == 0:
                            continue

                        c2out[i] = min(c_min,c)

                        parent[i] = curr
                        Q.append(i)
                        if i == y:
                            found = True
                            break
                    if found:
                        break

                if not found:
                    break
                c_min = c2out[y]
                flow += c_min

                last = y
                while last != s:
                    p_last = parent[last]
                    C[p_last][last] -= c_min
                    C[last][p_last] += c_min
                    last = p_last

            result = max(result,flow)



    return result

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( maxflow, all_tests = True )
