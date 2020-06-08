#include <ncurses.h>
#include <clocale>
#include <iostream>


void stage(int map[21][40])
{

  setlocale(LC_ALL, "");

  initscr();

  curs_set(FALSE);
  keypad(stdscr, TRUE);
  noecho();
  resize_term(50, 50);

  for(int i = 0 ; i < 21 ; i++)
  {
    for(int j = 0; j < 40 ; j++)
    {
        if(map[i][j] == 1) mvprintw(i, j, "\u2B1B");

        else if(map[i][j] == 0) mvprintw(i, j, " ");

        else mvprintw(i, j, "\u2B1C");
    }
  }

  refresh();
  getch();
  endwin();

}

int main()
{

  int map[21][40];
  for(int i = 0 ; i < 21 ; i++) ///initalizing map
  {
    for(int j = 0 ; j < 40 ; j++)
    {
      if(i == 0 || i == 20 || j == 0 || j == 39)
      {
        map[i][j] = 1;
      }
      else{
        map[i][j] = 0;
      }
    }
  }
  map[0][0] = 2;
  map[20][39] = 2;
  map[0][39] = 2;
  map[20][0] = 2;

  stage(map);

  return 0;
}
