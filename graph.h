//
// Created by kacper on 26.09.16.
//


#ifndef SNAKE_GRAPH_H
#define SNAKE_GRAPH_H

#include "sprite.h"

void showGame(int height, int width, point_t startpoint);
void showPoints(sprite_t *sprite, WINDOW* my_win);
void showBomb(point_t bomb, WINDOW* my_win);
void showWin(sprite_t *sprite, point_t bomb, WINDOW* my_win);
#endif //SNAKE_GRAPH_H

