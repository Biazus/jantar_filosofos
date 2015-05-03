#ifndef PHILLIE_H
#define PHILLIE_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_WAITING_TIME 10
#define MIN_WAITING_TIME 1

typedef enum {
    EATING,
    HUNGRY,
    THINKING
} Status;

typedef struct phillie {
    size_t id;
    Status status;
    bool is_lefthanded;
} Phillie;

void
phillie_create(Phillie *phillie,
               const size_t id,
               const bool is_lefthanded);

void
phillie_show(const Phillie phillie);

void
phillie_run(Phillie *phillie);

void
phillie_eat(Phillie *phillie);

void
phillie_think(Phillie *phillie);

void
phillie_wait(void);

#endif
