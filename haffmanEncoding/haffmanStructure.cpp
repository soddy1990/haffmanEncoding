//
//  haffmanStructure.cpp
//  haffmanEncoding
//
//  Created by 黄美强 on 15/4/20.
//  Copyright (c) 2015年 黄 美强. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "haffmanStructure.h"

using namespace std;

BiTree::BiTree(){
    leftchild = NULL;
    rightchild = NULL;
    code = "";
    this->char_a = NULL;
}
BiTree::BiTree(string code,int count, char charactor){
    leftchild = NULL;
    rightchild = NULL;
    this->code = code;
    this->count = count;
    this->char_a = charactor;
}
void BiTree::appendCode(string c){
    this->code.append(c);
}
int BiTree::getCount(){
    return this->count;
}
string BiTree::getCode(){
    return this->code;
}
unsigned char BiTree::getChar_a(){
    return this->char_a;
}
bool BiTree::hasChild(){
    return this->rightchild != NULL || this->leftchild != NULL;
}
BiTree::~BiTree(){
    deleteNode(this);
}
void BiTree::deleteNode(BiTree *head){
    if(!head->hasChild()){
        delete head;
    }
    else{
        if(head->leftchild!=NULL){
            deleteNode(head->leftchild);
        }
        if(head->rightchild!=NULL){
            deleteNode(head->rightchild);
        }
    }
}


BiTreeNode::BiTreeNode(BiTree* node){
    this->node = node;
}


void TreeTravel_makemap(BiTree *head, map<unsigned char,string> *code_map){
    if(head->hasChild()){
        if(head->leftchild!=NULL){
            head->leftchild->appendCode(head->getCode());
            head->leftchild->appendCode("0");
            TreeTravel_makemap(head->leftchild,code_map);
        }
        if(head->rightchild!=NULL){
            head->rightchild->appendCode(head->getCode());
            head->rightchild->appendCode("1");
            TreeTravel_makemap(head->rightchild,code_map);
        }
        //cout<<head->getChar_a()<<" has "<<head->getCount()<<" code is: "<<head->getCode()<<endl;
    }
    else{
        //cout<<head->getChar_a()<<" has "<<head->getCount()<<" code is: "<<head->getCode()<<endl;
        (*code_map)[head->getChar_a()] = head->getCode();
    }
}

void TreeTravel(BiTree *head,map<unsigned char,int> &countmap){
    if(head->hasChild()){
        if(head->leftchild!=NULL){
            TreeTravel(head->leftchild,countmap);
        }
        if(head->rightchild!=NULL){
            TreeTravel(head->rightchild,countmap);
        }
        //cout<<head->getChar_a()<<" has "<<head->getCount()<<" code is: "<<head->getCode()<<endl;
    }
    else{
        countmap[head->getChar_a()] = (int)(head->getCode()).length();
    }
}

unsigned char TreeTravel(BiTree *head, string &result , unsigned long &pos){
    if (!head->hasChild()) {
        return head->getChar_a();
    }
    if (result.at(pos) == '0') {
        if (head->leftchild != NULL) {
            pos++;
            return TreeTravel(head->leftchild,result,pos);
        }
        cout<<"leftchild error!"<<endl;
        return NULL;
    }
    else if(result.at(pos) == '1') {
        if (head->rightchild != NULL) {
            pos++;
            return TreeTravel(head->rightchild,result,pos);
        }
        cout<<"rightchild error!"<<endl;
        return NULL;
    }
    else{
        cout<<"unknown child error!"<<endl;
        return NULL;
    }
}

bool compare_by_key(pair<unsigned char,int> &c1,pair<unsigned char,int> &c2){
    return c1.first<c2.first;
}
bool compare_by_value(BiTreeNode &c1, BiTreeNode &c2){
    return (*(c1.node)).getCount()<(*(c2.node)).getCount();
}
