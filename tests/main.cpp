#include <iostream>
#include "test.h"
#include "core-test.h"
#include "combination-test.h"
#include "solver-test.h"
#include "generator-test.h"

void printLine() {
    for (int i = 0; i < 78; i++) {
        std::cout << "=";
    }
    
    std::cout << std::endl;
}

void printTestStarts() {
    printLine();
    std::cout << "Testing..." << std::endl;
    printLine();
}

void printTestResults() {
    int s = countSuccess();
    int f = countFailure();
    
    if (f > 0) {
        std::cout << std::endl;
        printLine();
        
        std::cout << f << " of " << (f + s) << " test(s) failed "
            << "(" << (100.0f * f / (f + s)) << "%)" << std::endl;
        
        printLine();
    } else if (s > 0) {
        std::cout << std::endl;
        printLine();
        std::cout << "All tests completed successfully" << std::endl;
        printLine();
    }
}

int main() {
    printTestStarts();
    
    testCells();
    testDig();
    testDigWithFlags();
    
    testCombinations();
    
    testSearchSingle_1();
    testSearchSingle_2();
    testSearchDouble_1();
    testSearchDouble_2();
    testSearchDouble_3();
    
    testSearchMultiple_Depth3_1();
    testSearchMultiple_Depth3_2();
    testSearchMultiple_Depth3_3();
    testSearchMultiple_Depth4_1();
    testSearchMultiple_Depth4_2();
    testSearchMultiple_Depth5_1();
    
    testBackward_Depth1_1();
    testBackward_Depth1_2();
    testBackward_Depth2_1();
    testBackward_Depth2_2();
    testBackward_Depth3_1();
    
    testSolvable();
    testUnsolvable();
    
    testGenerate();
    
    printTestResults();
    return 0;
}
