#Szymon Mamoń
#

import collections

from zad6testy import runtests

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

    curr = t
    prev_has_alternative = False
    while parents[curr]:
        if len(parents[curr]) == 1:
            if not prev_has_alternative:
                return (parents[curr][0],curr)
            else:
                prev_has_alternative = False
                curr = parents[curr][0]
        else:
            curr = parents[curr][0]
            prev_has_alternative = True

    return None


    #return (0,0)

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( longer, all_tests = True )
