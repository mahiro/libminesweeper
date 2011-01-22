#ifndef _TESTS_TEST_H_
#define _TESTS_TEST_H_

#include "../minesweeper.h"

#define C minesweeper::core::Cell::COVERED
#define M minesweeper::core::Cell::MINE
#define F minesweeper::core::Cell::FLAG

#define INPUT  0x1000
#define OUTPUT 0x2000
#define RED    0x4000
#define BLUE   0x8000

#define IR (INPUT  | RED )
#define IB (INPUT  | BLUE)
#define OR (OUTPUT | RED )
#define OB (OUTPUT | BLUE)

int countSuccess();
int countFailure();
void recordSuccess();
void recordFailure();
int getCellNumber(const minesweeper::core::Cell & cell);
int getCellRest(const minesweeper::core::Cell & cell);
int getCellCovered(const minesweeper::core::Cell & cell);
int getCellUnknown(const minesweeper::core::Cell & cell);
void setFieldMatrix(const minesweeper::core::Field & field, ...);

bool _assertEquals(const char *filename, int lineno, int expected, int actual);

bool _assertFieldMatrix(const char *filename, int lineno,
		const minesweeper::core::Field & field,
		int (*func)(const minesweeper::core::Cell &), ...);

#define assertFieldMatrix(_field, _func, ...) \
	_assertFieldMatrix(__FILE__, __LINE__, (_field), (_func), __VA_ARGS__)

#define assertEquals(_expected, _actual) \
	_assertEquals(__FILE__, __LINE__, (_expected), (_actual))

#define assertTrue(_actual) \
	_assertEquals(__FILE__, __LINE__, true, (_actual))

#define assertFalse(_actual) \
	_assertEquals(__FILE__, __LINE__, false, (_actual))

#endif
