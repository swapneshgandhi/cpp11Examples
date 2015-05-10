#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
typedef struct LinkedListNode LinkedListNode;

struct LinkedListNode{
    int val;
    LinkedListNode *next;
};

/*
A singly linkedList,
 to which we can add new elements
 and remove a perticular elements elements
*/

LinkedListNode* _insert_node_into_singlylinkedlist(LinkedListNode *head, int val){
    if(head == NULL) {
        head = (LinkedListNode *) (malloc(sizeof(LinkedListNode)));
        head->val = val;
        head->next = NULL;
    }
    else {
        LinkedListNode *end = head;
        while (end->next != NULL) {
            end = end->next;
        }
        LinkedListNode *node = (LinkedListNode *) (malloc(sizeof(LinkedListNode)));
        node->val = val;
        node->next = NULL;
        end->next = node;
    }
    return head;
}


void removeAll(int val, LinkedListNode** list) {
    if (!list || !(*list) ){
        return;
    }

    LinkedListNode * trav= *list;
    LinkedListNode * Next=NULL;
    int index=0;

	   if ( (*list)->val == val){

         Next=(*list)->next;
         free(*list);
         *list=Next;
		 if (Next!=NULL)
         trav=*list;
        }

	
    while (trav && trav->next!=NULL){

		if (trav->next->val == val){

           Next=trav->next->next;
           free(trav->next);
           trav->next=Next;
        }
        else{
            trav=trav->next;
        }
    }
}

int main() {
    int _val;
    scanf("%d\n", &_val);


    int _list_size;
    int _list_item;
    LinkedListNode* _list = NULL;
    scanf("%d\n", &_list_size);
    int _list_i;

    //load elements to the linkedList
    for(_list_i = 0; _list_i < _list_size; _list_i++) {
        scanf("%d\n", &_list_item);
        _list = _insert_node_into_singlylinkedlist(_list, _list_item);
    }

    //remove elements which match the val
    removeAll(_val, &_list);

    //print out all the elements in the end.
    LinkedListNode* _current = _list;
        while (_current != NULL)
    {
      printf("%d ", _current->val);
      _current = _current->next;
    }

    return 0;
}

