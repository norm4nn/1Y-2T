#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STR_LEN 64

typedef struct Vector {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Vector;

typedef struct Person {
    int age;
    char first_name[MAX_STR_LEN];
    char last_name[MAX_STR_LEN];
} Person;

// Allocate vector to initial capacity (block_size elements),
// Set element_size, size (to 0), capacity
void print_vector_int(Vector *vector);
void print_vector_char(Vector *vector);
void print_vector_person(Vector *vector);
void init_vector(Vector *vector, size_t block_size, size_t element_size){

    vector->data = malloc(block_size*element_size);
    vector->element_size = element_size;
    vector->size = 0;
    vector->capacity = block_size;

}

// If new_capacity is greater than the current capacity,
// new storage is allocated, otherwise the function does nothing.
void reserve(Vector *vector, size_t new_capacity){
    if (vector->capacity >= new_capacity)
       return;
    else {
        void *ptr = vector->data;
        memcpy(ptr,vector->data,vector->size*vector->element_size);
        //print_vector_int(vector->data);

        vector->data = calloc(new_capacity,vector->element_size);

        vector->capacity = new_capacity;


        memcpy(vector->data,ptr,vector->size*vector->element_size);

    }


}

// Resizes the vector to contain new_size elements.
// If the current size is greater than new_size, the container is
// reduced to its first new_size elements.

// If the current size is less than new_size,
// additional zero-initialized elements are appended
void resize(Vector *vector, size_t new_size){
    if (vector->size >= new_size)
        vector->size = new_size;
    else {
        while (vector->capacity < new_size){
            reserve(vector,vector->capacity*2);
        }
        void *ptr = vector->data;
        size_t i = vector->size;
        memcpy(ptr,vector->data,vector->size*vector->element_size);
        //printf("%d ",((int*)ptr)[0]);
        vector->data = calloc(new_size,vector->element_size);
        memcpy(vector->data,ptr,i*vector->element_size);
        vector->size = new_size;
    }

}

// Add element to the end of the vector
void push_back(Vector *vector, void *value){
    size_t  i = vector->size;
    if (vector->size + 1 > vector->capacity)
            reserve(vector,(vector->capacity)*2);
    if (vector->element_size == sizeof(int))
        ++vector->size;
    else
        resize(vector,vector->size + 1);

    memcpy(&(vector->data)[i*vector->element_size],value,vector->element_size);



}


// Remove all elements from the vector
void clear(Vector *vector){
    vector->size = 0;
}

// Remove the last element from the vector
void pop_back(Vector *vector){
    if (vector->size > 0)
        vector->size -= 1;
}

// Insert new element at index (0 <= index <= size) position

void insert(Vector *vector, int index, void *value){

    if (vector->size + 1 > vector->capacity) reserve(vector,vector->capacity*2);
    ++vector->size;
    void* ptr2 = &vector->data[index*vector->element_size];
    void* ptrwhere = &vector->data[(index+1)*vector->element_size];
    memmove(ptrwhere,ptr2,(vector->size - index)*vector->element_size);

    memcpy(ptr2,value,vector->element_size);
}

// Erase element at position index
void erase(Vector *vector, int index){
    if (index >= vector->size || index < 0)  return;

    void *from = &vector->data[(index+1)*vector->element_size];
    void *where = &vector->data[(index)*vector->element_size];

    memmove(where,from,vector->element_size*(vector->size-index));
    --vector->size;

    //print_vector_int(vector);
}

// Erase all elements that compare equal to value from the container
void erase_value(Vector *vector, void *value, int(*cmp)(const void*, const void*)){
    int i = 0;

    while (i<vector->size){
        if (cmp(value,&vector->data[i*vector->element_size]) == 0) {
            erase(vector,i);
        } else  ++i;
    }

}

// Erase all elements that satisfy the predicate from the vector
void erase_if(Vector *vector, int (*predicate)(void *)){
    int i = 0;

    while (i<vector->size){
        if (predicate(&vector->data[i*vector->element_size])) {
            erase(vector,i);
        } else  ++i;
    }
}

// Request the removal of unused capacity
void shrink_to_fit(Vector *vector){
    //free(&vector->data[vector->size-1]);

    vector->capacity = vector->size;
}

// Print integer vector
void print_vector_int(Vector *vector){
    int i = 0;
    printf("%zu\n",vector->capacity);
    while (i < vector->size){
        printf("%d ",((int*)vector->data)[i]);
        ++i;
    }
    printf("\n");
}

// Print char vector
void print_vector_char(Vector *vector){
    int i = 0;
    printf("%zu\n",vector->capacity);
    while (i < vector->size){
        printf("%c ",((char*)vector->data)[i]);
        ++i;
    }
    printf("\n");
}

// Print vector of Person
void print_vector_person(Vector *vector){
    int i = 0;
    printf("%zu\n",vector->capacity);
    while (i < vector->size){
        printf("%d %s %s\n",
               ((Person *)vector->data)[i].age,
               ((Person *)vector->data)[i].first_name,
               ((Person *)vector->data)[i].last_name);
        ++i;
    }
    printf("\n");
}

// integer comparator - increasing order
int int_cmp(const void *v1, const void *v2){
    int i1 = *(int*)v1;
    int i2 = *(int*)v2;
    return i1 - i2;
}

// char comparator - lexicographical order (case sensitive)
int char_cmp(const void *v1, const void *v2){
    char c1 = *(char*) v1;
    char c2 = *(char*) v2;
    return c1 - c2;
}

// Person comparator:
// Sort according to age (decreasing)
// When ages equal compare first name and then last name
int person_cmp(const void *p1, const void *p2){
    Person p11= *(Person*) p1;
    Person p22 = *(Person*) p2;

    if (p11.age == p22.age){
        if (strcmp(p11.first_name,p22.first_name) ==0)
            return strcmp(p11.last_name,p22.last_name);
        return strcmp(p11.first_name,p22.first_name);
    }
    return p22.age - p11.age;

}

// predicate: check if number is even
int is_even(void *value){
    if ((*(int*)value)%2 == 0)   return 1;
    return 0;
}

// predicate: check if char is a vowel
int is_vowel(void *value){
    char c = *(char*) value;
    int lowercase_vowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
    int uppercase_vowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y');
    return lowercase_vowel || uppercase_vowel;
}

// predicate: check if person is older than 25
int is_older_than_25(void *person){
    Person p1 = *(Person*) person;
    int older = p1.age > 25;
    return older;
}

// -------------------------------------------------------------

void read_int(void* value) {
    scanf("%d", (int*)value);
}

void read_char(void* value) {
    char c[2];
    scanf("%s", c);
    *(char*)value = c[0];
}

void read_person(void* value) {
    Person *person = (Person*)value;
    scanf("%d %s %s", &person->age, person->first_name, person->last_name);
    //printf("%d %s %s\n",person->age,person->first_name,person->last_name);
}

void vector_test(Vector *vector, int n, void(*read)(void*),
                 int (*cmp)(const void*, const void*), int(*predicate)(void*)) {
    char op[2];
    int index;
    size_t size;
    void *v = malloc(vector->element_size);
    for (int i = 0; i < n; ++i) {
        scanf("%s", op);
        switch (op[0]) {
            case 'p': // push_back
                read(v);
                push_back(vector, v);
                break;
            case 'i': // insert
                scanf("%d", &index);
                read(v);
                insert(vector, index, v);
                break;
            case 'e': // erase
                scanf("%d", &index);
                read(v);
                erase(vector, index);
                erase_value(vector, v, cmp);
                break;
            case 'd': // erase (predicate)
                erase_if(vector, predicate);
                break;
            case 'r': // resize
                scanf("%zu", &size);
                resize(vector, size);
                break;
            case 'c': // clear
                clear(vector);
                break;
            case 'f': // shrink
                shrink_to_fit(vector);
                break;
            case 's': // sort
                qsort(vector->data, vector->size,
                      vector->element_size, cmp);
                break;
            default:
                printf("No such operation: %s\n", op);
                break;
        }
    }
    free(v);
}

int main(void) {
    int to_do, n;
    Vector vector_int, vector_char, vector_person;

    scanf("%d%d", &to_do, &n);

    switch (to_do) {
        case 1:
            init_vector(&vector_int, 4, sizeof(int));
            vector_test(&vector_int, n, read_int, int_cmp, is_even);
            print_vector_int(&vector_int);
            free(vector_int.data);
            break;
        case 2:
            init_vector(&vector_char, 2, sizeof(char));
            vector_test(&vector_char, n, read_char, char_cmp, is_vowel);
            print_vector_char(&vector_char);
            free(vector_char.data);
            break;
        case 3:
            init_vector(&vector_person, 2, sizeof(Person));
            vector_test(&vector_person, n, read_person, person_cmp, is_older_than_25);
            print_vector_person(&vector_person);
            free(vector_person.data);
            break;
        default:
            printf("Nothing to do for %d\n", to_do);
            break;
    }

    return 0;
}

