//
//  Encoding.cpp
//  haffmanEncoding
//
//  Created by 黄美强 on 15/4/20.
//  Copyright (c) 2015年 黄 美强. All rights reserved.
//

#include "haffmanStructure.h"
#include "Encoding.h"
using namespace std;

int Encoding::Encoding_main(string input_str,string output_str,BiTree &code_tree) {

    map<unsigned char,int> charCount_map;
    vector<unsigned char> source;
    //ifstream file_input(input_str.c_str(),ios_base::in | ios_base::binary);
    FILE * file_input;
    file_input = fopen(input_str.c_str(), "rb");
    ofstream file_output(output_str.c_str());
    if(!file_output || !file_input)
        return -1;
    /*
    file_input.seekg (0, file_input.end);
    unsigned long source_length = file_input.tellg();
    file_input.seekg (0, file_input.beg);*/
    unsigned char c;

    while (fread(&c,sizeof(unsigned char),1,file_input)!=0) {
        source.push_back(c);
        if (charCount_map.find(c) == charCount_map.end()) {
            charCount_map[c] = 1;
        }
        else{
            charCount_map[c]++;
        }
    }
    /*for(unsigned long i = 0; i<source_length; i++){
        file_input.read(&c[0], 1);
        source.append(c);
        if(charCount_map.find(c[0]) == charCount_map.end()){
            charCount_map[c[0]] = 1;
        }
        else{
            charCount_map[c[0]]++;
        }
    }*/
    fclose(file_input);
    //cout<<source<<endl<<endl<<endl;
    vector<BiTreeNode> Trees;

    map<unsigned char,int>::iterator map_it;
    map_it = charCount_map.begin();
    while(map_it!=charCount_map.end()){
        //stringstream ss;
        //string s;
        //ss << map_it->first;
        //ss >> s;
        BiTree *temp = new BiTree("", map_it->second, map_it->first);
        BiTreeNode *temp_node = new BiTreeNode(temp);
        Trees.push_back(*temp_node);
        map_it++;
    }
    sort(Trees.begin(),Trees.end(),compare_by_value);

     /*vector<BiTreeNode>::iterator it;
     it = Trees.begin();
     while(it!=Trees.end()){
     cout<<(*(*it).node).getChar_a()<<" has "<<(*(*it).node).getCount()<<endl;
     it++;
     }*/

    if(Trees.size() == 0){
        cout<<"Nothing in this document!"<<endl;
        return -1;
    }

    while(Trees.size() != 1){
        BiTree *node = new BiTree("",(*(Trees[0].node)).getCount()+(*(Trees[1].node)).getCount(),'n');
        if(!(*(Trees[0].node)).hasChild()){
            node->rightchild = Trees[1].node;
            node->leftchild = Trees[0].node;
        }else{
            node->leftchild = Trees[0].node;
            node->rightchild = Trees[1].node;
        }
        Trees.erase(Trees.begin(), Trees.begin()+2);
        BiTreeNode *temp = new BiTreeNode(node);
        Trees.push_back(*temp);
        sort(Trees.begin(),Trees.end(),compare_by_value);
    }

    map<unsigned char,string> code_map;
    TreeTravel_makemap(Trees[0].node,&code_map);

    code_tree = *(Trees[0].node);
    /*
    map<char,string>::iterator code_map_it;
     for(code_map_it = code_map.begin();code_map_it != code_map.end();code_map_it++){
     cout<<(*code_map_it).first<<"\t"<<(*code_map_it).second<<endl;
     }
    */
    string code = "";
    for(int i = 0; i<source.size(); i++){
        //cout<<source.at(i);
        code.append(code_map[source[i]]);
    }
    /*
    unsigned long count = 0;
    map<char,int> countmap;
    TreeTravel(&code_tree, countmap);
    for(int i = 0; i<source.length(); i++){
        //cout<<source.at(i);
        count += countmap[source.at(i)];
    }

    cout<<"original long ="<<count<<endl;
    cout<<code.length()<<endl;
    */
    //cout<<code<<endl;
    unsigned int rem = 8 - code.length()%8;
    if(rem != 8){
        for(int i = 0; i<rem;i++){
            code.append("0");
        }
    }
    file_output<<rem;

    for(int i = 0; i<code.length()/8; i++){
        unsigned char a = 0;
        for(int j = 0; j<8;j++){
            a <<= 1;
            a |= (code.at(8*i+j)-'0');
        }
        //cout<<a<<endl;
        file_output<<a;
    }
    file_output.close();

    return 0;
} 
