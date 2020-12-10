/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2020 Luis Bandarra <luis@bandarra.pt>
 * All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

int
main(int argc, char *argv[])
{
	printf("Testing parse movement input\n");
	printf("Test 1: Empty string\tinput: ; expect: \n");
	char *str1 = "";
	char *test1 = parse_move(str1);
	if (strlen(test1) == 0) 
		printf("OK (%s)\n", test1);
	else 
		printf("NOK (%s)\n", test1);
	free(test1);

	printf("Test 2: Invalid movement\tinput: WQRTU; expect: empty string\n");
	char *str2 = "WQRTU";
	char *test2 = parse_move(str2);
	if (strlen(test2) == 0)
		printf("OK (%s)\n", test2);
	else
		printf("NOK (%s)\n", test2);
	free(test2);

	printf("Test 3: Mixed valid movement\tinput: NEDSE; expect: NESE\n");
	char *str3 = "NEDSE";
	char *test3 = parse_move(str3);
	if (strcmp("NESE", test3) == 0)
		printf("OK (%s)\n", test3);
	else
		printf("NOK (%s)\n", test3);
	free(test3);

	printf("Test 4: Small movement\tinput: NEESSO; expect: NEESSO\n");
	char *str4 = "NEESSO";
	char *test4 = parse_move(str4);
	if (strcmp("NEESSO", test4) == 0)
		printf("OK (%s)\n", test4);
	else
		printf("NOK (%s)\n", test4);
	free(test4);

	printf("Test 5: Big movement\tinput: NNNNNNNNNOOOOOOOOOOOOO; expect: NNNNNNNNNOOOOOOOOOOOOO\n");
	char *str5 = "NNNNNNNNNOOOOOOOOOOOOO";
	char *test5 = parse_move(str5);
	if (strcmp("NNNNNNNNNOOOOOOOOOOOOO", test5) == 0)
		printf("OK (%s)\n", test5);
	else
		printf("NOK (%s)\n", test5);
	free(test5);

	printf("Test 6: Bad chars\tinput: \\NE\'; expect: NE\n");
	char *str6 = "\\NE\'";
	char *test6 = parse_move(str6);
	if (strcmp("NE", test6) == 0)
		printf("OK (%s)\n", test6);
	else
		printf("NOK (%s)\n", test6);
	free(test6);

	/* measure time of call */
	clock_t t;
	double timing;
	
	int score;
	printf("\nTesting player moving\n");
	printf("Test 7: Single movement: input: N; expect: score 2\n");
	t = clock();
	score = move("N");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 2)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);

	printf("Test 8: Small movement, not resizing board: input: NESO; expect: score 4\n");
	t = clock();
	score = move("NESO");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 4)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);

	printf("Test 9: Big movement, not resizing board: input: NSNSNSNSNS; expect: score 2\n");
	t = clock();
	score = move("NSNSNSNSNS");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 2)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);

	printf("Test 10: Big movement, increase board X (negative): input: NNNNNNNNNN; expect: score 12\n");
	t = clock();
	score = move("NNNNNNNNNNN");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 12)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);

	printf("Test 11: Big movement, increase board Y (negative): input: OOOOOOOOOO; expect: score 11\n");
	t = clock();
	score = move("OOOOOOOOOO");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 11)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);

	printf("Test 12: Big movement, increase board X (positive): input: SSSSSSSSSSS; expect: score 12\n");
	t = clock();
	score = move("SSSSSSSSSSS");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 12)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);

	printf("Test 13: Big movement, increase board Y (positive): input: EEEEEEEEEEEEEEEEEEEE; expect: score 21\n");
	t = clock();
	score = move("EEEEEEEEEEEEEEEEEEEE");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 21)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);

	printf("Test 14: Big movement, increase board X and Y (positive): input: SSSSSSSSEEEEEEEEEEE; expect: score 21\n");
	t = clock();
	score = move("SSSSSSSSEEEEEEEEEEE");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 21)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);

	printf("Test 15: Big movement, increase board X and Y (negative): input: OOOOOOONNNNNNNNNNNNN; expect: score 21\n");
	t = clock();
	score = move("OOOOOOONNNNNNNNNNNNN");
	t = clock() - t;
	timing = ((double) t) / CLOCKS_PER_SEC;
	if (score == 21)
		printf("OK");
	else 
		printf("NOK");
	printf(" (%d)\trun time: %f\n\n", score, timing);


	return 0;
}

