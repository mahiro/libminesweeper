#ifndef _MINESWEEPER_CORE_FIELD_H_
#define _MINESWEEPER_CORE_FIELD_H_

#include "common.h"

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
			friend class Cell;
			friend class FieldIter;
			
			private:
				const int width, height;
				const Cell *** cells;
				mutable int number, rest, pending;
				
				const FieldIter endIter;
					// end() returns this value to test termination of iterators
				
				void constructCells();
				void destructCells();
				
			public:
				explicit Field::Field(int _width, int _height) :
						width(_width), height(_height),
						number(0), rest(0), pending(_width * _height),
						endIter(*this) {
					constructCells();
				}
				
				virtual ~Field() {
					destructCells();
				}
				
				virtual const Cell * createCell(int x, int y) const;
				
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
				void setupRandomMines(int numMines, const Cell & startCell, int dist) const;
				
				// Iterators
				FieldIter begin() const;
				const FieldIter & end() const;
				
				// Others
				void print() const;
				
		};
	}
}

#endif
