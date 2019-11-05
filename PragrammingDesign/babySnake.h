#ifndef BABYSNAKE_H_
#define BABYSNAKE_H_

#include <vector>
#include <string>
using namespace std;



class Record // 一局游戏的记录
{
  public:
    string name; // 玩家名
    int score;   // 最终得分
    int steps;   // 总步数
    
    Record(string n, int scr, int stp);
};

class Point // 坐标
{
  public:
    int x;
    int y;

    Point(int _x, int _y); // 构造函数
};

void Banner();

void Menu();

void SetParam();

void SetMapHeight();

void SetMapWidth();

void SetDifficulty();

void ExmParam();

void Setup();

void DrawWall();



void Logic(); // 运行主逻辑

void HandleKbhit(); // 根据键入改变方向

void DrawEnd();

void DrawBody();

void ResetFood(); // 重置食物位置

void DrawFood();

bool WillDie(int x, int y); // 判断是否将要死亡

bool WillEat(int x, int y); // 判断是否将要吃到食物

void ShowSorceboard();

void LoadSorceboard();

void WriteSorceboard(); // 把排行榜数据写入文件中

void AddPlayer(); //

void HandleAdd();

bool Campare(Record r1, Record r2);

void Exit();

void Gotoxy(int i, int y); // 将光标定位至(x, y)

void InvisibleCursor();












#endif