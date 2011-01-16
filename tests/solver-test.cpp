#include "../minesweeper.h"
#include "test.h"
#include "solver-test.h"

using namespace minesweeper::solver;

static Searcher * pSearcher = 0;

static bool isCellInSet(const Cell & cell, const CellSet & cells) {
	return cells.find(&cell) != cells.end();
}

static int getCellResult(const Cell & cell) {
	int ret = 0;
	if (isCellInSet(cell, pSearcher->getInputRedCells  ())) ret |= INPUT  | RED ;
	if (isCellInSet(cell, pSearcher->getInputBlueCells ())) ret |= INPUT  | BLUE;
	if (isCellInSet(cell, pSearcher->getOutputRedCells ())) ret |= OUTPUT | RED ;
	if (isCellInSet(cell, pSearcher->getOutputBlueCells())) ret |= OUTPUT | BLUE;
	return ret;
}

void testSearchBySinglePoint_1() {
	SolverField field(3, 3);
	Searcher searcher(field);
	pSearcher = &searcher;
	
	setFieldMatrix(field,
		-C ,  (M), -C,
		(M), (-C), -C,
		-C ,  -C , (M));
	
	assertEquals(true, searcher.searchSingle(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	
	assertFieldMatrix(field, getCellResult,
		 0, OR,  0,
		OR, IR,  0,
		 0,  0, OR);
}

void testSearchBySinglePoint_2() {
	SolverField field(3, 3);
	Searcher searcher(field);
	pSearcher = &searcher;
	
	setFieldMatrix(field,
		(0),  M|F, (0),
		M|F, (-C), (0),
		(0),  (0), M|F);
	
	assertEquals(true, searcher.searchSingle(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	
	assertFieldMatrix(field, getCellResult,
		OB,  0, OB,
		 0, IB, OB,
		OB, OB,  0);
}

void testSearchByDoublePoints_1() {
	SolverField field(4, 3);
	Searcher searcher(field);
	pSearcher = &searcher;
	
	setFieldMatrix(field,
		(M),   0 ,   M , (0),
		M|F, (-C), (-C), M|F,
		-C ,  -C ,  -C , -C );
	
	assertEquals(true, searcher.searchDouble(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	
	assertFieldMatrix(field, getCellResult,
		OR,  0,  0, OB,
		 0, IR, IB,  0,
		 0,  0,  0,  0);
}

void testSearchByDoublePoints_2() {
	SolverField field(4, 3);
	Searcher searcher(field);
	pSearcher = &searcher;
	
	setFieldMatrix(field,
		(0),   M ,   0 , (M),
		(0), (-C), (-C), (M),
		(0),   0 ,   0 , (M));
	
	assertEquals(true, searcher.searchDouble(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	
	assertFieldMatrix(field, getCellResult,
		OB,  0,  0, OR,
		OB, IB, IR, OR,
		OB,  0,  0, OR);
}

void testSearchByDoublePoints_3() {
	SolverField field(5, 3);
	Searcher searcher(field);
	pSearcher = &searcher;
	
	setFieldMatrix(field,
		-C ,  M|F, 0,  (0), (0),
		-C , (-C), M, (-C), (0),
		M|F,  -C , 0,  (0), (0));
	
	assertEquals(true, searcher.searchDouble(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	
	assertFieldMatrix(field, getCellResult,
		0,  0, 0, OB, OB,
		0, IR, 0, IB, OB,
		0,  0, 0, OB, OB);
}
