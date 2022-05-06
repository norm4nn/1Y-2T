#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 1000
#define MAX_RANGE 1000

typedef struct {
    int first;
    int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair *pairs, int n, pair newPair){
    for(int i=0;i<n;++i)
        if (pairs[i].first == newPair.first && pairs[i].second == newPair.second)    return 0;

    pairs[n] = newPair;
    return 1;
}

// Case 1:
// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair *pairs, int n){
    for(int i=0;i<n;++i)
        if (pairs[i].first == pairs[i].second)  return 1;
    return 0;
}
// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair *pairs, int n ){
    for(int i=0;i<n;++i)
        if (pairs[i].first == pairs[i].second)  return 0;
    return 1;
}
// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair* pairs, int n){
    for(int i=0;i<n;++i){
        int flag = 0;
        for(int j=0;j<n;++j)
            if (pairs[i].first == pairs[j].second && pairs[i].second == pairs[j].first){
                flag = 1;
                break;
            }
        if (flag == 0)  return 0;

    }
    return 1;
}
// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair* pairs, int n ){
    for(int i=0;i<n;++i){
        int flag = 0;
        for(int j=0;j<n;++j)
            if (pairs[i].first == pairs[j].second && pairs[i].second == pairs[j].first){
                if (pairs[i].first != pairs[i].second){
                    flag = 1;
                    break;
                }
            }
        if (flag == 1)  return 0;

    }
    return 1;
}
// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair* pairs, int n){
    for(int i=0;i<n;++i){
        int flag = 0;
        for(int j=0;j<n;++j)
            if (pairs[i].first == pairs[j].second && pairs[i].second == pairs[j].first){
                    flag = 1;
                    break;
                }

        if (flag == 1)  return 0;

    }
    return 1;
}
// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair* pairs, int n){
    int flag;
    for(int i=0;i<n;++i){
       int x = pairs[i].first;
       int y = pairs[i].second;
       for(int j=0;j<n;++j){
            if (pairs[j].first == y){
                flag = 0;
                int z = pairs[j].second;
                for(int k=0;k<n;k++){
                    if (pairs[k].first == x && pairs[k].second == z){
                        flag = 1;
                        break;
                    }

                }//third loop
                if (flag == 0)  return 0;
            }//if statement
       }//second loop

    }//first loop
    return 1;
}

// Case 2:
// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair* pairs, int n){
    return (is_reflexive(pairs,n) && is_transitive(pairs,n) && is_antisymmetric(pairs,n));
}
// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair* pairs, int n){
    int unique[MAX_REL_SIZE];
    int sizeU = 0;
    int x,add;
    for(int i=0;i<2*n;++i){
        if (i%2 == 0)   x = pairs[i/2].first;
        else x = pairs[i/2].second;
        add = 1;
        for(int j=0;j<sizeU;j++){
            if(unique[j]==x){
                add = 0;
                break;
            }
        }
        if (add){
            unique[sizeU] = x;
            ++sizeU;
        }
    }
    int howMany = 0;
    howMany = (sizeU+1)*(sizeU)/2 + sizeU+1;

    if (n != howMany) return 0;
    return 1;
//    for(int i=0;i<n;++i){
//        int x1 = pairs[i].first;
//        int add = 1;
//        for(int j=0;j<sizeU;++j){
//            if (unique[j] == x1) {
//                add = 0;
//                break;
//            }
//        }//scnd loop
//        if (add == 1){
//            unique[sizeU] = x1;
//            ++sizeU;}
//            x1 = pairs[i].second;
//            add = 1;
//            for(int j=0;j<sizeU;++j){
//                if (unique[j] == x1) {
//                    add = 0;
//                    break;
//                }
//            }//scnd loop
//            if (add == 1){
//                unique[sizeU] = x1;
//                ++sizeU;
//
//            }
//        }//fst loop
//
//        int *zeroes = new int[sizeU];
//        for(int i=0;i<n;++i){
//            zeroes[i] = 0;
//        }
//        for(int i=0;i<2*n;++i){
//            int x;
//            if (i%2 == 0)
//                 x = pairs[i/2].first;
//            else     x = pairs[i/2].second;
//
//            for(int g=0;g<n;++g){
//                zeroes[g] = 0;
//            }
//            for(int j=0;j<n;++j)
//                if (pairs[j].first == x)
//                for(int k=0;k<sizeU;++k){
//                    if (pairs[j].second == unique[k]){
//                        zeroes[k] = 1;
//                        break;
//                    }
//
//                }//unique loop
//            for(int j=0;j<n;++j)
//                if (pairs[j].second == x)
//                    for(int k=0;k<sizeU;++k) {
//                        if (pairs[j].first == unique[k]) {
//                            zeroes[k] = 1;
//                            break;
//                        }
//                    }
//            for(int h=0;h<sizeU;++h){
//                if (unique[h] == 0) return 0;
//            }
//
//            }//second
//    return 1;

}
// A total order relation is a partial order relation that is connected
int is_total_order(pair* pairs, int n){
    if (!is_partial_order(pairs,n)) return 0;
    if(is_connected(pairs,n)) return 1;
    return 0;
}
int cmpf(const void * a, const void * b) {
    return (*(int *) a - *(int *) b);
}
int find_max_elements(pair* pairs, int n, int* maxElements){
    int result = 0;
    int snd;
    int add;
//printf("%d -",n);
    for(int i=0;i<n;++i){
        add = 0;
        int found = 0;
        snd = pairs[i].second;
        for(int j=0;j<result;++j)
            if(snd == maxElements[j]){
                found = 1;
                break;
            }//if statement
        if (!found){
            add = 1;
        for(int k=0;k<n;++k){
            if(pairs[k].first == snd && pairs[k].second != snd){
                add = 0;
                break;
            }//if statement

        }    //K loop
        }//if !found
        if (add){
            maxElements[result] = snd;
            result += 1;
        }
    }
    qsort(maxElements,result, sizeof(int),cmpf);
    return result;
}


int find_min_elements(pair* pairs, int n, int* minElements){
    int result = 0;
    int snd;
    int add;
    for(int i=0;i<n;++i){
        add = 0;
        int found = 0;
        snd = pairs[i].first;
        for(int j=0;j<result;++j)
            if(snd == minElements[j]){
                found = 1;
                break;
            }//if statement
        if (!found){
            add = 1;
            for(int k=0;k<n;++k){
                if(pairs[k].second == snd && pairs[k].first != snd){
                    add = 0;
                    break;
                }//if statement

            }    //K loop
        }//if !found
        if (add){
            minElements[result] = snd;
            result += 1;
        }


    }
    //qsort(*minElements,result, sizeof(int),cmpf);
    qsort(minElements,result,sizeof(int),cmpf);
    return result;
}
int get_domain(pair* pairs, int n, int* domain){
    int res = 0;
    int fst;
    int add = 1;
    for(int i=0;i<n;++i){
        add = 1;
        fst = pairs[i].first;
        for(int j=0;j<res;++j){
            if (fst == domain[j]){
                add = 0;
                break;
            }//if statement

        }//domain loop
        if (add){
            domain[res] = fst;
            ++res;
        }
        add = 1;
        fst = pairs[i].second;
        for(int j=0;j<res;++j){
            if (fst == domain[j]){
                add = 0;
                break;
            }//if statement

        }//domain loop
        if (add){
            domain[res] = fst;
            ++res;
        }
    }// i loop
    qsort(domain,res,sizeof(int),cmpf);
    return res;
}

// Case 3:
int composition (pair* R, int nr, pair* S, int ns, pair* RnS){
    int result = 0;
    int add,fst,scnd,third;
    pair newPair;
    for(int i=0;i<nr;++i){
        fst = R[i].first;
        scnd = R[i].second;
        for(int j=0;j<ns;++j){
            if(S[j].first == scnd){
                third = S[j].second;
                newPair.first = fst;
                newPair.second = third;
                add = 1;
                for(int k=0;k<result;++k){
                    if (newPair.first == RnS[k].first && newPair.second == RnS[k].second){
                        add = 0;
                        break;
                    }
                }//k loop
                if (add){
                    RnS[result] = newPair;
                    ++result;
                }
            }//if statement
        }//j loop
    }//i loop
    return result;
}

int cmp (pair p1, pair p2) {
    if (p1.first == p2.first) return p1.second - p2.second;
    return p1.first - p2.first;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *pairs){
    int n;
    scanf("%d",&n);
    int fst,snd;
    for(int i =0;i<n;++i){
        scanf("%d %d",&fst,&snd);
        pairs[i].first = fst;
        pairs[i].second = snd;
    }
    return n;
}

void print_int_array(int *array, int n) {
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void) {
    int to_do;
    pair relation[MAX_REL_SIZE];
    pair relation_2[MAX_REL_SIZE];
    pair comp_relation[MAX_REL_SIZE];
    int domain[MAX_REL_SIZE];

    scanf("%d",&to_do);
    int size = read_relation(relation);
    int ordered, size_2, n_domain;

    switch (to_do) {
        case 3:
            size_2 = read_relation(relation_2);
            printf("%d\n", composition(relation, size,
                                       relation_2, size_2, comp_relation));
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
        case 1:
            printf("%d ", is_reflexive(relation, size));
            printf("%d ", is_irreflexive(relation, size));
            printf("%d ", is_symmetric(relation, size));
            printf("%d ", is_antisymmetric(relation, size));
            printf("%d ", is_asymmetric(relation, size));
            printf("%d\n", is_transitive(relation, size));
            break;
        case 2:
            ordered = is_partial_order(relation, size);
            n_domain = get_domain(relation, size, domain);
            printf("%d %d\n", ordered, is_total_order(relation, size));
            print_int_array(domain, n_domain);
            if (!ordered) break;
            int max_elements[MAX_REL_SIZE];
            int min_elements[MAX_REL_SIZE];
            int no_max_elements = find_max_elements(relation, size, max_elements);
            int no_min_elements = find_min_elements(relation, size, min_elements);
            print_int_array(max_elements, no_max_elements);
            print_int_array(min_elements, no_min_elements);
            break;


    }
    return 0;
}

