#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define NumBertices 100
typedef int VertexData;
typedef int EdgeData;
typedef struct{
    int parent;
    int weight;
}Tree;
typedef struct{
    VertexData Verlist[NumBertices];
    EdgeData edge[NumBertices][NumBertices];
    int n,e;
}MTGraph;
typedef struct node{
    int adjvex;
    EdgeData weight;
    struct node *next;
}EdgeNode;
typedef struct{
    VertexData Vertex;
    EdgeNode *firstedge;
}VertexNode;
typedef struct{
    VertexNode verlist[NumBertices];
    int n, e;
}AdjGraph;

void create_mgraph(MTGraph *G);
void print_mgraph(MTGraph *G);
void create_adjgraph(AdjGraph *G);
void print_adjgraph(AdjGraph *G);
void m_adj(MTGraph *G1, AdjGraph *G2);
void adj_m(MTGraph *G1, AdjGraph *G2);
void bfs_mgraph(MTGraph *G);
void bfs_adjgraph(AdjGraph *G);
void dfs_mgraph_f(MTGraph *G);
void dfs_mgraph(MTGraph *G);
void DFSB(MTGraph *G, int n, int flag[]);
void dfs_adjgraph_f(AdjGraph *G);
void dfs_adjgraph(AdjGraph *G);
void DFSA(AdjGraph *G, int n, int flag[]);
void cal_degree(AdjGraph *G, int k, int &degree, int &r_degree, int &c_degree);

FILE *fp = fopen("result.txt", "w");

int main(){
    MTGraph *G1 = (MTGraph*)malloc(sizeof(MTGraph));
    AdjGraph *G2 = (AdjGraph*)malloc(sizeof(AdjGraph));
    MTGraph *G3 = (MTGraph*)malloc(sizeof(MTGraph));
    AdjGraph *G4 = (AdjGraph*)malloc(sizeof(AdjGraph));
    FILE *fp = fopen("result.txt", "w");
    create_mgraph(G1);
    print_mgraph(G1);
    create_adjgraph(G2);
    print_adjgraph(G2);

    cout<<"相互转化："<<endl;
    m_adj(G1, G4);
    print_adjgraph(G4);
    adj_m(G3, G2);
    print_mgraph(G3);

    dfs_mgraph(G1);
    bfs_mgraph(G1);
    dfs_adjgraph(G2);
    bfs_adjgraph(G2);
    dfs_mgraph_f(G1);
    dfs_adjgraph_f(G2);

    int degree, c_degree, r_degree;
    cal_degree(G2, 3, degree, r_degree, c_degree);
    return 0;
}

void dfs_adjgraph_f(AdjGraph *G){
    int current;
    EdgeNode *p;
    int *flag = (int*)malloc(sizeof(int)*G->n);
    memset(flag, 0, sizeof(int)*G->n);
    stack<int>s;
    cout<<"（邻接表）深度优先搜索序列为（非递归）："<<endl;
    fprintf(fp, "%s", "（邻接表）深度优先搜索序列为（非递归）：\n");
    for(int i=0; i<G->n; i++){
        if(flag[i] == 0){
            s.push(i);
            flag[current] = 1;
        }
        while(!s.empty()){
            current = s.top();
            s.pop();
            cout<<G->verlist[current].Vertex<<" ";
            fprintf(fp, "%d", G->verlist[current].Vertex);
            fprintf(fp, "%c", ' ');
            p = G->verlist[current].firstedge;
            while(p){
                if(flag[p->adjvex] == 0){
                    s.push(p->adjvex);
                    flag[p->adjvex] = 1;
                }
                p = p->next;
            }
        }
    }cout<<endl;
    fprintf(fp, "%c", '\n');
}

void dfs_mgraph_f(MTGraph *G){
    int current;
    int *flag = (int*)malloc(sizeof(int)*G->n);
    memset(flag, 0, sizeof(int)*G->n);
    stack<int>s;
    cout<<"（邻接矩阵）深度优先搜索序列为（非递归）："<<endl;
    fprintf(fp, "%s", "（邻接矩阵）深度优先搜索序列为（非递归）：\n");
    for(int i=0; i<G->n; i++){
        if(flag[i] == 0){
            s.push(i);
        }
        while(!s.empty()){
            current = s.top();
            s.pop();
            flag[current] = 1;
            cout<<G->Verlist[current]<<" ";
            fprintf(fp, "%d", G->Verlist[current]);
            fprintf(fp, "%c", ' ');
            for(int j=0; j<G->n; j++){
                if(G->edge[current][j] == 0 || flag[j] == 1) continue;
                s.push(j);
            }
        }
    }cout<<endl;
    fprintf(fp, "%c", '\n');
}

void cal_degree(AdjGraph *G, int k, int &degree, int &r_degree, int &c_degree){
    EdgeNode *p = G->verlist[k].firstedge;
    degree = 0;
    r_degree = 0;
    c_degree = 0;
    while(p){
        c_degree++;
        p = p->next;
    }
    for(int i=0; i<G->n; i++){
        p = G->verlist[i].firstedge;
        while(p){
            if(p->adjvex == k){
                r_degree++;
            }
            p = p->next;
        }
    }
    degree = r_degree + c_degree;
    cout<<"度为："<<degree<<endl;
    cout<<"入度为："<<r_degree<<endl;
    cout<<"出度为："<<c_degree<<endl;
}

void adj_m(MTGraph *G1, AdjGraph *G2){
    cout<<"邻接表转化为邻接矩阵："<<endl;
    G1->e = G2->e;
    G1->n = G2->n;
    for(int i=0; i<G2->n; i++){
        G1->Verlist[i] = G2->verlist[i].Vertex;
    }
    EdgeNode *p;
    int j;
    memset(G1->edge, 0, sizeof(G1->edge));
    for(int i=0; i<G2->n; i++){
        p = G2->verlist[i].firstedge;
        while(p){
            j = p->adjvex;
            G1->edge[i][j] = p->weight;
            p = p->next;
        }
    }
}

void m_adj(MTGraph *G1, AdjGraph *G2){
    cout<<"邻接矩阵转化为邻接表："<<endl;
    EdgeNode *p;
    G2->e = G1->e;
    G2->n = G1->n;
    for(int i=0; i<G1->n; i++){
        G2->verlist[i].firstedge = NULL;
        G2->verlist[i].Vertex = G1->Verlist[i];
    }
    for(int i=0; i<G1->n; i++){
        for(int j=0; j<G1->n; j++){
            if(G1->edge[i][j]){
                p = (EdgeNode*)malloc(sizeof(EdgeNode));
                p->adjvex = j;
                p->weight = G1->edge[i][j];
                p->next = G2->verlist[i].firstedge;
                G2->verlist[i].firstedge = p;
            }
        }
    }
}

void create_adjgraph(AdjGraph *G){
    FILE *fp = fopen("graph.txt", "r+");
    fscanf(fp, "%d %d", &G->n, &G->e);
    for(int i=0; i<G->n; i++){
        fscanf(fp, "%d", &G->verlist[i].Vertex);
        //cin>>G->verlist[i].Vertex;
        G->verlist[i].firstedge = NULL;
    }
    int i, j, w;
    for(int k=0; k<G->e; k++){
        fscanf(fp, "%d %d %d", &i, &j, &w);
        //cin>>i>>j>>w;
        EdgeNode *edge = new EdgeNode;
        edge->adjvex = j;
        edge->next = G->verlist[i].firstedge;
        edge->weight = w;
        G->verlist[i].firstedge = edge;
    }
}

void bfs_adjgraph(AdjGraph *G){
    int *flag = (int*)malloc(sizeof(int)*G->n);
    queue<int> q;
    memset(flag, 0, sizeof(int)*G->n);
    int count = 0;
    int a;
    EdgeNode *p;
    cout<<"（邻接表）广度优先搜索序列为："<<endl; 
    fprintf(fp, "%s", "（邻接表）广度优先搜索序列为：\n");
    for(int i=0; i<G->n; i++){
        if(!flag[i]){
            flag[i] = 1;
            cout<<G->verlist[i].Vertex<<" ";
            fprintf(fp, "%d", G->verlist[i].Vertex);
            fprintf(fp, "%c", ' ');
            p = G->verlist[i].firstedge;
            while(p){
                q.push(p->adjvex);
                p = p->next;
            }
        }
        while(!q.empty()){
            a = q.front();
            if(!flag[a]){
                flag[a] = 1;
                cout<<G->verlist[a].Vertex<<" ";
                fprintf(fp, "%d", G->verlist[a].Vertex);
                fprintf(fp, "%c", ' ');
                p = G->verlist[a].firstedge;
                while(p){
                    q.push(p->adjvex);
                    p = p->next;
                }
            }
            q.pop();
        }
    }cout<<endl;
    fprintf(fp, "%c", '\n');
}

void dfs_mgraph(MTGraph *G){
    int *flag = (int*)malloc(sizeof(int)*G->n);
    memset(flag, 0, sizeof(int)*G->n);
    int count = 0;
    cout<<"（邻接矩阵）深度优先搜索序列为（递归）："<<endl;
    fprintf(fp, "%s", "（邻接矩阵）深度优先搜索序列为（递归）：\n");
    for(int i=0; i<G->n; i++){
        if(flag[i] == 0){
            DFSB(G, i, flag);
        }
    }cout<<endl;
    fprintf(fp, "%c", '\n');
}

void DFSB(MTGraph *G, int n, int flag[]){
    cout<<G->Verlist[n]<<" ";
    fprintf(fp, "%d", G->Verlist[n]);
    fprintf(fp, "%c", ' ');
    flag[n] = 1;
    for(int j=0; j<G->n; j++){
        if(G->edge[n][j] && !flag[j]){
            DFSB(G, j, flag);
        }
    }
}

void dfs_adjgraph(AdjGraph *G){
    int *flag = (int*)malloc(sizeof(int)*G->n);
    memset(flag, 0, sizeof(int)*G->n);
    int count = 0;
    cout<<"（邻接表）深度优先搜索序列为（递归）："<<endl;
    fprintf(fp, "%s", "（邻接表）深度优先搜索序列为（递归）：\n");
    for(int i=0; i<G->n; i++){
        if(flag[i] == 0){
            DFSA(G, i, flag);
        }
    }cout<<endl;
    fprintf(fp, "%c", '\n');
}

void DFSA(AdjGraph *G, int n, int flag[]){
    EdgeNode *p = G->verlist[n].firstedge;
    cout<<G->verlist[n].Vertex<<" ";
    fprintf(fp, "%d", G->verlist[n].Vertex);
    fprintf(fp, "%c", ' ');
    flag[n] = 1;
    while(p){
        if(!flag[p->adjvex]){
            DFSA(G, p->adjvex, flag);
        }
        p = p->next;
    }
}

void print_adjgraph(AdjGraph *G){
    EdgeNode *node;
    cout<<"邻接表\n";
    cout<<"顶点数为："<<G->n<<"\t边数为："<<G->e<<endl;
    cout<<"顶点为：";
    for(int i=0; i<G->n; i++){
        cout<<G->verlist[i].Vertex<<" ";
    }cout<<endl;
    cout<<"邻接表为："<<endl;
    cout<<"编号\ti\tj\t权值\n";
    int count = 0;
    for(int i=0; i<G->n; i++){
        count = 0;
        node = G->verlist[i].firstedge;
        while(node){
            cout<<++count<<"\t"<<G->verlist[i].Vertex<<"\t"<<G->verlist[node->adjvex].Vertex<<"\t"<<node->weight<<"\t";
            node = node->next;
        }
        if(count) cout<<endl;
    }
}

void create_mgraph(MTGraph *G){
    FILE *fp = fopen("graph.txt", "r+");
    int i, j, k, w;
    fscanf(fp, "%d %d", &G->n, &G->e);
    for(int i=0; i<G->n; i++){
        fscanf(fp, "%d", &G->Verlist[i]);
    }
    memset(G->edge, 0, sizeof(G->edge));
    for(int k=0; k<G->e; k++){
        fscanf(fp, "%d %d %d", &i, &j, &w);
        G->edge[i][j] = w;
    }
}

void print_mgraph(MTGraph *G){
    cout<<"邻接矩阵\n";
    cout<<"顶点数为："<<G->n<<"\t边数为："<<G->e<<endl;
    cout<<"顶点为：";
    for(int i=0; i<G->n; i++){
        cout<<G->Verlist[i]<<" ";
    }cout<<endl;
    cout<<"邻接矩阵为："<<endl;
    for(int i=0; i<G->n; i++){
        for(int j=0; j<G->n; j++){
            cout<<G->edge[i][j]<<" ";
        }cout<<endl;
    }
}

void bfs_mgraph(MTGraph *G){
    int *flag = (int*)malloc(sizeof(int)*G->n);
    queue<int> q;
    memset(flag, 0, sizeof(int)*G->n);
    int count = 0;
    cout<<"（邻接矩阵）广度优先搜索序列为："<<endl;
    fprintf(fp, "%s", "（邻接矩阵）广度优先搜索序列为：\n");
    for(int i=0; i<G->n; i++){
        if(flag[i] == 0){
            flag[i] = 1;
            count++;
            cout<<G->Verlist[i]<<" ";
            fprintf(fp, "%d", G->Verlist[i]);
            fprintf(fp, "%c", ' ');
            for(int j=0; j<G->n; j++){
                if(j!=i && G->edge[i][j]){
                    q.push(j);
                }
            }
        }
        while(!q.empty() && count != G->n){
            if(!flag[q.front()]){
                flag[q.front()] = 1;
                count++;
                cout<<G->Verlist[q.front()]<<" ";
                fprintf(fp, "%d", G->Verlist[q.front()]);
                fprintf(fp, "%c", ' ');
                for(int j=0; j<G->n; j++){
                    if(j != q.front() && G->edge[q.front()][j]){
                        q.push(j);
                    }
                }
            }
            q.pop();
        }
    }
    cout<<endl;
    fprintf(fp, "%c", '\n');
}