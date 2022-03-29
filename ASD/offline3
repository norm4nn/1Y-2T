#basic bucket sort
#zwykły bucket sort z select sortem
from zad3testy import runtests


def selectSort(L):
    for i in range(len(L)-1):
        minID = i
        for j in range(i+1,len(L)):
            if L[j] <= L[minID]:
                minID = j
        L[i],L[minID] = L[minID],L[i]


def SortTab(T,P):
    # tu prosze wpisac wlasna implementacje
    n = len(T)
    minimum = min(T)
    maximum = max(T)
    howManyBuckets = n


    howManyBuckets //= 8
    if howManyBuckets == 0: howManyBuckets = 1

    Buckets = [[] for _ in range(howManyBuckets)]


    limit = (maximum-minimum)/howManyBuckets

    for val in T:
        where = int((val-minimum)/limit)
        if where >= howManyBuckets:  where = howManyBuckets -1
        Buckets[where].append(val)

    for list in Buckets:
        if len(list) > 0:
            #selectSort(list)
            for i in range(len(list) - 1):
                minID = i
                for j in range(i + 1, len(list)):
                    if list[j] <= list[minID]:
                        minID = j
                list[i], list[minID] = list[minID], list[i]

    j = 0
    for list in Buckets:
        for val in list:
            T[j] = val
            j += 1
    return T

runtests( SortTab )
