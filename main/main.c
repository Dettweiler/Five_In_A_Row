#include "config.h"

#define IN_CHECKERBOARD_CONDICTION(y, x) ((x) > 0 && (x) <= CHECKER_BOARD_SIZE && (y) > 0 && (y) <= CHECKER_BOARD_SIZE)

#define CHECK(Gamer,WinFlag)    if (checkerboard[i][j] == (Gamer))    \
                                {                                   \
                                    (WinFlag)++;                      \
                                }                                   \
                                else                                \
                                {                                   \
                                    break;                          \
                                }

#define SWITCH_PLAYER(Gamer) ((Gamer) == GamerA ? GamerB : GamerA)

/* 数组表示棋盘状态，空白；【 0 】，黑子：【 1 】，白子：【 2 】 */
TypeGamer checkerboard[CHECKER_BOARD_SIZE+1][CHECKER_BOARD_SIZE+1];

const char JudgeDirection[DIRECTION_NUM][POLARITY_NUM] = 
{
    {DIRECTION_L , DIRECTION_R },
    {DIRECTION_U , DIRECTION_D },
    {DIRECTION_LU, DIRECTION_RD},
    {DIRECTION_LD, DIRECTION_RU}
};

unionDirection Direction;    /* 横纵坐标变化方向 */
TypeGamer Gamer;             /* 当前玩家 */
TypeGamer Robot;
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
            /* 棋子 */
            if (GamerA == checkerboard[i][j])
                strcat(buffer,"●");
            else if (GamerB == checkerboard[i][j])
                strcat(buffer,"◎");
            /* 首行空格 */
            else if(0 == i)
                strcat(buffer,"  "); 
            /* 首列空格  */
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
        system("color E0");   /* 窗口及字体颜色 */
        system("cls");
        Robot = GamerB;
        turn = 1;             /* 游戏回合 */  
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
    TypeGamer temp;
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
    if(Gamer == Robot)
    {
        RobotMove();
    }
    else
    {    
        fflush(stdin);
        Select();

        if(NoGamer != checkerboard[y][x])
        {
            printf("\n这个位置已经有棋子了, 请重新下子。");
            Move();
        }
        // PlaySound(TEXT(MOVE_RES), NULL, SND_FILENAME | SND_SYNC);
        checkerboard[y][x] = Gamer;
    }
}

void Play(void)
{
    Move();

    if (Judge())
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
        Gamer = SWITCH_PLAYER(Gamer);  /* 更新 Gamer */
        Draw(); /* 输出下棋者信息 */
        Play();
    }
}

void Count(char* ptrWinflag, const char DirectionValue, char i, char j, TypeGamer Gamer)
{
    if (ptrWinflag == NULL)
    {
        fprintf(stderr, "空指针错误！\n");
        exit(EXIT_FAILURE);
    }

    char WinFlag;
    WinFlag = *ptrWinflag;
    Direction.value = DirectionValue;

    while (IN_CHECKERBOARD_CONDICTION(i, j) && WinFlag <= 5)
    {
        i += Direction.yPositive - Direction.yNegative;
        j += Direction.xPositive - Direction.xNegative;
        CHECK(Gamer,WinFlag);
    }

    *ptrWinflag = WinFlag;
}

bool Judge()
{
    for(char i = 0; i<DIRECTION_NUM ;i++)
    {
        char WinFlag = 1;
        for(char j = 0; j<POLARITY_NUM ;j++)
        {
            Count(&WinFlag,JudgeDirection[i][j],y,x,Gamer);
            if (WinFlag >= WIN_COUNT_NUM)
                return TRUE;
        }
    }

    return FALSE;
}

// Alpha-Beta剪枝算法实现
int AlphaBeta(TypeGamer board[CHECKER_BOARD_SIZE+1][CHECKER_BOARD_SIZE+1], int depth, int alpha, int beta, int maximizingPlayer) {
    if(depth == 0) 
        return Evaluate(Robot) - Evaluate(SWITCH_PLAYER(Robot));
    
    if(maximizingPlayer) 
    {
        int maxEval = -9999;
        for(int i=1; i<=CHECKER_BOARD_SIZE; i++) 
        {
            for(int j=1; j<=CHECKER_BOARD_SIZE; j++) 
            {
                if(board[i][j] == NoGamer) 
                { // 空位
                    board[i][j] = Robot; // AI下子
                    int eval = AlphaBeta(board, depth-1, alpha, beta, 0);
                    board[i][j] = NoGamer; // 撤销
                    maxEval = (eval > maxEval) ? eval : maxEval;
                    alpha = (alpha > eval) ? alpha : eval;
                    if(beta <= alpha) 
                        break; // β剪枝
                }
            }
        }
        return maxEval;
    } 
    else 
    {
        int minEval = 9999;
        for(int i=1; i<=CHECKER_BOARD_SIZE; i++) 
        {
            for(int j=1; j<=CHECKER_BOARD_SIZE; j++) 
            {
                if(board[i][j] == NoGamer) 
                {
                    board[i][j] = SWITCH_PLAYER(Robot); // 玩家下子
                    int eval = AlphaBeta(board, depth-1, alpha, beta, 1);
                    board[i][j] = NoGamer; // 撤销
                    minEval = (eval < minEval) ? eval : minEval;
                    beta = (beta < eval) ? beta : eval;
                    if(beta <= alpha) 
                        break; // α剪枝
                }
            }
        }
        return minEval;
    }
}

// AI自动下棋函数
void RobotMove() {
    int bestScore = -9999;
    int bestMove[2] = {0};
    
    for(int i=1; i<=CHECKER_BOARD_SIZE; i++) 
    {
        for(int j=1; j<=CHECKER_BOARD_SIZE; j++) 
        {
            if(checkerboard[i][j] == NoGamer && NearbyJudge(i,j)) 
            {
                checkerboard[i][j] = Robot; // 假设AI下子
                int score = AlphaBeta(checkerboard, 3, -9999, 9999, 0); // 搜索深度3层
                checkerboard[i][j] = NoGamer; // 撤销
                
                if(score > bestScore) 
                {
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }
    
    if(bestMove[0] != 0) 
        checkerboard[bestMove[0]][bestMove[1]] = Robot; // 实际下子
}

int Evaluate(TypeGamer Gamer)
{
    int score = 0;
    for(int i=1; i<=CHECKER_BOARD_SIZE; i++) 
    {
        for(int j=1; j<=CHECKER_BOARD_SIZE; j++) 
        {
            if(checkerboard[i][j] == Gamer) 
            {
                for(char ni = 0; ni<DIRECTION_NUM ;ni++)
                {
                    char WinFlag = 1;
                    for(char nj = 0; nj<POLARITY_NUM ;nj++)
                    {
                        Count(&WinFlag,JudgeDirection[ni][nj],y,x,Gamer);
                    }
                    score += WinFlag * WinFlag;
                }
            }
        }
    }
    return score;
}
// 判断是否在已有棋子周围
bool NearbyJudge(int i, int j) 
{
    for(int di = -2; di <= 2; di++) 
    {
        for(int dj = -2; dj <= 2; dj++) 
        {
            int ni = i + di, nj = j + dj;
            if(checkerboard[ni][nj] != NoGamer) 
                return true;
        }
    }
    return false;
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