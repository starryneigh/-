#include <iostream>
using namespace std;

#define SIZE 256

int moveByGs(int j, int m, int suffix[], bool prefix[]);
void generateBC(string b, int m, int bc[]);
void generateGS(string b, int m, int suffix[], bool prefix[]);
int bm(string a, string b);

void get_shift(int shift[SIZE], string b);
int Sunday(string a, string b);

int main(){
    string a = "math is simple";
    string b = "simple";
    int index = bm(a, b);
    cout<<a<<endl;
    for(int i=0; i<index; i++) cout<<" ";
    cout<<b<<endl;
    cout<<"用BM算法，匹配下标为: "<<index<<endl;
    cout<<"用Sunday算法，匹配下标为: "<<Sunday(a, b)<<endl;
    return 0;
}

//j表示坏字符对应模式串的字符下标，m为模式串长度
int moveByGs(int j, int m, int suffix[], bool prefix[]){
    int k = m-1-j;
    if(suffix[k] != -1) return j-suffix[k]+1;   //若suffix[k]不为-1，则将模式串前移
    for(int r=j+2; r<=m-1; ++r){        //j=m-2不用考虑，若为一个好字符且suffix[k]=-1,则prefix[0]必为false
        if(prefix[m-r] == true){        
            return r;               //r为前移格数
        }
    }
    return m;
}

//生成坏字符哈希表
//b为模式串，m为模式串长度，bc为坏字符哈希表
void generateBC(string b, int m, int bc[]){
    for(int i=0; i<SIZE; ++i){
        bc[i] = -1;             //初始化为-1
    }
    for(int i=0; i<m; ++i){
        int ascii = (int)b[i];  //在模式串中的字符取其ascii码值
        bc[ascii] = i;          //其值为最后一次出现的下标
    }
}

//生成好字符哈希表
void generateGS(string b, int m, int suffix[], bool prefix[]){
    for(int i=0; i<m; ++i){
        suffix[i] = -1;         //初始化为-1, suffix[i]为长度为i的好字符（后缀）
        prefix[i] = false;      //初始化为false
    }
    for(int i=0; i<m-1; ++i){   //循环开始，寻找相同后缀
        int j=i;
        int k=0;
        while(j>=0 && b[j] == b[m-1-k]){    
            --j;
            ++k;
            suffix[k] = j+1;    //j+1 为后缀左侧下标
        }
        if(j == -1) prefix[k] = true;   //j=-1说明公共后缀子串也是模式串的前缀子串
    }
}

//a为主串，b为模式串
int bm(string a, string b){
    int bc[SIZE];               //坏字符哈希表
    int n = a.length();         
    int m = b.length();
    generateBC(b, m, bc);       //生成坏字符哈希表
    int *suffix = new int[m];   //开可变长度的数组
    bool *prefix = new bool[m]; 
    generateGS(b, m, suffix, prefix);
    int i=0;
    while(i<=n-m){
        int j;
        for(j =m-1; j>=0; --j){
            if(a[i+j] != b[j]) break;
        }
        if(j<0){
            return i;
        }
        int x = j-bc[(int)a[i+j]];      
        int y=0;
        if(j<m-1){
            y = moveByGs(j, m, suffix, prefix);
        }
        i = i+max(x, y);        //取两者最大值
    }
    return -1;
}

void get_shift(int shift[SIZE], string b){
    for(int i=0; i<SIZE; i++){
        shift[i] = -1;
    }
    for(int i=0; i<b.length(); i++){
        shift[(int)b[i]] = i;
    }
}

int Sunday(string a, string b){
    int shift[SIZE];
    get_shift(shift, b);
    int i=0;
    int j=0;
    int n = a.length();
    int m = b.length();
    while(i<=n-m+1){
        for(j=0; j<m; j++){
            if(a[i+j] != b[j]) break;
        }
        if(j==m) return i;
        else{
            i += m - shift[a[i+m]];
        }
    }
    return -1;
}