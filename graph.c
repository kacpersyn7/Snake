//
// Created by kacper on 26.09.16.
//


#include "graph.h"

void showGame(int height, int width, point_t start)
{
    int DELAY = 100;
    point_t some = {5,1};
    sprite_t snake;
    unsigned int score = 0;
    addStart(&snake, start);
    WINDOW *win;
    WINDOW *menu;
    WINDOW *text;
    initscr();
    cbreak();
    noecho();
    start_color();
    bool flag = false;
    init_pair(4, COLOR_BLUE, COLOR_GREEN);
    init_pair(5, COLOR_BLUE, COLOR_MAGENTA);
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    win = newwin(height, width, starty, startx);
    menu = newwin(10,15,starty,startx + width);
    text = newwin(10,20,starty,startx - width);
    wrefresh(text);
    wrefresh(win);
    wrefresh(menu);
    mvwprintw(text,1,1,"sterowanie: wsad\n"
                       "k by zakonczyc\n"
                       "zmiana predkosci:u,j");
    wrefresh(text);
    char ch;
    do
    {
        mvwprintw(menu,1,1,"score:%d",score);
        wrefresh(menu);
        if(flag)
            addEnd(&snake);
        flag = false;
        wtimeout(text,DELAY);
        ch = wgetch(text);
        switch (ch)
        {
            case 'w': 
                changeStartDirection(&snake, DOWN);
                break;
            case 's':  
                changeStartDirection(&snake, UPS);
                break;
            case 'a': 
                changeStartDirection(&snake, LEFT);
                break;
            case 'd': 
                changeStartDirection(&snake, RIGHT);
		        break;
            case 'u': 
                DELAY-=10;
                break;
            case 'j': 
                DELAY+=10;
                break;
            default:
                break;
        }
        updatePosition(&snake);
        if(checkContact(snake,&some,(M_ROWS-2)*(M_COLS-2) - 1 - score))
        {
            ++score;
            flag = true;
        }
        if(checkError(snake))
        {
            wclear(menu);
            deleteAll(&snake);
            addStart(&snake, start);
            score = 0;
        }
        showWin(&snake,some,win);
    }
    while(ch != 'k');
    deleteAll(&snake);
    delwin(text);
    delwin(menu);
    delwin(win);
    endwin();
}
void showPoints(sprite_t *sprite, WINDOW* my_win)
{
    snake_t *pointer;

    wattron(my_win, COLOR_PAIR(4));
    for(pointer = sprite->m_head; pointer!= NULL; pointer = pointer->next_s)
        mvwprintw(my_win, pointer->position.y, pointer->position.x, " ");
    wrefresh(my_win);
    wattroff(my_win, COLOR_PAIR(4));
}
void showBomb(point_t bomb, WINDOW* my_win)
{
    wattron(my_win, COLOR_PAIR(5));
    mvwprintw(my_win, bomb.y, bomb.x, " ");
    wrefresh(my_win);
    wattroff(my_win, COLOR_PAIR(5));
}
void showWin(sprite_t *sprite, point_t bomb, WINDOW* my_win)
{
    box(my_win, ACS_VLINE, ACS_HLINE);
    showPoints(sprite, my_win);
    showBomb(bomb, my_win);
    wrefresh(my_win);
    wclear(my_win);
}
