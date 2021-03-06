#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    if (q != NULL) {
        /* Points to NULL initially */
        q->head = NULL;
        q->tail = NULL;
        q->size = 0; /* set size 0 initially */
    }

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *ptr;  // Declare operating pointer

    /* check if q is NULL or not */
    if (q != NULL) {
        ptr = q->head;
    } else
        return;

    /* Free list nodes and its string space*/
    while (ptr != NULL) {
        free(ptr->value);
        ptr = ptr->next;
        free(q->head);
        q->head = ptr;
    }

    free(q); /* Free queue structure space */
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /*  Local variable declaration */
    list_ele_t *newh;
    size_t len_s;

    /* Return false while q is NULL */
    if (q == NULL)
        return false;

    /* Allocate the memory space */
    newh = (list_ele_t *) malloc(sizeof(list_ele_t));

    /* Failed to allocate node space, retrun false*/
    if (newh == NULL)
        return false;

    /* Assign length of string s */
    len_s = strlen(s);

    /* Allocate the space of string, include end-of-string '\0' */
    newh->value = (char *) malloc(sizeof(char) * (len_s + 1));

    /* Failed to allocate string space, free allocated node and return false */
    if (newh->value == NULL) {
        free(newh);
        return false;
    }

    /* Copy the string */
    strncpy(newh->value, s, len_s);
    *(newh->value + len_s) = '\0';  // Set end-of-string

    /* Do pointer and parameter edition (queue insert head) */
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL)
        q->tail = newh;  // Initialize case
    q->size++;

    return true;  // All allocation correct, return true
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /*  Local variable declaration */
    list_ele_t *newt;
    size_t len_s;

    /* Return false while q is NULL */
    if (q == NULL)
        return false;

    /* Allocate the memory space iff q != null */
    newt = (list_ele_t *) malloc(sizeof(list_ele_t));

    /* Allocate the memory space failed, return false*/
    if (newt == NULL)
        return false;

    /* Assign length of string*/
    len_s = strlen(s);

    /* Allocate the space of string */
    newt->value = (char *) malloc(sizeof(char) * (len_s + 1));

    /* Allocate the space of string failed, free node space and return false */
    if (newt->value == NULL) {
        free(newt);
        return false;
    }

    /* Copy string */
    strncpy(newt->value, s, len_s);
    *(newt->value + len_s) = '\0';  // Edit end-of-string

    /* Do pointer and parameter edition (insert tail in queue)*/
    if (q->tail == NULL) {  // Initialize case
        q->head = newt;
    } else {
        q->tail->next = newt;  // Move tail pointer
    }
    q->tail = newt;
    /* Assign newl->next to NULL to avoid illegal memory access.
       (Because malloc() inital value may not be zero!) */
    newt->next = NULL;
    q->size++;

    return true;  // All correct, return true
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* Declare operating pointer on nodes */
    list_ele_t *ptr;
    // size_t len_qs;

    /* Reject q is NULL and q->head is NULL cases */
    if (q == NULL || q->head == NULL)
        return false;

    /* Operating Pointer Assignment */
    ptr = q->head;

    /* Copy string to *sp */
    if (sp != NULL) {
        strncpy(sp, ptr->value, bufsize);
        *(sp + bufsize - 1) = '\0';  // Edit end-of-string
    }

    /* Edit pointer and free node space */
    q->head = q->head->next;
    free(ptr->value);
    free(ptr);
    q->size--;
    if (q->size == 0) {
        q->tail = NULL;
    }
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q != NULL)
        return q->size;
    else
        return 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* Operating pointer declaration */
    list_ele_t *prev, *curr, *nex;

    /* Reject null pointer case */
    if (q == NULL || q->head == NULL)
        return;

    /* Size is 1, return */
    if (q->size == 1)
        return;

    /* Operating pointer initialize */
    curr = q->head;
    nex = q->head->next;
    prev = NULL;

    /* Do list reverse */
    while (curr != NULL) {
        curr->next = prev;
        prev = curr;
        curr = nex;
        /* To Avoid null pointer dereference,
           Add NULL pointer judge for pointer nex */
        if (nex != NULL)
            nex = nex->next;
    }

    /* Re-assign head and tail pointer */
    q->tail = q->head;
    q->head = prev;
}

/*
 * Recursive merge sort sub-function
 * Compare and merge
 */
list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    // int cnt = 0;
    size_t len_l1, len_l2;

    // merge with recursive
    if (!l2)
        return l1;
    if (!l1)
        return l2;

    // Fetch string length
    len_l1 = strlen(l1->value);
    len_l2 = strlen(l2->value);

    // Use maximum length
    if (len_l1 < len_l2)
        len_l1 = len_l2;

    if (strncmp(l1->value, l2->value, len_l1) <= 0) {
        // l1 is smaller than or equal to l2
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        // l1 is bigger than l2
        l2->next = merge(l1, l2->next);
        return l2;
    }
}

/*
 *  Merge sort sub-function
 *  Merge bigger list...
 */
list_ele_t *mergeSortList(list_ele_t *head)
{
    // merge sort
    if (!head || !head->next)
        return head;

    list_ele_t *fast = head->next;
    list_ele_t *slow = head;

    // split list
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;

    // sort each list
    list_ele_t *l1 = mergeSortList(head);
    list_ele_t *l2 = mergeSortList(fast);

    // merge sorted l1 and sorted l2
    return merge(l1, l2);
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* Sort list by [Merge Sort] */
    list_ele_t *ptr;

    /* Reject q is NULL case  */
    if (q == NULL)
        return;

    /* Return directly while queue has only 1 element or less than 1 */
    if (q->size <= 1)
        return;

    /* Call Sorting function */
    q->head = mergeSortList(q->head);

    /* Re-assign tail pointer */
    ptr = q->head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    q->tail = ptr;
}
