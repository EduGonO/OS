#include <stdio.h>
#include "ASSN4_declarations.h"
#include <stdint.h>
#include "LinkedList.c"

unsigned int_size = sizeof(int);

struct SegmentTable
{
    char pid;
    int (*st)[][2];
    int sizee;
};

// run with gcc ASSN4_Example.c ASSN4_grader.o -o ASSN4_Example; ./ASSN4_Example
void main()
{   
    printf("%3s, %7s %20s\n", "pid", "status", "---------------segments---------------" );
    Process x = get_input();

    unsigned int_size = sizeof(int);
    struct Node *segmentTableList = NULL; 
    struct Node *holes = NULL;
    
    while (x.pid!=-1) {

        struct SegmentTable st;

        printf("%3d, %7d, ", x.pid, x.status);
        printer(x.segments);

        st.pid = x.pid;
        //push(&segmentTableList, &st, int_size);

        if(x.status==0){

            struct SegmentTable st;
            int count = 0;
            st.pid = x.pid;
            st.sizee = 0;
            
            while((*x.segments)[count][0]!=0) {
                st.sizee = st.sizee + (*x.segments)[count][1];
                count++;
            }
            
            // We fill the segment table of the process we are currently reading
            int segTable[count][3];
            
            segTable[0][0] = 1;
            segTable[0][1] = (*x.segments)[0][1];
            segTable[0][2] = 1;

            int i = 1;

            while((*x.segments)[i][0]!=0) {
                segTable[i][0] = segTable[i-1][0] + (*x.segments)[i-1][1];
                segTable[i][1] = (*x.segments)[i][1];
                segTable[i][2] = 1;
                i++;
            }

            segTable[0][0] = 0;

            //fillArray(segTable, (*st.st),count);

            printf("\n");
            printf("Segment Table for Process %d, size: %d", st.pid, st.sizee);
            printf("\n");
            
            for(int k=0; k<count; k++){
                for(int l = 0; l < 3; l++)
                    printf("%d ", segTable[k][l]); 
                printf("\n");
            }
            printf("\n");

            //push(&segmentTableList, segTable, &st, int_size);
        }

        if(x.status==1){

            /* 
            This Code does not work. I wrote it and left it since I belive a few changes can
            make it work, however I've been stuck for several days now. I do not know C so I'm using
            my Java knolege of a linkedList and Object Oriented Programming to code the following.
            */
/*             
            //instead of creating a new structure, we get the already existing one
            struct segmentTable *find(segmentTableList, printInt, x.pid);
            
            int count = 0;

            while((*x.segments)[count][0]!=0) {
                st.sizee = st.sizee + (*x.segments)[count][1];
                count++;
            }
            
            // We fill the segment table of the process we are currently reading
            int segTable[count][3];
            
            segTable[0][0] = 1;
            segTable[0][1] = (*x.segments)[0][1];
            segTable[0][2] = 1;

            int i = 1;

            while((*x.segments)[i][0]!=0) {
                segTable[i][0] = segTable[i-1][0] + (*x.segments)[i-1][1];
                segTable[i][1] = (*x.segments)[i][1];
                segTable[i][2] = 1;
                i++;
            }

            segTable[0][0] = 0;

            // We update the array
            segmentTable->segments = segTable;
*/
        }

        if(x.status==2){

            printf("\n");
            printf("Process %d has been swapped out", x.pid);
            printf("\n");
            printf("\n");
        // This does not work either, I really tried but I'm very unfamiliar with C
        // nevertheless, I wrote and explained what it is supposed to do
/*
            struct segmentTable *find(segmentTableList, printInt, x.pid);

            // In the node, the data section, the size of the process
            printf("There is a hole now of: %d units", segmentTable->data.sizee);
            */
        }

        if(x.status==3){

            printf("\n");
            printf("Process %d has been terminated", x.pid);
            printf("\n");
            printf("\n");

            // This does not work either, I really tried but I'm very unfamiliar with C
        // nevertheless, I wrote and explained what it is supposed to do
/*
            struct segmentTable *find(segmentTableList, printInt, x.pid);

            // In the node, the data section, the size of the process
            printf("There is a hole now of: %d units", segmentTable->data.sizee);
            */
        }
        x=get_input();
    }
    
}
