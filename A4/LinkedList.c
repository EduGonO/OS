// C program for generic linked list 
#include<stdio.h> 
#include<stdlib.h> 
  
/* A linked list node */
struct Node 
{ 
    // Any data type can be stored in this node 
    int pid;
    int (*segments)[][3];
    void *data; 
    struct Node *next; 
}; 

/* Function to add a node at the beginning of Linked List. 
   This function expects a pointer to the data to be added 
   and size of the data type 

void setPid(struct Node *node, int pid) {
    node->pid = pid;
}
*/
void fillArray(int (*segTable)[][3], int (*p)[][3], int count){

    for(int i=0; i<count; i++) 
        for (int j=0; j<3; j++) 
            (*p)[i][j] = (*segTable)[i][j];
}

void push(struct Node** head_ref, void *new_data, int (*p)[][3], size_t data_size) 
{ 
    // Allocate memory for node 
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
  
    new_node->data  = malloc(data_size); 
    new_node->next = (*head_ref); 
    new_node->segments = (*p);
  
    // Copy contents of new_data to newly allocated memory. 
    // Assumption: char takes 1 byte. 
    int i; 
    for (i=0; i<data_size; i++) 
        *(char *)(new_node->data + i) = *(char *)(new_data + i); 
  
    // Change head pointer as new node is added at the beginning 
    (*head_ref)    = new_node; 
} 
  
/* Function to print nodes in a given linked list. fpitr is used 
   to access the function to be used for printing current node data. 
   Note that different data types need different specifier in printf() */
void printList(struct Node *node, void (*fptr)(void *)) 
{ 
    while (node != NULL) 
    { 
        (*fptr)(node->data); 
        node = node->next; 
    }
}

/*
struct Node *node find(struct Node *node, void (*fptr)(void *), int *pid) 
{ 
    while (node->data != pid) 
    { 
        (*fptr)(node->data); 
        int i = (int)(uintptr_t) node->data;
        node = node->next; 
    }
    if(node->data == pid){
        return node;
    } else {
        printf("Error");
    }
}*/

// Function to print an integer 
void printInt(void *n) 
{ 
   printf(" %d", *(int *)n); 
} 
