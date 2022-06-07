#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define MEMORY_ALLOCATION_ERROR  -1
#define LIST_ERROR               -2
#define PROGRAM_ERROR            -3

struct tagList;
typedef void (*ConstDataFp)(const void*);
typedef void (*DataFp)(void*);
typedef  int (*CompareDataFp)(const void*, const void*);
typedef void (*InsertInOrder)(struct tagList*, void*);

typedef struct tagListElement {
    struct tagListElement *next;
    void                  *data;
} ListElement;

typedef struct tagList {
    ListElement *head;
    ListElement *tail;
    ConstDataFp dump_data;
    DataFp      free_data;
    CompareDataFp compare_data;
    InsertInOrder insert_sorted;
} List;

typedef struct DataInt {
    int id;
} DataInt;


typedef struct DataWord {
    char *word;
    int counter;
} DataWord;

// -----------------------------------------------------------------
// generic functions - they are common for all instances of the list
// (independent of the data type)
// -----------------------------------------------------------------

void init_list(List *p_list, ConstDataFp dump_data, DataFp free_data,
               CompareDataFp compare_data, InsertInOrder insert_sorted) {
    p_list->head = NULL;
    p_list->tail = NULL;
    p_list->dump_data = dump_data;
    p_list->free_data = free_data;
    p_list->compare_data = compare_data;
    p_list->insert_sorted = insert_sorted;

}

// Print all elements of the list
void dump_list(const List* p_list) {
    ListElement *p = p_list->head;

    while (p){
        //printf("%d ",(*(int*)p->data));
        p_list->dump_data(p->data);
        p = p->next;
    }
    printf("\n");


}

// Print elements of the list if comparable to data
void dump_list_if(List *p_list, void *data) {
    DataWord *sdata = (DataWord*) data;

    ListElement *p = p_list->head;
    while (p){
        if (((DataWord*)p->data)->counter == sdata->counter)
            p_list->dump_data(p->data);
            //printf("%d ",(*(int*)p->data));

        p = p->next;
    }
    printf("\n");

}

// Free all elements of the list
void free_list(List* p_list) {
    ListElement *p = p_list->head;
    ListElement *q = NULL;
    while (p){
        q = p;
        p = p->next;
        q->next = NULL;
        free(q);
    }
    p_list->head = NULL;
    p_list->tail = NULL;

}

// Push element at the beginning of the list
void push_front(List *p_list, void *data){
    ListElement *element = malloc(sizeof(ListElement));
    if(element == NULL) exit(MEMORY_ALLOCATION_ERROR);
    element->data = data;
    element->next = p_list->head;
    p_list->head = element;
    if (!p_list->tail) p_list->tail = element;
}

// Push element at the end of the list
void push_back(List *p_list, void *data) {
    ListElement *element = malloc(sizeof(ListElement));
    if(element == NULL) exit(MEMORY_ALLOCATION_ERROR);
    element->data = data;
    element->next = NULL;
    if(p_list->tail) p_list->tail->next = element;
    p_list->tail = element;
    if(!p_list->head) p_list->head = p_list->tail;
}

// Remove the first element
void pop_front(List *p_list) {
    if (p_list->head == NULL)   return;
    ListElement *p = p_list->head->next;
    p_list->head = p;
    if (!p) p_list->tail = NULL;
    //if (p && p->next == NULL) p_list->tail = p;

}

// Reverse the list
void reverse(List *p_list) {
    if (p_list->head == NULL)   return;

    ListElement *tmp_head;
    ListElement *r,*q,*p;

    r = NULL;
    q = NULL;
    p = p_list->head;

    tmp_head = p_list->head;
    p_list->head = p_list->tail;
    p_list->tail = tmp_head;



    while (p != NULL){
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
}

// insert element preserving the ordering (defined by insert_sorted function)
void insert_in_order(List *p_list, void *data) {
    ListElement *p = malloc(sizeof(ListElement));
    p->data = data;
    p_list->insert_sorted(p_list, data);
}

// find element in sorted list after which to insert given element
ListElement* find_insertion_point(const List *p_list, ListElement *p_element) {
    if (!p_list->head) return NULL;//|| (int*)p_element->data <= (int*)p_list->head->data)  return NULL;
    ListElement *p = p_list->head;
    ListElement *q = NULL;
    //dump_list(p_list);

    //printf("- ((DataInt*) p->data)->id);
    //printf("weszlo");

    while (p && p_list->compare_data(p_element,p->data) > 0){
        //printf("%d",p_list->compare_data(p_element,p->data));
        q = p;
        p = p->next;
    }
    //if (!p) return p_list->tail;
    return q;


}

// Insert element after 'previous'
void push_after(List *p_list, void *data, ListElement *previous) {

    ListElement  *element = malloc(sizeof(ListElement));
    element->data = data;
    element->next = NULL;

    if (!previous){
        if (!p_list->head) {
            p_list->head = element;
            p_list->tail = element;
        }
        else{
            element->next = p_list->head;
            p_list->head = element;
        }
        return;
    }
    ListElement *next = previous->next;
    previous->next = element;
    element->next = next;
    if (p_list->tail == previous)   p_list->tail = element;
}

// Insert element preserving order (no counter)
void insert_elem(List *p_list, void *p_data) {
    ListElement *p = p_list->head;
    while (p){
        if (p_list->compare_data(p_data,p->data) == 0)  return;
        p = p->next;
    }
    ListElement *prev = find_insertion_point(p_list,p_data);
    push_after(p_list,p_data,prev);
}

void insert_elemS(List *p_list, void *p_data) {

    ListElement *prev = find_insertion_point(p_list,p_data);
    push_after(p_list,p_data,prev);
}
// ---------------------------------------------------------------
// type-specific definitions
// ---------------------------------------------------------------

// int element

//typedef struct DataInt {
//    int id;
//} DataInt;

void dump_int(const void *d) {
    DataInt *di = (DataInt*) d;
    printf("%d ",di->id);

}

void free_int(void *d) {

}

int cmp_int(const void *a, const void *b) {
    DataInt *ia = (DataInt *)a;
    DataInt *ib = (DataInt *)b;

    //rprintf("xx %d %d xxx",ia->id,ib->id);
//    if (ia->id > ib->id)    return 1;
//    return 0;
    return  ia->id - ib->id;
}

DataInt *create_data_int(int v) {
    DataInt *d = malloc(sizeof(int));
    d->id = v;
    return d;
}

// Word element


void dump_word (const void *d) {
    DataWord *dd = (DataWord*)d;
    printf("%s\n",dd->word);
}

void dump_word_lowercase (const void *d) {
    DataWord *dd = (DataWord*)d;
    char *word = dd->word;
    for(int i = 0;word[i];i++){
        word[i] = (char)tolower(word[i]);
    }
    printf("%s\n",word);
}

void free_word(void *d) {

}

// compare words case insensitive
int cmp_word_alphabet(const void *a, const void *b) {
    DataWord *sa = (DataWord *)a;
    DataWord *sb = (DataWord *)b;
    //printf(" %d ", strcmp("abc","xy"));
    return strcmp(sa->word, sb->word);
//    if (sa->word > sb->word) return 1;
//    else return -1;
}

int cmp_word_counter(const void *a, const void *b) {
    DataWord *sa = (DataWord *)a;
    DataWord *sb = (DataWord *)b;
    return sa->counter - sb->counter;
}

// insert element; if present increase counter
void insert_elem_counter(List *p_list, void *data) {
    DataWord *sdata = (DataWord *)data;
    for(int i=0 ;sdata->word[i];i++) sdata->word[i] = (char)tolower(sdata->word[i]);
    ListElement *p = p_list->head;
    if (!p){
        ListElement *newd = malloc(sizeof(ListElement));
        sdata->counter = 1;
        newd->data = sdata;
        newd->next = NULL;
        p_list->head = newd;
        p_list->tail = newd;
        //dump_list(p_list);
        return;
    }
    ListElement *q = NULL;
    while (p){
        //printf(" t %s %s t ",(char*)(((DataWord*)p->data)->word),(char*)(sdata->word));
        if (strcmp(((DataWord*)p->data)->word, sdata->word ) == 0){
            ++((DataWord*)p->data)->counter;
            //printf("%d-%s ",((DataWord*)p->data)->counter,sdata->word);
            return;
        }
        q = p;
        p = p->next;

    }
    insert_elemS(p_list,sdata);




}

// read text, parse it to words, and insert those words to the list
// in order given by the last parameter (0 - read order,
// 1 - alphabetical order)
void stream_to_list(List *p_list, FILE *stream, int order) {

    int max_size = BUFFER_SIZE;
    char *line;
    char *word;
    char single;
    single = getchar();
    while ((int)single != 10) single = getchar();
    line = (char*)malloc(BUFFER_SIZE*sizeof(char));
    word = (char*)malloc(BUFFER_SIZE*sizeof(char));
    while (fgets(line,max_size,stream)) {
        //printf("%s",line);
        if (strcmp(line,"\n") == 0)   break;
        word = strtok(line," \n-,.;?!:\r\t");
        //strcpy(word,line);
        while (word != NULL) {
            //printf("%s  x ",word);
            DataWord *data = malloc(sizeof(DataWord));
            data->word = word;
            data->counter = 1;
            //printf("%s <-",data->word);
            //ListElement *p = malloc(sizeof(ListElement));
            //p->data

            if (order){
                //for( ;*data->word;data->word++) tolower(*data->word);
                insert_in_order(p_list,data);
                //dump_list(p_list);
            } else{
                push_back(p_list,data);
            }

            word = strtok(NULL, ".  \n-,.;?!:\r\t");
        }
        line = (char*)malloc(BUFFER_SIZE*sizeof(char));
    }
    //dump_list(p_list);
}

// test integer list
void list_test(List *p_list, int n) {
    char op[2];
    int v;
    for (int i = 0; i < n; ++i) {
        scanf("%s", op);
        switch (op[0]) {
            case 'f':
                scanf("%d", &v);
                push_front(p_list, create_data_int(v));
                break;
            case 'b':
                scanf("%d", &v);
                push_back(p_list, create_data_int(v));
                break;
            case 'd':
                pop_front(p_list);
                break;
            case 'r':
                reverse(p_list);
                break;
            case 'i':
                scanf("%d", &v);
                insert_in_order(p_list, create_data_int(v));
                break;
            default:
                printf("No such operation: %s\n", op);
                break;
        }
    }
}

int main(void) {
    int to_do, n;
    List list;

    scanf ("%d", &to_do);
    switch (to_do) {
        case 1: // test integer list
            scanf("%d",&n);
            init_list(&list, dump_int, free_int,
                      cmp_int, insert_elem);
            list_test(&list, n);
            dump_list(&list);
            free_list(&list);
            break;
        case 2: // read words from text, insert into list, and print
            init_list(&list, dump_word, free_word,
                      cmp_word_alphabet, insert_elem_counter);
            stream_to_list(&list, stdin, 0);
            dump_list(&list);
            free_list(&list);
            break;
        case 3: // read words, insert into list alphabetically, print words encountered n times
            scanf("%d",&n);
            init_list(&list, dump_word_lowercase, free_word,
                      cmp_word_alphabet, insert_elem_counter);
            stream_to_list(&list, stdin, 1);

            list.compare_data = cmp_word_counter;
            DataWord data = { NULL, n };
			list.dump_data = dump_word_lowercase;

            dump_list_if(&list, &data);

            printf("\n");
            free_list(&list);

            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}
