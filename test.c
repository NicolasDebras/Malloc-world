#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    struct Node* next;
};

typedef struct Node Node;

int nodeSize(Node* node){
    Node* tmp = node;

    int counter = 0;
    while (node != NULL)
    {
        counter++;
        node = node->next;
    }
    node = tmp;
    return counter;
}

void appendNode(Node* head, Node* last) {
    while(head->next != NULL) {
        head = head->next;
    }
    head->next = last;
}

Node* newNode(int value){
    Node* tmp = malloc(sizeof(Node));

    tmp->value = value;
    tmp->next = NULL;

    return tmp;
}

int main(){
    // Node* a = newNode(14);
    // Node* a1 = newNode(15);
    // Node* a2 = newNode(16);
    // Node* a3 = newNode(17);
    // Node* a4 = malloc(sizeof(Node));

    // if ( a4 == NULL ){
    //     printf("test ok\n");
    // }

    // appendNode(a, a1);
    // appendNode(a, a2);
    // appendNode(a, a3);

    // printf("On a %d et le premier element contient %d et a2 = %d \n", nodeSize(a), a->value, a->next->next->value);

    // a2->value = 34;

    // printf("On a %d et le premier element contient %d et a2 = %d \n", nodeSize(a), a->value, a->next->next->value);
    // free(a);
    // free(a1);
    // free(a2);
    // free(a3);
    int a = 3;
    switch (a)
    {
        case 2 || 3 || 4:
            printf("on est dans la première liste\n");
            break;
        // case 5 || 6 || 7:
        //     printf("on est dans la première liste\n");
        //     break;
    }
    
    return 0;
}