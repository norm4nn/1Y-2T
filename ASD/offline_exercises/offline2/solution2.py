# Szymon Mamoń
# algorytm najpierw sortuje za pomoca quicksorta tablice przedzialow malejąco wzgledem rozmiaru przedzialu
# nastepnie tworzy pustą listę po ktorej bedzie przechodzic n przedzialami w kolejnosci od najwiekszego
# do najmniejszego, jesli przedzial ktorym przechodzimy po nowej liscie zawiera sie w ktoryms z przedzialow na tejże
# liście zwieksza sie o 1 'licznik' przypisany w nowej liscie do tego przedzialu, jesli natomiast nie zawieral sie w zadnym
# przedziale w nowej liscie dodaje go do nowej listy, powtarza te czynnosci dla wszystkich n przedzialow z listy L
# na koncu funkcja depth zwraca maksymalny z 'licznikow'
# zlozonosc to nlogn + n^2 (pesymistycznie, a w praktyce duzo mniej)
from zad2testy import runtests
def quick_sort(A,l,r):
    stack0 = [[l, r]]
    while len(stack0) > 0:
        tuple0 = stack0.pop(-1)
        l = tuple0[0]
        r = tuple0[1]
        if l < r:
            #start
            x = A[r][1] - A[r][0]
            i = l - 1
            for j in range(l, r):
                if A[j][1] - A[j][0] >= x:
                    i += 1
                    A[i], A[j] = A[j], A[i]
            A[i + 1], A[r] = A[r], A[i + 1]
            q = i+1
            #koniec
            if q - l > r - q:
                stack0.append([l, q - 1])
                stack0.append([q + 1, r])
            else:
                stack0.append([q + 1, r])
                stack0.append([l, q - 1])
def depth(L):
    newList = []
    quick_sort(L,0,len(L)-1)
    counters = []
    for i in range(len(L)):
        add = True
        for j in range(len(newList)):
            if L[i][0] >= newList[j][0] and L[i][1] <= newList[j][1]:
                counters[j] += 1
                add = False
        if add:
            newList.append(L[i])
            counters.append(0)

    return max(counters)
    pass
runtests(depth)

