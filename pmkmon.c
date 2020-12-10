/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2020 Luis Bandarra <luis@bandarra.pt>
 * All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int
main(int argc, char *argv[])
{
	if (argc == 1 || strcmp(argv[1], "-h") == 0) {
		usage();
		return 0;
	}
	run(argv[1]);
	
	return 0;
}

void
run(const char *arg)
{
	char *str = parse_move(arg);
	if (strlen(str) == 0) {
		printf("\"%s\" doesn\'t have a valid movement. Exiting\n", arg);
		exit(1);
	}
	printf("Moves: %s\tScore: %d\n", str, move(str));
	free(str);
}

