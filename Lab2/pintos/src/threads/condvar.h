#ifndef CONDVAR_H
#define CONDVAR_H

#include "threads/semaphore.h"
#include "threads/lock.h"

/* Condition variable */
struct condvar {
    struct list waiters; /* List of semaphore_elems */
};

void condvar_init(struct condvar *);
void condvar_wait(struct condvar *, struct lock *);
void condvar_signal(struct condvar *, struct lock *);
void condvar_broadcast(struct condvar *, struct lock *);

bool condvar_compare(const struct list_elem *list1, const struct list_elem *list2, void *aux);

#endif /* UCSC CSE130 */
