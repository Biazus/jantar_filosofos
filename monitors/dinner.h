#ifndef DINNER_H
#define DINNER_H

#include "phillie.h"
#include <pthread.h>
#include <stddef.h>

#define MAX_NUM_PHILLIES 127

Phillie Phillies[MAX_NUM_PHILLIES];
size_t Num_Phillies;

pthread_cond_t Fork_Is_Free[MAX_NUM_PHILLIES];
pthread_mutex_t Phillie_Is_Trying_To_Eat;
pthread_mutex_t Forks_Are_Being_Grabbed;
pthread_mutex_t Forks_Are_Being_Dropped;

void
dinner_start(const size_t num_phillies);

void
dinner_show(void);

Phillie *
get_left_phillie(const Phillie phillie);

Phillie *
get_right_phillie(const Phillie phillie);

size_t
get_left_fork(const Phillie phillie);

size_t
get_right_fork(const Phillie phillie);

#endif
