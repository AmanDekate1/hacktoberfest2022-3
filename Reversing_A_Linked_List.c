#include <stdio.h>
#include <stdlib.h> // for 'malloc'
#include <limits.h> // for 'INT_MIN' macro

struct Node {
    int data;
    struct Node *next;
}*first = NULL; // this is a global pointer

void create(int A[], int n) {
    struct Node *t, *last;
    first = (struct Node *)malloc(sizeof(struct Node));
    first->data = A[0];
    first->next = NULL;
    last = first;

    for (int i = 1; i < n; i++) {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

// we can also pass the parameter by value since we are not modifying it
// 'p' is a copy of 'first' pointer.
void display(struct Node *p) {

    // Iterate over the linked list
    while (p != NULL) { // same as 'while (p)'
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


// displays the linked list data in reverse order
// 'p' is a copy of 'first' pointer.
// Time Complexity: O(n)
// Space Complexity: O(n)
void revRecDisplay(struct Node *p) {
    if (p != NULL) { // same as 'if (p)'
        revRecDisplay(p->next);
        printf("%d ", p->data);
    }
}

// counts the number of nodes in the linked list.
// 'p' is a copy of 'first' pointer.
// Time Complexity: O(n)
// Space Complexity: O(1)
int count(struct Node *p) {
    int l = 0; // length is initially zero
    while (p) { // same as 'while (p != NULL)'
        l++;
        p = p->next;
    }
    return l; // return the length
}

// sums up all of the elements in the linked list
// 'p' is a copy of 'first' pointer.
// Time Complexity: O(n)
// Space Complexity: O(1)
int sum(struct Node *p) {
    int s = 0;
    while (p) { // same as 'while (p != NULL)'
        s += p->data;
        p = p->next;
    }
    return s;
}

// Linear Search on a linked list
struct Node* linearSearch(struct Node *p, int key) {
    while (p) {
        if (key == p->data)
            return p;
        p = p->next;
    }
    return NULL;
}


// Linear Search on a linked list w/ 'Move to head'
struct Node* improvedLinearSearch(struct Node *p, int key) {
    struct Node *q = NULL; // a tail pointer which will follow 'p'
    while(p) {
        if (key == p->data) {
            q->next = p->next;
            p->next = first;
            first = p;
            return p;
        }
        q = p;
        p = p->next;
    }
    return NULL;
}

// Time Complexity: O(n)
void insert(struct Node *p, int index, int x) {

    // check if the index is valid
    if (index < 0 || index > count(p))
        return;

    struct Node *t = (struct Node *)malloc(sizeof(struct Node)); //temp
    t->data = x;

    //Now we need to link the new node 't' in the linked list
    if (index == 0) { // if '0', insert before 'first' node
        t->next = first;
        first = t;
    }
    else {
        // move pointer 'p' to correct position
        for (int i = 0; i < index-1; i++)
            p = p->next;
        t->next = p->next;
        p->next = t;
    }
}

// Time Complexity: O(n)
void sortedInsert(struct Node *p, int x) {

    struct Node *q = NULL; // tail pointer which will follow 'p'
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;

    if (first == NULL) // if linked list is empty
        first = t;
    else {
        while (p && p->data < x) {
            q = p;
            p = p->next;
        }
        if (p == first) {
            t->next = first;
            first = t;
        }
        else {
            t->next = q->next;
            q->next = t;
        }
    }
}

// Time Complexity: O(n)
// returns the data of the deleted Node
// index start at 1
int Delete(struct Node *p, int index) {
    struct Node *q = NULL; // tail pointer
    int x = -1;

    // check if the index is valid
    if (index < 1 || index > count(p))
        return -1;

    // if we want to delete the first node in LL
    if (index == 1) {
        first = first->next;
        x = p->data;
        free(p); // deleting the first Node
        return x;
    }
    else {
        for (int i = 0; i < index-1; i++) {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        x = p->data;
        free(p); // deleting the first Node
        return x;
    }
}

// 'int' because C does not support 'bool'
// Time Complexity: O(n)
int isSorted(struct Node *p) {
    int x = INT_MIN; // 'x' will hold the previous Node's data

    while(p) { // while p is not null
        if (p->data < x)
            return 0;
        x = p->data;
        p = p->next;
    }
    return 1;
}

// Time Complexity: O(n)
// In this function, p will be the tail pointer
void removeDuplicates(struct Node *p) {
    struct Node *q = p->next;

    while(q) {
        if (p->data != q->data) {
            p = q;
            q = q->next;
        }
        else {
            p->next = q->next;
            free (q);
            q = p->next;
        }
    }
}


// Method 1 of Reverse: Reversing the links of the LL
// NOTE: This is the recommended way of reversing a LL
void reverse2(struct Node *p) {

    struct Node *q = NULL, *r = NULL;

    while(p) {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    first = q;
}

// Method 2 of Reverse: Reversing the links of the LL using Recursion
void reverse3(struct Node *q, struct Node *p) {
    if(p) {
        reverse3(p, p->next);
        p->next = q;
    }
    else {
        first = q;
    }
}

int main() {
    int A[] = {5,9,10,20,30,50};
    create(A, 6);
    display(first);
    reverse3(NULL,first);
    display(first);

    return 0;
}
