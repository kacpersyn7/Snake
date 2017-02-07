//
// Created by kacper on 26.09.16.
//

#ifndef SNAKE_SPRITE_H
#define SNAKE_SPRITE_H
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#define M_COLS (20)
#define M_ROWS (20)
typedef enum dir {
    DOWN, UPS, LEFT, RIGHT} direction_t;
typedef struct point
{
    int x;
    int y;
} point_t;
typedef struct snake
{
    point_t position;
    struct snake *next_s;
} snake_t;
typedef struct sprite
{
    direction_t start;
    direction_t end;
    snake_t *m_head;
    snake_t *m_end;
    //int length;
} sprite_t;

int addStart(sprite_t *sprite, point_t startpoint);
int addEnd(sprite_t *sprite);
void updatePosition(sprite_t *sprite);
direction_t calculateDirection(point_t first, point_t second);
void deleteAll(sprite_t *sprite);
bool checkError(sprite_t sprite);
void changeStartDirection(sprite_t *sprite, direction_t turn);
int randome(int min, int max);
bool checkContact(sprite_t sprite, point_t *bomb, int n);
#endif //SNAKE_SPRITE_H

