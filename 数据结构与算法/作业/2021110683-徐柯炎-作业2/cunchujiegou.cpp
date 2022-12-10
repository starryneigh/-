#include <iostream>
#include <ctime>
using namespace std;

#define MAXSIZE 20      //最大容量

typedef int Elementtype;    //元素类型为int
typedef struct SeqList{
    Elementtype element[MAXSIZE];
    int last;   //数组有效长度
}SeqList;       //顺序存储结构

typedef struct LinkList{
    Elementtype element;
    LinkList *next;
}LinkList;      //链式存储结构

//排序（快排）
void sort_seqlist(SeqList *L);
void quick_sort(SeqList *L);
void Qsort(int arr[MAXSIZE], int start, int last);
int partition(int arr[MAXSIZE], int start, int last);

//顺序存储结构相关函数
void Print_seqlist(SeqList *L);
void delete_seqlist(SeqList *L, Elementtype a);
SeqList* delete_repeat_seqlist(SeqList *L);
SeqList* reverse_seqlist(SeqList *L);
SeqList* k_move_seqlist_left(SeqList *L, int k);
SeqList* k_move_seqlist_right(SeqList *L, int k);
SeqList* hebing_seqlist(SeqList *L1, SeqList *L2);

//链式存储结构相关函数
void Print_linklist(LinkList *L);
void delete_linklist(LinkList *L, Elementtype a);
void delete_repeat_linklist(LinkList *L);
void reverse_linklist(LinkList *L);
LinkList* reverse(LinkList *p);
void k_move_linklist_left(LinkList *L, int k);
void k_move_linklist_right(LinkList *L, int k);
LinkList* hebing_linklist(LinkList *L1, LinkList *L2);

//主函数
int main(){
    //顺序存储部分
    SeqList *L = new SeqList;
    srand(time(0));                 //随机
    for(int i=0; i<MAXSIZE; i++){
        L->element[i] = rand()%100+1;   //随机初始化
    }
    L->last = MAXSIZE;

    sort_seqlist(L);        //排序

    //初始化
    L->element[0] = 0;
    L->element[1] = 1;
    L->element[2] = 1;
    L->element[3] = 0;
    L->element[4] = 2;
    L->element[5] = 0;
    L->element[6] = 3;
    cout<<"初始化L:"<<endl;
    Print_seqlist(L);

    //测试删除给定元素的算法
    delete_seqlist(L, 0);
    cout<<"测试删除给定元素的算法(删除元素0):"<<endl;
    Print_seqlist(L);

    //测试对于已排好序的线性表，删除所有重复元素的算法
    L = delete_repeat_seqlist(L);
    cout<<"测试对于已排好序的线性表，删除所有重复元素的算法:"<<endl;
    Print_seqlist(L);

    //测试线性表“逆置”算法
    L = reverse_seqlist(L);
    cout<<"测试线性表“逆置”算法:"<<endl;
    Print_seqlist(L);

    //测试线性表循环左移k位的算法
    L = k_move_seqlist_left(L, 3);
    cout<<"测试线性表循环左移k位的算法(k=3):"<<endl;
    Print_seqlist(L);

    //测试线性表循环右移k位的算法
    L = k_move_seqlist_right(L, 3);
    cout<<"测试线性表循环右移k位的算法(k=3):"<<endl;
    Print_seqlist(L);

    //初始化L1，L2
    cout<<"初始化L1，L2:"<<endl;
    SeqList *L1 = new SeqList, *L2 = new SeqList;
    for(int i=0; i<MAXSIZE/2; i++){
        L1->element[i] = rand()%100+1;   //随机初始化
    }
    L1->last = MAXSIZE/2;
    sort_seqlist(L1);
    cout<<"L1 = ";
    Print_seqlist(L1);

    for(int i=0; i<MAXSIZE/2; i++){
        L2->element[i] = rand()%100+1;   //随机初始化
    }
    L2->last = MAXSIZE/2;
    sort_seqlist(L2);
    cout<<"L2 = ";
    Print_seqlist(L2);

    //测试合并两个已排好序的线性表的算法
    L = hebing_seqlist(L1, L2);
    cout<<"测试合并两个已排好序的线性表的算法(合并L1，L2):"<<endl;
    Print_seqlist(L);

    //链式存储部分
    LinkList *T = new LinkList;
    T->element = -999;
    LinkList *q = T;
    for(int i=0; i<MAXSIZE; i++){       //初始化且以排好序
        LinkList *p = new LinkList;
        p->element = i/2;
        p->next = NULL;
        q->next = p;
        q = q->next;
    }
    cout<<"初始化T:"<<endl;
    Print_linklist(T);

    //测试删除给定元素的算法
    delete_linklist(T, 5);
    cout<<"测试删除给定元素的算法:"<<endl;
    Print_linklist(T);
    
    //测试对于已排好序的线性表，删除所有重复元素的算法
    delete_repeat_linklist(T);
    cout<<"测试对于已排好序的线性表，删除所有重复元素的算法:"<<endl;
    Print_linklist(T);

    //测试线性表“逆置”算法
    reverse_linklist(T);
    cout<<"测试线性表“逆置”算法:"<<endl;
    Print_linklist(T);

    //测试线性表循环左移k位的算法
    k_move_linklist_left(T, 4);
    cout<<"测试线性表循环左移k位的算法(k=4):"<<endl;
    Print_linklist(T);

    //测试线性表循环右移k位的算法
    k_move_linklist_right(T, 4);
    cout<<"测试线性表循环右移k位的算法(k=4):"<<endl;
    Print_linklist(T);

    LinkList *S = new LinkList;
    LinkList *R;
    S->element = -999;
    q = S;
    for(int i=0; i<MAXSIZE; i++){
        LinkList *p = new LinkList;
        p->element = 2*i;
        p->next = NULL;
        q->next = p;
        q = q->next;
    }
    reverse_linklist(T);
    cout<<"初始化T:"<<endl;
    Print_linklist(T);
    cout<<"初始化S:"<<endl;
    Print_linklist(S);
    
    //测试合并两个已排好序的线性表的算法
    R = hebing_linklist(T, S);
    cout<<"测试合并两个已排好序的线性表的算法(合并T, S):"<<endl;
    Print_linklist(R);
    return 0;
}

LinkList* hebing_linklist(LinkList *L1, LinkList *L2){
    LinkList *L = new LinkList;
    LinkList *p = L1->next;
    LinkList *q = L2->next;
    LinkList *r = L;
    while(p || q){
        if(!q){
            r->next = p;
            break;
        }
        else if(!p){
            r->next = q;
            break;
        }
        else{
            LinkList *s = new LinkList;
            s->next = NULL;
            r->next = s;
            if(p->element < q->element){
                s->element = p->element;
                r = r->next;
                p = p->next;
            }
            else{
                s->element = q->element;
                r = r->next;
                q = q->next;
            }
        }
        
    }
    return L;
}

void k_move_linklist_right(LinkList *L, int k){
    LinkList *p = L->next;
    LinkList *q = L->next;
    LinkList *r = L->next;
    int count = 0;
    while(count!=k && p){
        p = p->next;
        count++;
    }
    while(p->next){
        p = p->next;
        q = q->next;
    }
    p->next = L->next;
    L->next = q->next;
    q->next = NULL;
}

void k_move_linklist_left(LinkList *L, int k){
    LinkList *p = L->next;
    LinkList *q = L->next;
    LinkList *r = L->next;
    int count = 0;
    while(count!=k && p){
        p = p->next;
        count++;
    }
    while(r->next){
        r = r->next;
    }
    r->next = q;
    while(q != r){
        p = p->next;
        q = q->next;
    }
    L->next = p->next;
    p->next = NULL;
}

void reverse_linklist(LinkList *L){
    L->next = reverse(L->next);
}

LinkList* reverse(LinkList *p){
    if(!p->next){
        return p;
    }
    LinkList *head;
    LinkList *q, *r;
    head = reverse(p->next);
    r = head;
    q = p; 
    q->next = NULL;
    while(r->next){
        r = r->next;
        
    }
    r->next = q;
    return head;
}

void delete_repeat_linklist(LinkList *L){
    LinkList *p = L->next;
    LinkList *q = L;
    while(p && p->next){
        p = p->next;
        q = q->next;
        while(p && p->element == q->element){
            q->next = p->next;
            delete p;
            p = q->next;
        }
    }
}

void Print_linklist(LinkList *L){
    LinkList *p = L->next;
    while(p){
        cout<<p->element<<" ";
        p = p->next;
    }
    cout<<endl;
}

void delete_linklist(LinkList *L, Elementtype a){
    LinkList *p = L->next;
    LinkList *q = L;
    while(p){
        if(p->element == a){
            q->next = p->next;
            delete p;
        }
        else{
            q = q->next;
        }
        if(!q){
            break;
        }  
        else{
            p = q->next;
        }    
    }
}

void Print_seqlist(SeqList *L){
    for(int i=0; i<L->last; i++){
        cout<<L->element[i]<<" ";
    }
    cout<<endl;
}

void delete_seqlist(SeqList *L, Elementtype a){
    int flag = 0;
    int j = 0;
    for(int i=0; i<L->last; i++){
        if(L->element[i] == a){
            for(j=i; j<L->last-1; j++){
                L->element[j] = L->element[j+1];
            }
            flag++;
        }
    }
    L->last -= flag;
}

SeqList* delete_repeat_seqlist(SeqList *L){
    SeqList *L1 = new SeqList;
    L1->last = 1;
    L1->element[0] = L->element[0];
    for(int i=1; i<L->last; i++){
        if(L->element[i] == L1->element[L1->last-1]){
            continue;
        }
        else{
            L1->element[L1->last] = L->element[i];
            L1->last++;
        }
    }
    return L1;
}

SeqList* reverse_seqlist(SeqList *L){
    SeqList *L1 = new SeqList;
    L1->last = 0;
    for(int i=L->last-1; i>=0; i--){
        L1->element[L1->last] = L->element[i];
        //cout<<L1->element[L1->last]<<" "<<L->element[i]<<endl;
        L1->last++;
    }
    return L1;
}

SeqList* k_move_seqlist_left(SeqList *L, int k){
    SeqList *L1 = new SeqList;
    L1->last = 0;
    for(int i=0; i<L->last; i++){
        //cout<<(i-k+L->last)%(L->last-1)<<endl;
        L1->element[(i-k+L->last)%(L->last)] = L->element[i];
    }
    L1->last = L->last;
    return L1;
}

SeqList* k_move_seqlist_right(SeqList *L, int k){
    SeqList *L1 = new SeqList;
    for(int i=0; i<L->last; i++){
        L1->element[(i+k+L->last)%(L->last)] = L->element[i];
    }
    L1->last = L->last;
    return L1;
}

SeqList* hebing_seqlist(SeqList *L1, SeqList *L2){
    SeqList *L = new SeqList;
    int i=0;
    int j=0;
    L->last = 0;
    while(i != L1->last || j != L2->last){
        if(i == L1->last){
            L->element[L->last] = L2->element[j];
            j++;
            L->last++;
        }
        else if(j == L2->last){
            L->element[L->last] = L1->element[i];
            i++;
            L->last++;
        }
        else{
            if(L1->element[i] <= L2->element[j]){
                L->element[L->last] = L1->element[i];
                i++;
                L->last++;
            }
            else{
                L->element[L->last] = L2->element[j];
                j++;
                L->last++;
            }
            
        }
    }
    return L;
}

void sort_seqlist(SeqList *L){
    quick_sort(L);
}

void quick_sort(SeqList *L){
    Qsort(L->element, 0, L->last-1);
}

void Qsort(int arr[MAXSIZE], int start, int last){
    if(start < last){
        int pivot = partition(arr, start, last);
        Qsort(arr, start, pivot-1);
        Qsort(arr, pivot+1, last);
    }
    
}

int partition(int arr[MAXSIZE], int start, int last){
    int pivotkey = arr[start];
    while(start < last){
        while(start < last && arr[last]>=pivotkey){
            last--;
        }
        
        swap(arr[start], arr[last]);
        while(start < last && arr[start]<=pivotkey){
            start++;
        }
        swap(arr[start], arr[last]);
    }
    return last;
}