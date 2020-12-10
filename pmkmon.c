/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2020 Luis Bandarra <luis@bandarra.pt>
 * All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct board {
	int	**arr; /* we want a (dynamic) bidimensional array */
	size_t	  size_x;
	size_t	  size_y;
};

struct game {
	struct board	*board; 
	int		 player_x;
	int		 player_y;
};

void	usage(void);
char*	parse_move(const char*);
int	move(const char*);
int	move_player(struct game*, int, int);

#define NORTH	-1
#define SOUTH	 1
#define EAST	 1
#define WEST	-1

#define BOARD_SIZE 9
#define PLAYER_START_X 4
#define PLAYER_START_Y 4

int
main(int argc, char *argv[])
{
	if (argc == 1 || strcmp(argv[1], "-h") == 0) {
		usage();
		return 0;
	}

	if (strcmp(argv[1], "-i") == 0) {
		return 0;
	}
	
	char *str = parse_move(argv[1]);
	printf("\nMoves: %s\tScore: %d\n", str, move(str));

	free(str);
	
	return 0;
}

/* 
 * Show help to user
 */
void
usage()
{
	printf("usage: \tpmkmon -h\n");
	printf("\tpmkmon -i\n");
	printf("\tpmkmon directions\n\n");
	printf("\t-h: show this text\n");
	printf("\t-i: enter interactive mode\n");
	printf("\tdirections: N S E O\n");
	printf("\texample: pmkmon NNES\n");
}

/*
 * Parse input string with movement to a valid string with movements and 
 * correct terminated.
 *
 * Only valid movements are:
 *  - N(orte)
 *  - S(ul)
 *  - E(ste)
 *  - O(este)
 *
 *  All others are ignore and considered as staying in place.
 */
char*
parse_move(const char* movement)
{
	size_t size = 0;
	char *dst;

	if ((dst = malloc(strlen(movement) + 1)) == NULL) {
		printf("Out of memory");
		exit(1);
	}

	const char* m = movement;
	char* n = dst;
	while (*m != 0) {
		if (*m == 'N' || *m == 'S' || *m == 'E' || *m == 'O') {
			*n = *m;
			n++;
			++size;
		}
		m++;
	}
	*n = 0; /* terminate string */

	return dst;
}

/* 
 * Read movements from a valid string and count player new pokemons catched.
 *
 * This function create our game and board, filling the world available with
 * pokemons to catch.
 * In the specification, our world is unlimited, there is no such thing,
 * so for simulation, we create a small board and check if we need to expand
 * our current board. This can be a problem, because for that we need to use
 * the heap and not the stack for the board arrays.
 *
 * This is the worst problem, because we need to reallocate new array,
 * point to it, and populate with our already catch pokemons. This means:
 * 
 * We suffer some performance issues here and must make sure about memory
 * management.
 *
 */
int
move(const char *move)
{
	struct board board;
	struct game game;
	int score = 1; /* we allways catch the one were we start */

	/* malloc for 1 array to store the other, calloc to 0: penalties!
	 * on a bright note, most other langs do something like this when stack
	 * is not an option
	 */
	if ((board.arr = (int **)malloc(BOARD_SIZE * sizeof(int *))) == NULL) {
		printf("Out of memory\n");
		exit(1);
	}
	for (int i = 0; i < BOARD_SIZE; i++) {
		if ((board.arr[i] = (int *)calloc(BOARD_SIZE, sizeof(int))) == NULL) {
			printf("Out of memory\n");
			exit(1);
		}
	}

	board.size_x = BOARD_SIZE;
	board.size_y = BOARD_SIZE;

	game.board = &board;
	game.player_x = PLAYER_START_X;
	game.player_y = PLAYER_START_Y;

	/* place player in board and catch pokemon */
	game.board->arr[game.player_x][game.player_y] = 1;

	const char *c = move;
	while (*c != 0) {
		switch (*c) {
			case 'N':
				score += move_player(&game, NORTH, 0);
				break;
			case 'S':
				score += move_player(&game, SOUTH, 0);
				break;
			case 'E':
				score += move_player(&game, 0, EAST);
				break;
			case 'O':
				score += move_player(&game, 0, WEST);
				break;
		}
		++c;
	}

	/* clear bidimensional array */
	for (int i = 0; i < board.size_x; i++)
		free(board.arr[i]);

	free(board.arr);
	
	return score;
}

/*
 * Move player in board, returning pokemon catch or not
 */
int
move_player(struct game *game, int x, int y)
{
	int score = 0;
	game->player_x += x;
	game->player_y += y;

	/* set new board and adjust player position */
	if (game->player_x < 0 || game->player_x > game->board->size_x - 1) {
		size_t new_size_x = game->board->size_x * 2;
		int **new_arr_x = (int **) calloc(new_size_x, sizeof(int *));
		if (new_arr_x == NULL) {
			printf("Out of memory\n");
			exit(1);
		}

		if (game->player_x < 0) {
			int i = game->board->size_x;
			int j = 0;
			for (; i < game->board->size_x; i++, j++)
				new_arr_x[i] = game->board->arr[j];

			free(game->board->arr);
			game->board->arr = new_arr_x;

			for (i = 0; i < game->board->size_x; i++) {
				int *new_y = (int *) calloc(game->board->size_y,
						sizeof(int));

				if (new_y == NULL) {
					printf("Out of memory\n");
					exit(1);
				}

				game->board->arr[i] = new_y;
			}
		} else {
			for (int i = 0; i < game->board->size_x; i++)
				new_arr_x[i] = game->board->arr[i];
	
			free(game->board->arr);
			game->board->arr = new_arr_x;

			for (int i = game->board->size_x; i < new_size_x; i++) {
				game->board->arr[i] = (int *) calloc(
						game->board->size_y,
						sizeof(int));

				if (game->board->arr[i] == NULL) {
					printf("Out of memory\n");
					exit(1);
				}
			}
		}
		game->board->size_x = new_size_x;
	}

	if (game->player_y < 0) {
		size_t new_size_y = game->board->size_y * 2;

		for (int i = 0; i < game->board->size_x; i++) {
			int *new_arr_y = (int *) calloc(new_size_y,
					sizeof(int));
			if (new_arr_y == NULL) {
				printf("Out of memory\n");
				exit(1);
			}

			for (int j = new_size_y - 1; j > game->board->size_y - 1; j--)
				new_arr_y[j] = game->board->arr[i][j];

			free(game->board->arr[i]);
			game->board->arr[i] = new_arr_y;
		}

		/* we translate the player position */
		game->player_y = game->board->size_y - 1; 
		game->board->size_y = new_size_y;
	}

	if (game->player_y > game->board->size_y - 1) {
		size_t new_size_y = game->board->size_y * 2;
		
		for (int i = 0; i < game->board->size_x; i++) {
			int *new_arr_y = (int *) calloc(new_size_y,
					sizeof(int));
			if (new_arr_y == NULL) {
				printf("Out of memory\n");
				exit(1);
			}

			for (int j = 0; j < game->board->size_y; j++)
				new_arr_y[j] = game->board->arr[i][j];

			free(game->board->arr[i]);
			game->board->arr[i] = new_arr_y;
		}
		game->board->size_y = new_size_y;
	}

	/* lets score */
	if (game->board->arr[game->player_x][game->player_y] == 0) {
		score++;
		game->board->arr[game->player_x][game->player_y] = 1;
	}
 
	return score;
}
