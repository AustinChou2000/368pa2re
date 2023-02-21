#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "helper.h"

void writeDim(TreeNode* tn){
    int llen = tn->left->length;
    int rlen = tn->right->length;
    int lwid = tn->left->width;
    int rwid = tn->right->width;

    char temp[20] = {'\0'};
    char dummy[8] = {'\0'};
    int count = 0;
    int idx = 0;
    char c = '\0';

    // case H
    if(tn->c == 'H'){
        /* width is the larger of right and left child 
        while length is the sum of left child and right child lengths */
        tn->width = (lwid > rwid)? lwid : rwid;
        tn->length = llen + rlen;
        temp[count]='(';
        count++;
        int wid = (lwid > rwid)? lwid : rwid;
        tn->width = wid;
        int len = llen + rlen;
        tn->length = len;
        while(wid != 0){
            c = (char)(wid % 10 + 48);
            dummy[idx] = c;
            idx++;
            count++;
            wid /= 10;
        }
        int i = 1;
        for(idx = 1; idx < count; idx++){
            temp[idx] = dummy[count - i - 1];
            i++;
        }
        temp[count] = ',';
        count++;
        idx = count;
        int idx2 = 0;
        while(len != 0){
            c = (char)(len % 10 + 48);
            dummy[idx2] = c;
            idx2++;
            count++;
            len /= 10;
        }
        i = count - idx;
        for(; idx < count; idx++){
            temp[idx] = dummy[i-1];
            i--;
        }
        temp[count] = ')';
        count++;
        temp[count] = '\n';
        count++;
        tn->dim = malloc(sizeof(char)*count);
        strncpy(tn->dim, temp, count);
    }

    // case V
    if(tn->c == 'V'){
        /* length is the larger of right and left child 
        while width is the sum of left child and right child widths */
        tn->length = (llen > rlen)? llen : rlen;
        tn->width = lwid + rwid;
        temp[count]='(';
        count++;
        int len = (llen > rlen)? llen : rlen;
        tn->length = len;
        int wid = lwid + rwid;    
        tn->width = wid;
        while(wid != 0){
            c = (char)(wid % 10 + 48);
            dummy[idx] = c;        
            idx++;
            count++;
            wid /= 10;
        }
        int i = 1;
        for(idx = 1; idx < count; idx++){
            temp[idx] = dummy[count - i - 1];
            i++;
        }
        temp[count] = ',';
        count++;
        idx = count;
        int idx2 = 0;
        while(len != 0){
            c = (char)(len % 10 + 48);
            dummy[idx2] = c;
            idx2++;
            count++;
            len /= 10;
        }
        i = count - idx;
        for(; idx < count; idx++){
            temp[idx] = dummy[i-1];
            i--;
        }
        temp[count] = ')';
        count++;
        temp[count] = '\n';
        count++;
        tn->dim = malloc(sizeof(char)*count);
        strncpy(tn->dim, temp, count);
    }
}

/* write int to string and fwrite into file for output */
void printIntToStr(FILE* fp, TreeNode* tn, int wid, int len){
    char temp[20] = {'\0'};
    char dummy[8] = {'\0'};
    int count = 0;
    int idx = 0;
    char c = '\0';

    temp[count]='(';
    count++;
    if(wid == 0){
        dummy[0] = '0';
        count++;
    }
    while(wid != 0){
        c = (char)(wid % 10 + 48);
        dummy[idx] = c;        
        idx++;
        count++;
        wid /= 10;
    }
    int i = 1;
    for(idx = 1; idx < count; idx++){
        temp[idx] = dummy[count - i - 1];
        i++;
    }
    temp[count] = ',';
    count++;
    idx = count;
    int idx2 = 0;
    if(len == 0){
        dummy[0] = '0';
        count++;
    }
    while(len != 0){
        c = (char)(len % 10 + 48);
        dummy[idx2] = c;
        idx2++;
        count++;
        len /= 10;
    }
    
    i = count - idx;
    for(; idx < count; idx++){
        temp[idx] = dummy[i-1];
        i--;
    }
    temp[count] = ')';
    count++;
    temp[count] = '\n';
    count = 0;
    while(temp[count] != '\n'){
        fwrite(&temp[count], sizeof(char), 1, fp);
        count++;
    }  
}
