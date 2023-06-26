
/* TINY 编译器的扫描器 */


#ifndef SCAN_H
#define SCAN_H
#include "global.h"

#define MAXTOKENLEN 40

//tokenString 数组存储每个标记的词法
extern char tokenString[MAXTOKENLEN+1];

//返回源程序中的下一个token
TokenType getToken(void);
//重置Scan相关的参数，以便下次使用
void resetScan();

#endif
