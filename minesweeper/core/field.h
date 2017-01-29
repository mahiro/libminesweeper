#ifndef _MINESWEEPER_CORE_FIELD_H_
#define _MINESWEEPER_CORE_FIELD_H_

#include "common.h"
#include <iostream>

namespace minesweeper {
    namespace core {
        class FieldIter {
            friend class Field; // for private ctor access
            
            private:
                const Field & field;
                mutable const Cell * ptr;
                
                // Constructor is marked private so only Field class can access
                explicit FieldIter(const Field & f) : field(f), ptr(0) {}
                
                // Default copy constructor and assignment operator should work 
                // with the default bit-by-bit copy.
                
            public:
                const Cell * operator *() const {
                    return ptr;
                }
                
                bool operator ==(const FieldIter & other) const {
                    return ptr == other.ptr;
                }
                
                bool operator !=(const FieldIter & other) const {
                    return ptr != other.ptr;
                }
                
                const FieldIter & operator ++() const;
                const FieldIter & operator --() const;
                const FieldIter operator +(int n) const;
                const FieldIter operator -(int n) const;
                
                const FieldIter operator ++(int) const {
                    const FieldIter tmp = *this;
                    ++*this;
                    return tmp;
                }
                
                const FieldIter operator --(int) const {
                    const FieldIter tmp = *this;
                    --*this;
                    return tmp;
                }
                
        };
        
        class Field {
            friend class FieldIter;
            friend class Cell;
            
            private:
                const int width, height;
                const Cell *** cells;
                mutable int number, rest, pending;
                
                const FieldIter endIter;
                    // end() returns this value to test termination of iterators
                
            protected:
                void constructCells();
                void destructCells();
                
            public:
                explicit Field(int _width, int _height, bool _init = true) :
                        width(_width), height(_height), cells(0),
                        number(0), rest(0), pending(_width * _height),
                        endIter(*this) {
                    if (_init) {
                        constructCells();
                    }
                }
                
                virtual ~Field() {
                    destructCells();
                }
                
                virtual const Cell * createCell(int x, int y) const;
                virtual void clearCells() const;
                virtual void resetCells() const;
                
                // Getters
                const Cell & getCell(int x, int y) const {
                    return *cells[y][x];
                }
                
                int getWidth() const {
                    return width;
                }
                
                int getHeight() const {
                    return height;
                }
                
                int getNumber() const {
                    return number;
                }
                
                int getRest() const {
                    return rest;
                }
                
                int getPending() const {
                    return pending;
                }
                
                // Setters
                void setupRandom(const Cell & startCell, int numMines, int dist) const;
                
                // Iterators
                FieldIter begin() const;
                const FieldIter & end() const;
                
        };
        
        std::ostream & operator << (std::ostream & out, const Field & field);
    }
}

#endif
