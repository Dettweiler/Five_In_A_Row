#include "config.h"

#define IN_CHECKERBOARD_CONDICTION(y, x) ((x) > 0 && (x) <= CHECKER_BOARD_SIZE && (y) > 0 && (y) <= CHECKER_BOARD_SIZE)

#define CHECK()     if (checkerboard[i][j] == Gamer)    \
                    {                                   \
                        WinFlag++;                      \
                    }                                   \
                    else                                \
                    {                                   \
                        break;                          \
                    }

/* 数组表示棋盘状态，空白；【 0 】，黑子：【 1 】，白子：【 2 】 */
char checkerboard[CHECKER_BOARD_SIZE+1][CHECKER_BOARD_SIZE+1];

const char JudgeDirection[4][2] = 
{
    {DIRECTION_L , DIRECTION_R },
    {DIRECTION_U , DIRECTION_D },
    {DIRECTION_LU, DIRECTION_RD},
    {DIRECTION_LD, DIRECTION_RU}
};

unionDirection Direction;    /* 横纵坐标变化方向 */
TypeGamer Gamer;             /* 当前玩家 */
TypeState GameState; 
char y, x;                   /* 横纵坐标 */
char turn;                   /* 游戏回合 */ 
char step;                   /* 当前步骤 */
char choice;                 /*  选择   */
char winA,winB;              /* 获胜次数 */

int main(void)
{
    Init();
    Play();
}

void StaManager(void)
{
    fflush(stdin);
    choice = getch();
    if ((choice == 'y') || (choice == 'Y'))
    {
        if(GameState == State_WaitESC)
        {
            exit(0);
        }
        else
        {
            main();
        }
    }
    else if ((choice == 'n') || (choice == 'N'))
    {
        if(GameState == State_WaitRST || GameState == State_WaitESC)
        {
            printf("\r      您已取消操作，请玩家%d继续下子。\n", Gamer);
            return;
        }
        else
        {
            exit(0);
        }
    } 
    else
    {
        printf("\n     输入字符错误, 请重新输入: ");
        StaManager();
    }
}

void Draw(void)
{
    system("cls");
    char buffer[BUFFER_MAX_NUM]={0};

    for (char i = 0 ;i <= CHECKER_BOARD_SIZE; i++)
    {
        for (char j = 0;j <= CHECKER_BOARD_SIZE; j++)
        {
            //棋子
            if (1 == checkerboard[i][j])
                strcat(buffer,"●");
            else if (2 == checkerboard[i][j])
                strcat(buffer,"◎");
            //首行空格
            else if(0 == i)
                strcat(buffer,"  "); 
            //首列空格
            else if(0 == j)
                strcat(buffer,"\n  ");
            else if ((i == 1) && (j == 1)) 
                strcat(buffer,"┏ ");
            else if ((i == CHECKER_BOARD_SIZE) && (j==1))
                strcat(buffer,"┗ ");
            else if((i == 1) && (j == CHECKER_BOARD_SIZE))
                strcat(buffer,"┓");
            else if((i == CHECKER_BOARD_SIZE) && (j == CHECKER_BOARD_SIZE))
                strcat(buffer,"┛");
            else if(i == 1)
                strcat(buffer,"┳ ");
            else if(i == CHECKER_BOARD_SIZE)
                strcat(buffer,"┻ ");
            else if(j == 1)
                strcat(buffer,"┣ ");
            else if(j == CHECKER_BOARD_SIZE)
                strcat(buffer,"┫");
            else
                strcat(buffer,"╋ ");
        }
    }
    printf("%s \n   玩家1: 获胜%d次 玩家2: 获胜%d次\n\n【回合%d】现在轮到玩家%d, 请落子。"
            ,buffer, winA, winB, turn, Gamer);
}

void Init(void)
{
    static char InitFlag = FALSE;
    if(!InitFlag)
    {
        system("mode con cols=40 lines=40");//窗口大小
        system("chcp 65001");               //使用UTF-8编码
        system("title Five In A Row");      //窗口标题
        system("cls");                      //清除先前命令行
        // PlaySound(TEXT(BGM_RES), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        printf("【游戏介绍】\n\n玩家需通过键盘 W S A D 或方向键移动\n\n星标以下子。"
        "\n\n按下R键可重启游戏，按下ESC键可退出游戏\n\n\n\n");
        printf
        (
            "@@     &...&&& &.&  &&      @@@@@ \n"
            " @         .&& .&&  &          @@\n"
            " @          &&   &  &&          @\n"
            " @           &&  &&  &&&        @\n"
            " @           &&  &&    &        @\n"
            " @            .                @\n"
            " @                              @ \n"
            "  @    @@@@@           @@@@@    @ \n"
            "  @    ::                ::    @ \n"
            "  @    ::                ::    @ \n"
            "  @    ::                ::    @ \n"
            "  @    ::      @@@@@@   ::    @ \n"
            "  @           @@ @@ @@         @ \n"
            "  @@          @  @@  @         @ \n"
            "   @@          @@@@@@         @@ \n"
            "    @@@@@@            @@@@@@@@@  \n"
            "          @@@@@@@@@@@@@          \n"
        );

        Sleep(5000);
        system("color E0");//窗口及字体颜色
        system("cls");

        turn = 1;             //游戏回合  
        InitFlag = TRUE;
    }

    memset(checkerboard,0,sizeof(checkerboard));
    Direction.value = DIRECTION_INIT;
    step = 1;
    x = CHECKER_BOARD_SIZE/2 + 1;
    y = CHECKER_BOARD_SIZE/2 + 1;
    Gamer = GamerA;
    Update();
}

void Update(void)
{
    char temp;
    temp = checkerboard[y][x];
    checkerboard[y][x] = Gamer;
    Draw();
    checkerboard[y][x] = temp;
}

void Select(void)
{
    choice = getch();
    switch (choice)
    {
        case 'w':
        case 'W':
        case KEYCODE_U:
            if(IN_CHECKERBOARD_CONDICTION(y-1, x))
            {   
                y--; 
                Update();
            }
            break;

        case 'a':
        case 'A':
        case KEYCODE_L:
            if(IN_CHECKERBOARD_CONDICTION(y, x-1))
            {    
                x--;
                Update();
            }
            break;

        case 's':
        case 'S':
        case KEYCODE_D:
            if(IN_CHECKERBOARD_CONDICTION(y+1, x))
            {    
                y++;
                Update();
            }
            break;

        case 'd':
        case 'D':
        case KEYCODE_R:
            if(IN_CHECKERBOARD_CONDICTION(y, x+1))
            {    
                x++;
                Update();
            }
            break;

        case 'r':
        case 'R':
            GameState = State_WaitRST;
            printf("\r      注意, 此操作无法撤回!!               \n      是否需要重新开始游戏(Y/N):");  /* 准备重启游戏, 并询问是否继续 */
            StaManager();
            break;

        case KEYCODE_ESC:
            GameState = State_WaitESC;
            printf("\r      注意, 此操作无法撤回!!               \n      是否需要直接退出游戏(Y/N):");  /* 准备重启游戏, 并询问是否继续 */
            StaManager();
            break;

        case '\r':
            return;
            break;
    }
    Select();
}

void Move(void)
{
    fflush(stdin);
    Select();

    if(0 != checkerboard[y][x])
    {
        printf("\n这个位置已经有棋子了, 请重新下子。");
        Move();
    }
    // PlaySound(TEXT(MOVE_RES), NULL, SND_FILENAME | SND_SYNC);
    checkerboard[y][x] = Gamer;
}

void Play(void)
{
    Move();

    if (Judge(y, x))
    {
        GameState = State_Win;
        winA += (Gamer==GamerA? 1 : 0);
        winB += (Gamer==GamerB? 1 : 0);
        Draw(); /* 输出获胜次数 */
        printf("\r      玩家%d获胜!!               \n      是否进行第%d场游戏(Y/N):", Gamer, ++turn);  /* 更新 turn 并询问是否继续 */
        StaManager();
    }
    else if ((++step) > (CHECKER_BOARD_SIZE*CHECKER_BOARD_SIZE))    /* 更新 step 判断是否为平局 */
    {
        GameState = State_Tie;
        printf("\r      此局为平手!!               \n      是否进行第%d场游戏(Y/N):",  ++turn);  /* 更新 turn 并询问是否继续 */
        StaManager();
    }
    else
    {
        GameState = State_Normal;
        Gamer = Gamer==GamerA ? GamerB : GamerA;  /* 更新 Gamer */
        Draw(); /* 输出下棋者信息 */
        Play();
    }
}

void Count(char* ptrWinflag, const char DirectionValue)
{
    if (ptrWinflag == NULL)
    {
        fprintf(stderr, "空指针错误！\n");
        exit(EXIT_FAILURE);
    }

    char i, j, WinFlag;
    WinFlag = *ptrWinflag;
    Direction.value = DirectionValue;
    i = y; j = x;

    while (IN_CHECKERBOARD_CONDICTION(i, j) && WinFlag <= 5)
    {
        i += Direction.yPositive - Direction.yNegative;
        j += Direction.xPositive - Direction.xNegative;
        CHECK();
    }

    *ptrWinflag = WinFlag;
}

bool Judge(char y, char x)
{
    for(char i = 0; i<DIRECTION_NUM ;i++)
    {
        char WinFlag = 1;
        Count(&WinFlag,JudgeDirection[i][0]);
        Count(&WinFlag,JudgeDirection[i][1]);
        if (WinFlag >= WIN_COUNT_NUM)
           return TRUE;
    }

    return FALSE;
}

                           /*_oo0oo_\
                           088888880\
                           88” . “88\
                           (| -_- |)\
                            0\\ = /0\\
                        ___/'---'\___\\
                      .' \\\\|     |// '.
                    / \\\\|||  :  |||// \\\
                    /_ ||||| -:- |||||- \\\
                    |   | \\\\\\  -  /// |   |\
                    | \\_|  ''\---/''  |_/ |\
                   \\  .-\\__  '-'  __/-.  /
                ___'. .'  /--.--\\  '. .'___
                ... '<  '.___\\_<|>_/___.' >'  ...
            | | : '-  \\'.;'\\ _ /';.'/ - ' : | |\
            \\  \\ '_.   \\_ __\\ /__ _/   .-' /  /
        ====='-.____'.___ \\_____/___.-'____.-'=====
                            '=---='\
                                                        
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"*/
        /*2025.01.28 , by Dettweiler Wong*/