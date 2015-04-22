//
//  Decoding.cpp
//  haffmanEncoding
//
//  Created by 黄美强 on 15/4/20.
//  Copyright (c) 2015年 黄 美强. All rights reserved.
//

#include "Decoding.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

int Decoding::Decoding_main(string input_str,string output_str, BiTree &code_tree) {
    //cout<<"this is output by decoding"<<endl;
    //TreeTravel(&code_tree);

    ifstream file_input(input_str.c_str());
    FILE *file_output;
    file_output = fopen(output_str.c_str(),"wb");
    if(!file_output || !file_input)
        return -1;

    file_input.seekg (0, file_input.beg);
    file_input.seekg (0, file_input.end);
    unsigned long huff_length = file_input.tellg();

    file_input.seekg (0, file_input.beg);
    unsigned long huff_pos = 0;
    char c;
    file_input.get(c);
    huff_pos++;
    unsigned int rem = c-'0';
    //cout<<rem;

    string result = "";

    for (; huff_pos< huff_length - 1; huff_pos++) {
        file_input.get(c);
        unsigned char temp = c;
        stack<int> s;
        unsigned int t = 1;
        for(int i=0; i<8; i++){
            unsigned int tem = temp & t;
            temp >>= 1;
            s.push(tem);
        }
        while (!s.empty()) {
            string str = to_string(s.top());
            s.pop();
            result.append(str);
        }
    }


    file_input.get(c);
    unsigned char temp = c;
    stack<int> s;
    //cout<<rem;
    unsigned int t = 1;
    for (int i = 0; i<rem; i++) {
        temp >>= 1;
    }
    for(int i=0; i<8-rem; i++){
        unsigned int tem = temp & t;
        temp >>= 1;
        s.push(tem);
    }
    while (!s.empty()) {
        string str = to_string(s.top());
        s.pop();
        result.append(str);
    }
    //cout<<endl<<endl<<result;

    unsigned long result_length = result.length();
    unsigned long result_pos = 0;
    //cout<<"this is decoded"<<endl;
    while(result_pos < result_length){
        unsigned char k;
        k = TreeTravel(&code_tree,result,result_pos);
        //cout<<k;
        fwrite(&k, sizeof(unsigned char), 1, file_output);
        //file_output.write(k, 1);
        if(result_pos == result_length){
            cout<<endl<<"end"<<endl;
            break;
        }
    }

    file_input.close();
    fclose(file_output);

    return 0;
}
