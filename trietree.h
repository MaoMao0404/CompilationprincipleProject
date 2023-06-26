#ifndef TRIE_TYPES_H
#define TRIE_TYPES_H
#ifndef TRIE_TYPE
#define TRIE_TYPE
#include <QDebug>
#include <stdbool.h>
#define MAX 260

    typedef struct TrieNode {
        char val;      // 存储单个字符
        bool isEnd;    // 标记单词最后一个字符，即叶子节点
        struct TrieNode *next[MAX];
    } *Trie, TrieNode;

    TrieNode *create_node(int val);
    void insert_trie(Trie trie, const char *str);  // 插入字符串
    void search_trie(Trie *trie, const char *str);   // 查找词组是否在字典树中
    void delete_trie(Trie *trie);     // 删除字典树
    bool get_word_by_last_char(Trie tire, char ch, int pos,char chBuff[],int buffPos);
#endif

#endif // TRIE_TYPES_H
