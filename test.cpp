//
// Created by admin on 19.05.2019.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "haffman.h"

using testing::Eq;
namespace {
    class ClassDeclaration:public testing::Test{
    public:
        haf_Tree tree;
        ClassDeclaration(){
            tree;
        }
    };
}

TEST_F(ClassDeclaration, nameOfTheTest1){
    char strInput[7]={'a','a','a','b','b','c','\0'};
    char * input=strInput;
    char strOutput[10]={'0','0','0','1','1','1','1','1','0','\0'};
    char * out;
    out= tree.makeTree (input, 6);
    bool ok=true;
    for (int i=0;out[i]!='\0';i++)
        if (out[i]!=strOutput[i])
            ok=false;
    if (ok)
        SUCCEED();
    else
        FAIL();
}
TEST_F(ClassDeclaration, nameOfTheTest2){
    char strInput='\0';
    char * input=&strInput;
    char strOutput='\0';
    char * out;
    out= tree.makeTree (input, 0);

    if (strOutput==out[0])
        SUCCEED();
    else
        FAIL();
}
