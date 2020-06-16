#include <ncurses.h>
#include <clocale>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <string>
#include <algorithm>

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
class Gate
{
private:

public:
  int g1x;
  int g1y;
  int g2x;
  int g2y;
  int g1pos;
  int g2pos;

  Gate()
  {

  }
  void makeGate()
  {
    /// 벽 위치 랜덤 설정 0 ~ 3 ///
    g1pos = rand() % 4;
    g2pos = rand() % 4;

    switch (g1pos) {
      case 0:
        g1x = rand() % 38 + 1; //// 1 ~ 38 까지 난수
        g1y = 0;
        break;
      case 1:
        g1x = 39;
        g1y = rand() % 19 + 1; //// 1 ~ 19 까지 난수
        break;
      case 2:
        g1x = rand() % 38 + 1; //// 1 ~ 38 까지 난수
        g1y = 20;
        break;
      case 3:
        g1x = 0;
        g1y = rand() % 19 + 1; //// 1 ~ 19 까지 난수
        break;
    }

    switch (g2pos) {
      case 0:
        g2x = rand() % 38 + 1; //// 1 ~ 38 까지 난수
        g2y = 0;
        if(g2x == g1x && g2y == g1y) g2x = rand() % 38 + 1;
        break;
      case 1:
        g2x = 39;
        g2y = rand() % 19 + 1; //// 1 ~ 19 까지 난수
        if(g2x == g1x && g2y == g1y) g2y = rand() % 19 + 1;
        break;
      case 2:
        g2x = rand() % 38 + 1; //// 1 ~ 38 까지 난수
        g2y = 20;
        if(g2x == g1x && g2y == g1y) g2x = rand() % 38 + 1;
        break;
      case 3:
        g2x = 0;
        g2y = rand() % 19 + 1; //// 1 ~ 19 까지 난수
        if(g2x == g1x && g2y == g1y) g2y = rand() % 19 + 1;
        break;
    }
  }

};

class item
{
private:
  int x;
  int y;
public:
  item(int a, int b)
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
};

class game
{

private:
  int stageNum;

  int tick_cnt = 0;
  int gatestart;
  bool gateon = false;
  bool gatepassing = false;

  int plusSC = 0;
  int minusSC = 0;
  int gateSC = 0;
  int maxLen = 3;

  int Mlen = 10;
  int Mplus = 5;
  int Mminus = 2;
  int Mgate = 2;

  bool isClear = false;

  int item_cnt = 0;
  int addx;
  int addy;
  int delx;
  int dely;

  bool plusItempassing = false;
  bool minusItempassing = false;
  bool itemon = false;
  int plusItemstart;
  int minusItemstart;

public:

  vector<snake> snakes;
  vector<item> plus;
  vector<item> minus;
  int s_len = 10;
  int plustime[3] = {0, 0, 0};
  int minustime[3] = {0, 0, 0};
  int map[21][40];
  int map1[21][40] = {{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}};

  int map3[21][40] = {{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}};

  int map4[21][40] = {{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                      {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}};



  game(int stage)
  {
    stageNum = stage;
    if(stageNum <= 2)
    {
      for(int i = 0; i < 21 ; i++)
      {
        copy(map1[i], map1[i] + 40, map[i]);
      }
    }
    else if(stageNum == 3)
    {
      for(int i = 0; i < 21 ; i++)
      {
        copy(map3[i], map3[i] + 40, map[i]);
      }
    }
    else if(stageNum == 4)
    {
      for(int i = 0; i < 21 ; i++)
      {
        copy(map4[i], map4[i] + 40, map[i]);
      }
    }
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    resize_term(80, 80);

    start_color();

    init_pair(1, COLOR_WHITE , COLOR_GREEN);
    init_pair(2, COLOR_WHITE , COLOR_BLACK);
    init_pair(3, COLOR_RED , COLOR_GREEN);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    /// MESSAGE CLEAR
    mvprintw(2,10, "                                            ");
    mvprintw(4,10, "                                            ");

    mvprintw(2,10, "SNAKE GAME STAGE: ");
    move(2, 30);
    printw("%d", stageNum);



    refresh();
    attroff(COLOR_PAIR(2));

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
    if((r % 3) == 0 && item_cnt < 3)
    {
      addx = rand() % 38 + 1;
      addy = rand() % 19 + 1;

      if (map[addy][addx] > 0)
      {
        addItem();
        return;
      }
      else
      {
        for(int i = 0 ; i < s_len ; i++)
        {
          if(addx == snakes[i].getx() && addy == snakes[i].gety())
          {
            addItem();
            return;
          }
        }
        plusItemstart = tick_cnt;
        int index = plus.size();
        plustime[index] = plusItemstart;

        item tmp(addx, addy);
        plus.push_back(tmp);

        map[addy][addx] = 4;
        item_cnt++;

        if (item_cnt >= 3)
        {
          itemon = true;
        }
      }
    }
  }

  void addTail()
  {
    s_len += 1;
  }

  void delItem()
  {
    int r = rand() % 100 + 1;
    if((r % 3) == 0 && item_cnt < 3)
    {
      delx = rand() % 38 + 1;
      dely = rand() % 19 + 1;
      if (map[dely][delx] > 0)
      {
        delItem();
        return;
      }
      else
      {
        for(int i = 0 ; i < s_len ; i++)
        {
          if(delx == snakes[i].getx() && dely == snakes[i].gety())
          {
            delItem();
            return;
          }

        }
        minusItemstart = tick_cnt;
        int index = minus.size();
        minustime[index] = minusItemstart;

        item tmp(delx, dely);
        minus.push_back(tmp);

        map[dely][delx] = 5;
        item_cnt++;
        if (item_cnt >= 3)
        {
          itemon = true;
        }
      }
    }
  }

  void delTail()
  {
    s_len -= 1;
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

  void gateoff()
  {
    for(int i = 0 ; i < 21 ; i++)  ////MAP
    {
      for(int j = 0; j < 40 ; j++)
      {
          if (map[i][j] == 3) map[i][j] = 1;
      }
    }
  }



  void printMap()
  {
    WINDOW *gwin;

    gwin = newwin(21 , 40 , 5, 10);
    //wattron(gwin, COLOR_PAIR(1));

    for(int i = 0 ; i < 21 ; i++)  ////MAP
    {
      for(int j = 0; j < 40 ; j++)
      {   //wall
          if(map[i][j] == 1) mvwprintw(gwin, i, j, "\u2B1B");
          //blank
          else if(map[i][j] == 0) mvwprintw(gwin, i, j, " ");
          //Immune wall
          else if (map[i][j] == 2) mvwprintw(gwin, i, j, "\u2B1C");
          //gate
          else if (map[i][j] == 3)
          {
              wattron(gwin, COLOR_PAIR(3));
              mvwprintw(gwin, i, j, "\u2B1B");
              wattroff(gwin, COLOR_PAIR(3));
          }
          else if (map[i][j] == 4)
          {
            wattron(gwin, COLOR_PAIR(4));
            mvwprintw(gwin, i, j, "\u2B1B");
            wattroff(gwin, COLOR_PAIR(4));
          }
          else if (map[i][j] == 5)
          {
            wattron(gwin, COLOR_PAIR(5));
            mvwprintw(gwin, i, j, "\u2B1B");
            wattroff(gwin, COLOR_PAIR(5));
          }

      }
    }

    for(int i = 0 ; i < s_len ; i++)   ////SNAKE
    {
      int xx = snakes[i].getx();
      int yy = snakes[i].gety();
      if(i == 0) mvwprintw(gwin, yy, xx, "\u2B1B");
      else mvwprintw(gwin, yy, xx, "\u2B1C");
    }
  //  wattroff(gwin, COLOR_PAIR(1));


    wrefresh(gwin);

  }

  void printSC()
  {
    int clear = 0;

    WINDOW *sc;
    sc = newwin(21 , 15 , 5, 55);
    wbkgd(sc, COLOR_PAIR(1));
    wattron(sc, COLOR_PAIR(1));

    mvwprintw(sc, 1, 2, "SCORE BOARD");
    mvwprintw(sc, 3, 2, "B:    /");
    wmove(sc, 3, 5);
    wprintw(sc, "%d", s_len);
    wmove(sc, 3, 10);
    wprintw(sc, "%d", maxLen);

    mvwprintw(sc, 5, 2, "+: ");
    wmove(sc, 5, 5);
    wprintw(sc, "%d", plusSC);

    mvwprintw(sc, 7, 2, "-: ");
    wmove(sc, 7, 5);
    wprintw(sc, "%d", minusSC);

    mvwprintw(sc, 9, 2, "G: ");
    wmove(sc, 9, 5);
    wprintw(sc, "%d", gateSC);

    mvwprintw(sc, 10, 1, "*************");

    mvwprintw(sc, 11, 4, "MISSION");
    mvwprintw(sc, 13, 2, "B:   ( )");
    if(s_len >= Mlen)
    {
      wmove(sc, 13, 8);
      wprintw(sc, "v");
      clear++;
    }
    wmove(sc, 13, 5);
    wprintw(sc, "%d", Mlen);

    mvwprintw(sc, 15, 2, "+:   ( )");
    if(plusSC >= Mplus)
    {
      wmove(sc, 15, 8);
      wprintw(sc, "v");
      clear++;
    }
    wmove(sc, 15, 5);
    wprintw(sc, "%d", Mplus);

    mvwprintw(sc, 17, 2, "-:   ( )");
    if(minusSC >= Mminus)
    {
      wmove(sc, 17, 8);
      wprintw(sc, "v");
      clear++;
    }
    wmove(sc, 17, 5);
    wprintw(sc, "%d", Mminus);

    mvwprintw(sc, 19, 2, "G:   ( )");
    if(gateSC >= Mgate)
    {
      wmove(sc, 19, 8);
      wprintw(sc, "v");
      clear++;
    }
    wmove(sc, 19, 5);
    wprintw(sc, "%d", Mgate);

    wborder(sc, '*','*','*','*','*','*','*','*');
    wattroff(sc, COLOR_PAIR(1));
    wrefresh(sc);

    if(clear == 4) isClear = true;
  }


  char gate_col(int hx, int hy, Gate g)
  {
    if(hx == g.g1x && hy == g.g1y)
    {
      switch (g.g2pos) {
        case 0:
          snakes[0].setx(g.g2x);
          snakes[0].sety(g.g2y + 1);
          return 'd';
          break;
        case 1:
          snakes[0].setx(g.g2x - 1);
          snakes[0].sety(g.g2y);
          return 'l';
          break;
        case 2:
          snakes[0].setx(g.g2x);
          snakes[0].sety(g.g2y - 1);
          return 'u';
          break;
        case 3:
          snakes[0].setx(g.g2x + 1);
          snakes[0].sety(g.g2y);
          return 'r';
          break;
      }
    }
    else
    {
      switch (g.g1pos) {
        case 0:
          snakes[0].setx(g.g1x);
          snakes[0].sety(g.g1y + 1);
          return 'd';
          break;
        case 1:
          snakes[0].setx(g.g1x - 1);
          snakes[0].sety(g.g1y);
          return 'l';
          break;
        case 2:
          snakes[0].setx(g.g1x);
          snakes[0].sety(g.g1y - 1);
          return 'u';
          break;
        case 3:
          snakes[0].setx(g.g1x + 1);
          snakes[0].sety(g.g1y);
          return 'r';
          break;
      }
    }


  }
  bool play()
  {

    printMap();
    printSC();
    char dir = 'l'; ////처음 방향
    Gate g;
    int passingtime = -1;

    while(true)
    {
      srand((unsigned int)time(0));
      int ran1 = rand() % 100; //// 0 ~ 99 까지 난수

      if(passingtime <= tick_cnt) gatepassing = false;

      if(gateon == false && ran1 % 3 == 0) /// 33% 확률 게이트 생성
      {
          gatestart = tick_cnt;
          gateon = true;
          g.makeGate();
          map[g.g1y][g.g1x] = 3;
          map[g.g2y][g.g2x] = 3;
      }

      /// 게이트 지속시간 100틱
      if(gatepassing == false && tick_cnt - gatestart >= 50)
      {
        gateoff();
        gateon = false;
      }

      int key = getch(); ////입력이 있을 때
      if(key == KEY_LEFT)
      {
        if(dir == 'r')
        {
          mvprintw(2,10, "@@@@@ GAME OVER @@@@@");
          break;
        }
        dir = 'l';
      }
      else if (key == KEY_RIGHT)
      {
        if(dir == 'l')
        {
          mvprintw(2,10, "@@@@@ GAME OVER @@@@@");
          break;
        }
        dir = 'r';
      }
      else if (key == KEY_UP)
      {
        if(dir == 'd')
        {
          mvprintw(2,10, "@@@@@ GAME OVER @@@@@");
          break;
        }
        dir = 'u';
      }
      else if (key == KEY_DOWN)
      {
        if(dir == 'u')
        {
          mvprintw(2,10, "@@@@@ GAME OVER @@@@@");
          break;
        }
        dir = 'd';
      }



      moveSnake(dir);

      int headx = snakes[0].getx();
      int heady = snakes[0].gety();


      int gameover = 0;

      if(itemon == false)
      {
        addItem();
      }
      if(itemon == false)
      {
        delItem();
      }

      /// item 지속시간 100틱
      if(plustime[0] != 0){
        if(tick_cnt - plustime[0] >= 50)
        {
          map[plus[0].gety()][plus[0].getx()] = 0;
          plus.erase(plus.begin());
          plustime[0] = plustime[1];
          plustime[1] = plustime[2];
          plustime[2] = 0;
          item_cnt--;
          itemon = false;
          addItem();
        }
      }

      if(minustime[0] != 0){
        if(tick_cnt - minustime[0] >= 50)
        {
          map[minus[0].gety()][minus[0].getx()] = 0;
          minus.erase(minus.begin());
          minustime[0] = minustime[1];
          minustime[1] = minustime[2];
          minustime[2] = 0;
          item_cnt--;
          itemon = false;
          delItem();
        }
      }



      if(map[heady][headx] == 4)
      {
        plusSC++;
        map[heady][headx] = 0;
        for (int i = 0; i < plus.size(); i++)
        {
          if (headx == plus[i].getx() && heady == plus[i].gety())
          {
            plus.erase(plus.begin() + i);
            item_cnt--;
            itemon = false;
            if (i == 0)
            {
              plustime[0] = plustime[1];
              plustime[1] = plustime[2];
              plustime[2] = 0;
            }
            else if (i == 1)
            {
              plustime[1] = plustime[2];
              plustime[2] = 0;
            }
            else plustime[i] = 0;
            break;
          }
        }
        addTail();
        addItem();
      }

      if(map[heady][headx] == 5)
      {
        minusSC++;
        map[heady][headx] = 0;
        for (int i = 0; i < minus.size(); i++)
        {
          if (headx == minus[i].getx() && heady == minus[i].gety())
          {
            minus.erase(minus.begin() + i);
            item_cnt--;
            itemon = false;
            if (i == 0)
            {
              minustime[0] = minustime[1];
              minustime[1] = minustime[2];
              minustime[2] = 0;
            }
            else if (i == 1)
            {
              minustime[1] = minustime[2];
              minustime[2] = 0;
            }
            else minustime[i] = 0;
          }
        }
        delTail();
        addItem();
      }
      /************************************
      *                                   *
      *                                   *
      *      여기서 아이템 생성 랜덤뽑기!!!   *
      *                                   *
      *                                   *
      **************************************/
      // 왜냐면 스네이크 움직이고 -> 아이템 만들고 -> 출력하기 순서가 되어야 하기 때문 //



      //// into gate
      if(map[heady][headx] == 3)
      {
        gatepassing = true;
        passingtime = tick_cnt + s_len + 1;
        gateSC++;
        dir = gate_col(headx, heady, g);
      }


      /**** GAMEOVER ****/
      if(map[heady][headx] == 1) gameover = 1;

      for(int i = 1 ; i < s_len ; i++)
      {
        if(headx == snakes[i].getx() && heady == snakes[i].gety())
        {
          delTail();
          break;
        }
      }

      if(gameover)
      {
        mvprintw(2,10, "@@@@@ GAME OVER @@@@@");
        break;
      }

      tick_cnt++;
      printMap();
      printSC();
      if(isClear)
      {
        mvprintw(2,10, "@@@@@@ CONGRATULATION! STAGE CLEAR!! @@@@@@");
        mvprintw(4,10, "PRESS ANY KEY TO NEXT STAGE");
        break;
      }
      usleep(100000); ///  micro seconds - > 0.5 seconds
    }

    nodelay(stdscr, FALSE);
    getch();

    return isClear;
  }

};



int main()
{
  int stage = 1;
  while(stage <= 4)
  {
    game g1(stage);
    if(g1.play()) stage++;
    else break;
  }
  endwin();

  return 0;
}
