#include <ncurses.h>
#include <clocale>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdlib>

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
  int addX, addY, delX, delY;

  game()
  {
    for(int i = 0 ; i < 21 ; i++) ///initalizing map
    {
      for(int j = 0 ; j < 40 ; j++)
      {
        if(i == 0 || i == 20 || j == 0 || j == 39) map[i][j] = 1;
        else map[i][j] = 0;
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
    for(int i = 0 ; i < s_len ; i++)
    {
      snake temp(20 + i ,10);
      snakes.push_back(temp);
    }
  }

  void addItem()
  {
    int r = rand() % 100 + 1;
    if((r % 3) == 0)
    {
      addX = rand() % 38 + 1;
      addY = rand() % 19 + 1;
      map[addX][addY] = 3;
    }
  }

  bool addTail()
  {
    int headx = snakes[0].getx();
    int heady = snakes[0].gety();
    if(headx == addX && heady == addY)
    {
      s_len += 1;
      map[addX][addY] = 0;
      addItem();
      return true;
    }
    return false;
  }

  void delItem()
  {
    int r = rand() % 100 + 1;
    if((r % 3) == 0)
    {
      delX = rand() % 38 + 1;
      delY = rand() % 19 + 1;
      map[delX][delY] == 4;
    }
  }

  bool delTail()
  {
    int headx = snakes[0].getx();
    int heady = snakes[0].gety();
    if(headx == delX && heady == delY)
    {
      s_len -= 1;
      map[delX][delY] = 0;
      delItem();
      return true;
    }
    return false;
  }

  void moveSnake(char dir)
  {

    for(int i = s_len - 1 ; i > 0 ; i--)
    {
      snakes[i].setx(snakes[i-1].getx());
      snakes[i].sety(snakes[i-1].gety());
    }


    int nowx = snakes[0].getx();
    int nowy = snakes[0].gety();


    switch(dir)
    {
      case 'l' :
          snakes[0].setx(nowx - 1);
          break;
      case 'r' :
          snakes[0].setx(nowx + 1);
          break;
      case 'u' :
          snakes[0].sety(nowy - 1);
          break;
      case 'd' :
          snakes[0].sety(nowy + 1);
          break;
    }

  }

  void printMap()
  {
    WINDOW *gwin;

    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    resize_term(50, 50);
    start_color();

    init_pair(1, COLOR_WHITE , COLOR_GREEN);
    init_pair(2, COLOR_BLUE , COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_GREEN);
    init_pair(4, COLOR_RED, COLOR_GREEN);

    attron(COLOR_PAIR(2));
    mvprintw(1,1, "snake game");
    refresh();
    attroff(COLOR_PAIR(2));

    gwin = newwin(21 , 40 , 5, 10);
    wattron(gwin, COLOR_PAIR(1));

    for(int i = 0 ; i < 21 ; i++)  ////MAP
    {
      for(int j = 0; j < 40 ; j++)
      {
          if(map[i][j] == 1) mvwprintw(gwin, i, j, "\u2B1B");

          else if(map[i][j] == 0) mvwprintw(gwin, i, j, " ");

          else if(map[i][j] == 3)
          {
            wattroff(gwin, COLOR_PAIR(1));
            wattron(gwin, COLOR_PAIR(3));
            mvwprintw(gwin, i, j, "\u2B1B");
            wattroff(gwin, COLOR_PAIR(3));
            wattron(gwin, COLOR_PAIR(1));
          }
          else if(map[i][j] == 4)
          {
            wattroff(gwin, COLOR_PAIR(1));
            wattron(gwin, COLOR_PAIR(4));
            mvwprintw(gwin, i, j, "\u2B1B");
            wattroff(gwin, COLOR_PAIR(4));
            wattron(gwin, COLOR_PAIR(1));
          }

          else mvwprintw(gwin, i, j, "\u2B1C");
      }
    }

    for(int i = 0 ; i < s_len ; i++)   ////SNAKE
    {
      int xx = snakes[i].getx();
      int yy = snakes[i].gety();
      if(i == 0) mvwprintw(gwin, yy, xx, "\u2B1B");
      else mvwprintw(gwin, yy, xx, "\u2B1C");
    }
    wrefresh(gwin);

  }

  void stage1()
  {
    addItem();
    delItem();
    printMap();
    int count1 = 1; //count1 -> addTail
    int count2 = 1; //count2 -> delTail
    char dir = 'l'; ////처음 방향
    while(true)
    {
      int key = getch(); ////입력이 있을 때
      if(key == KEY_LEFT)
      {
        if(dir == 'r')
        {
          mvprintw(1,1, "@@@@@ GAME OVER @@@@@");
          break;
        }
        dir = 'l';
      }
      else if (key == KEY_RIGHT)
      {
        if(dir == 'l')
        {
          mvprintw(1,1, "@@@@@ GAME OVER @@@@@");
          break;
        }
        dir = 'r';
      }
      else if (key == KEY_UP)
      {
        if(dir == 'd')
        {
          mvprintw(1,1, "@@@@@ GAME OVER @@@@@");
          break;
        }
        dir = 'u';
      }
      else if (key == KEY_DOWN)
      {
        if(dir == 'u')
        {
          mvprintw(1,1, "@@@@@ GAME OVER @@@@@");
          break;
        }
        dir = 'd';
      }

      moveSnake(dir);

      //***** GAMEOVER *****//
      int headx = snakes[0].getx();
      int heady = snakes[0].gety();

      int gameover = 0;

      if(headx == 0 || headx == 39 || heady == 0 || heady == 20 ) gameover = 1;

      for(int i = 1 ; i < s_len ; i++)
      {
        if(headx == snakes[i].getx() && heady == snakes[i].gety())
        {
          gameover = 1;
          break;
        }
      }
      if(addTail())
      {
        count1 = 0;
      }
      if(delTail())
      {
        count2 = 0;
      }


      if(gameover)
      {
        mvprintw(1,1, "@@@@@ GAME OVER @@@@@");
        break;
      }

      if(count1 == 10)
      {
        count1 = 1;
        map[addX][addY] = 0;
        addItem();
      }
      else count1++;

      if(count2 == 10)
      {
        count2 = 1;
        map[delX][delY] = 0;
        delItem();
      }
      else count2++;

      printMap();
      usleep(5000); ///micro seconds - > 0.5 seconds
    }

    nodelay(stdscr, FALSE);
    getch();

    endwin();

  }

};



int main()
{
  setlocale(LC_ALL, "");

  game g1;
  g1.stage1();

  return 0;
}
