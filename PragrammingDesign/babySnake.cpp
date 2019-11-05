#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include "snake.h"

using namespace std;

bool gameOver = true; // 用于结束游戏

int mapHeight = 20, mapWidth = 20; // 地图高宽

Point head(0, 0); // 贪吃蛇头部位置

Point food(0, 0); // 食物位置

int score = 0; // 当前得分
int totalSteps = 0; // 记录步数

vector<Point> wall; // 墙

deque<Point> body; // 贪吃蛇身体

enum Direction { STOP=0, UP=1, DOWN=2, LEFT=3, RIGHT=4 };
Direction dir = STOP;
Direction lastDir = dir;

int numberOfList = 0; // 排行榜记录的条数
vector<Record> records; //排行榜记录

int difficulty = 1; // 游戏难度
int interval;       // 时间间隔

bool accelerated = false; // 是否被F1加速
bool decelerated = false; // 是否被F2减速

Record::Record(string n, int scr, int stp)
{
    name = n;
    score = scr;
    steps = stp;
}

Point::Point(int _x, int _y)
{
    x = _x;
    y = _y;
}

void Banner() // 游戏开始的横幅
{
    cout << "++++欢迎来到贪吃蛇小游戏++++" << endl;
}

void Menu() // 菜单选项
{
    
    while(1)
    {
        int choice; //菜单选项

        cout << "\n=====菜单=====" << endl;
        cout << "1. 开始游戏" << endl;
        cout << "2. 设置参数" << endl;
        cout << "3. 查看参数" << endl;
        cout << "4. 排行榜" << endl;
        cout << "5. 退出游戏" << endl;
        cout << "请输入选项：";

        cin >> choice;
        switch (choice)
        {
        case 1:
            return; // 开始游戏
        case 2:
            SetParam();
            break;
        case 3:
            ExmParam();
            break;
        case 4:
            ShowSorceboard();
            break;
        case 5:
            Exit();
        default:
            cout << "\x1b[31;4m无效选项！\e[0m" << endl;
        }
    }
}


void SetParam() // 设置参数
{
    while(1)
    {
        int choice; // 参数选项

        cout << "\n可以设置的参数：" << endl;
        cout << "1. 地图高度" << endl;
        cout << "2. 地图宽度" << endl;
        cout << "3. 游戏难度" << endl;
        cout << "4. 返回" << endl;
        cout << "请输入选项：";

        cin >> choice;
        switch (choice)
        {
        case 1:
            SetMapHeight();
            break;
        case 2:
            SetMapWidth();
            break;
        case 3:
            SetDifficulty();
            break;
        case 4:
            return; // 返回至菜单
        default:
            cout << "\x1b[31;4m无效选项！\e[0m" << endl;
        }
    }
}

void SetMapHeight() // 设置地图高度
{
    int input;

    cout << "请输入地图高度(10~30)：" << endl;
    cin >> input;

    if (10 <= input && input <= 30)
    {
        mapHeight = input;
        cout << "地图高度已被成功设置为：" << mapHeight << endl;
    }
    else
        cout << "\x1b[31;4m无效输入！\e[0m" << endl;
}

void SetMapWidth() // 设置地图宽度
{
    int input;

    cout << "请输入地图宽度(10~50)：" << endl;
    cin >> input;

    if (10 <= input && input <= 50)
    {
        mapWidth = input;
        cout << "地图宽度已被成功设置为：" << mapWidth << endl;
    }
    else
        cout << "\x1b[31;4m无效输入！\e[0m" << endl;
}

void SetDifficulty() // 设置游戏难度
{
    int choice;
    cout << "请输入难度：(1：易, 2：中, 3：难)：" << endl;
    cin >> choice;

    switch(choice)
    {
    case 1:
        difficulty = 0;
        cout << "游戏难度已被成功设置为：易" << endl;
        break;
    case 2:
        difficulty = 25;
        cout << "游戏难度已被成功设置为：中" << endl;
        break;
    case 3:
        difficulty = 50;
        cout << "游戏难度已被成功设置为：难" << endl;
        break;
    default:
        cout << "\x1b[31;4m无效输入！\e[0m" << endl;
    }
}


void ExmParam() // 查看参数
{
    while(1)
    {
        int choice; // 参数选项

        cout << "\n可以查看的参数：" << endl;
        cout << "1. 地图高度" << endl;
        cout << "2. 地图宽度" << endl;
        cout << "3. 游戏难度" << endl;
        cout << "4. 所有参数" << endl;
        cout << "5. 返回" << endl;
        cout << "请输入选项：";

        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "地图高度：" << mapHeight << endl;
            break;
        case 2:
            cout << "地图宽度：" << mapWidth << endl;
            break;
        case 3:
            cout << "游戏难度：" << difficulty << endl;
            break;
        case 4:
            cout << "地图高度：" << mapHeight << endl;
            cout << "地图宽度：" << mapWidth << endl;
            cout << "游戏难度：" << difficulty << endl;
            break;
        case 5:
            return; // 返回至菜单
        default:
            cout << "\x1b[31;4m无效选项！\e[0m" << endl;
        }
    }
}

/***************************************/
void Setup() // 每局游戏的初始化
{
    gameOver = false;
    accelerated = false;
    totalSteps = 0;

    dir = UP;

    body.clear();
    wall.clear();

    head.x = mapHeight / 2 + 1;
    head.y = mapWidth / 2 + 1;
    body.push_back(head);

    food.x = rand() % mapWidth + 1;
    food.y = rand() % mapHeight + 1;
    // food.x = 2;
    // food.y = 3;

    DrawBody();
    DrawFood();
}

void DrawWall() // 绘制地图
{
    system("cls"); // 清空终端

    for(int i=0; i < mapWidth+2; i++) // 第0行
    {
        wall.push_back(Point(0, i));
        cout << "#";
    }
    cout << endl;

    for(int j=1; j < mapHeight+1; j++) // 每一列
    {
        wall.push_back(Point(j, 0));
        wall.push_back(Point(j, mapWidth+1));
        cout << "#";
        for(int k=0; k < mapWidth; k++)
            cout << " ";
        cout << "#" << endl;
    }

    for(int i=0; i < mapWidth+2; i++) // 最后一行
    {
        wall.push_back(Point(mapHeight+1, i));
        cout << "#";
    }

    // for (Point p : wall)
    // {
    //     cout << p.x << " " << p.y << ", ";
    // }
}


void Logic() // 运行主逻辑
{
    HandleKbhit();
    if (dir != STOP)
    {
        bool quit = false;
        int nextx, nexty;   // 下一步的坐标
        
        totalSteps++;

        switch(dir)
        {
        case UP:
            nextx = head.x - 1;
            nexty = head.y; 
            break;
        case DOWN:
            nextx = head.x + 1;
            nexty = head.y;
            break;
        case LEFT:
            nextx = head.x;
            nexty = head.y - 1;
            break;
        case RIGHT:
            nextx = head.x;
            nexty = head.y + 1;
            break;
        case STOP:
            quit = true;
        }

        if(WillDie(nextx, nexty))
            quit = true;
        if(!WillEat(nextx, nexty))
        {
            DrawEnd();
            body.pop_back(); // 删去末尾，向前移动一步
        }   
        else  // 如果吃到食物，则末尾不变，并重置食物位置
        {
            ResetFood();
            DrawFood();
            score += 10;
        }


        head.x = nextx;
        head.y = nexty;
        body.push_front(head);

        DrawFood();
        DrawBody();

        if(quit)
        {
            Gotoxy(mapHeight+2, 0);
            cout << "最终成绩：" << score << endl;
            return;
        }
    }
    interval = 300 - score * 0.5 - difficulty * 5;
    if(interval > 100)
        Sleep(interval);
    else
        Sleep(100);
}

void HandleKbhit() // 根据键入改变方向
{
    while(_kbhit()) // 键盘上按下某一个键
    {
        int key = _getch();
        if(key == 0)
        {
            switch (_getch())
            {
            case 72:            // 上
                dir = UP;
                break;
            case 75:            // 左
                dir = LEFT;
                break;
            case 77:            // 下
                dir = RIGHT;
                break;
            case 80:            // 右
                dir = DOWN;
                break;
            case 59:            // 'F1'
                if(accelerated) // 处于加速状态
                    break;
                difficulty += 50;
                if(!accelerated && !decelerated) // 正常速度
                    accelerated = true;
                else if(decelerated)             // 减速状态
                    decelerated = false;
                break;
            case 60:   // 'F2'
                if(decelerated) // 处于减速状态
                    break;
                difficulty -= 50;
                if(!accelerated && !decelerated) // 正常速度
                    decelerated = true;
                else if(accelerated)             // 加速状态
                    accelerated = false;
                break;
            default:
                break;
            }
        }
        else if (key == 112) // 'p'
            if(dir != STOP)
            {
                lastDir = dir;
                dir = STOP;
            }
            else
                dir = lastDir;
    }
}

void DrawEnd() // 去除贪吃蛇的尾部
{
    Point end = body.back();
    Gotoxy(end.x, end.y);
    cout << ' ';
}

void DrawBody() // 绘制贪吃蛇的身体
{
    for(Point p : body)
    {
        Gotoxy(p.x, p.y);
        cout << 'o';
    }
    // 绘制头部
    Gotoxy(head.x, head.y);
    cout << 'O';
}

void ResetFood() // 重置食物位置
{
    bool collision = true;
    while(collision)
    {
        food.x = rand() % mapHeight + 1;
        food.y = rand() % mapWidth + 1;
        collision = false;
        for (Point p: body) // 防止食物出现在身体上
            if(p.x == food.x && p.y == food.y)
                collision = true;
        for (Point p: wall) // 防止食物出现在墙上
            if(p.x == food.x && p.y == food.y)
                collision = true;
    }
}

void DrawFood() // 绘制新的食物
{
    Gotoxy(food.x, food.y);
    // cout << food.x << " " << food.y << endl;
    cout << "F";
}

bool WillDie(int x, int y) // 判断是否将要死亡
{
    for (Point p : wall) // 是否撞墙
    {
        if(x == p.x && y == p.y)
        {
            gameOver = true;
            return true;
        }
    }

    for (Point p : body) // 是否撞到自己
    {
        if(x == p.x && y == p.y)
        {
            gameOver = true;
            return true;
        }
    }

    return false;
}

bool WillEat(int x, int y) // 判断是否将要吃到食物
{
    if(x == food.x && y == food.y)
        return true;
    return false;
}

void ShowSorceboard() // 展示排行榜
{
    cout << left << setw(10) << "排名" 
         << left << setw(15) << "玩家名"
         << left << setw(10) << "得分" 
         << left << setw(10) << "总步数"
         << endl;

    for(int i=0; i < numberOfList; i++)
    {
        cout << left << setw(10) << i+1
             << left << setw(10) << records[i].name
             << left << setw(10) << records[i].score
             << left << setw(10) << records[i].steps
             << endl;
    }
}

void LoadSorceboard() // 从文件中读取排行榜数据
{
    ifstream infile;

    infile.open("records.dat");
    infile >> numberOfList; // 读入记录条数

    for(int i=0; i < numberOfList; i++)
    {
        Record tmp("", 0, 0);
        infile >> tmp.name;
        infile >> tmp.score;
        infile >> tmp.steps;
        records.push_back(tmp);
    }

    infile.close();
}

void WriteSorceboard() // 把排行榜数据写入文件中
{
    ofstream outfile;

    outfile.open("records.dat");
    outfile << numberOfList << endl;

    for(int i=0; i < numberOfList; i++)
    {
        outfile << records[i].name << " "
                << records[i].score << " "
                << records[i].steps << endl;
    }

    outfile.close();
}

void AddPlayer() // 游戏结束添加玩家
{
    char choice;
    cout << "是否加入排行榜(y/n)：";
    cin >> choice;

    switch(choice)
    {
    case 'y':
    case 'Y':
        HandleAdd();
    case 'n':
    case 'N':
    default:
        break;
    }
}

void HandleAdd() // 处理增加记录
{
    string name;
    cout << "请输入玩家名：";
    cin >> name;
    Record newRecord(name, score, totalSteps);
    numberOfList++;
    records.push_back(newRecord);
    sort(records.begin(), records.end(), Campare);
}

bool Campare(Record r1, Record r2) // 降序
{
    return r1.score > r2.score;
}

void Exit() // 退出游戏
{
    WriteSorceboard(); // 将记录写入排行榜中

    cout << "Bye!" << endl;
    exit(0);
}

void Gotoxy(int i,int j) //定位到第y行的第x列
{
    int xx=0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X = j;
    loc.Y = i;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
}

void InvisibleCursor() // 隐藏光标
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=false;
    SetConsoleCursorInfo(hOut,&cci);
}

int main()
{
    srand(time(nullptr));
    Banner(); // 横幅
    LoadSorceboard();
    InvisibleCursor();

    while(1) // 游戏整体循环
    {
        Menu();
        Setup(); // 初始化
        DrawWall();
        while(!gameOver)
        {
            Logic();
            // Sleep(1000);
        }
        AddPlayer();
    }
    
    return 0;
}
