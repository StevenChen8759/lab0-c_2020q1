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

    /* Return false while q is NULL */
    if (q == NULL)
        return false;

    /* Allocate the memory space */
    newh = (list_ele_t *) malloc(sizeof(list_ele_t));

    /* Malloc return cases handling (allocate newh) */
    if (newh != NULL) {
        /* Allocate success case */

        /* Allocate the space of string and copy it to that space,
           including end-of-string '\0' set and null allocation check */
        newh->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));

        /* Malloc return cases handling (allocate newh->value) */
        if (newh->value != NULL) {
            /* Allocate success case(newh->value) */

            memset(newh->value, '\0', sizeof(char) * (strlen(s) + 1));
            strncpy(newh->value, s, strlen(s));
        } else {
            /* Allocate fail case(newh->value) */

            free(newh);  // Don't forget to free allocated space(newh) while
                         // failed
                         // allocation
            return false;
        }

        /* Do pointer and parameter edition (queue insert head) */
        newh->next = q->head;
        q->head = newh;
        if (q->tail == NULL)
            q->tail = newh;  // Initialize case
        q->size++;

    } else {
        return false;  // Allocate fail case(newh), return false
    }

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

    /* Return false while q is NULL */
    if (q == NULL)
        return false;

    /* Allocate the memory space iff q != null */
    newt = (list_ele_t *) malloc(sizeof(list_ele_t));

    /* Malloc returns cases handling... */
    if (newt != NULL) {
        /* Allocate the space of string and copy it to that space,
           including end-of-string '\0' set and null allocation check */
        newt->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));

        /* Return false while string space allocation failed... */
        if (newt->value != NULL) {
            memset(newt->value, '\0', sizeof(char) * (strlen(s) + 1));
            strncpy(newt->value, s, strlen(s));
        } else {
            free(newt);  // Don't forget to free allocated space while failed
                         // allocation
            return false;
        }

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

    } else {
        return false;  // Failed to allocated newl, return false
    }

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
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */

    /* Declare operating pointer on nodes */
    list_ele_t *ptr;

    /* Reject q is NULL and q->head is NULL cases */
    if (q == NULL || q->head == NULL)
        return false;

    /* Operating Pointer Assignment */
    ptr = q->head;

    /* Copy string to *sp */
    if (sp != NULL) {
        strncpy(sp, ptr->value, bufsize);
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
