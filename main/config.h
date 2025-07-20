#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

#undef COMPILER_MSVC
#ifdef COMPILER_MSVC
#pragma comment(lib,"winmm.lib") /* 链接Windows多媒体库*/
#define _CRT_SECURE_NO_WARNINGS /* 用于关闭该编译器编译scanf等函数产生的安全警告*/
#endif

#define COMPILER_GCC
#ifdef COMPILER_GCC
#endif

#define TO_STRING(x) #x
#define MAKE_PATH(dir, file) dir TO_STRING(file)

#define RES_DIR "./resource/"
#define RES(x) MAKE_PATH(RES_DIR , x)
#define BGM_RES RES(BGM.wav)
#define MOVE_RES RES(Move.wav)

#define WIN_COUNT_NUM 5
#define CHECKER_BOARD_SIZE 15
#define BUFFER_MAX_NUM 1000

#define KEYCODE_R 77
#define KEYCODE_L 75
#define KEYCODE_U 72
#define KEYCODE_D 80
#define KEYCODE_ESC 27

#define DIRECTION_NUM   4
#define POLARITY_NUM    2
#define DIRECTION_INIT  (0b0000u)
#define DIRECTION_U     (0b0010u)
#define DIRECTION_D     (0b0001u)
#define DIRECTION_L     (0b1000u)
#define DIRECTION_R     (0b0100u)
#define DIRECTION_LU    (DIRECTION_L | DIRECTION_U)
#define DIRECTION_LD    (DIRECTION_L | DIRECTION_D)
#define DIRECTION_RU    (DIRECTION_R | DIRECTION_U)
#define DIRECTION_RD    (DIRECTION_R | DIRECTION_D)

typedef enum 
{
    NoGamer,
    GamerA,
    GamerB
} TypeGamer;

typedef enum 
{
    State_Normal ,
    State_Win,
    State_Tie,
    State_WaitRST,
    State_WaitESC

} TypeState;

typedef union
{
    struct 
    {
        unsigned char yPositive : 1;
        unsigned char yNegative : 1;
        unsigned char xPositive : 1;  
        unsigned char xNegative : 1; // 使用位域来存储
    };
    unsigned char value;  // 用于访问整个字节
} unionDirection;

#define DEBUG  (FALSE)

#if (DEBUG == TRUE)
#define dmsg(format,...)    printf(format,##__VA_ARGS__)
#else
#define dmsg(format)
#endif

void Draw(void);
void Init(void);
void Play(void);
void Update(void);
void Select(void);
void Move(void);
void StaManager(void);
void Count(char* ptrWinflag, const char DirectionValue, char i, char j, TypeGamer Gamer);
bool Judge();
int AlphaBeta(TypeGamer board[CHECKER_BOARD_SIZE+1][CHECKER_BOARD_SIZE+1], int depth, int alpha, int beta, int maximizingPlayer);
void RobotMove();
int Evaluate(TypeGamer Gamer);
bool NearbyJudge(int i, int j);