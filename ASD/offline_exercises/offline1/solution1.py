# Szymon Mamoń
# algorytm tworzy kopiec w tablicy z pierwszych k+1 wezlow posortowany za pomocą funkcji heapifyMINUP
# w taki sposob aby w korzeniu znalazl sie najmniejszy element, (**1**) nastepnie doklada kolejny element na koniec tablicy
# zamienia wartosci T[0] z T[len(T)-1], ostatni elemnt tablicy wstawia na koniec nowej posortowanej listy
# nastepnie naprawia zepsuty kopiec funkcją heapifyMINDown(T,0,n) tak aby kolejny najmniejszy element znalazl sie
# w korzeniu (na poczatku listy) i algorytm wraca do miejsca (**1**), powtarza te czynnosci do wyjscia wskaznika po za
# nieposortowaną liste, po czym wykonuje te same czynnosci tym razem zmniejszajac zakres "naprawiania" tablicy
# i nie zamieniając (swap) wartości a jedynie przypisując wartość z konca tablicy na jej poczatek- powtarza do skurczenia
#zakresu do 1
#dla k = Θ(1), średnia złożoność = Θ(n)
# k = Θ(logn), średnia złożoność = Θ(nlog^2(n))
# oraz k = Θ(n), średnia złożoność = Θ(nlog(n))
from zad1testy import Node, runtests


def SortH(p,k):
    # tu prosze wpisac wlasna implementacje
    if k == 0 or p == None or p.next == None:
        return p

    T = []
    counter1 = 0

    while counter1 < k + 1 and p != None:
        q = p
        p = p.next
        T.append(q)
        #heapifyMINUP(T, counter1)
        i = counter1
        daddy = (i - 1) // 2
        while i > 0 and T[daddy].val > T[i].val:
            T[i], T[daddy] = T[daddy], T[i]
            i = daddy
            daddy = (i - 1) // 2
        counter1 += 1

    if p != None:
        T.append(p)
    else:
        T.append(None)

    n =  len(T) - 1
    result  = T[0]
    tail = result

    while p != None:
        q = p
        p = p.next
        T[n] = q
        T[0],T[n] = T[n], T[0]
        #heapifyMINDown(T,0,n)
        i = 0
        flaga = True
        while flaga:
            min0 = i
            l = 2 * i + 1
            r = 2 * i + 2
            if l < n and T[l].val < T[min0].val:
                min0 = l
            if r < n and T[r].val < T[min0].val:
                min0 = r
            if min0 != i:
                T[min0], T[i] = T[i], T[min0]
                flaga = True
                i = min0
            else:
                flaga = False
        tail.next = T[0]
        tail = tail.next

    n1 = len(T) - 2
    for j in range(n1,0,-1):
        T[0] = T[j]
        #heapifyMINDown(T, 0, i)
        i = 0
        flaga = True
        while flaga:
            min0 = i
            l = 2 * i + 1
            r = 2 * i + 2
            if l < j and T[l].val < T[min0].val:
                min0 = l
            if r < j and T[r].val < T[min0].val:
                min0 = r
            if min0 != i:
                T[min0], T[i] = T[i], T[min0]
                flaga = True
                i = min0
            else:
                flaga = False
        tail.next = T[0]
        tail = tail.next

    tail.next = None
    return result
    pass
runtests( SortH )


