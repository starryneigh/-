#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAX 2000

typedef struct celltype{
    int data;
    struct celltype *lchild, *rchild;
}BSTNode;
typedef BSTNode *BST;
typedef struct List{
    int list[MAX];
    int length;
}List;

void random_text(List *L);
void random_file(int n, int a, int b);

BST create_bst(char *name);
List *create_list(char* name);
void insert_bst(BST &F, int key);
void print_bst_e(BST F);
void print_bst(BST F);
void print_list(List *L);
void delete_bst(BST &F, int key);
int deletemin(BST &F);
BSTNode *search_bst(BST F, int key);
int search_bst_e(BST F, int key, int &count);
float search_bst_count(BST F, int t);
int search_half(List *L, int key);
int search_half_list(List *L, int key);
float search_half_count(List *L, int t);

FILE *fpw = fopen("text2.txt", "r");
int count_s = 0;

int main(){
    BST F1, F2, F3;
    BSTNode *p;
    List *L1, *L2, *L3;
    int key = 67;
    int q;
    char file1[10] = "text1.txt";
    char file2[10] = "text2.txt";
    char file3[10] = "text3.txt";

    cout<<"BST："<<endl;
    F3 = create_bst(file3);
    print_bst(F3);

    p = search_bst(F3, 70);
    if(p->data == -1)   cout<<"没找到"<<p->data<<endl;
    else{
        cout<<"找到"<<p->data<<"的位置为";
        printf("%p\n", p);
    }

    delete_bst(F3, key);
    cout<<"删除"<<key<<"后的中序遍历为";
    print_bst(F3);
    
    cout<<"List:"<<endl;
    L3 = create_list(file3);
    sort(L3->list, L3->list+L3->length);
    print_list(L3);
    search_half(L3, key);
    search_half(L3, 30);

    F1 = create_bst(file1);
    L1 = create_list(file1);
    cout<<"测试数据1："<<endl;
    cout<<"折半查找："<<endl;
    search_half_count(L1, 0);
    search_half_count(L1, 1);
    cout<<"二叉搜索树："<<endl;
    search_bst_count(F1, 0);
    search_bst_count(F1, 1);
    cout<<endl;

    F2 = create_bst(file2);
    L2 = create_list(file1);
    cout<<"测试数据2："<<endl;
    cout<<"折半查找："<<endl;
    search_half_count(L2, 0);
    search_half_count(L2, 1);
    cout<<"二叉搜索树："<<endl;
    search_bst_count(F2, 0);
    search_bst_count(F2, 1);
    return 0;
}

float search_bst_count(BST F, int t){
    int temp;
    int sum = 0;
    float everage;
    for(int i=t; i<2049; i+=2){
        temp = search_bst_e(F, i, count_s);
        sum += temp;
    }
    everage = (float)sum/(1024+1-t);
    if(t == 1)  cout<<"查找成功";
    else        cout<<"查找失败"; 
    cout<<"平均长度为"<<everage<<endl;
    return everage;
}

float search_half_count(List *L, int t){
    int temp;
    int sum = 0;
    float everage;
    for(int i=t; i<2049; i+=2){
        temp = search_half_list(L, i);
        sum += temp;
    }
    everage = (float)sum/(1024+1-t);
    if(t == 1)  cout<<"查找成功";
    else        cout<<"查找失败"; 
    cout<<"平均长度为"<<everage<<endl;
    return everage;
}

int search_half(List *L, int key){
    int low = 0; 
    int high = L->length;
    int mid;
    int count = 0;
    while(high > low){
        count++;
        mid = (high+low+1)/2;
        if(key == L->list[mid]){
            low = mid; break;
        }
        else if(key > L->list[mid]){
            low = mid+1;
        }
        else if(key < L->list[mid]){
            high = mid-1;
        }
    }
    if(L->list[low] == key){
        cout<<"查找成功   "<<L->list[low]<<"的下标为"<<low<<"\t查找次数为"<<count<<endl;
    }
    else{
        cout<<"查找失败   没有找到"<<key<<"\t失败查找次数为"<<count<<endl;
    }
    return count;
}

int search_half_list(List *L, int key){
    int low = 0; 
    int high = L->length;
    int mid;
    int count = 0;
    while(high > low){
        count++;
        mid = (high+low+1)/2;
        if(key == L->list[mid]){
            low = mid; break;
        }
        else if(key > L->list[mid]){
            low = mid+1;
        }
        else if(key < L->list[mid]){
            high = mid-1;
        }
    }
    if(L->list[low] == key){
        //cout<<"查找成功   "<<L->list[low]<<"的下标为"<<low<<"\t查找次数为"<<count<<endl;
    }
    else{
        //cout<<"查找失败   没有找到"<<key<<"\t失败查找次数为"<<count<<endl;
    }
    return count;
}

List *create_list(char* name){
    List *L = new List;
    FILE *fp = fopen(name, "r");
    L->length = 0;
    while(!feof(fp) && L->length < MAX){
        fscanf(fp, "%d", &L->list[L->length++]);
    }
    if(L->list[L->length-1] == 0){
        L->length--;
    }
    return L;
}

void print_list(List *L){
    cout<<"数组长度为："<<L->length<<endl;
    for(int i=0; i<L->length; i++){
        cout<<L->list[i]<<" ";
    }cout<<endl;
}

BSTNode *search_bst(BST F, int key){
    count_s++;
    if(F == NULL){
        BSTNode *p = new BSTNode;
        p->data = -1;
        return p;
    }
    if(key > F->data)   return search_bst(F->rchild, key);
    else if(key < F->data)   return search_bst(F->lchild, key);
    else return F;
}

int search_bst_e(BST F, int key, int &count){
    count = 0;
    search_bst(F, key);
    //cout<<count<<endl;
    return count;
}

BST create_bst(char* name){
    BST F = NULL;
    int key;
    FILE *fp = fopen(name, "r+");
    fscanf(fp, "%d", &key);
    while(key){
        insert_bst(F, key);
        fscanf(fp, "%d", &key);
    }
    fclose(fp);
    return F;
}

void insert_bst(BST &F, int key){
    if(F == NULL){
        F = new BSTNode;
        F->data = key;
        F->lchild = F->rchild = NULL;
        return;
    }
    if(key > F->data)   insert_bst(F->rchild, key);
    else if(key < F->data) insert_bst(F->lchild, key);
}

void random_file(int n, int a, int b){
    FILE *fp = fopen("text3.txt", "w+");
    int ran;
    srand(time(0));
    for(int i=0; i<n; i++){
        ran = rand()%(b-a)+1;
        fprintf(fp, "%d ", ran);
    }
    fprintf(fp, "%d", 0);
    fclose(fp);
}

void random_text(List *L){
    int a, b;
    int l = L->length-1;
    FILE *fp = fopen("text.txt", "w+");
    srand(time(0));
    for(int i=0; i<L->length; i++){
        b = rand()%l+1;
        swap(L->list[i], L->list[b]);
    }
    for(int i=0; i<L->length; i++){
        fprintf(fp, "%d ", L->list[i]);
    }
    fclose(fp);
}

void print_bst(BST F){
    cout<<"二叉查找树中序遍历序列为：";
    print_bst_e(F);
    cout<<endl;
}

void print_bst_e(BST F){
    if(F == NULL) return;
    print_bst_e(F->lchild);
    if(F->data != -1)    cout<<F->data<<" ";
    print_bst_e(F->rchild);
}

void delete_bst(BST &F, int key){
    if(F!=NULL){
        if(key<F->data)
            delete_bst(F->lchild, key);
        else if(key>F->data)
            delete_bst(F->rchild, key);
        else{
            if(F->rchild == NULL){
                F = F->lchild;
            }
            else if(F->lchild == NULL){
                F = F->rchild;
            }
            else if(F->lchild && F->rchild){
                F->data = deletemin(F->rchild);
            }
        }
    }
}

int deletemin(BST &F){
    int temp;
    BST p;
    if(F->lchild == NULL){
        p = F;
        temp = F->data;
        F = F->rchild;
        delete p;
        return temp;
    }
    else    return deletemin(F->lchild);
}