
/* TINY 编译器的实用函数 */


#ifndef UTIL_H
#define UTIL_H

#include "global.h"

//将单词及其词素打印到列表文件
void printToken(TokenType, const char*);

//为语法树构造创建一个新的语句节点
TreeNode * newStmtNode(StmtKind);

//创建用于语法树构造的新表达式节点
TreeNode * newExpNode(ExpKind);

//分配并创建现有字符串的新副本
char * copyString(char *);

//使用缩进指示子树将语法树打印到列表文件
void printTree(TreeNode *);


#endif // UTIL_H
