#Szymon Mamoń
#algorytm najpierw sortuje tablice T2 ktora zawiera punkty 'b' ktore są koncami przedzialow i indeksy tych przedzialow
#nastepnie w algorytmie blizniaczo podobnym do rozwiazania dynamicznego problemu plecakowego
#wystepuje warunek kolizji dwoch budynkow, jesli budynek moze zostac zbudowany bo pozwala na to jego cena
# (*) sprawdzam czy nie wystepuje kolizja z poprzednim budynkiem, jesli nie to sprawdzam max, jesli kolizja wystepuje
# to cofam sie do jeszcze wczesniejszej lini i powtarzam czynnosc(*)
# po przejsciu w ten sposob przez n budynkow, odczytuje 'droge' z jaka doszedlem do maksymalnego wyniku w sposob odwrotny
# do przedstawionej wczesniej petli (*)
# zlozonosc pesymistyczna O(p*n^2 + nlogn)
from zad4testy import runtests

def vol(building):
    return building[0]*(building[2]-building[1])

# def price(building):
#     return building[3]
#
# def attractive(building):
#     return vol(building)/building[3]

def is_collision(B1,B2):
    #return (B1[1] <= B2[1] and B1[2] >=  B2[1]) or  (B1[1] >= B2[1] and B2[2] >=  B1[1])
    return not (B1[2] < B2[1] or B1[1] > B2[2])





def select_buildings(T,p):
    result = []
    n = len(T)

    # for i in range(n):
    #     print(T[i])
    T2 = [[T[i][2],i] for i in range(n)]

    T2.sort()
    # for i in range(n):
    #      print(T2[i])

    F = [[0 for _ in range(p+1)] for __ in range(n)]
    for i in range(T[T2[0][1]][3],p+1):
        F[0][i] = vol(T[T2[0][1]])

    for b in range(p+1):
        for i in range(1,n):
            F[i][b] = F[i-1][b]

            if b - T[T2[i][1]][3] >= 0:
                j = i - 1
                while (is_collision(T[T2[j][1]],T[T2[i][1]]))  and j >= 0:
                    j -= 1
                if j >= 0:
                    F[i][b] = max(F[i][b],F[j][b-T[T2[i][1]][3]]+vol(T[T2[i][1]]))
                else:
                    F[i][b] = max(F[i][b],vol(T[T2[i][1]]))

    #getting result
    x = p
    i = n-1
    #for i in range(n-1,-1,-1):
    while i >= 0:
        if  i != 0 and F[i][x] != F[i-1][x]:
            added = F[i][x]
            addin = vol(T[T2[i][1]])
            result.append(T2[i][1])
            x -= T[T2[i][1]][3]
            j = i-1

            while j >= 0 and F[j][x] + addin != added:
                j -= 1
                i -= 1
            #if j >= 0:
                #i = j
        elif i == 0 and F[0][x] != 0:
            result.append(T2[0][1])
        i -= 1
    result.sort()
    #result = result[::-1]
    # if n >= 10:
    #     for i in range(10):
    #         print(i,T[i])
    # for i in range(n):
    #     print(T2[i])
    # for i in range(n):
    #     print(F[i])
    return result

runtests( select_buildings )
