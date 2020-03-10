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

    /* TODO: May need to do something to solve NULL malloc return! */

    if (q == NULL) {
        printf("STCH HINT!!! -> q_new() malloc function return null!!!!! \n");
    } else {
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
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */

    list_ele_t *ptr;  // Declare operating pointer

    if (q != NULL) {
        ptr = q->head;
    } else
        return;

    /* Free nodes and string space*/
    while (ptr != NULL) {
        free(ptr->value);
        ptr = ptr->next;
        free(q->head);
        q->head = ptr;
    }

    free(q);
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

    /* Allocate the memory space iff q != null */
    newh = malloc(sizeof(list_ele_t));

    /* Malloc returns cases handling... */
    if (newh != NULL) {
        /* Allocate the space of string and copy it to that space,
           including end-of-string '\0' set and null allocation check */
        newh->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));

        /* Return false while string space allocation failed... */
        if (newh->value != NULL) {
            memset(newh->value, '\0', sizeof(char) * (strlen(s) + 1));
            strncpy(newh->value, s, strlen(s));
        } else {
            free(newh);  // Don't forget to free allocated space while failed
                         // allocation
            return false;
        }
        /* Do pointer and parameter edition */
        newh->next = q->head;
        q->head = newh;
        q->size++;

    } else {
        return false;  // Failed to allocated newh, return false
    }

    return true;  // All correct, return true
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
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return false;
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
    q->head = q->head->next;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
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
