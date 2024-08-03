#pragma once
typedef float 浮点数;
typedef double 双浮点数;
typedef int 整数型;
typedef short 短整数型;
typedef unsigned int 无符号整数型;
typedef const int 常量整数型;
typedef void 无属性;
typedef void* 无属性指针;
#define 或 | 
#define 与 &
#define 异或 ^
#define 且 &&
#define 或 ||
#define 类 class
#define 结构体 struct
#define 如果(a) if##(a)
#define 计次循环首(a,b,c) for(int i=a;b<a;c++)
#define 判断循环首(a) while##(a)