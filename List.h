/***
 * Tanvi Herwadkar
 * therwadk
 * 2023 Fall CSE101 PA2
 * List.h
 * Declares all functions for List ADT
***/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ListElement;
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

//newList()
//Returns a reference to an empty List
List newList(void); 

//freeList()
//Frees any memory allocated in the List
void freeList(List* pL); 

//Access functions -----------------------------------------------------------

//length()
//Returns the number of elements in the list L
int length(List L); 

//index()
//Returns the index of the cursor in the list. -1 if cursor is undefined
int index(List L); 

//front()
//Returns the front element of L
//Pre: length()>0
int front(List L);

//back()
//Returns back element of L.
//Pre: length()>0
int back(List L);

//get()
//Returns cursor element of L
//Pre: length()>0, index()>=0
int get(List L);

//equals()
// Returns true iff Lists A and B are in same state, false otherwise
bool equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

//clear()
//Resets L to its original empty state.
void clear(List L);

//set()
//Overwrites the cursor element’s data with x.
//Pre: length()>0, index()>=0
void set(List L, int x);

//moveFront()
// If L is non-empty, sets cursor under the front element,otherwise does nothing.
void moveFront(List L);

//moveBack()
//If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L); 

//movePrev()
//If cursor is defined and not at front, move cursor one
//step toward the front of L; if cursor is defined and at
//front, cursor becomes undefined; if cursor is undefined
//do nothing
void movePrev(List L);

//moveNext()
// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L);

//prepend()
//Insert new element into L. If L is non-empty,
//insertion takes place before front element.
void prepend(List L, int x); 

//append()
//Insert new element into L. If L is non-empty,
//insertion takes place after back element.
void append(List L, int x); 

//insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x);

//insertAfter()
//Insert new element after cursor. 
//Pre: length()>0, index()>=0
void insertAfter(List L, int x); 

//deleteFront()
//Delete the front element.
//Pre: length()>0
void deleteFront(List L);

//deleteBack()
//Delete the back element.
//Pre: length()>0
void deleteBack(List L);

//delete()
//Delete cursor element, making cursor undefined.
//Pre: length()>0, index()>=0
void delete(List L);

//printList()
//Prints to the file pointed to by out, a 
//string representation of L consisting
//of a space separated sequence of integers,
//with front on left.
void printList(FILE* out, List L);

//copyList()
//Returns a new List representing the same integer
//sequence as L. The cursor in the new list is undefined,
//regardless of the state of the cursor in L. The state
//of L is unchanged.
List copyList(List L);
