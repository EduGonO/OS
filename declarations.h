#include <stdbool.h>
#define SIZE 7
#define ALPHABET 26

struct A_SIZExSIZE_ARR { 
    int A[SIZE][SIZE];
};

struct RESULT {
    int letter_count, row_or_col_no;
    char letter;
    bool isrow;
};

// the grading public API
void verify(struct A_SIZExSIZE_ARR *array, struct RESULT *R);                 //verify the output
struct A_SIZExSIZE_ARR (*build_array(struct A_SIZExSIZE_ARR *arr)); // initalize a random array
int done();         // verify correctness
