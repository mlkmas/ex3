//
// Created by malak on 11/06/2023.
//

#ifndef UNTITLED23_TESTUTILS_H
#define UNTITLED23_TESTUTILS_H


#include <functional>
#include <iostream>

void runTest(std::function<bool()> testFunction, std::string testName)
{
    if(!testFunction()){
        std::cout << testName <<" FAILED." << std::endl;
    }
    else {
        std::cout << testName << " SUCCEEDED." << std::endl;
    }
    std::cout << std::endl;
}

#endif //UNTITLED23_TESTUTILS_H
