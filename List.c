/***
 * Tanvi Herwadjar
 * therwadk
 * 2023 Fall CSE101 PA2
 * List.c
 * Implements List ADT
***/ 

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"

//structs -------------------------------------------------

//private Node type
typedef struct NodeObj* Node;

//private NodeObj type
typedef struct NodeObj{
	ListElement data;
	Node next;
	Node prev;
} NodeObj;

//private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	int length;
	Node cursor;
	int index;
} ListObj;

// Function Definitions ------------------------------------------------------
List newList(void);
void freeList(List* pL); 
int length(List L);
int index(List L); 
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);

void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L); 
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

void printList(FILE* out, List L);
List copyList(List L);
// Constructors-Destructors ---------------------------------------------------

Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

void freeNode(Node *pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;	
	}
}

List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	assert(L != NULL);
	L->front = NULL;
	L->back = NULL;
	L->length = 0;
	L->cursor = NULL;
	L->index = -1;
	return(L);
}

void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL) {
		while( (*pL)->length!=0 ) {
			deleteBack(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------
int length(List L) {
	if (L == NULL) {
		fprintf(stderr,"List Error: calling length(List L) on a NULL List ref\n");
		exit(1);		
	}
	return L->length;
}

int index(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling index(List L) on a NULL List ref\n");
		exit(1);
	}
	if (L->cursor == NULL) {
		return -1;
	}	
	return L->index;
}

int front(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling front(List L) on a NULL List ref\n");
		exit(1);
	}
	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling front(List L) on empty List\n");
		exit(1);
	}
	return L->front->data;	
}

int back(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling back(List L) on a NULL List ref\n");
		exit(1);
	}
        if (length(L) == 0) {
		fprintf(stderr, "List Error: calling back(List L) on empty List\n");
                exit(1);
        }
        return L->back->data;
}

int get(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling get(List L) on a NULL List ref\n");
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: calling get(List L) on empty List\n");
		exit(1);
	}

	if (index(L) < 0) {
		fprintf(stderr, "List Error: calling get(List L) on List with undefined cursor\n");
		exit(1);
	}
	return L->cursor->data;
}

bool equals(List A, List B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr, "List Error: calling equals(List A, List B) on a NULL ref\n");
		exit(1);
	}
	if (A->length != B->length) {
		return false;
	}
	if (A->length == 0 && B->length == 0) {
		return true;
	}
	Node currentA = A->front;
	Node currentB = B->front;

	assert(currentA != NULL);
	assert(currentB != NULL);

	while(1) {
		if (currentA->data != currentB->data) {
			return false;
		}

		currentA = currentA->next;
		currentB = currentB->next;

		if (currentA == NULL) {
			break;
		}
		
		assert(currentB != NULL);	
	}
	return true;
}
// Manipulator functions ---------------------------------------------------
void clear(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling clear(List L) on a NULL List ref\n");
		exit(1);
	}
	while (L->length > 0) {
		deleteBack(L);					
	}
}

void set(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling set(List L) on a NULL List ref\n");
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: calling set(List L) on empty List\n");
		exit(1);
	}

	if (index(L) < 0) {
		fprintf(stderr, "List Error: calling set(List L) on List with undefined cursor\n");
		exit(1);
	}
	L->cursor->data = x;
}

void moveFront(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling moveFront(List L) on a NULL List ref\n");
		exit(1);
	}

	if (length(L) != 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L) {	
	if (L == NULL) {
		fprintf(stderr, "List Error: calling moveBack(List L) on a NULL List ref\n");
		exit(1);
	}
	
	if (length(L) != 0) {
		L->cursor = L->back;
		L->index = (L->length) - 1;
	}	
}

void movePrev(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling movePrev(List L) on NULL List ref\n");
		exit(1);
	}
	if (index(L) == 0) {
		L->index = -1;
		L->cursor = NULL;
	}
	else if (index(L) >= 0) {
		L->index -= 1;
		L->cursor = L->cursor->prev;
	}
}

void moveNext(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling movePrev(List L) on NULL List ref\n");
		exit(1);
	}
	if (index(L) == (L->length) - 1) {
		L->index = -1;
		L->cursor = NULL;		
	}
	else if (index(L) >= 0) {
		L->index += 1;
		L->cursor = L->cursor->next;
	}	
}

void prepend(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling prepend(List L, int x) on NULL List ref\n");
		exit(1);		
	}

	Node N = newNode(x);
	if (length(L) == 0) {
		L->front = N;
		L->back = N;		
		L->length += 1;
	}	
	else {
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		L->length += 1;
		if (L->cursor != NULL) {
			L->index += 1;
		}	
	}
}

void append(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling append(List L, int x) on NULL List ref\n");
		exit(1);		
	}
	
	Node N = newNode(x);
	if (length(L) == 0) {
		L->front = N;
		L->back = N;		
		L->length += 1;
	}	
	else {
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
		L->length += 1;
		//printf("%d\n", back(L));	
	}
}
void insertBefore(List L, int x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling insertBefore(List L, int x) on NULL List ref\n");
		exit(1);
	}	

	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling insertBefore(List L, int x) on empty List\n");
		exit(1);
	}

	if (index(L) < 0) {
		fprintf(stderr, "List Error: calling insertBefore(List L, int x) on undefined cursor\n");
		exit(1);
	}


	Node N = newNode(x);
	if (L->cursor == L->front) {
		N->next = L->cursor;
		L->cursor->prev = N;
		L->front = N;	
	}	
	else {
	N->next = L->cursor;

	L->cursor->prev->next = N;
	N->prev = L->cursor->prev;
	L->cursor->prev = N;
	}

	L->index += 1;
	L->length += 1;
}

void insertAfter(List L, int x) {	
	if (L == NULL) {
		fprintf(stderr, "List Error: calling insertAfter(List L, int x) on NULL List ref\n");
		exit(1);
	}	

	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling insertAfter(List L, int x) on empty List\n");
		exit(1);
	}

	if (index(L) < 0) {
		fprintf(stderr, "List Error: calling insertAfter(List L, int x) on undefined cursor\n");
		exit(1);
	}
	
	Node N = newNode(x);

	if (L->cursor == L->back) {
		N->prev = L->cursor;
		L->cursor->next = N;
		L->back = N;	
	}
	else {	
	N->prev = L->cursor;

	L->cursor->next->prev = N;
	L->cursor->next = N;
	N->next = L->cursor->next;
	}

	L->length += 1;
}

void deleteFront(List L) {	
	if (L == NULL) {
		fprintf(stderr, "List Error: calling deleteFront(List L) on NULL List ref\n");
		exit(1);
	}	

	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling deleteFront(List L) on empty List\n");
		exit(1);
	}
	if (length(L) == 1) {
		Node front = L->front;
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->index = -1;
		L->length = 0;
		freeNode(&front);
	}
	else {
		if (index(L) >= 0) {
			L->index -= 1;
		}
		if (L->cursor == L->front) {
			L->cursor = NULL;
			L->index = -1;
		}
		Node front = L->front;
		L->front = L->front->next;
		L->front->prev = NULL;

		L->length -= 1;
		freeNode(&front);
	}
}

void deleteBack(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling deleteFront(List L) on NULL List ref\n");
		exit(1);
	}	

	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling deleteFront(List L) on empty List\n");
		exit(1);
	}
	
	if (length(L) == 1) {
		Node back = L->back;
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->index = -1;
		L->length -= 1;
		freeNode(&back);
	}
	else {
		Node back = L->back;
		if (L->cursor == L->back) {
			L->cursor = NULL;
			L->index = -1;
		}
		L->back = L->back->prev;
		L->back->next = NULL;
	
		L->length -= 1;
	
		freeNode(&back);
	}
}
void delete(List L){
	if (L == NULL) {
		fprintf(stderr, "List Error: calling delete(List L) on NULL List ref\n");
		exit(1);
	}	
	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling delete(List L) on empty List\n");
		exit(1);
	}
	if (index(L) < 0) {
		fprintf(stderr, "List Error: calling delete(List L) on undefined cursor\n");
		exit(1);
	}

	if (index(L) == 0) {
		deleteFront(L);
		L->cursor = NULL;
		L->index = -1;
	}	
	else if (index(L) == length(L) - 1) {
		deleteBack(L);		
		L->cursor = NULL;
		L->index = -1;
	}
	else {
		L->cursor->next->prev = L->cursor->prev;
		L->cursor->prev->next = L->cursor->next;				
		Node cursor = L->cursor;
		L->cursor = NULL;
		L->index = -1;
		L->length -= 1;
		freeNode(&cursor);
	}
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling printList(FILE *out, List L) on NULL List reference\n");
		exit(1);
	}
	Node N = L->front;
	for (int i =0; i < L->length; i++) {
		assert(N != NULL);
		fprintf(out, "%d ", N->data);
		N = N->next;
	}	
}

List copyList(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: calling copyList() on NULL List ref");
		exit(1);
	}
	List Lcpy = newList();
	int idx = index(L);
	for(moveFront(L); index(L)>=0; moveNext(L)) {
		append(Lcpy, get(L));	
	}
	for(moveFront(L); index(L)>=0; moveNext(L)) {
                if (idx == index(L)) {
			break;
		}
        }
	return Lcpy;
}
