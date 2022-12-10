#include <iostream>
using namespace std;

#define MAXSIZE 20

typedef struct{
    char n, a, b, c;
}INFO;

INFO S[MAXSIZE];
int top = -1;

void hanoi(int n,char a,char b,char c);
void push(char n, char a, char b, char c);
void hanoi_f(char n, char a, char b, char c);

int main(){
    hanoi(3, 'a', 'b', 'c');
    cout<<endl;
    hanoi_f(3, 'a', 'b', 'c');
    return 0;
}

void hanoi(int n,char start,char by,char end){
    if(n == 1){
        cout<<start<<"->"<<end<<endl;
        return;
    }
    hanoi(n-1, start, end, by);
    cout<<start<<"->"<<end<<endl;
    hanoi(n-1, by, start, end);
}

void push(char n, char a, char b, char c){
    top++;
    S[top].n = n;
    S[top].a = a;
    S[top].b = b;
    S[top].c = c;
}

void hanoi_f(char n, char a, char b, char c){
    push(n, a, b, c);
    while(top>=0){
        INFO t = S[top];
        top--;
        if(t.n==1){
            cout<<t.a<<"->"<<t.c<<endl;
        }
        else{
            push(t.n-1, t.b, t.a, t.c);
            push(1, t.a, t.b, t.c);
            push(t.n-1, t.a, t.c, t.b);
        }
    }
}