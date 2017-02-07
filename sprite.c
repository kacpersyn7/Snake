//
// Created by kacper on 26.09.16.
//

#include "sprite.h"
int addStart(sprite_t *sprite, point_t startpoint)
{
    snake_t *new;
    new = malloc(sizeof(*new));
    if(new == NULL)
    {
        printf("BLAD PAMIECI!\n");
        return 1;
    }
    new->position = startpoint;
    sprite->start = RIGHT;
    sprite->end = RIGHT;
    new->next_s = NULL;
    sprite->m_head = new;
    sprite->m_end = new;
    /*addEnd(sprite);
    addEnd(sprite);*/
    return 0;
}
int addEnd(sprite_t *sprite)
{
    snake_t *new;
    new = malloc(sizeof(*new));
    snake_t *pointer = sprite->m_end;
    if(!new)
    {
        printf("BLAD PAMIECI!\n");
        return 1;
    }
    new->position = pointer->position;
    switch (sprite->end)
    {
        case UPS:
            (new->position.y) = (pointer->position.y) - 1;
            break;
        case DOWN:
            (new->position.y) = (pointer->position.y) + 1;
            break;
        case LEFT:
            (new->position.x) = (pointer->position.x) + 1;
            break;
        case RIGHT:
            (new->position.x) = (pointer->position.x) - 1;
            break;
    }
    new->next_s = NULL;
    pointer->next_s = new;
    sprite->m_end = new;
    return 0;
}
void updatePosition(sprite_t *sprite)
{
    snake_t *pointer;
    pointer = sprite->m_head;
    point_t tmp1, tmp2;
    tmp2 = pointer->position;
    while(pointer->next_s != NULL)
    {
        tmp1 = pointer->next_s->position;
        pointer->next_s->position = tmp2;
        tmp2 = tmp1;
        pointer = pointer->next_s;
    }
    switch (sprite->start)
    {

        case DOWN:
            (sprite->m_head->position.y)--;
            break;
        case UPS:
            (sprite->m_head->position.y)++;
            break;
        case LEFT:
            (sprite->m_head->position.x)--;
            break;
        case RIGHT:
            (sprite->m_head->position.x)++;
            break;
    }
    sprite->end = calculateDirection(pointer->position, sprite->m_end->position);

}
direction_t calculateDirection(point_t first, point_t second)
{
    int diff_x = second.x - first.x;
    int diff_y = second.y - first.y;
    direction_t turn;
    if(diff_x == 0)
    {
        if(diff_y == 1)
            turn = UPS;
        else
            turn = DOWN;
    }
    else if (diff_y == 0)
    {
        if(diff_x == 1)
            turn = RIGHT;
        else
            turn = LEFT;
    }
    return turn;
}
void changeStartDirection(sprite_t *sprite, direction_t turn)
{
    direction_t m_turn = sprite->start;
    if(!((RIGHT == turn && LEFT == m_turn) || (LEFT == turn && RIGHT == m_turn)
         || (UPS == turn && DOWN == m_turn) || (DOWN == turn && UPS == m_turn)))
        sprite->start = turn;
}
void deleteAll(sprite_t *sprite)
{
    snake_t *tmp;
    while(sprite->m_head != NULL)
    {
        tmp = (sprite->m_head);
        (sprite->m_head) = tmp->next_s;
        free(tmp);
    }
}
bool checkError(sprite_t sprite)
{
    bool error = false;
    point_t point = (sprite.m_head)->position;
    snake_t *pointer = (sprite.m_head)->next_s;
    if (!(sprite.m_head)->position.x || !(sprite.m_head)->position.y || M_COLS-1 == sprite.m_head->position.x
            || M_ROWS-1 == (sprite.m_head)->position.y)
        error = true;
    else
        while (pointer != NULL)
        {
            if(point.x == pointer->position.x && point.y == pointer->position.y)
            {
                error = true;
                break;
            }
            pointer = pointer->next_s;
        }
    return error;
}
int randome(int min, int max)
{
    srand(time(NULL));
    int tmp;
    if (max>=min)
        max-= min;
    else
    {
        tmp= min - max;
        min= max;
        max= tmp;
    }
    return max ? (rand() % max + min) : min;
}
bool checkContact(sprite_t sprite, point_t *bomb, int n)
{
    snake_t *pointer = sprite.m_head;
    if (pointer->position.x == bomb->x && pointer->position.y == bomb->y)
    {
        int temp;
        point_t *tab = malloc(n * sizeof(point_t));
        int k = 0;
        bool error = true;
        for (int i = 1; i < M_ROWS-1; ++i){
            for (int j = 1; j < M_COLS-1; ++j)
            {
                pointer = sprite.m_head;
                error = 1;
                while (pointer != NULL && error)
                {
                    if (pointer->position.x == i && pointer->position.y == j)
                        error = 0;
                    if(error)
                        pointer = pointer->next_s;
                }
                if (error)
                {
                    tab[k].x = i;
                    tab[k].y = j;
                    k++;
                }
             }
        }
        srand(time(NULL));
        temp = rand() % n;
        *bomb = tab[temp];
        free(tab);
        return true;
    }
    else
        return false;
}
