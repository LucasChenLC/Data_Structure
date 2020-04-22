#include <iostream>
#include <fstream>
#include <string.h>
#include "huffman.h"
using namespace std;

void count(long *counts);
treeNode *merge_sort(long *counts);

int main()
{

    Huffman h;
    h.huffCode_gene();
    h.print();
    return 0;

}


