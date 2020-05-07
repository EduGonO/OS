#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <stdbool.h>

pid_t pid;

//  Parent - reads: TeacherRead, writes: TeacherWrite
//  Child - reads: StudentRead, writes: StudentWrite
#define TeacherRead 0
#define StudentWrite 1
#define StudentRead 2
#define TeacherWrite 3

int main(){
    printf("\n");
    printf("------------------------------------------\n");
    printf("\n");
    printf("Operating Sistems: Assignment I\n");
    printf("Eduardo Gonzalez\n");
    printf("\n");
    printf("------------------------------------------\n");
    printf("\n");

    printf("\n");
    printf("Problem 1: Creating Processes using fork()\n");
    printf("\n");

    pid_t array[4] = {0};
    int aux = 0;

    for(int i=0;i<5;i++) {  // Level 1, creat 4 children

        pid = fork();
        array[aux] = pid;
        aux++;

        //printf("Array: %d ", array[aux-1]);
        if(pid<0) { // Level 1, error

            printf("Error when forking\n");

        } else if(pid==0 && i==0) { // Level 1, continues

            for(int j=0;j<6;j++) {  // Level 2, creat 5 children  

                pid = fork();
                array[aux] = pid;
                aux++;

                if(pid<0) { // Level 2, error

                    printf("Error when forking\n");

                } else if(pid==0 && j==0) { // Level 2, continues

                    for(int k=0;k<2;k++) {  // Level 3, creat 2 children

                        pid = fork();
                        array[aux] = pid;
                        aux++;

                        if(pid<0){ // Level 3, error

                            printf("Error when forking\n");

                        } else if(pid==0) {

                            printf("Level 3: [Son] pid %d from [Parent] pid %d\n", getpid(), getppid());
                            exit(0);

                        } else {
                            wait(NULL);
                        }
                    }
                    exit(0);

                } else if(pid==0) { // Level 2, closes children

                    printf("Level 2: [Son] pid %d from [Parent] pid %d\n", getpid(), getppid());
                    exit(0);

                } else {

                    wait(NULL);
                }
            }
            exit(0);

        } else if(pid==0) { // Level 1, closes children

            printf("Level 1: [Son] pid %d from [Parent] pid %d\n", getpid(), getppid());
            exit(0);

        } else {

            wait(NULL);
        }
    }


    printf("\n");
    printf("------------------------------------------\n");
    printf("\n");
    printf("Problem 2: Inter Process Communication\n");
    printf("           using Shared Memory\n");
    printf("\n");

    // We create the situations in Arrays
    // Used for problems 2 and 3

    char situation[5][40];
    strcpy(situation[0], "The light is turning green");
    strcpy(situation[1], "There is a pedestrian in front of me");
    strcpy(situation[2], "The car in front of me just stopped");
    strcpy(situation[3], "The car in front of me is moving");
    strcpy(situation[4], "The road is turning to the right");

    char recomendation[3][25];
    strcpy(recomendation[0], "Press the accelerator");
    strcpy(recomendation[1], "Press the break");
    strcpy(recomendation[2], "Steer right");

    char action[4][45];
    strcpy(action[0], "Done");
    strcpy(action[1], "Oops, I pressed the break instead");
    strcpy(action[2], "Oops, I pressed the accelerator instead");
    strcpy(action[3], "Oops, I steered left");

    char outcome[2][30];
    strcpy(outcome[0], "What a lousy teacher I am!");
    strcpy(outcome[1], "What a good teacher I am!\n");

    // Best way of getting a random number
    // Found it on the internet, will use later
    int randomNumber(int min, int max) {
        return rand() % ((max - min) + 1) + min;
    }

    // We create the flag
    bool flag = false;

    // We create the shared memory
    void* createMemory(size_t size) {
        int protection = PROT_READ | PROT_WRITE;
        int visibility = MAP_ANONYMOUS | MAP_SHARED;
        return mmap(NULL, size, protection, visibility, 0, 0);
    }

    char* memory = createMemory(128);

    // We create a random number to be used to determine the situation
    int r = rand()%5;

    // We create the child
    int pid_y = fork();

    if(pid<0){ // Error case
        printf("Error when forking\n");

    } else if (pid_y == 0) { // In the child
        printf("Situation: %d\n", r); // Say the situation
        memcpy(memory, situation[r], sizeof (situation[r])); // Send a random situation
        printf("\nStudent: %s\n", memory); // Say the situation
        sleep(1); // Waits fot the parent to answer

        int res = randomNumber(0, 1);

        printf("Student: ");
        if(randomNumber(0, 1) == 1) { // Did the right thing

            printf("%s\n", action[0]);

        } else if(res == 0 && memory == "0") { // Accelerator and failed
                
            printf("%s\n", action[1]);

        } else if(res == 0 && memory == "1") { // Press the Break and failed
                
            printf("%s\n", action[2]);

        } else if(res == 0 && memory == "2") { // Steer Right and failed
                
            printf("%s\n", action[3]);
        }
        memcpy(memory, &res, sizeof(res));

        exit(0);

    } else {

        // Based on the letter recieved, we give the correct advise
        // and also send the message

        wait(NULL);
        sleep(0.7); // If I don't put this here the print order gets messed up
        printf("Teacher: ");
        if(r == 0 || r == 3) {
            memcpy(memory, recomendation[0], sizeof (recomendation[0]));
            printf("Press the accelerator\n");
        } else if (r == 1 || r == 2) {
            memcpy(memory, recomendation[1], sizeof (recomendation[1]));
            printf("Press the break\n");
        } else if (r == 4) {
            memcpy(memory, recomendation[2], sizeof (recomendation[2]));
            printf("Steer right\n");
        }

        sleep(1); // If I don't put this here the print order gets messed up

        if(memory == "1") { // Made the right thing
            memcpy(memory, outcome[1], sizeof (outcome[1]));
            printf("%s\n", outcome[1]);
        }
        if(memory == "0") { // Made the wrong thing
            memcpy(memory, outcome[0], sizeof (outcome[0]));
            printf("%s\n", outcome[0]);
        }
        
        
    }


    printf("\n");
    printf("------------------------------------------\n");
    printf("\n");
    printf("Problem 3: Inter Process Communication\n");
    printf("           using Pipes\n");
    printf("\n");

    int fd[4];
    int message, status;
    pid_t pid;

    for (int i=0; i<2; ++i) {
        if (pipe(fd+(i*2)) < 0) {
            perror("Failed to allocate pipes");
            exit(EXIT_FAILURE);
        }
    }

    pid = fork(); // Create a child

    if(pid<0){ // Error case
        printf("Error when forking\n");
    }

    if (pid == 0) { // In the Child Process (Student)
    
        close(fd[TeacherRead]);
        close(fd[TeacherWrite]);

        // We create a random situation
        int s = randomNumber(0, 4);

        // Send the Student's Situation
        printf("Student: %s\n", situation[s]);
        write(fd[StudentWrite], &s, sizeof(s));

        // Wait for the Teacher's recomendation
        status = read(fd[StudentRead], &message, sizeof(message));

        if (status < 0) { // error case

            printf("Error when forking\n");

        } else if (status == 0) {

            // Found a message, I don't know when it would happen
            // But I'm putting it in just in case
            printf("No idea what happened");

        } else {

            // We generate either a 0 or a 1 randomly
            // (whether we followed the instructions or not)
            int binary = randomNumber(0, 1);

            printf("Student: ");
            if(binary == 1) { // Did the right thing

                printf("%s\n", action[0]);

            } else if(binary == 0 && message == 0) { // Accelerator and failed
                
                printf("%s\n", action[1]);

            } else if(binary == 0 && message == 1) { // Press the Break and failed
                
                printf("%s\n", action[2]);

            } else if(binary == 0 && message == 2) { // Steer Right and failed
                
                printf("%s\n", action[3]);
            }
            write(fd[StudentWrite], &binary, sizeof(binary));
        }

        close(fd[StudentRead]);
        close(fd[StudentWrite]);

        exit(0);
    }

    close(fd[StudentRead]);
    close(fd[StudentWrite]);

    // We wait for a response from the Student
    status = read(fd[TeacherRead], &message, sizeof(message));

    if (status < 0) { // error case

        printf("Error when forking\n");

    } else if (status == 0) {

        // Found a message, I don't know when it would happen
        // But I'm putting it in just in case
        printf("No idea what happened");

    } else {
        
        // Teacher's recomendation when hearing the situation

        printf("Teacher: ");
        if(message == 0 || message == 3) {

            int rec = 0;
            printf("%s\n", recomendation[0]);
            write(fd[TeacherWrite], &rec, sizeof(rec));

        } else if (message == 1 || message == 2) {

            int rec = 1;
            printf("%s\n", recomendation[1]);
            write(fd[TeacherWrite], &rec, sizeof(rec));

        } else if (message == 4) {

            int rec = 2;
            printf("%s\n", recomendation[2]);
            write(fd[TeacherWrite], &rec, sizeof(rec));
        }

        // Read if student made the right choice
        status = read(fd[TeacherRead], &message, sizeof(message));

        if (status < 0) { // error case

            printf("Error when forking\n");

        }
        else if (status == 0) {

            // Found a message, I don't know when it would happen
            // But I'm putting it in just in case
            printf("No idea what happened");

        } else {

            // Teacher's outcome of the situation

            sleep(0.7); // If I don't put this here the print order gets messed up
            printf("Teacher: ");

            if(message == 1) {
                printf("%s\n", outcome[1]);
            } else {
                printf("%s\n", outcome[0]);
            }
        }
    }

    close(fd[TeacherRead]);
    close(fd[TeacherWrite]);

    wait(NULL);

    return EXIT_SUCCESS;
}