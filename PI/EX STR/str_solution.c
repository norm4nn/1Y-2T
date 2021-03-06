#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// consider chars from [FIRST_CHAR, LAST_CHAR)
#define FIRST_CHAR 33
#define LAST_CHAR 127
#define MAX_CHARS (LAST_CHAR - FIRST_CHAR)
#define MAX_DIGRAMS (LAST_CHAR - FIRST_CHAR) * (LAST_CHAR - FIRST_CHAR)

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

int count[MAX_CHARS] = { 0 };
int count2[MAX_DIGRAMS] = { 0 };

// function to be used as comparator to qsort (compares counters and thes sorts
// alphabetically when equal)
int cmp (const void *a, const void *b) {
    int va = *(int*)a;
    int vb = *(int*)b;
    if (count[va] == count[vb]) return va - vb; // sort alphabetically if counts equal
    return count[vb] - count[va];
}

// function to be used as comparator to qsort for digrams (compares counters and
// thes sorts alphabetically when equal)
int cmp_di (const void *a, const void *b) {
    int va = *(int*)a;
    int vb = *(int*)b;
    // sort according to second char if counts and the first char equal
    if (count2[va] == count2[vb] && va / MAX_CHARS == vb / MAX_CHARS) return va % MAX_CHARS - vb % MAX_CHARS;
    // sort according to first char if counts equal
    if (count2[va] == count2[vb]) return va / MAX_CHARS - vb / MAX_CHARS;
    return count2[vb] - count2[va];
    //return count[va] - count[vb];
}



// count number of lines (nl), number of words (nw) and number of characters
// (nc) in the text read from stdin
void wc(int *nl, int *nw, int *nc){
    *nl = 0;
    *nw = 0;
    *nc = 0;
    int inputINT = 0;
    int last0 = 0;

    inputINT = getchar();
    while (inputINT != EOF){
        char input = (char)inputINT;
        char last = (char)last0;
        ++*nc;
        if (input == '\n')	{
            ++*nl;
            if (last != ' ' && last != '\n' && last != '\t') ++*nw;
        }
        if ((input == ' ' || input == '\t') && last != ' ' && last != '\n' && last != '\t')	++*nw;

        last0 = inputINT;
        inputINT = getchar();
    }
    *nl -= 1;
    *nc -= 1;
    *nw -= 1;
}

// count how many times each character from [FIRST_CHAR, LAST_CHAR) occurs
// in the text read from stdin. Sort chars according to their respective
// cardinalities (decreasing order). Set n_char and cnt to the char_no - th char
// in the sorted list and its cardinality respectively
void char_count(int char_no, int *n_char, int *cnt){
    int inpt = 0;
    int id[MAX_CHARS];

    for(int i=0;i<MAX_CHARS;i++){
        id[i] = i;
    }

    while (inpt != EOF){
        if (inpt >= FIRST_CHAR && inpt < LAST_CHAR) {
            ++count[inpt-FIRST_CHAR];
            //printf("%c: %d\n",(char)inpt,inpt);
        }
        inpt = getchar();
    }

    qsort(id,MAX_CHARS,sizeof(int),cmp);

    *n_char = id[char_no-1]+FIRST_CHAR;
    *cnt = count[id[char_no-1]];
}

// count how many times each digram (a pair of characters, from [FIRST_CHAR,
// LAST_CHAR) each) occurs in the text read from stdin. Sort digrams according
// to their respective cardinalities (decreasing order). Set digram[0] and
// digram[1] to the first and the second char in the digram_no - th digram_char
// in the sorted list. Set digram[2] to its cardinality.
void digram_count(int digram_no, int digram[]){
    int inpt;
    int last;
    inpt = getchar();
    last = inpt;
    inpt = getchar();
    int size = 0;
    int id[MAX_DIGRAMS];

    for(int i=0;i<MAX_DIGRAMS;i++)  id[i] = i;

    while (inpt != EOF){
        if (inpt >= FIRST_CHAR && inpt < LAST_CHAR && last >= FIRST_CHAR && last < LAST_CHAR )
            count2[(last - FIRST_CHAR)*MAX_CHARS+(inpt - FIRST_CHAR)]++;
        last = inpt;
        inpt = getchar();
    }
//    for(int i=0;i<MAX_DIGRAMS;i++){
//        printf("%c%c: %d \n",i/MAX_CHARS+FIRST_CHAR,i%MAX_CHARS+FIRST_CHAR,count2[i]);
//    }
    qsort(id, MAX_DIGRAMS, sizeof(id[0]),cmp_di);
//    for(int i=0;i<MAX_DIGRAMS;i++){
//        printf("%c%c: %d \n",id[i]/MAX_CHARS+FIRST_CHAR,id[i]%MAX_CHARS+FIRST_CHAR,count2[id[i]]);
//       //printf("%d: %d\n",i,id[i]);
//    }

    digram[0] = id[digram_no-1]/MAX_CHARS + FIRST_CHAR;
    digram[1] = id[digram_no-1]%MAX_CHARS + FIRST_CHAR;
    digram[2] = count2[id[digram_no-1]];


}

// Count block and line comments in the text read from stdin. Set
// line_comment_counter and block_comment_counter accordingly
void find_comments(int *line_comment_counter, int *block_comment_counter){//tekst i znak
    *line_comment_counter = 0;
    *block_comment_counter = 0;
    int blok = 0;
    int ignore = 0;
    int inpt;
    int last = 0;
    int text = 0;
    inpt = getchar();

    while (inpt != EOF){
        char c = (char)inpt;
        char c2 = (char)last;
        //printf("%c %d\n",c,text);
        if (text == 1 && (c == (char)34 || c == (char)39)) text = 0;
        else if(ignore == 0 && blok == 0 && text == 0 &&  (c == (char)34 || c == (char)39)) text = 1;

        if (text == 0) {
            if (ignore == 0 && blok == 0 && c2 == '/' && c == '/') {
                ++*line_comment_counter;
                ignore = 1;
            }
            if (ignore == 1 && c == '\n' && c2 != '\\') ignore = 0;
            if (ignore == 0 && blok == 0 && c2 == '/' && c == '*') blok = 1;

            if (blok == 1 && c2 == '*' && c == '/') {
                blok = 0;
                ++*block_comment_counter;
            }
        }

        last = inpt;
        inpt = getchar();
    }


}

#define MAX_LINE 128

int read_line() {
    char line[MAX_LINE];
    int n;

    fgets (line, MAX_LINE, stdin); // to get the whole line
    printf("%s",line);
    scanf (line, "%d", &n);
    printf("%s",line);
    return n;
}

int main(void) {
    int to_do;
    int nl, nw, nc, char_no, n_char, cnt;
    int line_comment_counter, block_comment_counter;
    int digram[3];
    //to_do = read_line();
    //printf("%c",34);

    scanf("%d",&to_do);

    switch (to_do) {
        case 1: // wc()
            wc (&nl, &nw, &nc);
            printf("%d %d %d\n", nl, nw, nc);
            break;
        case 2: // char_count()
            //char_no = read_line();
            scanf("%d",&char_no);
            char_count(char_no, &n_char, &cnt);
            printf("%c %d\n", n_char, cnt);
            break;
        case 3: // digram_count()
            scanf("%d",&char_no);
            digram_count(char_no, digram);
            printf("%c%c %d\n", digram[0], digram[1], digram[2]);
            break;
        case 4:
            find_comments(&line_comment_counter, &block_comment_counter);
            printf("%d %d\n", block_comment_counter, line_comment_counter);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;

}
