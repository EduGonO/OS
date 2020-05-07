#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

#include "declarations.h"       // this contains the functions and structs definitions I use

struct A_SIZExSIZE_ARR input;

#define MAX_THREADS 14
#define LETTERS 90 // Z is equal to 90 so the max int we could get is a 90
  
int threadNum = 0; 

// Final results
int finalRowLetter = -1;
int finalRowThread = -1;
int finalRowTimes = -1;
    
int finalColLetter = -1;
int finalColThread = -1;
int finalColTimes = -1;
  
// Function to find most frequent
void *maximum(void* arg) 
{ 

    int isVertical = *((int *) arg); // Start Vertically

    int num = threadNum++;

    int results[LETTERS] = {0};
    int frequency = -1;
    int letter = -1;

    if(isVertical==1) 
    {

        for(int i=0; i<7; i++) { 
            char res = input.A[i][num];
            results[res]++;
        }

        for (int i = 0; i < LETTERS; i ++) {
            if(results[i] > frequency) {
                frequency = results[i];
                letter = i;
            }
        }

        if(frequency>finalColTimes) {
            finalColLetter = (char)letter;

            if (num == 0) {
                finalColThread = 0;
            } 
            else {
                finalColThread = (num%7);
            }
            
            finalColTimes = frequency;
        }
        
    } 
    else {

        for(int i=0; i<7; i++) { 
            char res = input.A[num%7][i];
            results[res]++;
        }

        for (int i = 0; i < LETTERS; i ++) {
            if(results[i] > frequency) {
                frequency = results[i];
                letter = i;
            }
        }
        if(frequency>finalRowTimes) {
            finalRowLetter = (char)letter;
            finalRowThread = (num%7);
            finalRowTimes = frequency;
        }
    }
} 

int main() 
{

    printf("\n"); 

    srand(time(0));      // uncomment this to get random arrays
    build_array(&input); 

    int maxs = 0; 
    int i; 
    pthread_t threads[MAX_THREADS]; 
  
    // creating threads 
    // Prints thread
    for (i = 0; i < MAX_THREADS; i++) {

        // Sending either a 1 or 0 to specify if we need to evaluate a row or a column
        // 1 = Column
        // 0 = Row
        
        int *arg = malloc(sizeof(*arg));
        if (arg == NULL ) {
            fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
            exit(EXIT_FAILURE);
        }
        *arg = 1;

        if(i<7) {
            pthread_create(&threads[i], NULL, maximum, arg); 
        } else {
            *arg = 0;
            pthread_create(&threads[i], NULL, maximum, arg); 
        }
    }
    
    // joining threads
    for (i = 0; i < MAX_THREADS; i++) 
        pthread_join(threads[i], NULL); 

    printf("\n----------------\n"); 

    printf("\nRow: %d  Letter: %c  Number of Times: %d", finalRowThread, finalRowLetter, finalRowTimes);
    printf("\nColumn: %d  Letter: %c  Number of Times: %d\n", finalColThread, finalColLetter, finalColTimes);

    printf("\n----------------\n"); 
    printf("\n"); 

    // say "Row 3 contains 3 occurances of letter D". This is correct for the default RNG seed
    struct RESULT output = { .isrow = 1, .row_or_col_no=3, .letter_count = 3, .letter = 'D'};
    verify(&input, &output);    // check that the information in the output struct is correct

    return done(); 
}