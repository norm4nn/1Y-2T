from zad1ktesty import runtests

def  recursive(A,l,r):
    if l == r:
        return (A[l],0)
    if l+1 == r:
        return (max(A[l],A[r]),min(A[l],A[r]))

    if A[l] + recursive(A,l+1,r)[1] > A[r] + recursive(A,l,r-1)[1]:
        return (A[l] + recursive(A,l+1,r)[1],recursive(A,l+1,r)[0])
    else:
        return (A[r] + recursive(A,l,r-1)[1],recursive(A,l,r-1)[0])#(A[r],recursive(A,l,r-1,my_sum+A[r])[0],my_sum + A[r])


def garek ( A ):
    #print(A)
    #Tutaj proszę wpisać własną implementację

    return recursive(A,0,len(A)-1)[0]

runtests ( garek )
