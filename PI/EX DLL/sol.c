#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define MEMORY_ALLOCATION_ERROR  -1

// list node
typedef struct Node {
    int *data;
    int array_size;
    struct Node* next;
    struct Node* prev;
} Node;

// doubly linked list
typedef struct List {
    Node *head;
    Node *tail;
    int size;
} List;

// iterator
typedef struct iterator {
    int position;
    struct Node* node_ptr;
} iterator;

// forward initialization
iterator begin(Node* head) {
    iterator it = {0, head};
    return it;
}

// backward initialization
iterator end(Node* tail) {
    iterator it = {tail->array_size - 1, tail};
    return it;
}

// initialize list
void init(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// ---------------------------------------------- to implement ...

// append element to the list
void push_back(List *list, int *data, int array_size) {
    int *ndata = data;
    int a = 8;
    int b = a++;

    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->array_size = array_size;
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        return;
    }
    Node *p = list->tail;
    p->next = new_node;
    new_node->prev = p;
    list->tail = new_node;

}

// set iterator to move n elements forward from its current position
void skip_forward(iterator* itr, int n) {

    Node *node_ptr = itr->node_ptr;
    int curr_pos = itr->position;
    if (node_ptr == NULL) return;
    int len = node_ptr->array_size;
    if (curr_pos + n <= len - 1)    {
//        for (int i=curr_pos;i<=curr_pos+n;++i){
//            printf("%d ",node_ptr->data[i]);
//        }
        itr->position += n;
        return;
    }
    itr->node_ptr =node_ptr->next;
    n = curr_pos + n - len;
    skip_forward(itr,n);

}

// forward iteration - get n-th element in the list
int get_forward(List *list, int n) {
    --n;
    iterator iterator1;
    iterator1 = begin(list->head);

    skip_forward(&iterator1,n);
    Node *p = iterator1.node_ptr;
    return p->data[iterator1.position];
}

// set iterator to move n elements backward from its current position
void skip_backward(iterator* itr, int n) {
    Node *p = itr->node_ptr;
    if (p == NULL) return;
    int curr_pos = itr->position;

    if (curr_pos+1 - n >= 0) {
        itr->position =curr_pos - n + 1;
        return;
    }
    int prev_len = 0;
    if (p->prev != NULL) {
        prev_len = p->prev->array_size;
    }
    n -= (curr_pos+1);
    curr_pos = prev_len - 1;
    //n -= (curr_pos+1);
    itr->position = curr_pos;
    itr->node_ptr = p->prev;
    skip_backward(itr,n);
}

// backward iteration - get n-th element from the end of the list
int get_backward(List *list, int n) {
    //n;
    iterator iterator1;
    iterator1 = end(list->tail);

    skip_backward(&iterator1,n);
    Node *p = iterator1.node_ptr;
    return p->data[iterator1.position];


}

// remove n-th element; if array empty remove node
void remove_at(List *list, int n) {
    --n;
    Node *p;
    iterator iterator1;
    iterator1 = begin(list->head);

    skip_forward(&iterator1,n);

    p = iterator1.node_ptr;
    int position = iterator1.position;
    if (!p) return;
    if (p->array_size == 1){
        --list->size;
        Node *prev = p->prev;
        Node *next = p->next;
        if (prev)
            prev->next = next;
        if(next)
            next->prev = prev;

        return;
    }
    if (position == p->array_size-1){
        --p->array_size;
        return;
    }
    int *start_array = &p->data[position];
    int *next_element = &p->data[position+1];
    int how_many_copy = p->array_size-1 - position;
    memmove(start_array,next_element,how_many_copy*sizeof(int));
    --p->array_size;

}

// -------------------- helper functions

// print list
void dumpList(const List *list) {
    for(Node *node = list->head; node != NULL; node = node->next) {
        printf("-> ");
        for (int k = 0; k < node->array_size; k++) {
            printf("%d ", node->data[k]);
        }
        printf("\n");
    }
}

// remove the first element
void delete_front(List *list) {
    Node *to_delete;
    if(list->head == NULL) return;
    to_delete = list->head;
    list->head = list->head->next;
    if(list->head == NULL) list->tail = NULL;
    free(to_delete->data);
    free(to_delete);
    list->size--;
    //dumpList(list);
}

// free list
void freeList(List *list) {
    while(list->head) {
        delete_front(list);
    }
}

// read int vector
void read_vector(int tab[], int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%d", tab + i);
    }
}

// initialize the list and push data
void read_list(List *list) {
    int size, n;
    init(list);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &size);
        int *tab = (int*) malloc((size_t)size * sizeof(int));
        read_vector(tab, size);
        push_back(list, tab, size);
    }
}

int main() {
    int to_do, size, m;
    List list;

    scanf("%d", &to_do);
    read_list(&list);
    switch (to_do) {
        case 1:
            dumpList(&list);
            break;
        case 2:
            scanf("%d", &size);
            for (int i = 0; i < size; i++) {
                scanf("%d", &m);
                printf("%d ", get_forward(&list, m));
            }
            printf("\n");
            break;
        case 3:
            scanf("%d", &size);
            for (int i = 0; i < size; i++) {
                scanf("%d", &m);
                int g =  get_backward(&list, m);
                printf("%d ", g);
            }
            printf("\n");
            break;
        case 4:
            scanf("%d", &size);
            for (int i=0; i < size; i++) {
                scanf("%d", &m);
                remove_at(&list, m);
            }
            dumpList(&list);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    freeList(&list);

    return 0;
}
