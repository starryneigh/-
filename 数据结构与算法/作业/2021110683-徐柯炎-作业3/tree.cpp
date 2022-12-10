#include <iostream>
#include <queue>
using namespace std;

#define MAX 10

int ind = 0;

typedef int datatype;
typedef struct node{
    datatype data;
    node *lchild;
    node *rchild;
}node;
typedef node BTREE;
typedef struct{
    BTREE* sta[MAX];
    int top;
    int flag[MAX];
}INFO;

BTREE* lever_order(BTREE *BT);
BTREE* pre_order(BTREE *BT);
BTREE* in_order(BTREE *BT);
BTREE* post_order(BTREE *BT);
void create_btree(BTREE* &BT);
void f_pre_order(BTREE *BT);
void f_in_order(BTREE *BT);
void f_post_order(BTREE *BT);
bool judge_wanquan(BTREE *BT);
int btree_width(BTREE *BT);
void print_btree(BTREE *BT, datatype result[]);

int main(){
    BTREE *BT;
    int r[100] = {0};
    cout<<"please input data:"<<endl;
    create_btree(BT);
    print_btree(BT, r);
    cout<<"二叉树为："<<endl;
    for(int i=0; i<ind; i++){
        cout<<r[i]<<" ";
    }
    cout<<endl;

    cout<<"层序遍历（递归）：";
    BT = lever_order(BT);
    cout<<endl;

    cout<<"先序遍历（递归）：";
    BT = pre_order(BT);
    cout<<endl;
    
    cout<<"中序遍历（递归）：";
    BT = in_order(BT);
    cout<<endl;
    
    cout<<"后序遍历（递归）：";
    BT = post_order(BT);
    cout<<endl;

    f_pre_order(BT);
    f_in_order(BT);
    f_post_order(BT);

    bool result;
    result = judge_wanquan(BT);
    cout<<"是否为完全二叉树："<<result<<endl;

    int width;
    width = btree_width(BT);
    cout<<"宽度为："<<width<<endl;
    return 0;
}

void create_btree(BTREE* &BT){
    BTREE *node = new BTREE;
    int temp;
    cin>>temp;
    if(temp == -1){
        BT = NULL;
        return;
    }
    BT = node;
    BT->data = temp;
    create_btree(BT->lchild);
    create_btree(BT->rchild);
}

void print_btree(BTREE *BT, datatype result[]){
    if(!BT){
        result[ind++] = -1;
        return;
    }
    result[ind++] = BT->data;
    print_btree(BT->lchild, result);
    print_btree(BT->rchild, result);
}

BTREE* lever_order(BTREE *BT){
    queue<node*>Q;
    BTREE *T;
    if(!BT) return BT;
    Q.push(BT);
    while(!Q.empty()){
        T = Q.front();
        Q.pop();
        cout<<T->data<<" ";
        if(T->lchild){
            Q.push(T->lchild);
        }
        if(T->rchild){
            Q.push(T->rchild);
        }
    }
    return BT;
}

BTREE* pre_order(BTREE *BT){
    if(!BT){
        return NULL;
    }
    cout<<BT->data<<" ";
    pre_order(BT->lchild);
    pre_order(BT->rchild);
    return BT;
}

BTREE* in_order(BTREE *BT){
    if(!BT){
        return NULL;
    }
    in_order(BT->lchild);
    cout<<BT->data<<" ";
    in_order(BT->rchild);
    return BT;
}

BTREE* post_order(BTREE *BT){
    if(!BT){
        return NULL;
    }
    post_order(BT->lchild);
    post_order(BT->rchild);
    cout<<BT->data<<" ";
    return BT;
}

void f_pre_order(BTREE *BT){
    BTREE *root = BT;
    INFO S;
    S.top = -1;
    cout<<"先序遍历（非递归）：";
    while(root != NULL || S.top != -1){
        while(root != NULL){
            S.sta[++S.top] = root;
            cout<<root->data<<" ";
            root = root->lchild;
        }
        if(S.top != -1){
            root = S.sta[S.top--];
            root = root->rchild;
        }
    }
    cout<<endl;
}

void f_in_order(BTREE *BT){
    BTREE *root = BT;
    INFO S;
    S.top = -1;
    cout<<"中序遍历（非递归）：";
    while(root != NULL || S.top != -1){
        while(root != NULL){
            S.sta[++S.top] = root;
            root = root->lchild;
        }
        if(S.top != -1){
            root = S.sta[S.top--];
            cout<<root->data<<" ";
            root = root->rchild;
        }
    }
    cout<<endl;
}

void f_post_order(BTREE *BT){
    BTREE *root = BT;
    INFO S;
    S.top = -1;
    for(int i=0; i<MAX; i++){
        S.flag[i] = 1;
    }
    cout<<"后序遍历（非递归）：";
    while(root != NULL || S.top != -1){
        while(root != NULL){
            S.sta[++S.top] = root;
            root = root->lchild;
        }
        if(S.top != -1 && S.flag[S.top] == 1){
            S.flag[S.top] = 2;
            root = S.sta[S.top];
            root = root->rchild;
        }
        else if(S.top != -1 && S.flag[S.top] == 2){
            S.flag[S.top] = 1;
            cout<<S.sta[S.top]->data<<" ";
            S.top--;
        }
    }
    cout<<endl;
}

bool judge_wanquan(BTREE *BT){
    queue<node*>Q;
    BTREE *T;
    if(!BT) return true;
    Q.push(BT);
    while(!Q.empty()){
        T = Q.front();
        Q.pop();
        if(T==NULL && !Q.empty()){
            return false;
        }
        else if(T==NULL && Q.empty()){
            return true;
        }
        if(T->lchild || T->rchild){
            Q.push(T->lchild);
            Q.push(T->rchild);
        }
    }
    return true;
}

int btree_width(BTREE *BT){
    queue<node*>q;
    queue<int>height;
    int temp = 1;
    int rear;
    BTREE* T = NULL;
    int count = 0;
    int max = 1;
    if(!BT) return 0;
    q.push(BT);
    height.push(temp);
    while(!q.empty()){
        T = q.front();
        rear = height.front();
        q.pop();
        height.pop();
        if(rear == temp){
            count++;
        }
        else if(rear != temp){
            temp = rear;
            max = max<count ? count:max;
            count = 1;
        }
        if(T){
            rear++;
            if(T->lchild){
                q.push(T->lchild);
                height.push(rear);
            }
            if(T->rchild){
                q.push(T->rchild);
                height.push(rear);
            }
        }
    }
    max = max<count ? count:max;
    return max;
}