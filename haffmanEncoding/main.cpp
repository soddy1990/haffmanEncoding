//  main.cpp
//  haffmanEncoding
//
//  Created by 黄美强 on 15/4/22.
//  Created by 黄美强 on 15/4/20.
//  Copyright (c) 2015年 黄 美强. All rights reserved.
//

#include <iostream>
#include "Encoding.h"
#include "Decoding.h"
#include <map>
using namespace std;

int main(int argc, const char * argv[]) {
    Encoding *e = new Encoding();

    string input_doc = "Make Payment 2015 spring.pdf";
    string output_temp_doc = "test.huff";
    string output_doc = "test_decoded.pdf";
    BiTree *code_tree = new BiTree();
    e->Encoding_main(input_doc,output_temp_doc, *code_tree);

    Decoding *d = new Decoding();
    d->Decoding_main(output_temp_doc, output_doc, *code_tree);
}
