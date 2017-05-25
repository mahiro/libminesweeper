#include "test.h"
#include "combination-test.h"
#include "../src/minesweeper/solver-combination.h"

#include <cstdarg>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace minesweeper::solver;
using namespace std;

#define count(ary) (sizeof(ary) / sizeof(ary[0]))

#define setupVector(_comb, _ary) {                             \
    for (size_t i = 0; i < count(_ary); i++) {                 \
        vector<string> vec(_ary[i], _ary[i] + count(_ary[i])); \
        _comb.push_back(vec);                                  \
    }                                                          \
}

void testCombinations() {
    // Input
    const char * ary[] = {"A", "B", "C", "D", "E"};
    vector<string> input(ary, ary + 5);
    
    // Comb with length = 0
    vector<string> vec0;
    vector< vector<string> > comb0;
    comb0.push_back(vec0);
    
    // Comb with length = 1
    vector< vector<string> > comb1; {
        const char * ary[][1] = {
                {"A"}, {"B"}, {"C"}, {"D"}, {"E"},
        };
        
        setupVector(comb1, ary);
    }
    
    // Comb with length = 2
    vector< vector<string> > comb2; {
        const char * ary[][2] = {
                {"A", "B"}, {"A", "C"}, {"A", "D"}, {"A", "E"},
                            {"B", "C"}, {"B", "D"}, {"B", "E"},
                                        {"C", "D"}, {"C", "E"},
                                                    {"D", "E"},
        };
        
        setupVector(comb2, ary);
    }
    
    // Comb with length = 3
    vector< vector<string> > comb3; {
        const char * ary[][3] = {
                {"A", "B", "C"}, {"A", "B", "D"}, {"A", "B", "E"},
                                 {"A", "C", "D"}, {"A", "C", "E"},
                                                  {"A", "D", "E"},
                                 {"B", "C", "D"}, {"B", "C", "E"},
                                                  {"B", "D", "E"},
                                                  {"C", "D", "E"},
        };
        
        setupVector(comb3, ary);
    }
    
    // Comb with length = 4
    vector< vector<string> > comb4; {
        const char * ary[][4] = {
                {"A", "B", "C", "D"}, {"A", "B", "C", "E"},
                                      {"A", "B", "D", "E"},
                                      {"A", "C", "D", "E"},
                                      {"B", "C", "D", "E"},
        };
        
        setupVector(comb4, ary);
    }
    
    // Comb with length = 5
    vector< vector<string> > comb5; {
        const char * ary[][5] = {
                {"A", "B", "C", "D", "E"},
        };
        
        setupVector(comb5, ary);
    }
    
    testCombinationsInternal(input, 0, 0, 1, &comb0);
    testCombinationsInternal(input, 1, 1, 1, &comb1);
    testCombinationsInternal(input, 2, 2, 1, &comb2);
    testCombinationsInternal(input, 3, 3, 1, &comb3);
    testCombinationsInternal(input, 4, 4, 1, &comb4);
    testCombinationsInternal(input, 5, 5, 1, &comb5);
    testCombinationsInternal(input, 6, 6, 0);
    
    testCombinationsInternal(input, 0, 3, 4, &comb0, &comb1, &comb2, &comb3);
    testCombinationsInternal(input, 1, 4, 4, &comb1, &comb2, &comb3, &comb4);
    testCombinationsInternal(input, 2, 5, 4, &comb2, &comb3, &comb4, &comb5);
    testCombinationsInternal(input, 3, 6, 3, &comb3, &comb4, &comb5);
    testCombinationsInternal(input, 4, 7, 2, &comb4, &comb5);
    testCombinationsInternal(input, 5, 8, 1, &comb5);
    testCombinationsInternal(input, 6, 9, 0);
}

void printSet(const set<string> & s) {
    bool first = true;
    
    cout << "{";
    
    for (set<string>::const_iterator it = s.begin(); it != s.end(); it++) {
        if (first) {
            first = false;
        } else {
            cout << ", ";
        }
        
        cout << "\"" << *it << "\"";
    }
    
    cout << "}";
}

void printSetSet(const set< set<string> > & ss) {
    bool first = true;
    
    cout << "{";
    
    for (set< set<string> >::const_iterator it = ss.begin(); it != ss.end(); it++) {
        if (first) {
            first = false;
        } else {
            cout << ", ";
        }
        
        printSet(*it);
    }
    
    cout << "}";
}

void printVector(const vector<string> & s) {
    bool first = true;
    
    cout << "[";
    
    for (vector<string>::const_iterator it = s.begin(); it != s.end(); it++) {
        if (first) {
            first = false;
        } else {
            cout << ", ";
        }
        
        cout << "\"" << *it << "\"";
    }
    
    cout << "]";
}

bool _assertCombinationEquals(const char *filename, int lineno,
        set< set<string> > & expected, const set< set<string> > & actual) {
    bool ok = true;
    
    if (expected.size() == actual.size()) {
        for (set< set<string> >::iterator it = expected.begin(); it != expected.end(); it++) {
            if (actual.find(*it) == actual.end()) {
                ok = false;
                break;
            }
        }
    } else {
        ok = false;
    }
    
    if (ok) {
        recordSuccess();
    } else {
        if (filename) {
            std::cout << "FAILED: expected:" << std::endl;
            printSetSet(expected);
            std::cout << std::endl;
            std::cout << "but was:" << std::endl;
            printSetSet(actual);
            std::cout << std::endl;
            std::cout << "at " << filename << ":" << lineno << std::endl;
        }
        
        recordFailure();
    }
    
    return ok;
}

bool _testCombinationsInternal(const char *filename, int lineno,
        const vector<string> & input, int minK, int maxK, int numArgs, ...) {
    // Make expected set
    set<set<string> > expectedSet;
    
    va_list ap;
    va_start(ap, numArgs);
    
    for (int i = 0; i < numArgs; i++) {
        vector<vector<string> > * psubsets = va_arg(ap, vector< vector<string> > *);
        
        for (vector< vector<string> >::iterator it = psubsets->begin();
                it != psubsets->end(); it++) {
            vector<string> subset = *it;
            set<string> expected(subset.begin(), subset.end());
            expectedSet.insert(expected);
        }
    }
    
    va_end(ap);
    
    // Make actual set
    set<string> inputSet(input.begin(), input.end());
    
    set< set<string> > actualSet;
    size_t prev = 0;
    
    for (CombinationGenerator<string> cg(inputSet, minK, maxK); cg.hasNext();) {
        set<string> subset(cg.next());
        assertTrue(actualSet.find(subset) == actualSet.end()); // assert no duplicates
        assertTrue(prev <= subset.size()); // assert non-decreasing
        actualSet.insert(subset);
        prev = subset.size();
    }
    
    return _assertCombinationEquals(filename, lineno, expectedSet, actualSet);
}
