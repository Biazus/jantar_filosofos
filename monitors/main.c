#include "dinner.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc,
     char **argv)
{
	long int num_phillies;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s NUMBER-OF-PHILOSOPHERS\n", argv[0]);
		return 1;
	}

    num_phillies = strtol(argv[1], NULL, 0);
    dinner_start(num_phillies);

	while(true) {
		;
	}

    return 0;
}
