# Szymon Mamoń
# program najpierw tworzy 26 pustych kubków po jednym na kazda litere alfabetu nastepnie wypelnia je (zgodnie z indeksem
# pierwszej litery napisu) tablicą z napisem
# i counterem tego napisu w taki sposob ze najpierw sprawdza czy istnieje juz podany napis w danym kubku, jesli tak to
# zwieksza counter przy nim i przechodzi do nastepnego napisu w T, jesli nie to sprawdza kubek o indeksie ostatniego znaku
# tegoż napisu, jesli w nim takze nie znajdzie odwrotnego napisu to dodaje oryginalny napis do jego oryginalnego kubeczka z
# counterem ustawionym na 1, po przejsciu przez cala tablice T przechodze jeszcze raz po kubeczkach i listach counterow w nich
# zawartych i ustawiam siłe najsliniejszego napisu (max z counterow)
# złożonosć: O(n^2)
# dodatkowa pamieć: n


from kol1atesty import runtests
# def partition(T,l,r):
#     x = T[r]
#     j = l -1
#     for i in range(l,r):
#         if len(T[i]) <= len(x):
#             j += 1
#             T[i],T[j] = T[j],T[i]
#     j += 1
#     T[j],T[r] = T[r],T[j]
#     return j
#
# def qs(T,l,r):
#     stack = [[l,r]]
#     while stack:
#         tupl = stack.pop(-1)
#         l = tupl[0]
#         r = tupl[1]
#         if l<r:
#             q = partition(T,l,r)
#             stack.append([l,q-1])
#             stack.append([q+1,r])

def sortAlpha(T):
    lettters = [[] for i in range(26)]#inicjacja kubków
    for str in T:
        found = False
        id = ord(str[0])-97
        for tupl in lettters[id]:#sprawdzam czy nie ma juz takiego napisu w liscie o indeksie przypisanym do jego (napisu)
            if tupl[0] == str:#pierwszej litery
                tupl[1] += 1
                found = True
                break
        if found == False:#nie znaleziono napisu identycznego w liscie, jest szansa ze znajduje sie
            rev = str[::-1]# napis odwrotny do niego w kubku o indeksie ostatniej litery napisu
            id2 = ord(rev[0])-97
            if id != id2:#sprawdzam czy nie przechodze drugi raz po tej samej liscie
                for tupl in lettters[id2]:
                    if tupl[0] == rev:
                        tupl[1] += 1
                        found = True
                        break
            if found == False:#napis unikalny, nie ma napisu równoważnego do niego w żadnych z dwóch możliwych list
                lettters[id].append([str,1])
    max = 1
    for list in lettters:#szukam najwiekszej licznosci w liscie
        for tupl in list:
           if max < tupl[1]:
               max = tupl[1]
    return max
        #lettters[ord(str[0])-97].append(str)
    # j = 0
    # for list in lettters:
    #     while list:
    #         T[j] = list.pop(-1)
    #         j += 1


# def sortLen(T):
#     unicLen = []
#     for str in T:
#         flag = False
#         n = len(str)
#         for l in unicLen:
#             if n == l:
#                 flag = True
#                 break
#         if flag == False:
#             unicLen.append(l)
#
#     buckets = [[] for i in range(len(unicLen))]



# def revFromHalf(T):
#     halfOfAlphabet = 97 + 13
#     for i in range(len(T)):
#         if (ord(T[i][0]) >= halfOfAlphabet):
#             T[i] = T[i][::-1]

# def countStrongest(T):
#     counter = 0
#     max0 = 0
#     lastLen = T[0]
#     activeG = 0
#     newG = activeG
#     flag = False
#     for i in range(len(T)):
#         flag = False
#         if len(T[i]) != lastLen:
#             activeG = newG
#             lastLen = len(T[i])
#         counter = 0
#         for j in range(activeG,len(T)):
#             if len(T[i]) !=len(T[j]):
#                 newG = j
#                 flag = True
#             if T[i] == T[j] or T[i] == T[j][::-1]:
#                 counter += 1
#             if flag:
#                 break
#
#         if counter > max0:
#             max0 = counter
#
#     return max0


def g(T):
    # tu prosze wpisac wlasna implementacje

    #qs(T,0,len(T)-1)
    return sortAlpha(T)#countStrongest(T)


# Zamien all_tests=False na all_tests=True zeby uruchomic wszystkie testy
runtests( g, all_tests=True )
