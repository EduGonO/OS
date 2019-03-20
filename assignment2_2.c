#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

#include "declarations.h"       // this contains the functions and structs definitions I use

/* 
We declare 2 kinds of structs - these are basically like simple kinds of objects in C
The definitions are in "declarations.h" if you want to see how they are defined.

The first struct type is A_SIZExSIZE_ARR - this contains a single member: a 2D char array.
We begin by declaring one of these - A, in the global scope. Remember that after declaration,
the contents of this array are "garbage" values, so we must initalize them. 

We supply a function called build_array, which will initialize the contents of A to random characters.
We call build_array with a pointer to the struct A, as an argument: e.g: build_array(&A); 
Since the RNG seed is set to 1 by default, by commenting out the line 'srand(time(0));', you can
test your program against the same array, which should be:

N W L R B B M
Q B H C D A R
Z O W K K Y H
I D D Q S C D
X R J M O W F
R X S J Y B L
D B E F S A R

The correct (and only answer) is that:  Row 3 contains 3 occurances of letter D

Instead of printing your output, you will save your answers as a RESULT struct.
This structure contains fields which represents all the important parts of the output.
For instance: 
struct RESULT R = { .isrow = 1, .row_or_col_no=3, .letter_count = 3, .letter = 'D'};
represents that "Row 3 contains 3 occurances of letter D". 

Once you have initalized the RESULT struct R, you can pass both structs to the 'verify'
function, which will print the english version of the struct and tell you if it is correct.

Once you have "verified" all your answers, return the done function, which will check if you
found all the solutions, and return 1 if you did and -1 if you didn't. It will also print
"PASS" if you program is correct, and "ERROR: you didn't find all solutions" if it isn't.


In order for C to see all the functions, put all off the following in the same directory (probably OS-VM)
auto_grader.o, example_program.c, and declarations.h
You can then compile with
gcc -pthread example_program.c auto_grader.o -o example_program; ./example_program

Once you're done debugging, be sure to uncomment srand(time(0)); to start testing against actual random arrays. 
*/
struct A_SIZExSIZE_ARR input;
struct RESULT output;

int main()
{
    //srand(time(0));                               // uncomment this to get random arrays
    build_array(&input);                                // fill the contents of A
    /*
            You Program Here
    */
    // say "Row 3 contains 3 occurances of letter D". This is correct for the default RNG seed
    struct RESULT output = { .isrow = 1, .row_or_col_no=3, .letter_count = 3, .letter = 'D'};
    verify(&input, &output);    // check that the information in the output struct is correct

    return done(); 
}