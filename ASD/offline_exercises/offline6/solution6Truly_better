# Szymon Mamoń
# ALgorytm najpiewr wykonuje BFS od wierzcholka S z dodatkowym zapisywaniem 'rodzicow' (tylko takich z ktorzy są częścią jednej z potencjalnych
# najkrotszych ścieżek prowadzocych do tego wierzchloka), nastepnie 'naprawia' graf G w taki sposob zeby skladal sie tylko z
# najkrtszych sciezek z S do T, nasptenie wykonuje algorytm Tarjana (zmodyfikowane DFS) ktory numeruje kolejnosc odwiedzenia
# jezeli natrafi na juz odwiedzony wierzcholek o mniejszym numerze niz jego sam, zpaisuje tenże numer
# jeżeli wierzcholek na ktory natrafi ma  taki sam numer jak on sam, znaczy to że krawedz miedzy nimi jest mostem w tym grafie
# zlozonosc: O(V+E)
import collections

from zad6testy import runtests

def Tarjan(G,v,vf,num,c,L):
    num[v] = c
    low = c
    c += 1
    for w in G[v]:
        if w == vf:
            continue
        if num[w] != 0 and num[w] < low:
            low = num[w]
            continue
        if num[w] == 0:
            temp = Tarjan(G, w, v, num, c,L)
            if temp < low:
                low = temp
    if vf > -1 and low == num[v]:
        L.append((vf,v))
    return low



def longer( G, s, t ):
    # tu prosze wpisac wlasna implementacje
    n = len(G)
    distance = 0
    L = [-1 for _ in range(n)]
    visited = [False for _ in range(n)]
    parents = [[] for _ in range(n)]
    queue = collections.deque()
    queue.append((distance,s))
    L[s] = 0
    visited[s] = True
    while queue:
        tmp_tupl = queue.popleft()
        v = tmp_tupl[1]
        distance = tmp_tupl[0] + 1
        for w in G[v]:
            if not visited[w]:
                visited[w] = True
                L[w] = distance

                queue.append((distance,w))
            elif distance - 2 == L[w]:
                parents[v].append(w)


    if L[t] == -1:
        return None

    #new graph
    #clearing
    helpQ = collections.deque()
    helpQ.append(t)
    while helpQ:
        v = helpQ.popleft()
        G[v] = []
        for w in parents[v]:
            helpQ.append(w)

    queue_new = collections.deque()
    queue_new.append(t)
    while queue_new:
        v = queue_new.popleft()
        for w in parents[v]:
            G[v].append(w)
            G[w].append(v)
            queue_new.append(w)

    #algorytm Tarjana
    num = [0 for _ in range(n)]
    T = []
    Tarjan(G,s,-1,num,1,T)

    if T:
        return T[0]
    return None
    #return T


    #return (0,0)

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( longer, all_tests = True )

#G    = [[1,2],[0,3],[0,4],[1,5],[2,5],[3,4]]
#print(longer(G,0,5)) testy niemiarodajne
