#Szymon Mamoń
#algorytm dzieli tablice na 3 czesci, kolejno: 'przeszukana', 'do przeszukania', 'nie przeszuakana'
#                                               [0;start],     [start+1;maxfuel],  [maxfuel,n-1]
# przechodzi po kolei w czesci 'do przeszukani' i wpisuje paliwo jakie mozna zdobyc z kazdego pola i adres tego pola
# do kolejki prioretytowej, gdzie kluczem jest -(*paliwo_na_i-tym_polu*)
# nastepnie wartosci START przypisuje wartosc MAXFUEL, pozniej wyciaga z listy pierwszy element i dodaje paliwo z niego do wartosci MAXFUEL
# a adres wyciagnietego elementu dodaje do tablicy result
# na koniec sortuje tablice result i ja zwraca
# zlozonosc: O(nlogn)
from queue import PriorityQueue
from zad5testy import runtests


def plan(T):
    PQ = PriorityQueue()
    start = 0
    result = []
    n  = len(T)
    result.append(0)
    maxFuel = 0
    temp_fuel = T[0]
    while maxFuel + temp_fuel < n-1:
        maxFuel += temp_fuel
        for i in range(start+1,maxFuel+1):#position+fuel+1):
            temp_fuel -= 1
            PQ.put((-T[i],i))
        start = maxFuel
        temp_tuple = PQ.get()
        result.append(temp_tuple[1])
        temp_fuel = T[result[-1]]


    result.sort()
    #
    return result

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( plan, all_tests = True )
