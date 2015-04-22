//
//  haffmanStructure.h
//  haffmanEncoding
//
//  Created by 黄美强 on 15/4/20.
//  Copyright (c) 2015年 黄 美强. All rights reserved.
//

#ifndef haffmanEncoding_haffmanStructure_h
#define haffmanEncoding_haffmanStructure_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class BiTree{
private:
    string code;
    int count;
    unsigned char char_a;
public:
    BiTree *leftchild;
    BiTree *rightchild;

    BiTree();
    BiTree(string code,int count, char charactor);
    void appendCode(string c);
    int getCount();
    string getCode();
    unsigned char getChar_a();
    bool hasChild();
    void deleteNode(BiTree *head);
    ~BiTree();
};

class BiTreeNode{
public:
    BiTree* node;
    BiTreeNode(BiTree* node);
};

void TreeTravel_makemap(BiTree *head, map<unsigned char,string> *code_map);
void TreeTravel(BiTree *head, map<unsigned char,int> &countmap);
unsigned char TreeTravel(BiTree *head,string &result, unsigned long &pos);

bool compare_by_key(pair<unsigned char,int> &c1,pair<unsigned char,int> &c2);
bool compare_by_value(BiTreeNode &c1, BiTreeNode &c2);

#endif
