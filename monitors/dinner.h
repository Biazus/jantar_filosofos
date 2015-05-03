#ifndef DINNER_H
#define DINNER_H

#include "phillie.h"
#include <pthread.h>
#include <stddef.h>

#define MAX_NUM_PHILLIES 127

Phillie Phillies[MAX_NUM_PHILLIES];
size_t Num_Phillies;

pthread_cond_t Fork_Is_Free[MAX_NUM_PHILLIES];
pthread_mutex_t Fork_Is_Busy[MAX_NUM_PHILLIES];

void
dinner_start(const size_t num_phillies);

void
dinner_show(void);

Phillie *
get_left_phillie(Phillie phillie);

Phillie *
get_right_phillie(Phillie phillie);

size_t
get_left_fork(Phillie phillie);

size_t
get_right_fork(Phillie phillie);

#endif
