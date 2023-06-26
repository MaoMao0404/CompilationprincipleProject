
/* TINY 编译器的全局类型和变量 */
/* 必须位于其他包含文件之前 */


#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED：保留字数量*/

#define MAXRESERVED 18

typedef enum
    /* book-keeping tokens */
   {ENDFILE,ERROR,
    /* reserved words */
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
    /* multicharacter tokens */
    ID,NUM,
    /* special symbols */
    /*LPAREN是左括号,RPAREN是右括号，SEMI是分号*/
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI,
    WHILE,ENDWHILE,DO,FOR,TO,ENDDO,DOWNTO,MOD,ME,RE,GT,LE,GE,NE,AND,OR,NOT,ROR,RAND,RC,POW
   } TokenType;

extern FILE* source; //源代码文本文件
extern FILE* listing; //输出文本文件
extern FILE* code;
extern int lineno; //列表行号

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK,DoWhileK,ForK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;

//类型检查
typedef enum {Void,Integer,Boolean} ExpType;


#define MAXCHILDREN 4

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type;
   } TreeNode;

//用于跟踪的标志
extern int EchoSource;//使源程序在解析期间用行号回显到列表文件
extern int TraceScan;//在扫描程序识别每个标记时将标记信息打印到列表文件中
extern int TraceParse;//使语法树以线性化的形式打印到列表文件中（对子结点使用缩进）
extern int TraceAnalyze;//向列表文件报告符号表插入和查找
extern int TraceCode;//在生成代码时将注释写入TM代码文件
extern int Error;//发生错误时阻止进一步的传递
#endif
