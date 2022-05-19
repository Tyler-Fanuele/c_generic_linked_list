/*
    Copyright 2022, Tyler Fanuele
*/

#include "generic_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/*
    Node Implmentation
*/


Node* node_init(ITEM data, void (*item_assignment)(ITEM* pleft, ITEM right)) {
    Node* tempNode = (Node*)malloc(sizeof(Node));
    if (!tempNode) {
        printf("Node init failed to malloc\n");
        exit(1);
    }
    item_assignment(&(tempNode->data), &data);
    tempNode->next = NULL;
    return tempNode;
}
void node_destroy(Node** phnode, void (*item_destroy)(ITEM* phitem)) {
    item_destroy(&((*phnode)->data));
    *phnode = NULL;
}

/*
    List Implmentation
*/

List* list_init_default( void ) {
    List* tempList = (List*)malloc(sizeof(List));
    if(!tempList) {
        printf("List init node default failed to malloc\n");
        exit(1);
    }
    tempList->head = NULL;
    return tempList;
}
List* list_init(ITEM data, 
                void (*item_assignment)(ITEM* pleft, ITEM right), 
                void (*item_destroy)(ITEM* phitem)) {
    List* tempList = (List*)malloc(sizeof(List));
    if (!tempList) {
        printf("List init failed to malloc\n");
        exit(1);
    }
    tempList->head = node_init(data, item_assignment);
    return tempList;
}
List* list_init_node(Node* pnode) {
    List* tempList = (List*)malloc(sizeof(List));
    if (!tempList) {
        printf("List Init failed to malloc\n");
        exit(1);
    }
    tempList->head = pnode;
    return tempList;
}
void list_destroy(List** phlist) {
    Node* temp = (*phlist)->head;
    Node* next;
    while(temp) {
        next = temp->next;
        (*phlist)->item_destroy(temp->data);
        free(temp);
        temp = next;
    }
    free(*phlist);
    *phlist = NULL;
}
void list_append(List* plist, ITEM data) {
    if (!plist->head) {
        plist->head = node_init(data, plist->item_assignment);
        return;
    }
    Node* temp = plist->head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node_init(data, plist->item_assignment);
}

void list_push(List* plist, ITEM data) {
    if (!plist->head) {
        plist->head = node_init(data, plist->item_assignment);
    }
    Node* temp = plist->head;
    Node* new =  node_init(data, plist->item_assignment);
    new->next = temp;
    temp = new;
    plist->head = temp;
}

void list_print_debug(List* plist) {
    Node* temp = plist->head;
    int i = 0;
    printf("Linked list {\n");
    while(temp->next != NULL) {
        printf("Node[%d] -> %d\n", i, *(int*)temp->data);
        temp = temp->next;
        i++;
    }
    printf("Node[%d] -> %d\n", i, *(int*)temp->data);
    printf("}\n");
}

ITEM list_peak_front(List* plist) {
    if (!plist->head) {
        printf("list peak front null node");
        exit(1);
    }
    return plist->head->data;
}

ITEM list_peak_back(List* plist) {
    Node* temp = plist->head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;
}

void list_reverse(List* plist) {
    Node* prev = NULL;
    Node* curr = plist->head;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    plist->head = prev;
}

List* list_copy(List* plist) {
    List* retList = list_init_default();
    Node* curr = plist->head;
    while (curr->next) {
        list_append(retList, curr->data);
        curr = curr->next;
    }
    list_append(retList, curr->data);
    return retList;
}

List* list_reverse_copy(List* plist) {
    List* retList = list_copy(plist);
    list_reverse(retList);
    return retList;
}
