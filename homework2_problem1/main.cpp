#include <iostream>
#include <stack>
using namespace std;

class Calculate{
private:
    char oriExperssion[100];
    char expression[100];
    int length;
    int length_;
    stack<char> operate;
    stack<int> number;
public:
    Calculate();
    void print();
    void calculate();
};

int main() {
    Calculate cal;
    cal.print();
    cal.calculate();
}

Calculate::Calculate() {
    int index=0;
    cin>>oriExperssion;
    length = strlen(oriExperssion);
    length_ = length;
    for(int i=0;i<length;i++){
        if(oriExperssion[i]=='(') {
            length_--;
            operate.push(oriExperssion[i]);
        }
        else if(oriExperssion[i]==')'){
            length_--;
            while(operate.top()!='('){
                expression[index++] = operate.top();
                operate.pop();
            }
            operate.pop();
        }
        else if(oriExperssion[i]>='0' && oriExperssion[i]<='9')
            expression[index++] = oriExperssion[i];
        else{
            if(oriExperssion[i]=='*'||oriExperssion[i]=='/'){
                while(!operate.empty()&&operate.top()!='('){
                    if(operate.top()=='+'||operate.top()=='-') {
                        break;
                    }
                    else{
                        expression[index++] = operate.top();
                        operate.pop();
                    }
                }
                    operate.push(oriExperssion[i]);
            }
            else if(oriExperssion[i]=='+'||oriExperssion[i]=='-'){
                while(!operate.empty()&&operate.top()!='('){
                    expression[index++] = operate.top();
                    operate.pop();
                }
                operate.push(oriExperssion[i]);
            }
        }
    }
    while(!operate.empty()){
        expression[index++] = operate.top();
        operate.pop();
    }
}

void Calculate::print() {
    for(int i=0;i<length;i++) {
        cout<<expression[i];
    }
    cout<<endl;
}

void Calculate::calculate() {
    for(int i=0;i<length_;i++) {
        if(expression[i]>='0'&&expression[i]<='9'){
            number.push((int)(expression[i]-'0'));
        }
        else{
            int a,b,c;
            a = number.top();
            number.pop();
            b = number.top();
            number.pop();
            switch (expression[i]) {
                case '+':
                    c = a+b;
                    break;
                case '-':
                    c = b-a;
                    break;
                case '*':
                    c = a*b;
                    break;
                case '/':
                    c = b/a;
                    break;
            }
            number.push(c);
        }
    }
    cout<<number.top();
}