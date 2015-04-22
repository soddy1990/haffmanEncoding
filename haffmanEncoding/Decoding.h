//
//  Decoding.h
//  haffmanEncoding
//
//  Created by 黄美强 on 15/4/20.
//  Copyright (c) 2015年 黄 美强. All rights reserved.
//

#ifndef __haffmanEncoding__Decoding__
#define __haffmanEncoding__Decoding__

#include "haffmanStructure.h"
#include <map>
using namespace std;


class Decoding{
public:
    int Decoding_main(string input_str, string output_str, BiTree &code_tree);
};


#endif /* defined(__haffmanEncoding__Decoding__) */
