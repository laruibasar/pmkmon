/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2020 Luis Bandarra <luis@bandarra.pt>
 * All rights reserved.
 */


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
void	run(const char *);
void	interactive(void);
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

