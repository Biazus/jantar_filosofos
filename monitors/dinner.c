#include "dinner.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void
dinner_start(const size_t num_phillies)
{
    Phillie phillie;
	pthread_t threads[MAX_NUM_PHILLIES];

    srand(time(NULL));

    pthread_mutex_init(&Forks_Are_Being_Grabbed, NULL);
    pthread_mutex_init(&Forks_Are_Being_Dropped, NULL);
    pthread_mutex_init(&Phillie_Is_Trying_To_Eat, NULL);

	for (size_t i = 0; i != num_phillies; i++) {
		pthread_cond_init(&Fork_Is_Free[i], NULL);

        if (i % 2 == 0) {
		    phillie_create(&phillie, i, true);
        } else {
            phillie_create(&phillie, i, false);
        }

		Phillies[i] = phillie;
	}

    Num_Phillies = num_phillies;

    dinner_show();

    for (size_t i = 0; i != num_phillies; i++) {
        pthread_create(&threads[i], NULL,
                       (void *(*)(void *)) phillie_run, &Phillies[i]);
    }
}

void
dinner_show(void)
{
    for (size_t i = 0; i != Num_Phillies; i++) {
        phillie_show(Phillies[i]);
        printf(" ");
    }
    printf("\n");
}

Phillie *
get_left_phillie(const Phillie phillie)
{
    return &Phillies[(phillie.id + Num_Phillies - 1) % Num_Phillies];
}


Phillie *
get_right_phillie(const Phillie phillie)
{
   return &Phillies[(phillie.id + 1) % Num_Phillies];
}

size_t
get_left_fork(const Phillie phillie)
{
    return phillie.id;
}

size_t
get_right_fork(const Phillie phillie)
{
    return get_right_phillie(phillie)->id;
}
