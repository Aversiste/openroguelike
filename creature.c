/*
 * Copyright (c) 2013,2018 Tristan Le Guern <tleguern@bouledef.eu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdbool.h>
#include <stdlib.h>

#include "level.h"
#include "creature.h"
#include "rng.h"

static void human_init(struct creature *);
static void goblin_init(struct creature *);

void
creature_init(struct creature *c, enum race race)
{
	c->race = race;
	c->actionpoints = 0;
	switch (race) {
	case R_HUMAN:
		human_init(c);
		break;
	case R_GOBLIN:
		goblin_init(c);
		break;
	case R__MAX:
	default:
		return; /* XXX error in some way */
	}
}

void
creature_place_randomly(struct creature *c, struct level *l)
{
	int y, x;

	do {
		y = rng_rand_uniform(MAXROWS);
		x = rng_rand_uniform(MAXCOLS);
		if (tile_is_empty(&(l->tile[y][x]))) {
			c->x = x;
			c->y = y;
			l->tile[y][x].creature = c;
			break;
		}
	} while (1);
}

void
creature_place_at_stair(struct creature *c, struct level *l, bool up)
{
	int y, x;

	for (y = 0; y < MAXROWS; ++y)
		for (x = 0; x < MAXCOLS; ++x)
			if ((l->tile[y][x].type == T_UPSTAIR && up)
			    || (l->tile[y][x].type == T_DOWNSTAIR && !up)) {
				c->x = x;
				c->y = y;
				l->tile[y][x].creature = c;
				return;
			}
}

int
creature_move(struct creature *c, struct level *l, int row, int col)
{
	if (c->y + row < 0 || c->y + row >= MAXROWS) {
		return(-1);
	}
	if (c->x + col < 0 || c->x + col >= MAXCOLS) {
		return(-1);
	}
	if (tile_is_wall(&(l->tile[c->y + row][c->x + col]))) {
		return(-1);
	}
	if (tile_is_empty(&(l->tile[c->y + row][c->x + col])) == false) {
		return(-1);
	}
	l->tile[c->y][c->x].creature = NULL;
	c->y += row;
	c->x += col;
	l->tile[c->y][c->x].creature = c;
	return(0);
}

int
creature_move_left(struct creature *c, struct level* l)
{
	return(creature_move(c, l, 0, -1));
}

int
creature_move_down(struct creature *c, struct level* l)
{
	return(creature_move(c, l, 1, 0));
}

int
creature_move_up(struct creature *c, struct level* l)
{
	return(creature_move(c, l, -1, 0));
}

int
creature_move_right(struct creature *c, struct level* l)
{
	return(creature_move(c, l, 0, 1));
}

int
creature_move_upleft(struct creature *c, struct level* l)
{
	return(creature_move(c, l, -1, -1));
}

int
creature_move_downleft(struct creature *c, struct level* l)
{
	return(creature_move(c, l, 1, -1));
}

int
creature_move_upright(struct creature *c, struct level* l)
{
	return(creature_move(c, l, -1, 1));
}

int
creature_move_downright(struct creature *c, struct level* l)
{
	return(creature_move(c, l, 1, 1));
}

int
creature_climb_upstair(struct creature *c, struct level *f, struct level *t)
{
	if (f->tile[c->y][c->x].type != T_UPSTAIR) {
		return(-1);
	}
	f->tile[c->y][c->x].creature = NULL;
	creature_place_at_stair(c, t, false);
	return(0);
}

int
creature_climb_downstair(struct creature *c, struct level *f, struct level *t)
{
	if (f->tile[c->y][c->x].type != T_DOWNSTAIR) {
		return(-1);
	}
	f->tile[c->y][c->x].creature = NULL;
	creature_place_at_stair(c, t, true);
	return(0);
}

int
creature_rest(struct creature *c)
{
	(void)c;
	return(0);
}

void
creature_do_something(struct creature *c, struct level *l)
{
	uint32_t choice;

	choice = rng_rand_uniform(8);
	switch (choice) {
	case 0:
		creature_move_left(c, l);
		break;
	case 1:
		creature_move_down(c, l);
		break;
	case 2:
		creature_move_up(c, l);
		break;
	case 3:
		creature_move_right(c, l);
		break;
	case 4:
		creature_move_upleft(c, l);
		break;
	case 5:
		creature_move_downleft(c, l);
		break;
	case 6:
		creature_move_upright(c, l);
		break;
	case 7:
		creature_move_downright(c, l);
		break;
	}
}

static void
human_init(struct creature *c)
{
	c->speed = 5;
}

static void
goblin_init(struct creature *c)
{
	c->speed = 7;
}

