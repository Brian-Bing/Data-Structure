//
//  main.c
//  顺序表
//
//  Created by 史晓冰 on 2023/9/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERROR -1
#define OK 1;

typedef int ElemType; // 抽象化数据类型;
typedef int Status; // 抽象化返回值类型;

typedef struct seqList {
    int n;
    int maxLength;
    ElemType *element;
} SeqList;

Status Init(SeqList *L, int maxLength); // 声明初始化函数;
Status Find(SeqList L, int i, ElemType *x); // 声明查找函数;
Status Insert(SeqList *L, int i, ElemType x); // 声明插入函数;
Status Delete(SeqList *L, int i); // 声明删除函数;
Status Output(SeqList *L);
Status Reverse(SeqList *L);
void Intersection(SeqList *A, SeqList *B, SeqList *C);
void randAss(SeqList *L);




int main(int argc, const char * argv[]) {
    SeqList l1,l2,l3;
    Init(&l1, 20);
    Init(&l2, 20);
    Init(&l3, 20);
    l1.n = 10; l2.n = 12; l3.n = 12;
    
    randAss(&l1); randAss(&l2);
    Output(&l1);
    Output(&l2);
    Intersection(&l1, &l2, &l3);
    Output(&l3);
    
    return 0;
}



Status Init(SeqList *L, int maxLength) {
    L->n = 0;
    L->maxLength = maxLength;
    L->element = (ElemType*)malloc(sizeof(ElemType)*maxLength);
    if (L->element == NULL) {
        printf("Failed to allocate memory!"); // 分配内存失败;
        return ERROR;
    }
    return OK;
}

void randAss(SeqList *L) {
    srand((unsigned int)time(NULL));
    for (int i=0; i<L->n; i++) {
        L->element[i] = rand()%10+1;
    }
}


Status Find(SeqList L, int i, ElemType *x) {
    if (i<0 || i>L.n-1) {
        printf("Index out of range!"); // 下标越界;
        return ERROR;
    }
    *x = L.element[i];
    return OK;
}

Status Insert(SeqList *L, int i, ElemType x) {
    if (i<0 || i>L->n-1) {
        printf("Index out of range!"); // 下标越界;
        return ERROR;
    }
    if (L->n == L->maxLength) {
        printf("The list is full!"); // 顺序表已满
        return ERROR;
    }
    for (int j=L->n-1; j>i; j--) {
        L->element[j+1] = L->element[j];
    }
    L->element[i+1] = x;
    L->n++;
    return OK;
}

Status Delete(SeqList *L, int i) {
    if (i<0 || i>L->n-1) {
        printf("Index out of range!"); // 下标越界
        return ERROR;
    }
    if (L->n == 0) {
        printf("The list is empty"); // 顺序表为空
        return ERROR;
    }
    for (int j=i; j<L->n-1; j++) {
        L->element[j] = L->element[j+1];
    }
    L->n--; // 表长减1;
    return OK;
}

Status Output(SeqList *L) {
    if (L->n == 0) {
        printf("The list is empty!");
        return ERROR;
    }
    for (int i=0; i<L->n; i++) {
        printf("%d ",L->element[i]);
    }
    printf("\n");
    return OK;
}

Status Reverse(SeqList *L) {
    int i,j;
    ElemType temp;
    if (L->n == 0) {
        printf("The list is empty!");
        return ERROR;
    }
    for (i=0,j=L->n-1; i<j; i++,j--) {
        temp = L->element[i];
        L->element[i] = L->element[j];
        L->element[j] = temp;
    }
    return OK;
}


void Intersection(SeqList *A, SeqList *B, SeqList *C) {
    int k = 0;
    if (A->n<B->n) {
        for (int i=0; i<A->n; i++) {
            for (int j=0; j<B->n; j++) {
                if (A->element[i] == B->element[j]) {
                    C->element[k++] = A->element[i];
                    break;
                }
            }
        }
        for (int i=0; i<k-1; i++) {
            for (int j=i; j<k; j++) {
                if (C->element[i] == C->element[j]) {
                    for (int m=j; m<k-1; m++) {
                        C->element[m] = C->element[m+1];
                    }
                }
            }
        }
            
    }else {
        for (int i=0; i<B->n; i++) {
            for (int j=0; j<A->n; j++) {
                if (B->element[i] == A->element[j]) {
                    C->element[k++] = B->element[i];
                    break;
                }
            }
        }
        for (int i=0; i<k-1; i++) {
            for (int j=i; j<k; j++) {
                if (C->element[i] == C->element[j]) {
                    for (int m=j; m<k-1; m++) {
                        C->element[m] = C->element[m+1];
                    }
                }
            }
        }
            
    }
    
}
