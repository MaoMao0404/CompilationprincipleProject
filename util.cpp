

/* TINY编译器实用函数的实现  */

#include "global.h"
#include "util.h"


//增加保留字
void printToken(TokenType token, const char* tokenString)
{
    switch (token)
    {
    case IF:
    case THEN:
    case ELSE:
    case END:
    case REPEAT:
    case UNTIL:
    case READ:
    case WRITE:
    //do,while,for,and,or,not,endwhile,to,enddo,downto
    case DO:
    case WHILE:
    case FOR:
    case ENDWHILE:
    case ENDDO:
        fprintf(listing, "reserved word: %s\n", tokenString);
        break;
    //修改ASSIGN为=
    //修改判断等于是==
    case ASSIGN: fprintf(listing, "=\n"); break;//modified
    case LT: fprintf(listing, "<\n"); break;
    case EQ: fprintf(listing, "==\n"); break;//modified
    case LPAREN: fprintf(listing, "(\n"); break;
    case RPAREN: fprintf(listing, ")\n"); break;
    case SEMI: fprintf(listing, ";\n"); break;
    case PLUS: fprintf(listing, "+\n"); break;
    case MINUS: fprintf(listing, "-\n"); break;
    case TIMES: fprintf(listing, "*\n"); break;
    case OVER: fprintf(listing, "/\n"); break;
    case ENDFILE: fprintf(listing, "EOF\n"); break;
    case AND: fprintf(listing, "and\n"); break;
    case OR: fprintf(listing, "or\n"); break;
    case NOT: fprintf(listing, "not\n"); break;
    case TO: fprintf(listing, "to\n"); break;
    case DOWNTO: fprintf(listing, "to\n"); break;
    //added
    //MOD,ME,RE,GT,LE,GE,NE,ROR,RAND,RC,POW
    case MOD: fprintf(listing, "%%\n"); break;
    case ME: fprintf(listing, "-=\n"); break;
    case RE: fprintf(listing, ":=\n"); break;
    case GT: fprintf(listing, ">\n"); break;
    case LE: fprintf(listing, "<=\n"); break;
    case GE: fprintf(listing, ">=\n"); break;
    case NE: fprintf(listing, "<>\n"); break;
    case ROR: fprintf(listing, "|\n"); break;
    case RAND: fprintf(listing, "&\n"); break;
    case RC: fprintf(listing, "#\n"); break;
    case POW: fprintf(listing, "^\n"); break;
    //
    case NUM:
        fprintf(listing,"NUM, val= %s\n", tokenString);
        break;
    case ID:
        fprintf(listing,"ID, name= %s\n", tokenString);
        break;
    case ERROR:
        fprintf(listing,"ERROR: %s\n", tokenString);
        break;
    default: /* should never happen */
        fprintf(listing, "Unknown token: %d\n", token);
    }
}

//为语法树构造创建新的语句节点
TreeNode* newStmtNode(StmtKind kind)
{
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
    }
    return t;
}

//创建新表达式用于语法树构造的节点
TreeNode* newExpNode(ExpKind kind)
{
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
        t->type = Void;
    }
    return t;
}

//分配并创建现有字符串的新副本
char* copyString(char* s)
{
    int n;
    char* t;
    if (s == NULL) return NULL;
    n = strlen(s) + 1;
    t = (char*)malloc(n);//modified
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else strcpy(t, s);
    return t;
}

//printTree 使用变量缩进来存储当前要缩进的空格数
static int indentno = 0;//modified

#define INDENT indentno+=2
#define UNINDENT indentno-=2

//缩进
static void printSpaces(void)
{
    int i;
    for (i = 0; i < indentno; i++)
        fprintf(listing, " ");
}

//打印语法树
void printTree(TreeNode* tree)
{
    int i;
    INDENT;
    while (tree != NULL) {
        printSpaces();
        if (tree->nodekind == StmtK)
        {
            switch (tree->kind.stmt)
            {
            case IfK:
                fprintf(listing, "If\n");
                break;
            case RepeatK:
                fprintf(listing, "Repeat\n");
                break;
            case AssignK:
                fprintf(listing, "Assign to: %s\n", tree->attr.name);
                break;
            case ReadK:
                fprintf(listing, "Read: %s\n", tree->attr.name);
                break;
            case WriteK:
                fprintf(listing, "Write\n");
                break;
                //DoWhileK,ForK,RegularExprK
                //添加
            case DoWhileK:
                fprintf(listing, "DoWhie\n");
                break;
            case ForK:
                fprintf(listing, "For\n");
                break;
            default:
                fprintf(listing, "Unknown ExpNode kind\n");
                break;
            }
        }
        else if (tree->nodekind == ExpK)
        {
            switch (tree->kind.exp) {
            case OpK:
                fprintf(listing, "Op: ");
                printToken(tree->attr.op, "\0");
                break;
            case ConstK:
                fprintf(listing, "Const: %d\n", tree->attr.val);
                break;
            case IdK:
                fprintf(listing, "Id: %s\n", tree->attr.name);
                break;
            default:
                fprintf(listing, "Unknown ExpNode kind\n");
                break;
            }
        }
        else fprintf(listing, "Unknown node kind\n");
        for (i = 0; i < MAXCHILDREN; i++)
            printTree(tree->child[i]);
        tree = tree->sibling;
    }
    UNINDENT;
}