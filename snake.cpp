#include <ncurses.h>
#include <clocale>
#include <iostream>
#include <vector>
using namespace std;

class snake{

private:
  int x;
  int y;

public:

  snake(int a, int b)
  {
    x = a;
    y = b;
  }

  int getx()
  {
    return x;
  }
  int gety()
  {
    return y;
  }
  void setx(int a)
  {
    x = a;
  }
  void sety(int b)
  {
    y = b;
  }

};

class game
{

private:

public:

  int map[21][40];
  vector<snake> snakes;
  int s_len = 3;

  game()
  {
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

    initSnake();
  }


  void initSnake()
  {
    for(int i = 0 ; i < 3 ; i++)
    {
      snake temp(10,20 + i);
      snakes.push_back(temp);
    }
  }


  void addTail()
  {

  }


  void stage()
  {

    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    cbreak();

    resize_term(50, 50);

    for(int i = 0 ; i < 21 ; i++)  ////MAP
    {
      for(int j = 0; j < 40 ; j++)
      {
          if(map[i][j] == 1) mvprintw(i, j, "\u2B1B");

          else if(map[i][j] == 0) mvprintw(i, j, " ");

          else mvprintw(i, j, "\u2B1C");
      }
    }

    for(int i = 0 ; i < s_len ; i++)   ////SNAKE
    {
      int xx = snakes[i].getx();
      int yy = snakes[i].gety();
      if(i == 0) mvprintw(xx, yy, "\u2B1B");
      else mvprintw(xx, yy, "\u2B1C");

    }


    refresh();
    getch();
    endwin();

  }

};



int main()
{
  setlocale(LC_ALL, "");

  game g1;
  g1.stage();

  return 0;
}
