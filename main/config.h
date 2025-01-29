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
#define BGM_RES RES(sound.wav)

#define CHECKER_BOARD_SIZE 15
#define BUFFER_MAX_NUM 1000

#define KEYCODE_R 77
#define KEYCODE_L 75
#define KEYCODE_U 72
#define KEYCODE_D 80

#define DIRECTION_NUM   4
#define DIRECTION_INIT  ((unsigned char)0b0000)
#define DIRECTION_U     ((unsigned char)0b0001)
#define DIRECTION_D     ((unsigned char)0b0010)
#define DIRECTION_L     ((unsigned char)0b1000)
#define DIRECTION_R     ((unsigned char)0b0100)
#define DIRECTION_LU    (DIRECTION_L | DIRECTION_U)
#define DIRECTION_LD    (DIRECTION_L | DIRECTION_D)
#define DIRECTION_RU    (DIRECTION_R | DIRECTION_U)
#define DIRECTION_RD    (DIRECTION_R | DIRECTION_D)

typedef enum 
{
    GamerA = 1u,
    GamerB
} TypeGamer;

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
void Restart(void);
void Count(char* ptrWinflag, const char DirectionValue);
_Bool Judge(char y, char x);