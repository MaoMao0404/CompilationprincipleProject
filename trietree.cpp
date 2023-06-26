#include "trietree.h"
#include <malloc.h>
#include <stdio.h>


static TrieNode *queue[1024];  // 数组实现队列


//static TrieNode *create_node(int val);  // 创建新节点
static void traverse_trie(Trie trie);  // 广度遍历字典树


TrieNode *create_node(int val)
{
    // 创建新节点
    TrieNode *newNode;
    newNode = (TrieNode *)malloc(sizeof(TrieNode));

    newNode->val = val;
    newNode->isEnd = false;
    for (int i=0; i<MAX; i++)
    {
        newNode->next[i] = NULL;
    }

    return newNode;
}


static void traverse_trie(Trie *trie)
{
    // 广度优先遍历
    TrieNode *node = *trie;
    int head = 0, tail = 0;       // 队列头尾指针

    queue[tail++] = node;         // 头节点入队
    while (head != tail)
    {
        node = queue[head++];     // 节点出队
        for (int i=0; i<MAX; i++)
        {
            if (node->next[i])
            {
                queue[tail++] = node->next[i];
            }
        }
    }
}

void insert_trie(Trie trie, const char *str)
{
    // 插入单词到字典树中
    int i = 0, index = 0;

    if (!trie)
    {
        return;
    }

    Trie node = trie;
    while (str[i])
    {

        index = str[i] ;
        if (!node->next[index])
        {
            node->next[index] = create_node(str[i]);
        }
        node = node->next[index];
        i++;
    }
    node->isEnd = true;    // 单词最后一个字母标记为true
}


void search_trie(Trie *trie, const char *str)
{
    /*
        查询单词是否在字典树中，不包括含有相同前缀的
        例如已插入：he，那么h和her都不算在字典树中
    */
    TrieNode *node = *trie;
    int i = 0, index = 0;

    if (!node)
    {
        // 判断是否是空树
        fputs("Trie is null!\n", stdout);
        return;
    }

    while(str[i])
    {
        /*
            比较str中的每一个字符，
            直到走到字符数组结尾或者字典树中不存在对应节点
        */
        index = str[i] - 'a';
        if (!node->next[index])
            break;
        node = node->next[index];
        i++;
    }
    if (node->isEnd && !str[i])
    {
        printf("%s is exist!\n", str);
    }
    else
    {
        printf("%s is not exist!\n", str);
    }
}

bool get_word_by_last_char(Trie tire, char ch, int pos,char chBuff[],int buffPos)
{
    //qDebug()<<pos<<buffPos;
    chBuff[buffPos] = tire->val;
    //qDebug()<<chBuff[1]<<chBuff[2]<<chBuff[3]<<tire->val;
    if(pos == 0)
    {
        if(tire->val == ch && tire->isEnd)
        {
            qDebug()<<"true";
            return true;
        }
        else
        {
            qDebug()<<"false";
            return false;
        }
    }
    for(int i=0;i<MAX;i++){
        if(tire->next[i] != NULL)
        {

            bool ret = get_word_by_last_char(tire->next[i],ch,pos-1,chBuff,buffPos+1);
            if(ret)
            {
                return ret;
            }
        }
    }
    return false;
}

void delete_trie(Trie *trie)
{
    // 释放字典树内存
    int i = 0;

    traverse_trie(trie);  // 存储字典树节点指针到队列中
    while (queue[i])
    {
        free(queue[i++]);
    }
}
