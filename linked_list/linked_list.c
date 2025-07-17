#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// LINKED LIST

typedef int T;

typedef struct node{

    T value;             // node's value
    struct node* next;   // is a pointer to the next node

}node;

node* new_node(T new_value){

    node* temp= (node*)malloc(sizeof(node)); // allocates memory for the next node

    if (temp != NULL){                       // if allocated
        temp -> value = new_value;           
        temp -> next = NULL;
        return temp;
    }
    else{
        printf("Memory error. Try again\n");
    }

}


// deletes next node if possible

node* delete_node(node* prev_node){

    if (prev_node -> next != NULL)          // if it has the next node changes the next pointer
        prev_node -> next = (prev_node -> next -> next = NULL)? NULL : prev_node -> next -> next;
    return prev_node;

}

void example_1(){  //adds nodes
    node* first = new_node(52);
    node* second = first -> next = new_node(25);

    printf("%d %d \n", first->value, first -> next -> value);

}

void example_2(){  //adds and deletes nodes
    node* ft = new_node(1);
    node* snd = ft -> next = new_node(2);
    node* thd = snd -> next = new_node(3);

    printf("%d %d %d \n", ft->value, snd -> value, thd -> value);

    delete_node(snd);

    printf("%d %d %d \n", ft->value, snd -> value, snd -> next);

}

int main (int argc, char** argv){

    example_1();
    printf("\n");
    example_2();

    return 0;
}