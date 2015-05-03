#include "phillie.h"
#include "dinner.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
phillie_create(Phillie *phillie,
               const size_t id,
               const bool is_lefthanded)
{
    phillie->id = id;
    phillie->status = THINKING;
    phillie->is_lefthanded = is_lefthanded;
}

void
phillie_show(const Phillie phillie)
{
    switch (phillie.status) {
        case EATING:
            printf("E");
            break;
        case HUNGRY:
            printf("H");
            break;
        case THINKING:
            printf("T");
            break;
    }
}

void
phillie_run(Phillie *phillie)
{
    while (true) {
        phillie_wait();
        phillie_eat(phillie);
        phillie_wait();
        phillie_think(phillie);
    }
}

void
phillie_eat(Phillie *phillie)
{
    Phillie *left_phillie = get_left_phillie(*phillie);
    Phillie *right_phillie = get_right_phillie(*phillie);

    if (left_phillie->status == EATING || right_phillie->status == EATING) {
        phillie->status = HUNGRY;
        dinner_show();
        if (phillie->is_lefthanded) {
            if (left_phillie->status == EATING) {
                pthread_cond_wait(&Fork_Is_Free[get_left_fork(*phillie)],
                                  &Fork_Is_Busy[get_left_fork(*phillie)]);
            }
            if (right_phillie->status == EATING) {
                pthread_cond_wait(&Fork_Is_Free[get_right_fork(*phillie)],
                                  &Fork_Is_Busy[get_right_fork(*phillie)]);
            }
        } else {
            if (right_phillie->status == EATING) {
                pthread_cond_wait(&Fork_Is_Free[get_right_fork(*phillie)],
                                  &Fork_Is_Busy[get_right_fork(*phillie)]);
            }
            if (left_phillie->status == EATING) {
                pthread_cond_wait(&Fork_Is_Free[get_left_fork(*phillie)],
                                  &Fork_Is_Busy[get_left_fork(*phillie)]);
            }
        }
    }
    phillie->status = EATING;
    dinner_show();
}

void
phillie_think(Phillie *phillie)
{
    pthread_cond_signal(&Fork_Is_Free[get_left_fork(*phillie)]);
    pthread_cond_signal(&Fork_Is_Free[get_right_fork(*phillie)]);
    phillie->status = THINKING;
    dinner_show();
}

void
phillie_wait(void)
{
    sleep(rand() % MAX_WAITING_TIME + MIN_WAITING_TIME);
}
