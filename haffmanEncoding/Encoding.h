//
//  Encoding.h
//  haffmanEncoding
//
//  Created by 黄美强 on 15/4/20.
//  Copyright (c) 2015年 黄 美强. All rights reserved.
//

#ifndef haffmanEncoding_Encoding_h
#define haffmanEncoding_Encoding_h

#include "haffmanStructure.h"
#include <map>
using namespace std;


class Encoding{
public:
    int Encoding_main(string input_str, string output_str,BiTree &code_tree);
};

#endif
