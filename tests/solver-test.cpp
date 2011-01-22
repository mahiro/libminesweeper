#include "../minesweeper.h"
#include "test.h"
#include "solver-test.h"

using namespace minesweeper::solver;

static const Result * pResult = 0;

static bool isCellInSet(const Cell & cell, const CellSet & cells) {
	return cells.find(&cell) != cells.end();
}

static int getCellResult(const Cell & cell) {
	int ret = 0;
	if (isCellInSet(cell, pResult->getInputRedCells  ())) ret |= INPUT  | RED ;
	if (isCellInSet(cell, pResult->getInputBlueCells ())) ret |= INPUT  | BLUE;
	if (isCellInSet(cell, pResult->getOutputRedCells ())) ret |= OUTPUT | RED ;
	if (isCellInSet(cell, pResult->getOutputBlueCells())) ret |= OUTPUT | BLUE;
	return ret;
}

void testSearchSingle_1() {
	SolverField field(3, 3);
	Searcher searcher(field);
	
	setFieldMatrix(field,
		-C ,  (M), -C,
		(M), (-C), -C,
		-C ,  -C , (M));
	
	assertEquals(true, searcher.searchSingle(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		 0, OR,  0,
		OR, IR,  0,
		 0,  0, OR);
}

void testSearchSingle_2() {
	SolverField field(3, 3);
	Searcher searcher(field);
	
	setFieldMatrix(field,
		(0),  M|F, (0),
		M|F, (-C), (0),
		(0),  (0), M|F);
	
	assertEquals(true, searcher.searchSingle(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		OB,  0, OB,
		 0, IB, OB,
		OB, OB,  0);
}

void testSearchDouble_1() {
	SolverField field(4, 3);
	Searcher searcher(field);
	
	setFieldMatrix(field,
		(M),   0 ,   M , (0),
		M|F, (-C), (-C), M|F,
		-C ,  -C ,  -C , -C );
	
	assertEquals(true, searcher.searchDouble(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		OR,  0,  0, OB,
		 0, IR, IB,  0,
		 0,  0,  0,  0);
}

void testSearchDouble_2() {
	SolverField field(4, 3);
	Searcher searcher(field);
	
	setFieldMatrix(field,
		(0),   M ,   0 , (M),
		(0), (-C), (-C), (M),
		(0),   0 ,   0 , (M));
	
	assertEquals(true, searcher.searchDouble(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		OB,  0,  0, OR,
		OB, IB, IR, OR,
		OB,  0,  0, OR);
}

void testSearchDouble_3() {
	SolverField field(5, 3);
	Searcher searcher(field);
	
	setFieldMatrix(field,
		-C ,  M|F, 0,  (0), (0),
		-C , (-C), M, (-C), (0),
		M|F,  -C , 0,  (0), (0));
	
	assertEquals(true, searcher.searchDouble(field.getCell(1, 1)));
	assertEquals(true, searcher.hasResult());
	
	if (!searcher.hasResult()) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		0,  0, 0, OB, OB,
		0, IR, 0, IB, OB,
		0,  0, 0, OB, OB);
}

void testSearchMultiple_Depth3_1() {
	
}

void testSearchMultiple_Depth3_2() {
	
}

void testSearchMultiple_Depth3_3() {
	
}

void testSearchMultiple_Depth4_1() {
	
}

void testSearchMultiple_Depth4_2() {
	
}

void testSearchMultiple_Depth5_1() {
	
}
