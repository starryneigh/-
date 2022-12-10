#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

int to_num(string s){       //将数字字符串转化成相应的数值
    int i=0;
    int result = 0;
    int temp;
    while(i<s.length()){
        temp = s[i]-48;
        result *= 10;
        result += temp;
        i++;
    }
    return result;
}

int isp(char a){        //栈内优先级in_stack_priority
    if(a == '#'){
        return 0;
    }
    else if(a == '('){
        return 1;
    }
    else if(a == '+' || a == '-'){
        return 3;
    }
    else if(a == '*' || a == '/'){
        return 5;
    }
    else if(a == ')'){
        return 6;
    }
    else{
        return -1;
    }
}

int icp(char a){        //入栈优先级 
    if(a == '#'){
        return 0;
    }
    else if(a == ')'){
        return 1;
    }
    else if(a == '+' || a == '-'){
        return 2;
    }
    else if(a == '*' || a == '/'){
        return 4;
    }
    else if(a == '('){
        return 6;
    }
    else{
        return -1;
    }
}

string zhong_hou(string s){     //中缀转后缀
    string result;
    stack<char>t;
    int i=0;
    t.push('#');
    cout<<"栈中\"#\"为标识符，判断是否到栈底"<<endl;
    while(i<s.length()){        
        if(s[i] == '#'){        //若为#，则跳过
            i++;
            continue;
        }
        if(s[i] == ' '){        //若为空格，则跳过
            i++;
            continue;
        }
        if(isalnum(s[i])){      //若为字母或数字，直接加入result
            cout<<s[i]<<": 为字母或数字，直接进入result中"<<endl;
            result += s[i];
            i++;
        }
        else if(isp(t.top()) < icp(s[i])){  //若栈内优先级小于入栈优先级，则入栈
            if(result[result.length()-1] != ' '){
                result += ' ';
            }
            cout<<s[i]<<": "<<t.top()<<"的栈内优先级小于"<<s[i]<<"的入栈优先级，将"<<s[i]<<"入栈"<<endl;
            t.push(s[i]);
            i++;
        }
        else if(isp(t.top()) > icp(s[i])){  //若栈内优先级大于入栈优先级，则出栈
            if(result[result.length()-1] != ' '){
                result += ' ';
            }
            cout<<s[i]<<": "<<t.top()<<"的栈内优先级大于"<<s[i]<<"的入栈优先级，将"<<t.top()<<"出栈加入result中"<<endl;
            result += t.top();
            t.pop();
        }
        else if(isp(t.top()) == icp(s[i])){ //若相等，则为括号，将（出栈
            cout<<"\"(\"和\")\"配对，将\"(\"出栈"<<endl;
            t.pop();
            i++;
        }
    }
    while(t.top() != '#'){      //将栈中剩余元素出栈
        if(result[result.length()-1] != ' '){
            result += ' ';
        }
        cout<<"将"<<t.top()<<"出栈加入result中"<<endl;
        result += t.top();
        t.pop();
    }
    return result;
}

int cal_zhonghouzhui(string s){     //计算后缀表达式
    stack<int>t;
    string num;
    int i=0;
    int a, b;
    int result;
    while(i<s.length()){
        if(s[i] == ' '){            //若为空格，则跳过
            if(num != ""){          //若num不为空，则计算num串的数值，并入栈
                cout<<"将"<<to_num(num)<<"入栈"<<endl;
                t.push(to_num(num));
                num = "";
            }
            i++;
        }
        if(isalnum(s[i])){          //若为数字或字母，则加入num串
            num += s[i];
            i++;
        }
        else{
            b = t.top();        //取出栈顶的两个元素
            t.pop();
            a = t.top();
            t.pop();
            switch (s[i])       //判断s[i]为何种运算符
            {
            case '+': 
                t.push(a+b);
                cout<<a<<'+'<<b<<'='<<a+b<<endl;
                break;
            case '-': 
                t.push(a-b);
                cout<<a<<'-'<<b<<'='<<a-b<<endl;
                break;
            case '*': 
                t.push(a*b);
                cout<<a<<'*'<<b<<'='<<a*b<<endl;
                break;
            case '/': 
                t.push(a/b);
                cout<<a<<'/'<<b<<'='<<a/b<<endl;
                break;
            default:
                break;
            }
            i++;
        }
    }
    if(!t.empty()){
        result = t.top();
    }
    return result;
}

int main(){
    string s, temp;
    ifstream infile;
    infile.open("change.txt");
    getline(infile, s);
    cout<<s<<endl;
    string result;
    result = zhong_hou(s);
    cout<<"中缀表达式为：";
    cout<<s<<endl;
    cout<<"后缀表达式为：";
    cout<<result<<endl;

    int cal;
    cout<<"计算过程："<<endl;
    cal = cal_zhonghouzhui(result);
    cout<<cal<<endl;

    return 0;
}