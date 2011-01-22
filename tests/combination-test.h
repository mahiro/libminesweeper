#ifndef _TESTS_COMBINATION_TEST_H_
#define _TESTS_COMBINATION_TEST_H_

#include <set>
#include <string>
#include <vector>

void testCombinations();

void printSet(const std::set<std::string> & s);
void printSetSet(const std::set<std::set<std::string> > & ss);
void printVector(const std::vector<std::string> & s);

bool _testCombinationsInternal(const char *filename, int lineno, const std::vector<std::string> & input, int minK, int maxK, ...);
bool _assertCombinationEquals(const char *filename, int lineno, std::set<std::set<std::string> > & expected, const std::set<std::set<std::string> > & actual);

#define testCombinationsInternal(_input, _minK, _maxK, ...) \
	_testCombinationsInternal(__FILE__, __LINE__, (_input), (_minK), (_maxK), __VA_ARGS__)

#define assertCombinationEquals(_expected, _actual) \
	_assertCombinationEquals(__FILE__, __LINE__, (_expected), (_actual))

#endif
