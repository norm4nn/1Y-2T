import  random
T_range = 10
T = [random.randint(0,1000000000) for _ in range(T_range)]

def count(val):
    res = [0,0]
    T = [0 for _ in range(10)]
    while val > 0:
        T[val%10] += 1
        val //= 10

    for howMany in T:
        if howMany == 1:
            res[0] += 1
        elif howMany > 1:
            res[1] += 1
    return res
def pretty_Sort(T):
    buckets = [[[] for __ in range(11)] for _ in range(11)]
    for val in T:
        tupl = count(val)
        buckets[tupl[0]][tupl[1]].append(val)

    j = 120
    for i in range(len(T)):
        first = j//11
        second = 10 - j%11
        while buckets[first][second] == []:
            j -= 1
            first = j // 11
            second = 10 - j % 11
        T[i] = buckets[first][second].pop(-1)
        #print(first, " ",second)



print(T)
pretty_Sort(T)
print(T)





