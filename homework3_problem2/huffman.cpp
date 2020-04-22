//
// Created by Blue Sky on 3/26/20.
//
#include "huffman.h"
Huffman::Huffman(void) {

    char str[100];
    cin.getline(str,100);
    memset(counts,0,128*sizeof(double));
    for(int i=0;i<strlen(str);i++){
        counts[str[i]]++;
    }
    int num;
    int x = strlen(str);
    treeNode *data;
    data=merge_sort_cp(counts,&num);
    this->size = num;
    int mini_1,mini_2;
    for(int a=0;a<size-1;a++){
        mini_1 = a;mini_2 = a+1;
        double beta = INT_MAX;
        for(int b=0;b<size;b++)
        {
            if(data[b].times>0 && data[b].times<beta){
                beta = data[b].times;
                mini_1 = b;
            }
        }
        beta = INT_MAX;
        for(int b=0;b<size;b++)
        {
            if(data[b].times>0 && data[b].times<beta && b!=mini_1 ){
                beta = data[b].times;
                mini_2 = b;
            }
        }
        treeNode *n = (treeNode *)malloc(sizeof(treeNode));
        n->times = data[mini_2].times;
        n->ltree = data[mini_2].ltree;
        n->rtree = data[mini_2].rtree;
        n->ch = data[mini_2].ch;
        data[mini_2].ltree = &data[mini_1];
        data[mini_2].rtree = n;
        data[mini_2].times = data[mini_2].rtree->times + data[mini_2].ltree->times;
        n->times = -1;
        data[mini_1].times = -1;
    }
        root = &data[mini_2];
        for(double & count : counts)
            count/=x;
    return;
}

Huffman::Huffman(string str){
    filePath = str;
    this->root = (treeNode *)malloc(sizeof(treeNode));
    resetTree();
}

void Huffman::saveTree(){
    replaceNode(root);
    ofstream outFile(filePath,ios::out);
    preTravel(root,&outFile);
    const int flag = 255;
    outFile<<flag<<" ";
    midTravel(root,&outFile);
    outFile<<flag<<"  ";
    outFile.close();
}

void Huffman::replaceNode(treeNode *root){
    static int num=256;
    if(root->rtree==NULL&&root->ltree==NULL){
        return;
    }
    else{
        if(root->ltree!=NULL)
            replaceNode(root->ltree);
        root->ch = num++;
        if(root->rtree!=NULL)
            replaceNode(root->rtree);
    }
}

void Huffman::preTravel(treeNode *root,ofstream *outFile){
    if(root->ltree==NULL&&root->rtree==NULL){
        *outFile<<root->ch<<" ";
        return;
    }
    else{
        *outFile<<root->ch<<" ";
        if(root->ltree!=NULL)
            preTravel(root->ltree,outFile);
        if(root->rtree!=NULL)
            preTravel(root->rtree,outFile);
    }
}



void Huffman::resetTree(){
    int mid[256],pre[256];
    int root_p=-1;
    ifstream inFile(filePath,ios::in);
    int count1=0,count2=0;
    while(true)
    {
        inFile>>pre[count1];
        if(pre[count1]==255)
        {
            pre[count1]='\0';
            break;
        }
        count1++;
    }

    while(true)
    {
        inFile>>mid[count2];
        if(mid[count2]==255)
        {
            mid[count2]='\0';
            break;
        }
        count2++;
    }
    tree_length = count1;
    find_root(&root_p,pre,mid,0,count1-1);
    build_tree(this->root,pre,mid,0,root_p,count1-1);
}

void Huffman::build_tree(treeNode *root,int *pre_s,int *mid_s,int start,int root_p,int end){
    if(start==end){
        root->ch = mid_s[start];
        root->ltree=NULL;
        root->rtree=NULL;
    }
    else{
        root->ch = mid_s[root_p];
        treeNode *ltree,*rtree;
        if(root_p>start) {
            int mid1=-1;
            ltree = (treeNode *)malloc(sizeof(treeNode));
            find_root(&mid1,pre_s,mid_s,start,root_p-1);
            root->ltree = ltree;
            build_tree(ltree,pre_s,mid_s,start, mid1 ,root_p-1);
        }
        else
            root->ltree=NULL;
        if(root_p<end) {
            int mid2=-1;
            rtree = (treeNode *)malloc(sizeof(treeNode));
            find_root(&mid2,pre_s,mid_s,root_p+1,end);
            root->rtree = rtree;
            build_tree(rtree,pre_s,mid_s,root_p+1, mid2 ,end);
        }
        else
            root->rtree = NULL;
    }
}

void Huffman::find_root(int *root_p,int *pre_s,int *mid_s,int start,int end){
    for (int a = 0; a < tree_length; a++) {
        for (int b = start; b <= end; b++) {
            if (pre_s[a] == mid_s[b])
                *root_p = b;
        }
        if (*root_p!=-1)
            break;
    }
}

void Huffman::midTravel(treeNode *root,ofstream *outFile){
    if(root->ltree==NULL&&root->rtree==NULL){
        *outFile<<root->ch<<" ";
        return;
    }
    else{

        if(root->ltree!=NULL)
            midTravel(root->ltree,outFile);
        *outFile<<root->ch<<" ";
        if(root->rtree!=NULL)
            midTravel(root->rtree,outFile);
    }
}

void Huffman::generateCode(treenode *root,char *code,int length){
    if(root->ltree==NULL && root->rtree==NULL){
        int num = root->ch;
        char ch = root->ch;
        //cout<<ch<<endl;
        for(int a=0;a<length;a++) {
            huffcode[num].push((bool)code[a]);
            //cout<<code[a]+0<<" ";
        }
        //cout<<endl;
        arra[num].length = length;
        arra[num].ch = root->ch;
        return;
    }
    else{
        code[length]=0;
        generateCode(root->ltree,code,length+1);
        code[length]=1;
        generateCode(root->rtree,code,length+1);
    }
}

void Huffman::print() {
    bool find;
    while(true) {
        int p=0;
        find = false;
        for(int i=0;i<128;i++)
        {
            if(counts[i]>counts[p] && counts[i]>0) {
                p = i;
                find = true;
            }
        }

        if (!huffcode[p].empty()) {
                cout << (char) p << ":";
            cout<<fixed<<setprecision(2) <<counts[p]<<":";
                while (!huffcode[p].empty()) {
                    cout << huffcode[p].front();
                    huffcode[p].pop();
                }
                cout << endl;
        }
        counts[p]=0;
        if(!find)
            break;
    }
}

void Huffman::huffCode_gene() {
    char code[128];
    arra = (huffCode *)malloc(128*sizeof(huffCode));
    generateCode(root,code,0);
    /*
   for(int a=0;a<size;a++)
    {
        cout<<arra[a].ch<<" "<<arra[a].length<<endl;
        for(int b=0;b<arra[a].length;b++)
            cout<<arra[a].code[b]+0<<" ";
        cout<<endl;
    }*/
    return;
}

void Huffman::save_code() {
    ofstream outFile("compress.txt",ios::binary);
    outFile<<size<<endl;
    for(int a=0;a<size;a++){
        outFile<<arra[a].length<<" "<<arra[a].ch;
        compressCode(&outFile,a);
    }
    outFile.close();
}

void Huffman::compressCode(ofstream *outFile,int index){
    int posi = arra[index].length;
    unsigned char data=0;
    //cout<<arra[index].ch<<" "<<arra[index].length<<endl;
    for(int a=0;a<arra[index].length;a++){
        data += arra[index].code[a]*pow(2,a%8);
        if((a+1)%8==0) {
            //cout << "data  " << data + 0;
            *outFile << data;
            data=0;
        }
    }
    if(arra[index].length%8!=0){
        *outFile<<data;
    }
    *outFile<<endl;
}

void Huffman::compress(string str,string str1) {
    filePath = str;
    saveTree();
    char code[128],data;
    unsigned char outCode;
    array.clear();
    arra = (huffCode *)malloc(128*sizeof(huffCode));
    generateCode(root,code,0);
    ofstream outFile(filePath,ios::app);
    ifstream inFile(str1,ios::in);
    while(inFile.get(data)||!inFile.eof())
    {
        for(int a=0;a<arra[data].length;a++){
            array.insert_back(arra[data].code[a]);
        }
        if(array.size()>=8) {
            outCode = exchangeCode();
            outFile<<outCode;
         //   //cout<<0+outCode<<endl;
        }
    }
    if(array.size()<8){
        while(array.size()<8)
        array.insert_back(0);
        outCode = exchangeCode();
        outFile<<outCode;
     //   //cout<<0+outCode<<endl;
    }
    outFile.close();
    inFile.close();
}

unsigned char Huffman::exchangeCode() {
    unsigned char ans=0;
    int x;
    for(int a=0;a<8;a++){
        x = array.pop();
        //cout<<x+0;
        ans+=x*pow(2,a);
    }
    //cout<<endl;
    return ans;
}

void Huffman::decompress(string inPath,string outPath){
    int blank,count=0,flag=0;
    unsigned char data;
    char ans;
    array.clear();
    ifstream inFile(inPath,ios::binary);
    while(true) {
        inFile >> blank;
        if(blank==255)
            count++;
        if(count>=2)
            break;
    }
    ofstream outFile(outPath,ios::out);
    while(inFile>>noskipws>>data||!inFile.eof()){
        if(flag==0)
        {
            flag=1;
            inFile>>noskipws>>data;
            continue;
        }
        decode(data,0);
        do{
            ans = huffSearch();
            //cout<<ans;
            if(ans!=0)
                outFile.put(ans);
        }while(ans);
    }
    inFile.close();
    outFile.close();
    /*int z;
    inFile>>z;
    outFile.close();
    ofstream aa("new.txt",std::ios::in);
    if(z!=0)
    for(int a=-z;a<=0;a++) {
        aa.seekp(a, std::ios::end);
        aa << " ";
    }
    aa.close();*/
}

void Huffman::decode(unsigned char code,int times){
    if(times==8)
        return;
    if(code%2==0){
        array.insert_back(0);
        decode(code/2,times+1);
    }
    else{
        array.insert_back(1);
        decode(code/2,times+1);
    }
}

char Huffman::huffSearch(){
    char a;
    treeNode *temp=root;
    stack<int> temp_store;
    int size = array.size();
    for(a=0;a<size;a++){
        int t = array.pop();
        temp_store.push(t);
        if(t==1)
            temp = temp->rtree;
        else
            temp = temp->ltree;
        if(temp->ltree==NULL && temp->rtree == NULL){
            return (char)temp->ch;
        }
    }
    while(!temp_store.empty())
    {
        array.insert_front(temp_store.top());
        temp_store.pop();
    }
    return 0;
}