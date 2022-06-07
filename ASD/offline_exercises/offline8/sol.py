#Szymon Mamoń
#algorytm szuka MST za pomoca algorytmu kruskala dla zaczynajac od kazdej krawedzi zwracajac dla kazdego mst roznice pomiedzy
#najdluzsza krawedzia i najkrotsza
# O(v^2 + v^5 * log v)
from zad8testy import runtests

def cost(c1,c2):
    d = (c1[0]-c2[0])**2 + (c1[1]-c2[1])**2
    d **= 1/2
    if d > int(d):
        return int(d) + 1
    return int(d)


class Node:
    def __init__(self,val):
        self.rank = 0
        self.val = val
        self.parent = self


def find(x):
    if x.parent != x:
        x.parent = find(x.parent)

    return x.parent

def union(x,y):
    if x == y:
        return
    if x.rank > y.rank:
        y.parent = x
    else:
        x.parent = y
        if x.rank == y.rank:
            y.rank += 1


def build_MST(L,start,n,Nodes,m):
    edges = 0
    i = start
    while edges < n - 1 and i < len(L):
        x = find(Nodes[L[i][1]])
        y = find(Nodes[L[i][2]])

        if x == y:
            i += 1
            continue
        union(x,y)
        edges += 1
        i += 1
        if L[i-1][0]-L[start][0] >= m:
            return m
    if edges == n-1:
        return L[i-1][0] - L[start][0]
    return m



def highway( A ):
    n = len(A)
    L = []
    for i in range(n):
        for j in range(i+1,n):
            L.append((cost(A[i],A[j]),i,j))

    result = float('inf')
    L.sort()
    m = float('inf')
    for i in range(n*(n-1)//2-n+1):
            if not L[i+n-2][0]-L[i][0] > m:
                Nodes = [Node(i) for i in range(n)]
                m = build_MST(L,i,n,Nodes,m)


    return m

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( highway, all_tests = True )
