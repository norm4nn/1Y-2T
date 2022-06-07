#Szymon Mamoń
#uruchamiam DFS'a ktory przechodzi po grafie sprawdzajac w kazdym wierzcholku ktora bramą może wyjść
# DFS cofa sie jesli doszedl do konca i nie moze dojsc do startowego wierzcholka
#O((v+e)*logk)
from zad7testy import runtests

def binnarySearch(L,val):
    l = 0
    p = len(L) - 1
    while l <= p:
        m = (l+p)//2
        if val < L[m]:
            p = m - 1
        elif val > L[m]:
            l = m + 1
        else:
            return True
    return False



def droga( G ):
    # tu prosze wpisac wlasna implementacje
    n = len(G)
    visited = [ False for _ in range(n)]
    L = []
    found = False
    def DFSh(G, start, v, vf,visited, numberOfvisited, L):
        nonlocal found
        if found:
            return L

        numberOfvisited += 1
        L.append(v)
        visited[v] = True

        if vf != -1 and binnarySearch(G[v][0],vf):
            p = 1
        else:   p = 0

        if numberOfvisited == len(G):
            for w in G[v][p]:
                if w == start:
                    found = True
                    DFSh(G, start, v,w, visited, numberOfvisited, L)
                    if found:
                        return L
            numberOfvisited -= 1
            visited[v] = False
            L.pop(-1)
            return

        for w in G[v][p]:
            if not visited[w]:

                DFSh(G, start, w,v, visited, numberOfvisited, L)
                if found:
                    return L

        numberOfvisited -= 1
        visited[v] = False
        L.pop(-1)

        return None

    #DFSh(G,0,0,-1,visited,0,L)


    # if L != None and len(L) == len(G):
    #     for w in G[L[-1]][0]:
    #         if w == 0:
    #             return L
    #     for w in G[L[-1]][1]:
    #         if w == 0:
    #             return L

    return DFSh(G,0,0,-1,visited,0,L)
# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( droga, all_tests = True )
