#include "../minesweeper.h"
#include "test.h"

void testCells() {
	minesweeper::core::Field field(4, 4);
	
	setFieldMatrix(field,
		0, M, 0, 0,
		0, 0, M, 0,
		M, 0, 0, M,
		0, M, 0, M);
	
	assertFieldMatrix(field, getCellNumber,
		1, 1, 2, 1,
		2, 3, 2, 2,
		1, 3, 4, 2,
		2, 1, 3, 1);
	
	setFieldMatrix(field,
		0, 0, 0, 0,
		0, 0, F, 0,
		F, 0, 0, 0,
		0, 0, 0, F);
	
	assertFieldMatrix(field, getCellRest,
		1, 0, 1, 0,
		1, 1, 2, 1,
		1, 1, 2, 0,
		1, 0, 2, 1);
	
	setFieldMatrix(field,
		0,  0,  0, 0,
		0, -C,  0, 0,
		0, -C, -C, 0,
		0,  0,  0, 0);
	
	assertFieldMatrix(field, getCellUnknown,
		1, 1, 1, 1,
		1, 0, 0, 1,
		0, 0, 0, 1,
		1, 1, 1, 0);
}

void testDig() {
	minesweeper::core::Field field(5, 5);
	
	setFieldMatrix(field,
		(0),  0 ,  M ,  M ,  0 ,
		(0),  0 ,  0 ,  0 ,  M ,
		(0), (0), (0),  0 ,  0 ,
		 0 ,  0 ,  0 ,  0 ,  M ,
		 M ,  0 ,  M ,  0 ,  M );
	
	field.getCell(0, 0).dig();
	
	assertFieldMatrix(field, getCellCovered,
		(0),  0 ,  1 ,  1 ,  1 ,
		(0),  0 ,  0 ,  0 ,  1 ,
		(0), (0), (0),  0 ,  1 ,
		 0 ,  0 ,  0 ,  0 ,  1 ,
		 1 ,  1 ,  1 ,  1 ,  1 );
}

void testDigWithFlags() {
	minesweeper::core::Field field(5, 5);
	
	setFieldMatrix(field,
		(0),  0 , M|F,  M ,  0 ,
		(0),  F ,  0 ,  0 , M|F,
		(F), (0), (0),  0 ,  0 ,
		 0 ,  0 ,  0 ,  F ,  M ,
		 M ,  0 , M|F,  0 ,  M );
	
	field.getCell(0, 0).dig();
	
	assertFieldMatrix(field, getCellCovered,
		(0),  0 ,  1 ,  1 ,  1 ,
		(0),  1 ,  0 ,  0 ,  1 ,
		(1), (0), (0),  0 ,  1 ,
		 0 ,  0 ,  0 ,  1 ,  1 ,
		 1 ,  1 ,  1 ,  1 ,  1 );
}
