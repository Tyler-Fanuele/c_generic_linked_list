/*
    Copyright 2022, Tyler Fanuele
*/
#include <stdio.h>
#include <stdlib.h>
#include "generic_linked_list.h"

void node_init_int(ITEM* spot, ITEM data) {
    Node* tempNode = (Node*)malloc(sizeof(Node));
    if (!tempNode) {
        printf("Node init failed to malloc\n");
        exit(1);
    }
    tempNode->data = &data;
    tempNode->next = NULL;
}
void node_destroy_int(ITEM* phnode) {
    free(*phnode);
    *phnode = NULL;
}

int main(int argc, char* argv[]) {
    List* test = list_init((ITEM)200, node_init_int, node_destroy_int);
    printf("sss\n");
    int x = 4;
    list_append(test, (ITEM)&x);
    printf("sss\n");
    list_append(test, (ITEM)4);
    list_append(test, (ITEM)5);
    list_push(test, (ITEM)100);

    printf("front %d, back %d\n", *(int*)list_peak_front(test), *(int*)list_peak_back(test));

    List* test2 = list_reverse_copy(test);
    
    list_append(test2, (ITEM)3);

    list_print_debug(test);
    list_print_debug(test2);

    list_destroy(&test2);
    list_destroy(&test);
    return 0;
}
