#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 64
#define MAX_PERSONS 1024

typedef struct Person {
    int age;
    char first_name[MAX_STR_LEN];
    char last_name[MAX_STR_LEN];
} Person;

// Sort according to age (decreasing)
// When ages equal compare first name and then last name
int cmp_person(const void *p1, const void *p2){
    Person per1 = *(Person*) p1;
    Person per2 = *(Person*) p2;
    if (per1.age == per2.age){
        if (per1.first_name == per2.first_name){
            return strcmp(per1.last_name,per2.last_name);
        }
        return strcmp(per1.first_name,per2.first_name);
    }
    return -(per1.age-per2.age);
}

// Read data to Person array (till EOF)
int read_person_array(Person *persons){
//    int n = 0, age;
//    char fn[MAX_STR_LEN], ln[MAX_STR_LEN];
    int n = 0;
    while (scanf("%d %s %s",&persons[n].age,persons[n].first_name,persons[n].last_name) != EOF){//0
        ++n;
    }
    return n;
}

// Print Person array
void print_person_array(Person *persons, int n){
    for(int i=0;i<n;++i){
        printf("%d %s %s\n",persons[i].age,persons[i].first_name,persons[i].last_name);
    }
}

// Sort women first (woman's first name ends with 'a');
// Then sort women by age and men by last name
// Line consists of: age, first_name, last_name
// (int that order)
int cmp_lines(const void *l1, const void *l2){

    int age1,age2;



    char *ageS1, *fn1, *ln1;
    char *ageS2, *fn2, *ln2;

    char *line11 = (char*) l1;
    char *line12 = (char*) l2;

    char line1[strlen(line11)+1];
    char line2[strlen(line12)+1];

    strcpy(line1,line11);
    strcpy(line2,line12);


    ageS1 = strtok(line1," ");
    fn1 = strtok(NULL," ");
    ln1 = strtok(NULL," ");

    ageS2 = strtok(line2," ");
    fn2 = strtok(NULL," ");
    ln2 = strtok(NULL," ");

    int len_fn1 = strlen(fn1);
    int len_fn2 = strlen(fn2);

    age1 = atoi(ageS1);
    age2 = atoi(ageS2);

    if (fn1[len_fn1-1] == 'a'){
        if (fn2[len_fn2-1] == 'a')    return age1 - age2;
        else    return -1;
    }
    if (fn2[len_fn2-1] == 'a')  return 1;

    return strcmp(ln1,ln2);



}

// Read lines with students' data (as text)
int read_lines(char lines[][MAX_STR_LEN]){
    int n = 0;

    while (fgets(lines[n],MAX_STR_LEN, stdin) != NULL && strlen(lines[n]) > 1)
        ++n;

    return n;
}

// Print sorted lines
void print_lines(char lines[][MAX_STR_LEN], int n){
    for(int i=0;i<n;++i){
        printf("%s",lines[i]);
    }

}

// -------------------------------------------------

int read_int() {
    char buf[MAX_STR_LEN];
    int n;
    fgets(buf, MAX_STR_LEN, stdin);
    sscanf(buf, "%d", &n);
    return n;
}

int main(void) {
    int to_do = read_int();
    int n;
    Person persons[MAX_PERSONS];
    char lines[MAX_PERSONS][MAX_STR_LEN];
    switch (to_do) {
        case 1:
            n = read_person_array(persons);
            qsort(persons, (size_t)n, sizeof(Person), cmp_person);
            print_person_array(persons, n);
            break;
        case 2:
            n = read_lines(lines);
            qsort(lines, (size_t) n, MAX_STR_LEN, cmp_lines);
            print_lines(lines, n);
            break;
        default:
            printf("Nothing to do for %d\n", to_do);
            break;
    }
}

