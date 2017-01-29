#include "test.h"
#include <cstdarg>
#include <iostream>

static int success = 0;
static int failure = 0;

int countSuccess() {
    return success;
}

int countFailure() {
    return failure;
}

void recordSuccess() {
    success++;
}

void recordFailure() {
    failure++;
}

int getCellNumber(const minesweeper::core::Cell & cell) {
    return cell.getNumber();
}

int getCellRest(const minesweeper::core::Cell & cell) {
    return cell.getRest();
}

int getCellCovered(const minesweeper::core::Cell & cell) {
    return cell.isCovered();
}

int getCellUnknown(const minesweeper::core::Cell & cell) {
    return cell.isUnknown() ? 1 : 0;
}

void setFieldMatrix(const minesweeper::core::Field & field, ...) {
    va_list ap;
    int x, y;
    
    va_start(ap, field);
    
    for (y = 0; y < field.getHeight(); y++) {
        for (x = 0; x < field.getWidth(); x++) {
            int state = va_arg(ap, int);
            const minesweeper::core::Cell & cell = field.getCell(x, y);
            int value = 1;
            
            if (state < 0) {
                state = -state;
                value = 0;
            }
            
            if (value) {
                if (state & C) cell.cover();
                if (state & M) cell.setMine();
                if (state & F) cell.setFlag();
            } else {
                if (state & C) cell.uncover();
                if (state & M) cell.unsetMine();
                if (state & F) cell.unsetFlag();
            }
        }
    }
    
    va_end(ap);
}

bool _assertEquals(const char *filename, int lineno, int expected, int actual) {
    if (expected == actual) {
        recordSuccess();
        return true;
    } else {
        if (filename) {
            std::cout << std::endl
                << "FAILED: expected " << expected << " but was " << actual
                << " in assertEquals at " << filename << ":" << lineno << std::endl;
        }
        
        recordFailure();
        return false;
    }
}

bool _assertFieldMatrix(const char *filename, int lineno,
        const minesweeper::core::Field & field,
        int (*func)(const minesweeper::core::Cell &), ...) {
    va_list ap;
    int x, y;
    bool ok = true;
    
    va_start(ap, func);
    
    for (y = 0; y < field.getHeight() && ok; y++) {
        for (x = 0; x < field.getWidth() && ok; x++) {
            int expected = va_arg(ap, int);
            const minesweeper::core::Cell & cell = field.getCell(x, y);
            int actual = func(cell);
            
            if (expected != actual) {
                if (filename) {
                    std::cout << std::endl
                        << "FAILED: expected " << expected << " but was " << actual
                        << " for cell (" << x << ", " << y << ") in assertFieldMatrix"
                        << " at " << filename << ":" << lineno << std::endl;
                }
                
                ok = false;
                break;
            }
        }
    }
    
    va_end(ap);
    
    if (ok) {
        recordSuccess();
    } else {
        recordFailure();
    }
    
    return ok;
}
