#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAX 100             //输入点的最大个数
#define infinity INT16_MAX  //int 16位的最大值，输入的权值不能比它大

typedef struct{
    int n, e;
    char ver[MAX];          //顶点集
    int edge[MAX][MAX];     //边集
}MGraph;

void create_mgraph(MGraph *G);
void print_mgraph(MGraph *G);
void print_min(int min[MAX][MAX], int next[MAX][MAX], int n);
void floyd(MGraph *G, int min[MAX][MAX], int next[MAX][MAX]);
void floyd_uv(int min[MAX][MAX], int next[MAX][MAX], int u, int v);
void dijkstra_start(MGraph *G, int cost[], int p[], int start);
void dijkstra_end(MGraph *G, int cost[], int p[], int end);
void dijkstra_start_end(MGraph *G, int cost[], int p[], int start, int end);
void dijkstra_uv(MGraph *G, int cost[], int p[], int start, int end);

int main(){
    MGraph *G = (MGraph*)malloc(sizeof(MGraph));
    int min[MAX][MAX] = {0};    //最短路径长度矩阵
    int next[MAX][MAX] = {0};   //最短路径矩阵
    int cost[MAX];              //最短路径长度 (dijkstra)
    int p[MAX];                 //前驱结点或者后继节点 (dijkstra)
    
    //准备工作
    memset(next, -1, sizeof(next));
    memset(cost, 0, sizeof(cost));
    memset(p, 0, sizeof(p));
    create_mgraph(G);           //构造邻接矩阵

    floyd(G, min, next);        //floyd算法
    floyd_uv(min, next, 0, 11); //计算特定路径

    dijkstra_start(G, cost, p, 1);  //dijkstra算法（源点）
    dijkstra_end(G, cost, p, 10);   //目标点
    dijkstra_uv(G, cost, p, 1, 7);  //顶点对

    return 0;
}

void floyd_uv(int min[MAX][MAX], int next[MAX][MAX], int u, int v){
    cout<<"从"<<u<<"到"<<v<<"的最短路径长度为："<<min[u][v]<<"\t";
    cout<<"最短路径为：";
    cout<<u;
    int k = next[u][v];     
    while(k != v){
        cout<<"->"<<k;
        k = next[k][v];     //输出后继结点
    }cout<<endl<<endl;
}

//输出最短路径长度矩阵和最短路径矩阵
void print_min(int min[MAX][MAX], int next[MAX][MAX], int n){
    cout<<"最短路长矩阵为："<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(min[i][j] == infinity){
                cout<<"oo\t";
                continue;
            }
            cout<<min[i][j]<<"\t";
        }cout<<endl;
    }cout<<endl;
    cout<<"最短路径矩阵为："<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<next[i][j]<<"\t";
        }cout<<endl;
    }cout<<endl;
}

void dijkstra_uv(MGraph *G, int cost[], int p[], int start, int end){
    cout<<"单顶点对间最短路径：顶点对为 ("<<start<<","<<end<<")"<<endl;
    dijkstra_start_end(G, cost, p, start, end);     //u->v
    dijkstra_start_end(G, cost, p, end, start);     //v->u
}

void floyd(MGraph *G, int min[MAX][MAX], int next[MAX][MAX]){
    int current;
    for(int i=0; i<G->n; i++){
        for(int j=0; j<G->n; j++){
            if(G->edge[i][j] != infinity){
                next[i][j] = j;     //初始化next
            }
            min[i][j] = G->edge[i][j];  //初始化min
        }
    }
    for(int k=0; k<G->n; k++){
        for(int i=0; i<G->n; i++){
            for(int j=0; j<G->n; j++){
                current = min[i][k] + min[k][j];    //当前经过k时两点间距离
                if(min[i][j] > current){
                    min[i][j] = current;            //更新矩阵
                    next[i][j] = next[i][k];        //表示i->j要经过k
                }
            }
        }
    }
    print_min(min, next, G->n);
}

void create_mgraph(MGraph *G){
    FILE *fp = fopen("graph1.txt", "r+");   //读取文件
    int i, j, k, w;
    fscanf(fp, "%d %d", &G->n, &G->e);
    for(int i=0; i<G->n; i++){
        fscanf(fp, " %c", &G->ver[i]);      //初始化邻接矩阵
    }
    for(int i=0; i<G->n; i++){
        for(int j=0; j<G->n; j++){
            G->edge[i][j] = infinity;       //无邻接点则为无限长
        }
    }
    for(int i=0; i<G->n; i++){
        G->edge[i][i] = 0;      //自己到自己距离为0
    }
    for(int k=0; k<G->e; k++){
        fscanf(fp, "%d %d %d", &i, &j, &w);
        G->edge[i][j] = w;
    }
    print_mgraph(G);
}

void print_mgraph(MGraph *G){
    cout<<"邻接矩阵\n";
    cout<<"顶点数为："<<G->n<<"\t边数为："<<G->e<<endl;
    cout<<"顶点为：";
    for(int i=0; i<G->n; i++){
        cout<<G->ver[i]<<" ";
    }cout<<endl;
    cout<<"邻接矩阵为："<<endl;
    for(int i=0; i<G->n; i++){
        for(int j=0; j<G->n; j++){
            if(G->edge[i][j] == infinity){
                cout<<"oo\t";
                continue;
            }
            cout<<G->edge[i][j]<<"\t";
        }cout<<endl;
    }cout<<endl;
}

void dijkstra_start_end(MGraph *G, int cost[], int p[], int start, int end){
    int *flag = (int*)malloc(sizeof(int)*G->n); //标记矩阵
    int min = infinity;
    int min_index = end;    //从end开始向前遍历
    int sum;
    memset(flag, 0, sizeof(int)*G->n);
    flag[end] = 1;
    for(int i=0; i<G->n; i++){  //初始化
        cost[i] = G->edge[i][end];
        p[i] = end;
        if(min > cost[i] && flag[i] == 0){
            min_index = i;
            min = cost[i];
        }
    }
    flag[min_index] = 1;
    int count = 2;
    while(min_index!=start && count <= G->n){   //遍历到起始节点或者遍历完所有结点
        count++;
        for(int i=0; i<G->n; i++){
            sum = cost[min_index] + G->edge[i][min_index];  //当前路径长度
            if(sum < cost[i]){
                cost[i] = sum;      //更新cost
                p[i] = min_index;   //更新后继结点
            }
        }
        min = infinity;
        for(int i=0; i<G->n; i++){
            if(min > cost[i] && flag[i] == 0){
                min_index = i;
                min = cost[i];      //寻找最小值的下标
            }
        }
        flag[min_index] = 1;        //标记走过此结点
    }
    int current;
    cout<<"从"<<start<<"到"<<end<<"  \t";   //输出
    if(cost[start] == infinity){
        cout<<"无路径"<<endl;
        return;
    }
    cout<<"最短路长："<<cost[start]<<"\t";
    cout<<"\t最短路径：";
    current = start;
    while(current != end){
        cout<<current<<"->";
        current = p[current];
    }cout<<current<<endl;
}

//过程同上
void dijkstra_end(MGraph *G, int cost[], int p[], int end){
    cout<<"单目标最短路径：目标为"<<end<<endl;
    int *flag = (int*)malloc(sizeof(int)*G->n);
    int min = infinity;
    int min_index = end;
    int sum;
    memset(flag, 0, sizeof(int)*G->n);
    flag[end] = 1;
    for(int i=0; i<G->n; i++){
        cost[i] = G->edge[i][end];
        p[i] = end;
        if(min > cost[i] && flag[i] == 0){
            min_index = i;
            min = cost[i];
        }
    }
    flag[min_index] = 1;
    for(int k=0; k<G->n; k++){
        for(int i=0; i<G->n; i++){
            sum = cost[min_index] + G->edge[i][min_index];
            if(sum < cost[i]){
                cost[i] = sum;
                p[i] = min_index;
            }
        }
        min = infinity;
        for(int i=0; i<G->n; i++){
            if(min > cost[i] && flag[i] == 0){
                min_index = i;
                min = cost[i];
            }
        }
        flag[min_index] = 1;
    }
    int current;
    for(int i=0; i<G->n; i++){
        cout<<"从"<<i<<"到"<<end<<"  \t";
        if(cost[i] == infinity){
            cout<<"无路径"<<endl;
            continue;
        }
        cout<<"最短路长："<<cost[i]<<"\t";
        cout<<"\t最短路径：";
        current = i;
        while(current != end){
            cout<<current<<"->";
            current = p[current];
        }cout<<current<<endl;
    }cout<<endl;
}

//过程同上
void dijkstra_start(MGraph *G, int cost[], int p[], int start){
    cout<<"但源点最短路径：源点为"<<start<<endl;
    int *flag = (int*)malloc(sizeof(int)*G->n);
    int min = infinity;
    int min_index = start;
    int sum;
    memset(flag, 0, sizeof(int)*G->n);
    flag[start] = 1;
    for(int i=0; i<G->n; i++){
        cost[i] = G->edge[start][i];
        p[i] = start;
        if(min > cost[i] && flag[i] == 0){
            min_index = i;
            min = cost[i];
        }
    }
    flag[min_index] = 1;
    for(int k=0; k<G->n; k++){
        for(int i=0; i<G->n; i++){
            sum = cost[min_index] + G->edge[min_index][i];
            if(sum < cost[i]){
                cost[i] = sum;
                p[i] = min_index;
            }
        }
        min = infinity;
        for(int i=0; i<G->n; i++){
            if(min > cost[i] && flag[i] == 0){
                min_index = i;
                min = cost[i];
            }
        }
        flag[min_index] = 1;
    }
    for(int i=0; i<G->n; i++){
        cout<<"从"<<start<<"到"<<i<<"  \t";
        if(cost[i] == infinity){
            cout<<"无路径"<<endl;
            continue;
        } 
        cout<<"最短路长："<<cost[i]<<"\t";
        cout<<"\t最短路径：";
        int current = i;
        stack<int>s;
        while(current!=start){
            s.push(current);
            current = p[current];
        }
        cout<<current;
        while(!s.empty()){
            cout<<"->"<<s.top();
            s.pop();
        }cout<<endl;
    }cout<<endl;
}