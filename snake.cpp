#include <ncurses.h>
#include <clocale>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <ctime>

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
class game
{

private:
  int tick_cnt = 0;
  int gatestart;
  bool gateon = false;
  bool gatepassing = false;

public:


  vector<snake> snakes;
  int s_len = 10;
  int map[21][40] = { {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
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
                      {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2} };
  game()
  {
    start_color();

    init_pair(1, COLOR_WHITE , COLOR_GREEN);
    init_pair(2, COLOR_WHITE , COLOR_BLACK);
    init_pair(3, COLOR_RED , COLOR_GREEN);
    attron(COLOR_PAIR(2));
    mvprintw(2,10, "snake game");
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
    WINDOW *sc;
    sc = newwin(21 , 15 , 5, 60);
    wbkgd(sc, COLOR_PAIR(1));
    wattron(sc, COLOR_PAIR(1));
    mvwprintw(sc, 1, 2, "SCORE BOARD");
    wborder(sc, '*','*','*','*','*','*','*','*');
    wrefresh(sc);

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
  void play()
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

      if(passingtime < tick_cnt) gatepassing = false;

      if(gateon == false && ran1 % 3 == 0) /// 5% 확률 게이트 생성
      {
          gatestart = tick_cnt;
          gateon = true;
          g.makeGate();
          map[g.g1y][g.g1x] = 3;
          map[g.g2y][g.g2x] = 3;
      }

      if(gatepassing == false && tick_cnt - gatestart == 100)
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

      if(headx == 0 || headx == 39 || heady == 0 || heady == 20 )
      {
        if(map[heady][headx] == 3)
        {
          gatepassing = true;
          passingtime = tick_cnt + s_len + 1;
          dir = gate_col(headx, heady, g);
        }
        else gameover = 1;
      }



      for(int i = 1 ; i < s_len ; i++)
      {
        if(headx == snakes[i].getx() && heady == snakes[i].gety())
        {
          gameover = 1;
          break;
        }
      }

      if(gameover)
      {
        mvprintw(2,10, "@@@@@ GAME OVER @@@@@");
        break;
      }


      printMap();
      usleep(100000); ///micro seconds - > 0.5 seconds
      tick_cnt++;
    }

    nodelay(stdscr, FALSE);
    getch();

    endwin();

  }

};



int main()
{
  setlocale(LC_ALL, "");
  initscr();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  noecho();
  cbreak();
  resize_term(80, 80);

  game g1;
  g1.play();

  return 0;
}
