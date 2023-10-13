//
//  main.c
//  一元多项式的基本操作
//
//  Created by Brian on 2023/10/13.
//

#include <stdio.h>
#include <stdlib.h>

// 自定义结点结构体类型, 重命名 struct pNode 为 PNode;
typedef struct pNode {
    int coef; // 数据域-系数
    int exp; // 数据域-指数
    struct pNode *link; // 指针域;
}PNode;

// 自定义多项式结构体类型, 重命名 struct polynominal 为 Polynominal;
typedef struct polynominal {
    PNode *head;
}Polynominal;

void Creat(Polynominal *p);
void Output(Polynominal *);
void Add(Polynominal *p1, Polynominal *p2, Polynominal *p3);
void Multiply(Polynominal *p1, Polynominal *p2, Polynominal *p3);

int main(int argc, const char * argv[]) {
    Polynominal a, b, c;
    printf("用户手动输入创建多项式\n");
    printf("请输入第一个多项式f(x)\n");
    Creat(&a);
    printf("多项式f(x)为:");
    Output(&a);
    printf("请输入第二个多项式g(x)\n");
    Creat(&b);
    printf("多项式g(x)为:");
    Output(&b);
    printf("请初始化辅助多项式h(x)\n");
    Creat(&c);
    printf("多项式f(x)与g(x)相乘的结果为:\n");
    Multiply(&a, &b, &c);
    Output(&c);
    printf("多项式f(x)与g(x)相加的结果为:\n");
    Add(&a, &b, &c);
    Output(&c);
    return 0;
}

// 带表头结点的多项式的创建操作
void Creat(Polynominal *p) {
    PNode *pre, *pn, *q;
    p->head = (PNode *)malloc(sizeof(PNode));
    if (NULL == p->head) { // 如果内存分配失败;
        printf("分配内存失败!\n");
        return;
    }
    p->head->exp = -1;
    p->head->link = NULL;
    for (;;) {
        pn = (PNode *)malloc(sizeof(PNode));
        printf("coef:");
        scanf("%d",&pn->coef);
        printf("exp:");
        scanf("%d",&pn->exp);
        if (pn->exp<0){ // 需要用户手动输入小于0的指数值跳出函数;
            break;
        }
        pre = p->head;
        q = pre->link;
        while (q&&pn->exp<q->exp) {
            pre = q;
            q = q->link;
        }
        pn->link = q;
        pre->link = pn;
    }
}

// 带表头结点的多项式的输出操作
void Output(Polynominal *p) {
    PNode *pn;
    pn = p->head->link; // 工作指针pn指向第一项(头结点);
    if (NULL == pn) { // 如果多项式为空;
        printf("The Polynominal list is empty!\n");
        return;
    }
    while (NULL != pn->link) {
        if (pn->exp == 1) {
            if (pn->coef == 1) {
                printf("(x)+");
            }else if (pn->coef == -1){
                printf("(-x)+");
            }else {
                printf("(%dx)+",pn->coef);
            }
        }else if (pn->exp == 0) {
            printf("(%d)+",pn->coef);
        }else {
            if (pn->coef == 1) {
                printf("(x^%d)+",pn->exp);
            }else if (pn->coef == -1) {
                printf("(-x^%d)+",pn->exp);
            }else {
                printf("(%dx^%d)+",pn->coef,pn->exp);
            }
        }
        pn = pn->link;
    }
    if (pn->exp == 1) {
        if (pn->coef == 1) {
            printf("(x)\n");
        }else if (pn->coef == -1){
            printf("(-x)\n");
        }else {
            printf("(%dx)\n",pn->coef);
        }
    }else if (pn->exp == 0) {
        printf("(%d)\n",pn->coef);
    }else {
        if (pn->coef == 1) {
            printf("(x^%d)\n",pn->exp);
        }else if (pn->coef == -1) {
            printf("(-x^%d)\n",pn->exp);
        }else {
            printf("(%dx^%d)\n",pn->coef,pn->exp);
        }
    }
    return;
}

// 带表头结点的多项式的相加操作
void Add(Polynominal *p1, Polynominal *p2, Polynominal *p3) {
    PNode *pa, *pb, *pc;
    pa = p1->head->link; // 工作指针 pa 指向多项式(链表) p1 的第一项(头结点);
    pb = p2->head->link; // 工作指针 pb 指向多项式(链表) p2 的第二项(头结点);
    pc = p3->head; // 工作指针 pc 指向多项式链表 p3 的表头结点, 下面在Add()函数中称 pc 链为主链表;
                    // p3 为辅助指针, 可以理解为新的"表头";
    while (pa && pb) { // 当 pa 与 pb 都不为 NULL 时, 即没有遍历完其中任何一个多现实时;
        if (pa->exp>pb->exp) { // 如果是大于的情况( pa 指向的结点所对应的指数大于 pb 指向的结点所对应的指数);
            pc->link = pa; // pc 指向的结点指向 pa 指向的结点, 即让指数大的结点连接在主链表上;
            pc = pa; // "更新" pc;
            pa = pa->link; // pa后移, 即指向下一个结点;
        }else if (pb->exp>pa->exp) { // 如果是小于的情况(pb 指向的结点所对应的指数大于 pa 指向的结点所对应的指数);
            pc->link = pb; // pc 指向的结点指向 pb 指向的结点, 即让指数大的结点连接在主链表上;
            pc = pb;
            pb = pb->link;
        }else { // 如果是指数相等的情况;
            pa->coef = pa->coef+pb->coef; // 利用 pa 指向的结点作为接收结点;
            if (pa->coef != 0) { // 系数相加不为0;
                pc->link = pa; // 将 pa 指向的结点连接在主链表上;
                pc = pa;
            }
            pa = pa->link; // pa 后移;
            pb = pb->link; // pb 后移;
        }
    }
    // 跳出上一个循环的条件是 (pa == NULL || pb == NULL)
    if (pa == NULL) { // 如果 pa 为 NULL, 包含两种情况(pb==NULL || pb!=NULL);
        while (pb != NULL) { // 当 pb 不为 NULL;
            pc->link = pb; // 将 p2多项式单链表 剩余的结点全部连接在主链表上;
            pc = pb;
            pb = pb->link;
        }
    }else { // 最后一种情况即 (pa!=NULL && pb==NULL)
        while (pa != NULL) { // 当 pa 不为 NULL;
            pc->link = pa; // 将 p3多项式单链表 剩余的结点全部连接在主链表上;
            pc = pa;
            pa = pa->link;
        }
    }
    pc->link = NULL; // 最后将尾结点赋值为NULL;
}

// 带表头结点的多项式的相乘操作
void Multiply(Polynominal *p1, Polynominal *p2, Polynominal *p3) {
    PNode *pa, *pb, *pc, *q;
    pa = p1->head->link; // pa 是指向 p1 多项式(链表) 第一项(头结点)的工作指针;
    pb = p2->head->link; // pb 是指向 p2 多项式(链表) 第一项(头结点)的工作指针;
    pc = p3->head; // pc 是指向 p3 多项式(链表) 表头结点的工作指针;
    // 进行对多项式p1和p2相乘的操作, 步骤为:p1多项式指数从大到小的每一项依次与p2多项式指数从大到小的每一项相乘, 并用p3链表来接收
    while (pa) {
        while (pb) {
            q = (PNode *)malloc(sizeof(PNode)); // 时间复杂度为O(n^2);
            q->coef = pa->coef * pb->coef;
            q->exp = pa->exp + pb->exp;
            pc->link = q;
            pc = pc->link;
            pb = pb->link; // pb指向下一项
        }
        pa = pa->link; //pa指向下一项
        pb = p2->head->link; // 将指针变量 pb 重新指向 p2 多项式(链表)的第一项(头结点);
    }
    pc->link = NULL;
    /*
     *  pc指向p3多项式(链表)的第二项,
     *  上面的计算表明p3多项式的第一项是由p1多项式的指数最大项与p2多项式的指数最大项相乘所得,
     *  所以一定是唯一最大项, 同理最后一项也一定是唯一最小项;
     */
    pc = p3->head->link->link;
    int tempcoef;
    int tempexp;
    // 按照指数从大到小的顺序完成对p3多项式的排序工作, 同时将指数相同的两项进行合并;
    while (pc->link->link->link != NULL) { // 选择排序法的思想, 当n个元素只需要循环n-1次, 且第一项一定为最大项,最后一项一定为最小项, 所以只需要循环n-3次;
        q = pc->link; // q 指向下一项;
        while (q->link->link != NULL) { // q遍历pc后面除最后一项的所有项;
            if (pc->exp < q->exp) { // 如果pc所指项的指数小于q所指项的指数, 交换两个项的指数与系数;
                tempexp = pc->exp;
                pc->exp = q->exp;
                q->exp = tempexp;

                tempcoef = pc->coef;
                pc->coef = q->coef;
                q->coef = tempcoef;
            }else if (pc->exp == q->exp) { // 如果pc所指项的指数大于q所指项的指数;
                pc->coef = q->coef+pc->coef; // pc指向的结点(项)接收运算结果;
                if (pc->coef == 0) { // 两项相加系数为0;
                    pc->coef = 0; // 将两个结点都标记为特殊结点——"系数为0,指数为-1"
                    pc->exp = -1;
                    q->coef = 0;
                    q->exp = -1;
                }else { // 两项相加系数不为0;
                    q->coef = 0; // 将后面的项标记为特殊结点
                    q->exp = -1;
                }
            }
            q = q->link;
        }
        pc = pc->link;
    }
    pc = p3->head->link->link;
    q = pc->link;
    // "删除标记"结点;
    while (q->link->link != NULL) {
        if (q->exp==-1) {
            pc->link = q->link;
            q->link = NULL;
            free(q);
            q = pc->link;
        }else {
            pc = pc->link;
            q = pc->link;
        }
    }
}
