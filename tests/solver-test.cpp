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
    
    setFieldMatrix(field,
         U , (M),  U,
        (M), (U),  U,
         U ,  U , (M));
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchSingle(field.getCell(1, 1)))) return;
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
        (0), M|F, (0),
        M|F, (U), (0),
        (0), (0), M|F);
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchSingle(field.getCell(1, 1)))) return;
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
        (M),  0 ,  M , (0),
        M|F, (U), (U), M|F,
         U ,  U ,  U ,  U );
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchDouble(field.getCell(1, 1)))) return;
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
        (0),  M ,  0 , (M),
        (0), (U), (U), (M),
        (0),  0 ,  0 , (M));
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchDouble(field.getCell(1, 1)))) return;
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
        U , M|F, 0 , (0), (0),
        U , (U), M , (U), (0),
        U , M|F, 0 , (0), (0));
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchDouble(field.getCell(1, 1)))) return;
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
        U , M|F, (M),  0 ,  0 ,  M ,
        U , (U),  M ,  M ,  0 ,  U ,
        U , M|F,  0 , (U), (U),  U ,
        M ,  0 , (0),  0 ,  0 , (M));
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchMultiple(field.getCell(1, 1), 3))) return;
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
        U , M|F, (M),  0 ,  0 ,  M ,
        U , (U),  M ,  M ,  0 ,  U ,
        U , M|F,  0 , (U), (U),  U ,
        M ,  0 , (0),  0 ,  0 , (M));
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchMultiple(field.getCell(3, 2), 3))) return;
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
        (0),  M ,  0 , (M),
        M|F, (U), (U),  0 ,
         U ,  U , (U),  M ,
        M|F,  U , M|F, (0));
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchMultiple(field.getCell(1, 1), 3))) return;
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
         0 , (M), (M),  (M),  0 ,  0 ,
         0 , (M), (U),   0 , (0), (0),
        (0),  0 ,  0 ,   M , (U), (0),
        (0), (U),  M ,   0 ,  0 , (0),
        (0), (0),  0 , ( U), (M),  0 ,
         0 ,  0 , (M),  (M), (M),  0 );
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchMultiple(field.getCell(2, 1), 4))) return;
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
         0 ,  0 ,  0, (0), (0), (0),
         0 ,  0 ,  0, (0), (U), (0),
        (0), (0),  M,  0 ,  M , (0),
        (0), (U),  0, (U), (M),  0 ,
        (0), (0),  M,  M ,  0 , (0),
         0 ,  0 ,  0, (0), (U), (0),
         0 ,  0 ,  0, (0), (0), (0));
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchMultiple(field.getCell(3, 3), 4))) return;
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
         0 ,  0 ,  0 , (0), (0), (0),  0 ,
        (0), (0), (0), (0), (U), (0),  0 ,
        (0), (U),  0 ,  M ,  0 , (0),  0 ,
        (0), (0),  M , (U),  M , (0), (0),
         0 , (0),  0 ,  M ,  0 , (U), (0),
         0 , (0), (U), (0), (0), (0), (0),
         0 , (0), (0), (0),  0 ,  0 ,  0 );
    
    Searcher searcher(field);
    if (!assertTrue(searcher.searchMultiple(field.getCell(1, 2), 5))) return;
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

void testBackward_Depth1_1() {
    for (int i = 0; i < 2; i++) {
        SolverField field(4, 4);
        
        setFieldMatrix(field,
             U , M|F,  0 , (0),
            M|F, (U),  M , (0),
             0 ,  M ,  0 , (0),
            (0), (0), (0), (0));
        
        Searcher searcher(field);
        bool fast = (i == 0);
        if (!assertTrue(searcher.searchBackward(1, fast))) return;
        if (!assertTrue(searcher.hasResult())) return;
        pResult = &searcher.getResult();
        
        assertFieldMatrix(field, getCellResult,
             0,  0,  0, OB,
             0, IR,  0, OB,
             0,  0,  0, OB,
            OB, OB, OB, OB);
    }
}

void testBackward_Depth1_2() {
    for (int i = 0; i < 2; i++) {
        SolverField field(4, 4);
        
        setFieldMatrix(field,
             U , M|F,  0 , (M),
            M|F, (U),  M , (M),
             0 ,  M ,  0 , (M),
            (M), (M), (M), (M));
        
        Searcher searcher(field);
        bool fast = (i == 0);
        if (!assertTrue(searcher.searchBackward(1, fast))) continue;
        if (!assertTrue(searcher.hasResult())) continue;
        pResult = &searcher.getResult();
        
        assertFieldMatrix(field, getCellResult,
             0,  0,  0, OR,
             0, IB,  0, OR,
             0,  0,  0, OR,
            OR, OR, OR, OR);
    }
}

void testBackward_Depth2_1() {
    for (int i = 0; i < 2; i++) {
        SolverField field(4, 4);
        
        setFieldMatrix(field,
             M|F,  (U),  0 , (0),
             (U),   M ,  M , (0),
              0 ,   M , (0), (0),
             (0),  (0), (0), (0));
        
        Searcher searcher(field);
        bool fast = (i == 0);
        if (!assertTrue(searcher.searchBackward(2, fast))) continue;
        if (!assertTrue(searcher.hasResult())) continue;
        pResult = &searcher.getResult();
        
        assertFieldMatrix(field, getCellResult,
             0, IR,  0, OB,
            IR, OR,  0, OB,
             0,  0, OB, OB,
            OB, OB, OB, OB);
    }
}

void testBackward_Depth2_2() {
    for (int i = 0; i < 2; i++) {
        SolverField field(4, 4);
        
        setFieldMatrix(field,
            M|F, (U),  0 , (M),
            (U), (0),  M , (M),
             0 ,  M , (M), (M),
            (M), (M), (M), (M));
        
        Searcher searcher(field);
        bool fast = (i == 0);
        if (!assertTrue(searcher.searchBackward(2, fast))) continue;
        if (!assertTrue(searcher.hasResult())) continue;
        pResult = &searcher.getResult();
        
        assertFieldMatrix(field, getCellResult,
             0, IB,  0, OR,
            IB, OB,  0, OR,
             0,  0, OR, OR,
            OR, OR, OR, OR);
    }
}

void testBackward_Depth3_1() {
    SolverField field(5, 4);
    
    setFieldMatrix(field,
        (0), (0),  0 ,  M ,  0 ,
         0 ,  M ,  0 , (U), (0),
         0 , (U),  M , (U), (0),
         0 ,  0 , (0), (0), (0));
    
    Searcher searcher(field);
    bool fast = false; // Fast mode doesn't work with red-blue-mixed backward search
    if (!assertTrue(searcher.searchBackward(3, fast))) return;
    if (!assertTrue(searcher.hasResult())) return;
    pResult = &searcher.getResult();
    
    assertFieldMatrix(field, getCellResult,
         OB,  OB,   0,   0,   0,
          0,   0,   0,  IR,  OB,
          0,  IR,   0,  IB,  OB,
          0,   0,  OB,  OB,  OB);
}

void testSolvable() {
    SolverField field(9, 9);
    
    setFieldMatrix(field,
        0 ,  M ,  0 ,  M ,  0 ,  M ,  0 ,  0 ,  M ,
        0 ,  0 ,  M ,  0 ,  0 ,  0 ,  M ,  M ,  M ,
        0 ,  0 ,  M ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,
        M ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  M ,  0 ,
        0 ,  0 ,  0 ,  0 , (0),  0 ,  M ,  0 ,  M ,
        0 ,  M ,  0 ,  0 ,  0 ,  0 ,  0 ,  M ,  M ,
        0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,
        0 ,  M ,  0 ,  M ,  0 ,  0 ,  0 ,  M ,  0 ,
        M ,  M ,  0 ,  M ,  M ,  M ,  0 ,  0 ,  0 );
    
    field.solve(field.getCell(4, 4), 4, 4);
    
    assertEquals(0, field.getPending());
    assertEquals(0, field.countUnknownCells());
}

void testUnsolvable() {
    SolverField field(9, 9);
    
    setFieldMatrix(field,
        0 ,  M ,  0 ,  M ,  0 ,  0 ,  M , (0), (M),
        0 ,  0 ,  M ,  0 ,  0 ,  M ,  M ,  0 ,  M ,
        0 ,  0 ,  0 ,  M ,  0 ,  0 ,  0 ,  0 ,  M ,
        M ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,
        0 ,  0 ,  0 ,  0 , (0),  0 ,  M ,  0 ,  M ,
        0 ,  M ,  0 ,  0 ,  0 ,  0 ,  0 ,  M ,  0 ,
        0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  M ,  0 ,  0 ,
        0 ,  M ,  0 ,  M ,  M ,  0 ,  0 ,  0 ,  M ,
        M ,  M , (0), (M),  M ,  0 ,  0 ,  0 ,  0 );
    
    field.solve(field.getCell(4, 4), 4, 4);
    
    assertEquals(2, field.getPending());
    assertEquals(4, field.countUnknownCells());
}
