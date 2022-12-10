#include <iostream>
using namespace std;

int jiao_gu(int a);
void jiao_gu_print(int a);

int main(){
    int temp=0;
    int ia;
    cout<<"i"<<"\t"<<"序列数"<<endl;
    for(int i=1; i<=100; i++){
        cout<<i<<"\t";
        cout<<jiao_gu(i)<<endl;
        if(temp<jiao_gu(i)){
            temp = jiao_gu(i);
            ia = i;
        }
    }
    cout<<"最大序列数为："<<temp<<endl;
    cout<<"为数："<<ia<<endl;
    cout<<"最大序列为："<<endl;
    jiao_gu_print(ia);
    return 0;
}

int jiao_gu(int a){
    int count = 0;
    while(a!=1){
        if(a%2 == 0){
            a /= 2;
        }
        else{
            a = a*3+1;
        }
        //cout<<a<<endl;
        count++;
    }
    //cout<<count<<endl;
    return count;
}

void jiao_gu_print(int a){
    while(a!=1){
        if(a%2 == 0){
            a /= 2;
        }
        else{
            a = a*3+1;
        }
        cout<<a<<"\t";
    }
}