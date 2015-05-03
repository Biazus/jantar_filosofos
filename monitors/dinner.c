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

    if (num_phillies > 0) {
			pthread_cond_init(&Fork_Is_Free[0], NULL);
			phillie_create(&phillie, 0, false);
			Phillies[0] = phillie;

		for (size_t i = 1; i != num_phillies; i++) {
			pthread_cond_init(&Fork_Is_Free[i], NULL);
			phillie_create(&phillie, i, true);
			Phillies[i] = phillie;
		}
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
get_left_phillie(Phillie phillie)
{
    return &Phillies[(phillie.id + Num_Phillies - 1) % Num_Phillies];
}


Phillie *
get_right_phillie(Phillie phillie)
{
   return &Phillies[(phillie.id + 1) % Num_Phillies];
}

size_t
get_left_fork(Phillie phillie)
{
    return phillie.id;
}

size_t
get_right_fork(Phillie phillie)
{
    return get_right_phillie(phillie)->id;
}
