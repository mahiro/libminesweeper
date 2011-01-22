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

static void printResult(const Field & field) {
	for (int y = 0; y < field.getHeight(); y++) {
		for (int x = 0; x < field.getWidth(); x++) {
			int ret = getCellResult(field.getCell(x, y));
			
			if (ret & INPUT) {
				if (ret & RED) {
					std::cout << "IR, ";
				} else if (ret & BLUE) {
					std::cout << "IB, ";
				}
			} else if (ret & OUTPUT) {
				if (ret & RED) {
					std::cout << "OR, ";
				} else if (ret & BLUE) {
					std::cout << "OB, ";
				}
			} else {
				std::cout << " 0, ";
			}
		}
		
		std::cout << std::endl;
	}
}

void testSearchSingle_1() {
	SolverField field(3, 3);
	
	setFieldMatrix(field,
		-C ,  (M), -C,
		(M), (-C), -C,
		-C ,  -C , (M));
	
	Searcher searcher(field);
	assertTrue(searcher.searchSingle(field.getCell(1, 1)));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		 0, OR,  0,
		OR, IR,  0,
		 0,  0, OR);
}

void testSearchSingle_2() {
	SolverField field(3, 3);
	
	setFieldMatrix(field,
		(0),  M|F, (0),
		M|F, (-C), (0),
		(0),  (0), M|F);
	
	Searcher searcher(field);
	assertTrue(searcher.searchSingle(field.getCell(1, 1)));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		OB,  0, OB,
		 0, IB, OB,
		OB, OB,  0);
}

void testSearchDouble_1() {
	SolverField field(4, 3);
	
	setFieldMatrix(field,
		(M),   0 ,   M , (0),
		M|F, (-C), (-C), M|F,
		-C ,  -C ,  -C , -C );
	
	Searcher searcher(field);
	assertTrue(searcher.searchDouble(field.getCell(1, 1)));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		OR,  0,  0, OB,
		 0, IR, IB,  0,
		 0,  0,  0,  0);
}

void testSearchDouble_2() {
	SolverField field(4, 3);
	
	setFieldMatrix(field,
		(0),   M ,   0 , (M),
		(0), (-C), (-C), (M),
		(0),   0 ,   0 , (M));
	
	Searcher searcher(field);
	assertTrue(searcher.searchDouble(field.getCell(1, 1)));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		OB,  0,  0, OR,
		OB, IB, IR, OR,
		OB,  0,  0, OR);
}

void testSearchDouble_3() {
	SolverField field(5, 3);
	
	setFieldMatrix(field,
		-C ,  M|F, 0,  (0), (0),
		-C , (-C), M, (-C), (0),
		M|F,  -C , 0,  (0), (0));
	
	Searcher searcher(field);
	assertTrue(searcher.searchDouble(field.getCell(1, 1)));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		0,  0, 0, OB, OB,
		0, IR, 0, IB, OB,
		0,  0, 0, OB, OB);
}

void testSearchMultiple_Depth3_1() {
	SolverField field(6, 4);
	
	setFieldMatrix(field,
		-C,  M|F, (M),   0 ,   0 ,  M ,
		-C, (-C),  M ,   M ,   0 , -C ,
		-C,  M|F,  0 , (-C), (-C), -C ,
		 M,   0 , (0),   0 ,   0 , (M));
	
	Searcher searcher(field);
	assertTrue(searcher.searchMultiple(field.getCell(1, 1), 3));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		0,  0, OR,  0,  0,  0,
		0, IR,  0,  0,  0,  0,
		0,  0,  0, IB, IR,  0,
		0,  0, OB,  0,  0, OR);
}

void testSearchMultiple_Depth3_2() {
	SolverField field(6, 4);
	
	setFieldMatrix(field,
		-C,  M|F, (M),   0 ,   0 ,  M ,
		-C, (-C),  M ,   M ,   0 , -C ,
		-C,  M|F,  0 , (-C), (-C), -C ,
		 M,   0 , (0),   0 ,   0 , (M));
	
	Searcher searcher(field);
	assertTrue(searcher.searchMultiple(field.getCell(3, 2), 3));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		0,  0, OR,  0,  0,  0,
		0, IR,  0,  0,  0,  0,
		0,  0,  0, IB, IR,  0,
		0,  0, OB,  0,  0, OR);
}

void testSearchMultiple_Depth3_3() {
	SolverField field(4, 4);
	
	setFieldMatrix(field,
		(0),   M ,   0 , (M),
		M|F, (-C), (-C),  0 ,
		-C ,  -C , (-C),  M ,
		M|F,  -C ,  M|F, (0));
	
	Searcher searcher(field);
	assertTrue(searcher.searchMultiple(field.getCell(1, 1), 3));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		OB,  0,  0, OR,
		 0, IB, IR,  0,
		 0,  0, IB,  0,
		 0,  0,  0, OB);
}

void testSearchMultiple_Depth4_1() {
	SolverField field(6, 6);
	
	setFieldMatrix(field,
		 0 ,  (M),  (M),  (M),   0 ,  0 ,
		 0 ,  (M), (-C),   0 ,  (0), (0),
		(0),   0 ,   0 ,   M , (-C), (0),
		(0), (-C),   M ,   0 ,   0 , (0),
		(0),  (0),   0 , (-C),  (M),  0 ,
		 0 ,   0 ,  (M),  (M),  (M),  0 );
	
	Searcher searcher(field);
	assertTrue(searcher.searchMultiple(field.getCell(2, 1), 4));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		 0, OR, OR, OR,  0,  0,
		 0, OR, IR,  0, OB, OB,
		OB,  0,  0,  0, IB, OB,
		OB, IB,  0,  0,  0, OB,
		OB, OB,  0, IR, OR,  0,
		 0,  0, OR, OR, OR,  0);
}

void testSearchMultiple_Depth4_2() {
	SolverField field(6, 6);
	
	setFieldMatrix(field,
		 0 ,   0 ,  0,  (0),  (0), (0),
		 0 ,   0 ,  0,  (0), (-C), (0),
		(0),  (0),  M,   0 ,   M , (0),
		(0), (-C),  0, (-C),  (M),  0 ,
		(0),  (0),  M,   M ,   0 , (0),
		 0 ,   0 ,  0,  (0), (-C), (0),
		 0 ,   0 ,  0,  (0),  (0), (0));
	
	Searcher searcher(field);
	assertTrue(searcher.searchMultiple(field.getCell(3, 3), 4));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		 0,   0,   0,  OB,  OB,  OB,
		 0,   0,   0,  OB,  IB,  OB,
		OB,  OB,   0,   0,   0,  OB,
		OB,  IB,   0,  IR,  OR,   0,
		OB,  OB,   0,   0,   0,  OB,
		 0,   0,   0,  OB,  IB,  OB,
		 0,   0,   0,  OB,  OB,  OB);
}

void testSearchMultiple_Depth5_1() {
	SolverField field(7, 7);
	
	setFieldMatrix(field,
		 0 ,   0 ,   0 ,  (0),  (0),  (0),  0 ,
		(0),  (0),  (0),  (0), (-C),  (0),  0 ,
		(0), (-C),   0 ,   M ,   0 ,  (0),  0 ,
		(0),  (0),   M , (-C),   M ,  (0), (0),
		 0 ,  (0),   0 ,   M ,   0 , (-C), (0),
		 0 ,  (0), (-C),  (0),  (0),  (0), (0),
		 0 ,  (0),  (0),  (0),   0 ,   0 ,  0 );
	
	Searcher searcher(field);
	assertTrue(searcher.searchMultiple(field.getCell(1, 2), 5));
	
	if (!assertTrue(searcher.hasResult())) return;
	pResult = &searcher.getResult();
	
	assertFieldMatrix(field, getCellResult,
		 0,   0,   0,  OB,  OB,  OB,   0,
		OB,  OB,  OB,  OB,  IB,  OB,   0,
		OB,  IB,   0,   0,   0,  OB,   0,
		OB,  OB,   0,  IR,   0,  OB,  OB,
		 0,  OB,   0,   0,   0,  IB,  OB,
		 0,  OB,  IB,  OB,  OB,  OB,  OB,
		 0,  OB,  OB,  OB,   0,   0,   0);
}
