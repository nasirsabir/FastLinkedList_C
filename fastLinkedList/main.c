#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "math.h"
typedef struct node{
    int val;
    struct node* next;
    struct node* down;
}NODE;

// We are creating nodes and sorting them into a linked list
void createNodeAndSort(NODE ** head){
    NODE * tmp;
    NODE * prev;
    NODE *newNode;

    newNode=(NODE *) malloc(1*sizeof (NODE));
    printf("Enter the value of Node: ");
    scanf("%d",&newNode->val);
    if (*head==NULL)
    {
        *head = newNode;
        newNode->next=NULL;
    } else
    {
        tmp = *head;
        while (tmp->next != NULL && tmp->val-newNode->val< 0) {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp == *head) {
            if (tmp->val-newNode->val>=0) {
                newNode->next = tmp;
                *head = newNode;
            } else{
                tmp->next = newNode;
                newNode->next = NULL;
            }
        } else {
            if (tmp->next == NULL) {
                if (tmp->val-newNode->val>=0) {

                    prev->next = newNode;
                    newNode->next = tmp;
                } else {
                    tmp->next = newNode;
                    newNode->next = NULL;
                }
            } else {
                prev->next = newNode;
                newNode->next = tmp;
            }
        }
    }

}
// The deleting and sorting operation into a linked list is happening in this function
void deleteNodeAndSort(NODE ** head,int *length){
    int value;
    printf("\nPlease enter the value that you want to delete ");
    scanf("%d",&value);
    NODE *current,*prev;

    prev=(*head);
    current=prev->next;
    while (current!=NULL && current->val!=value){
        prev=current;
        current=current->next;
    }
    if (current!= NULL && current->val==value)
    {
        prev->next=current->next;
        free(current);
        (*length)--;
    } else
        printf("\nThere is no such %d value in the list\n",value);
}
// We are going linear in our linked list and returning the node that we want.
NODE * traverseList(NODE ** head,int index){
    NODE *tmp;
    tmp=(*head)->next;
    while (tmp!=NULL && index!=0){
        tmp=tmp->next;
        index--;
    }
    return tmp;
}
// We are choosing a random node from our first complete linked list. And calling traverseList function to pick the node that we want.
NODE * getRandomNode(NODE *head,int length,int *lower){
    int i;
    if (length>5)
    {
        i=rand() % length/3 + *lower ;
    }else
        i=rand() % length/2 + *lower ;
    if(i==0)
        *lower=i+1;
    else
        *lower=i+1;
    return traverseList(&head,i);
}
// We print linked list, that we create in multiple ways and named fastLinkedList.
void printList(NODE ** head){
    NODE *tmp,*current;
    int i=0;
    if (*head==NULL)
        printf("Empty list\n");
    else{
        current=(*head);
        while (current->down!=NULL){
            current =current->down;
            tmp=current->next;
            printf("%d-) ",i+1);
            while(tmp!=NULL){
                printf("%d, ", tmp->val);
                tmp=tmp->next;
            }
            printf("\n");
            i++;
        }
    }
}

NODE * rekursion(NODE * head,int length){
    NODE * head1,*prev,*current,*newNode,*tmp;
    int i,lower =0;
    if (length==1){
        head1=(NODE*) malloc(1*sizeof (NODE));
        head1->down=head;
        newNode=(NODE*) malloc(sizeof (NODE));
        head1->next=newNode;
        newNode->next=NULL;
        tmp=getRandomNode(head,length,&lower);
        newNode->val= tmp->val;
        newNode->down= tmp;
        prev=(NODE*) malloc(sizeof (NODE));
        prev->down=head1;
        prev->next=NULL;
        return prev;
    } else{
        head1=(NODE*) malloc(1*sizeof (NODE));
        head1->down=head;
        current=head1;
        for ( i = 0; i < length; i++) {
            newNode=(NODE*) malloc(sizeof (NODE));
            current->next=newNode;
            tmp=getRandomNode(head,length,&lower);
            newNode->val= tmp->val;
            newNode->down= tmp;
            current=newNode;
            newNode=NULL;
        }
        current->next=NULL;
        head= rekursion(head1,(length+1)/2);
        return head;
    }
}
// We are going in the bottom linked list from our fastLinkedList
// and adding a node by calling createNodeAndSort function
// after we add a node in our bottom linked list we call the function rekursion
// to create the fastLinkedList composition again.
NODE * addNode(NODE * head,int length){
    NODE * head1;
    int i,boyut= ceil(log2(length))+1;
    head1=head;
    for ( i = 0; i < boyut; ++i) {
        head1=head1->down;
    }
    createNodeAndSort(&head1);
    head1=rekursion(head1,(length+1)/2);
    printList(&head1);
    return head1;
}
// We are going in the bottom linked list from our fastLinkedList
// and deleting a node by calling deleteNodeAndSort function
// after we delete a node from our bottom linked list we call the function rekursion
// to create the fastLinkedList composition again.
NODE * deleteNode(NODE * head, int *length){
    NODE * head1;
    int i,boyut= ceil(log2(*length))+1;
    head1=head;
    for ( i = 0; i < boyut; ++i) {
        head1=head1->down;
    }
    deleteNodeAndSort(&head1,length);
    head1=rekursion(head1,((*length)+1)/2);
    printList(&head1);
    return head1;
}
// We are searching the node in a new way that we created fastLinkedList.
// The function returns the level it found if the node exists
NODE * searchInList(NODE * head,int value, int length){
    int i=0,boyut = ceil(log2(length))+1;
    NODE * prev,*current;
    prev=head;
    while (  i < boyut) {
        prev=prev->down;
        current=prev->next;
        while(current!=NULL && value > current->val){
            prev=current;
            current=current->next;
        }
        if (current!=NULL && value == current->val)
        {
            printf("You have founded the number %d in %dth level\n",value,i+1);
            i=boyut;
        }
        i++;
    }
    if(i==boyut)
        printf("There is no such %d number in list.\n",value);

}
// Our test and menu sections are build in main
int main() {
    NODE * head=NULL;
    int i,length,choice,value;
    printf("Please enter the length of list: ");
    scanf("%d",&length);

    for ( i = 0; i < length ; ++i) {
        createNodeAndSort(&head);
    }
    NODE * newHead=(NODE*) malloc(1*sizeof (NODE));
    newHead->next=head;
    head=newHead;
    head->down=NULL;
    head=rekursion(head,(length+1)/2);
    printList(&head);

    printf("\n********MENU********");
    printf("\n1-) Search a value in the list");
    printf("\n2-) Add a new node to the list");
    printf("\n3-) Delete a node from the list");
    printf("\n0-) Quit\n");
    scanf("%d",&choice);
    while ( choice!=0)
    {
        switch (choice) {
            case 1:
                printf("\nPlease enter the value that you searching ");
                scanf("%d",&value);
                searchInList(head,value,length);
                break;
            case 2:
                length++;
                head=addNode(head,length);
                break;
            case 3:
                head= deleteNode(head,&length);
                break;
        }
        printf("\n*******************************\nTo see the menu again press 4, to quit press any button except 4.\n");
        scanf("%d",&choice);
        if (choice==4)
        {
            printf("\n********MENU********");
            printf("\n1-) Search a value in the list");
            printf("\n2-) Add a new node to the list");
            printf("\n3-) Delete a node from the list");
            printf("\n0-) Quit\n");
            scanf("%d",&choice);
        } else
            choice=0;
    }
    return 0;
}

