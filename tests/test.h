#ifndef _TEST_H_INCLUDED_
#define _TEST_H_INCLUDED_

#include "../minesweeper.h"

#define C minesweeper::core::Cell::COVERED
#define M minesweeper::core::Cell::MINE
#define F minesweeper::core::Cell::FLAG

int countSuccess();
int countFailure();
int getCellNumber(const minesweeper::core::Cell & cell);
int getCellRest(const minesweeper::core::Cell & cell);
int getCellCovered(const minesweeper::core::Cell & cell);
int getCellUnknown(const minesweeper::core::Cell & cell);
void setFieldMatrix(const minesweeper::core::Field & field, ...);

int _assertEquals(const char *filename, int lineno, int expected, int actual);

int _assertFieldMatrix(const char *filename, int lineno,
		const minesweeper::core::Field & field,
		int (*func)(const minesweeper::core::Cell &), ...);

#define assertFieldMatrix(_field, _func, ...) \
	_assertFieldMatrix(__FILE__, __LINE__, (_field), (_func), __VA_ARGS__)

#define assertEquals(expected, actual) \
	_assertEquals(__FILE__, __LINE__, expected, actual)

#endif
