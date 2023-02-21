#ifndef STRUCT_H
#define STRUCT_H

typedef struct TreeNode{
    int leaf;
    int height;
    char c;
    char* label;
    int width;
    int length;
    char* dim;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Node{
    TreeNode* tnptr;
    struct Node* next;
} Node;

typedef struct NodeTop{
    Node* top;
} NodeTop;

#endif
