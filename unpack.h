#ifndef UNPACK_H
#define UNPACK_H

TreeNode* unpack(FILE* ); // unpack the input file 
/* for constructing tree */
void push(TreeNode*, NodeTop*);
Node* pop(NodeTop* ); 
bool isEmptyStack(NodeTop*);
TreeNode* buildTreeNode(int,char,char*,int, char*, long, int,int);
Node* buildListNode(TreeNode* );
char* readNumbers(FILE*, char*, char, long*, int*, int*, int*); // read label width and length
void destroyList(NodeTop* );
void destroyTree(TreeNode* );

#endif
