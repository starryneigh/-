#include <iostream>
#include <limits>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

#define MAX 255         //huffman树结点的最大个数 
#define MAXCHAR 100000  //字符串最大长度 
#define lbits 20        //编码的最大位数

typedef struct heap{
    int *data;
    int *icon;
    int size;
    int capacity;
}heap;
typedef struct{
    double weight;  //权值
    int lchild;     //左孩子
    int rchild;     //右孩子
    int parent;     //父节点
}HTnode;            //huffman结点
typedef HTnode HuffmanT[MAX];   //huffman树
typedef struct{
    char bits[lbits] = "\0";    //字符的huffman编码
}CodeNode;
typedef CodeNode huffmancode[128];  //每个字符的huffman编码

void init_HT(HuffmanT T);       //huffman树的初始化
void print_HT(HuffmanT T);      //打印huffman树
void print_H(HuffmanT T,huffmancode H); //打印huffman编码
void select_min(HuffmanT T, int domain, int &p1, int &p2);  //寻找当前森林中两个最小根节点的值
void create_HT(HuffmanT T);     //创建huffman树
void cal_frequency(char* s);   //计算每个字符出现的频率
int huff_height(HuffmanT T);    //计算huffman树的高度
void huff_coding(HuffmanT T, huffmancode H);    //计算每个字符的huffman编码
char* encoding(char* s, huffmancode H);         //huffman编码
char* decoding(char* t, HuffmanT T);            //huffman解码
bool compare_str(char* s, char *r);             //比较
heap* init_heap(HuffmanT T);
void shift_down(int *arr, int *icon, int n, int cur);
void shift_up(int *arr, int *icon, int n, int cur);
int delete_heap(heap *hp);
void insert_heap(heap *hp, int data, int icon);
void select_min_heap(heap *hp, int &p1, int &p2);
void create_HT_heap(HuffmanT T);

int frequency[128] = {0};       //初始化
huffmancode H;
int n = 20;     //初始化：huffman树的外节点数

int main(){
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    char *s = (char*)malloc(sizeof(char)*MAXCHAR);
    char *temp = (char*)malloc(sizeof(char)*MAXCHAR);
    char* t;        //编码串
    char* r;        //译码串
    HuffmanT T;     //huffman树
    int height;     //树高
    double persent; //压缩率
    bool compare;   //比较原文本与译码结果是否相同

    s[0] = '\0';
    fp1 = fopen("article.txt", "r+");
    while(!feof(fp1)){
        fgets(temp, MAXCHAR, fp1);       //文件读取
        //cout<<temp;
        //if(temp[strlen(temp)-1] == '\n')
        //temp[strlen(temp)-1] = '\0';
        if(temp) strcat(s, temp);        //拼接到串s上
    }
    fclose(fp1);
    //cout<<s<<endl;
    cal_frequency(s);           //计算字符使用频率

    init_HT(T);
    for(int i=0; i<128; i++){
        T[i].weight = frequency[i];     //初始化huffman树
    }
    create_HT_heap(T);          //构建huffman树
    print_HT(T);

    height = huff_height(T);    //计算树高
    huff_coding(T, H);          //计算每个字符的huffman编码
    t = encoding(s, H);         //编码
    r = decoding(t, T);         //译码

    fp2 = fopen("result.txt", "r+");        
    fwrite(t, sizeof(char), strlen(t), fp2);    //写入译码结果
    fclose(fp2);

    persent = double(strlen(t))/(strlen(s)*8);
    cout<<"压缩率为："<<persent<<endl;
    
    compare = compare_str(s, r);
    if(compare == true) cout<<"与原字符串相同"<<endl;
    else cout<<"与原字符串不同"<<endl;

    init_heap(T);
    return 0;
}

void init_HT(HuffmanT T){
    for(int i=0; i<MAX; i++){       //初值结点全为-1，权值为0
        T[i].lchild = -1;
        T[i].rchild = -1;
        T[i].parent = -1;
        T[i].weight = 0;
    }
}

void print_HT(HuffmanT T){
    cout<<"i\t权值\t双亲\t左孩子\t右孩子\n";
    for(int i=0; i<128+n-1; i++){
        if(!T[i].weight){
            continue;
        }
        cout<<i<<"\t";
        cout<<T[i].weight<<"\t";
        cout<<T[i].parent<<"\t";
        cout<<T[i].lchild<<"\t";
        cout<<T[i].rchild<<endl;
    }
}

void print_H(HuffmanT T,huffmancode H){
    cout<<"字符\t编码\n";
    for(int i=0; i<128; i++){
        if(T[i].weight){
            if(char(i) == '\n'){
                cout<<"\\n"<<'\t'<<H[i].bits<<endl;
                continue;
            }
            cout<<char(i)<<'\t'<<H[i].bits<<endl;
        }
    }
}

heap* init_heap(HuffmanT T){
    heap *hp = (heap*)malloc(sizeof(heap));
    int j=0;
    hp->data = (int*)malloc(sizeof(int)*n);
    hp->icon = (int*)malloc(sizeof(int)*n);
    hp->capacity = hp->size = n;
    for(int i=0; i<n; i++){
        while(!T[j].weight && j<128){
            j++;
        }
        hp->data[i] = T[j].weight;
        hp->icon[i] = j;
        j++;
    }
    for(int i=(n-2)/2; i>=0; i--){
        shift_down(hp->data, hp->icon, hp->size, i);
    }
    //for(int i=0; i<hp->size; i++){
    //    cout<<hp->icon[i]<<" "<<hp->data[i]<<endl;
    //}
    return hp;
}

void select_min_heap(heap *hp, int &p1, int &p2){
    p1 = delete_heap(hp);
    p2 = delete_heap(hp);
}

int delete_heap(heap *hp){
    int index = hp->icon[0];
    swap(hp->data[0], hp->data[hp->size-1]);
    swap(hp->icon[0], hp->icon[hp->size-1]);
    hp->size--;
    shift_down(hp->data, hp->icon, hp->size, 0);
    return index;
}

void insert_heap(heap *hp, int data, int icon){
    hp->data[hp->size] = data;
    hp->icon[hp->size] = icon;
    hp->size++;
    shift_up(hp->data, hp->icon, hp->size, hp->size-1);
}

void shift_up(int *arr, int *icon, int n, int cur){
    int child = cur;
    int parent = (cur-1)/2;
    while(parent>=0){
        if(arr[parent]>arr[child]){
            swap(arr[parent], arr[child]);
            child = parent;
            parent = (cur-1)/2;
        }
        else break;
    }
}

void shift_down(int *arr, int *icon, int n, int cur){
    int parent = cur;
    int child = parent*2+1;
    while(child<n){
        if(child+1<n && arr[child]>arr[child+1]){
            child++;
        }
        if(arr[parent]>arr[child]){
            swap(arr[parent], arr[child]);
            swap(icon[parent], icon[child]);
            parent = child;
            child = parent*2+1;
        }
        else{
            break;
        }
    }
}

void select_min(HuffmanT T, int domain, int &p1, int &p2){
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    for(int i=0; i<domain; i++){
        if(T[i].parent == -1 && T[i].weight){
            if(min1>T[i].weight || min2>T[i].weight){
                if(min1>T[i].weight){
                    min2 = min1;
                    min1 = T[i].weight;
                    p2 = p1;
                    p1 = i;
                }
                else{
                    min2 = T[i].weight;
                    p2 = i;
                }
            }
        }
    }
}

void create_HT(HuffmanT T){
    int p1;
    int p2;
    for(int i=128; i<128+n-1; i++){
        select_min(T, i, p1, p2);       //选择huffman树中权值最小的两个树
        T[p1].parent = T[p2].parent = i;
        T[i].lchild = p1;
        T[i].rchild = p2;
        T[i].weight = T[p1].weight + T[p2].weight;
        //cout<<p1<<' '<<p2<<' ';
        //cout<<T[p1].weight<<" "<<T[p2].weight<<endl;
    }
}

void create_HT_heap(HuffmanT T){
    int p1;
    int p2;
    heap *hp;
    hp = init_heap(T);
    for(int i=128; i<128+n-1; i++){
        select_min_heap(hp, p1, p2);       //选择huffman树中权值最小的两个树
        T[p1].parent = T[p2].parent = i;
        T[i].lchild = p1;
        T[i].rchild = p2;
        T[i].weight = T[p1].weight + T[p2].weight;
        insert_heap(hp, T[i].weight, i);
        //cout<<p1<<' '<<p2<<' ';
        //cout<<T[p1].weight<<" "<<T[p2].weight<<endl;
    }
}

void cal_frequency(char* s){
    for(int i=0; i<strlen(s); i++){
        frequency[s[i]]++;      //哈希表计算频率
    }
    n = 0;
    cout<<"i\t字符\t频率\n";
    for(int i=0; i<128; i++){
        if(!frequency[i]) continue;     //跳过频率为0的点
        n++;
        if(char(i) == '\n'){
                cout<<i<<"\t\\n"<<'\t'<<frequency[i]<<endl;
                continue;
        }
        cout<<i<<"\t"<<char(i)<<"\t"<<frequency[i]<<endl;
    }
    //cout<<n<<endl;
    //cout<<s.length()<<endl;
}

int huff_height(HuffmanT T){
    int height = 1;
    int min_index;
    int min = INT_MAX;
    int q;
    for(int i=0; i<128; i++){
        if(T[i].weight){
            if(min>T[i].weight){
                min_index = i;
                min = T[i].weight;
            }
        }
    }
    q = min_index;
    while(T[q].parent != -1){
        //cout<<T[q].parent<<endl;
        q = T[q].parent;
        height++;
    }
    return height;      //算出最大高度，单个字符编码最大长度即为height-1
}

void huff_coding(HuffmanT T, huffmancode H){
    char cd[lbits] = "1234567890";
    int height = huff_height(T)-1;
    int start = height;     //从叶节点开始遍历
    int c, p;               //p结点记录parent，c结点记录child
    cd[start--] = '\0';     //编码最后加上终止符
    for(int i=0; i<128; i++){
        if(!T[i].weight){
            continue;
        }
        start = height-1;   
        c = i;
        p = T[c].parent;
        while(p != -1){     //遍历到根节点为止
            cd[start--] = (T[p].lchild==c)?'0':'1';     //判断是左子树还是右子树
            c = p;
            p = T[c].parent;
        }
        strcpy(H[i].bits, &cd[++start]);    //将结果保存到bits中
    }
    print_H(T, H);
}

char* encoding(char* s, huffmancode H){
    char *result = (char*)malloc(sizeof(char)*MAXCHAR);
    result[0] = '\0';
    for(int i=0; i<strlen(s); i++){
        strcat(result, H[s[i]].bits);   //编码
    }
    cout<<"编码结果："<<endl;
    cout<<result<<endl;
    return result;
}

char* decoding(char* t, HuffmanT T){
    char* result = (char*)malloc(sizeof(char)*MAXCHAR);
    result[0] = '\0';
    int gen = 128+n-2;
    char zifu[2];
    zifu[1] = '\0';
    int p = gen;
    //cout<<T[p].weight<<endl;
    for(int i=0; i<strlen(t); i++){     //根据huffman树来进行解码
        if(t[i]=='0'){
            p = T[p].lchild;    //为0则遍历左子树
        }
        else{
            p = T[p].rchild;    //为1则遍历右子树
        }
        if(T[p].lchild == -1 && T[p].rchild == -1){
            zifu[0] = char(p);
            strcat(result, zifu);
            p = gen;
        }
    }
    cout<<"译码结果："<<endl;
    cout<<result<<endl;
    return result;
}

bool compare_str(char* s, char *r){
    int i=0;
    for(i=0; i<strlen(s); i++){
        if(s[i] == r[i]) continue;      //比较是否相同
        else{
            //cout<<s[i]<<"\t"<<r[i]<<endl;
            //cout<<i<<endl;
            break;
        }
    }
    return i==strlen(s) && i==strlen(r);
}