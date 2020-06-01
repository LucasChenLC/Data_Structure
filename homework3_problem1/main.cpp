#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

typedef struct node{
    char operate;
    struct node *lTree;
    struct node *rTree;
}Node;

typedef struct flagnode{
    bool visit;
    Node *tRoot;
}flagNode;

class Expression{
private:
    stack<char> operate;
    char oriExpression[100];
    int length;
    Node *root;
    flagNode flag[10];
    void preSwitch();
    void inSwitch();
    void postSwitch();
    void buildTree(char temp);
    void pre(Node *root);
    void in(Node *root);
    void post(Node *root);
    void clearFlag(Node *root);
    int rootPos;
public:
    Expression(int mode);
    void preprint();
    void inprint();
    void postprint();
};

int main() {
    int mode;
    cin>>mode;
    Expression e(mode);
    e.preprint();
    e.inprint();
    e.postprint();
    return 0;
}

Expression::Expression(int mode){
    cin>>oriExpression;
    length = strlen(oriExpression);
    //flag = (flagNode *)malloc(length*sizeof(flagNode));
    for(int i=0;i<length;i++){
        flag[i].visit = false;
        flag[i].tRoot = (Node *)malloc(sizeof(Node));
        flag[i].tRoot->operate = oriExpression[i];
        flag[i].tRoot->lTree = NULL;
        flag[i].tRoot->rTree = NULL;
    }
    if(mode==1){
        preSwitch();
    }
    else if(mode==2){
        inSwitch();
    }
    else{
        postSwitch();
    }
}

void Expression::preSwitch() {
    for(int i=0;i<length;i++) {
        if(oriExpression[i]>='0'&&oriExpression[i]<='9'){
            flag[i].visit = true;
        }
    }
    int p=length-1,p1,p2;
    while(!flag[0].visit){
        while(true){
            if((oriExpression[p]<'0'||oriExpression[p]>'9')){
                for(p1=p+1;!flag[p1].visit;p1++){}
                for(p2=p1+1;!flag[p2].visit;p2++){}
                break;
            }
            else
                p--;
        }
        flag[p].tRoot->lTree = flag[p1].tRoot;
        flag[p].tRoot->rTree = flag[p2].tRoot;
        clearFlag(flag[p].tRoot);
        flag[p].visit = true;
        p--;
    }
    root = flag[0].tRoot;
}

void Expression::clearFlag(Node *root) {
    int i;
    if(root->lTree==NULL && root->rTree==NULL){
        for(i=0;flag[i].tRoot->operate!=root->operate;i++){}
            flag[i].visit = false;
    }
    else{
        for(i=0;flag[i].tRoot->operate!=root->operate;i++){}
            flag[i].visit = false;
        if(root->lTree!=NULL)
            clearFlag(root->lTree);
        if(root->rTree!=NULL)
            clearFlag(root->rTree);
    }
}
void Expression::inSwitch() {
    Node *n;
    char temp;
    for(int i=0;i<length;i++){
        if(oriExpression[i]>='0'&&oriExpression[i]<='9'){}
        else if(oriExpression[i]=='('){
            operate.push(oriExpression[i]);
        }
        else if(oriExpression[i]==')'){
            while(operate.top()!='('){
                temp = operate.top();
                operate.pop();
                buildTree(temp);
            }
            operate.pop();
        }
        else if(oriExpression[i]=='*'||oriExpression[i]=='/'){
                while(!operate.empty()&&operate.top()!='('){
                    if(operate.top()=='+'||operate.top()=='-')
                        break;
                    else{
                        temp = operate.top();
                        operate.pop();
                        buildTree(temp);
                    }
                }
                    operate.push(oriExpression[i]);
        }
        else if(oriExpression[i]=='+'||oriExpression[i]=='-'){
                while(!operate.empty()&&operate.top()!='('){
                    temp = operate.top();
                    operate.pop();
                    buildTree(temp);
                }
                operate.push(oriExpression[i]);
        }
    }
    while(!operate.empty()){
        temp = operate.top();
        operate.pop();
        buildTree(temp);
    }
    root = flag[rootPos].tRoot;
}

void Expression::postSwitch() {
    for(int i=0;i<length;i++) {
        if(oriExpression[i]>='0'&&oriExpression[i]<='9'){
            flag[i].visit = true;
        }
    }
    int p=0,p1,p2;
    while(!flag[length-1].visit){
        while(true){
            if((oriExpression[p]<'0'||oriExpression[p]>'9')){
                for(p1=p-1;!flag[p1].visit;p1--){}
                for(p2=p1-1;!flag[p2].visit;p2--){}
                break;
            }
            else
                p++;
        }
        flag[p].tRoot->rTree = flag[p1].tRoot;
        flag[p].tRoot->lTree = flag[p2].tRoot;
        clearFlag(flag[p].tRoot);
        flag[p].visit = true;
        p++;
    }
    root = flag[length-1].tRoot;
}

void Expression::buildTree(char temp) {
    int p;
    for(p=0;oriExpression[p]!=temp;p++){}
    rootPos = p;
    for(int i=p-1;i>=0;i--){
        if(!flag[i].visit && oriExpression[i]!='(' && oriExpression[i]!=')'){
            flag[p].tRoot->lTree = flag[i].tRoot;
            flag[i].visit=true;
            break;
        }
    }
    for(int i=p+1;i<length;i++){
        if(!flag[i].visit && oriExpression[i]!='(' && oriExpression[i]!=')'){
            flag[p].tRoot->rTree = flag[i].tRoot;
            flag[i].visit=true;
            break;
        }
    }
}

void Expression::preprint() {
    pre(root);
    cout<<endl;
}

void Expression::inprint() {
    in(root);
    cout<<endl;
}

void Expression::postprint() {
    post(root);
    cout<<endl;
}

void Expression::pre(Node *root){
    if(root->lTree==NULL && root->rTree==NULL){
        cout<<root->operate;
    }
    else{
        cout<<root->operate;
        if(root->lTree!=NULL)
            pre(root->lTree);
        if(root->rTree!=NULL)
            pre(root->rTree);
    }
}

void Expression::in(Node *root){
    if(root->lTree==NULL && root->rTree==NULL){
        cout<<root->operate;
    }
    else{
        if(root->lTree!=NULL) {
            if((root->operate=='*'||root->operate=='/') && (root->lTree->operate=='+'||root->lTree->operate=='-'))
                cout<<"(";
            in(root->lTree);
            if((root->operate=='*'||root->operate=='/') && (root->lTree->operate=='+'||root->lTree->operate=='-'))
                cout<<")";
        }
        cout<<root->operate;
        if(root->rTree!=NULL) {
            if((root->operate=='*'||root->operate=='/') && (root->rTree->operate=='+'||root->rTree->operate=='-'))
                cout<<"(";
            in(root->rTree);
            if((root->operate=='*'||root->operate=='/') && (root->rTree->operate=='+'||root->rTree->operate=='-'))
                cout<<")";
        }
    }
}

void Expression::post(Node *root){
    if(root->lTree==NULL && root->rTree==NULL){
        cout<<root->operate;
    }
    else{
        if(root->lTree!=NULL)
            post(root->lTree);
        if(root->rTree!=NULL)
            post(root->rTree);
        cout<<root->operate;
    }
}