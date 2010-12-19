#ifndef _MINESWEEPER_CORE_CELL_H_
#define _MINESWEEPER_CORE_CELL_H_

#include "common.h"

namespace minesweeper {
	namespace core {
		class AdjIter {
			friend class Cell; // for private ctor access
			
			private:
				const Cell & cell;
				mutable const Cell * ptr;
				mutable int x1, x2, y1, y2;
				
				// Constructors are marked private so only Cell class can access
				explicit AdjIter(const Cell & c, int dist);
				explicit AdjIter(const Cell & c); // only for endIter
				
				// Default copy constructor and assignment operator should work 
				// with the default bit-by-bit copy.
				
			public:
				const Cell * operator *() const {
					return ptr;
				}
				
				bool operator ==(const AdjIter & other) const {
					return ptr == other.ptr;
				}
				
				bool operator !=(const AdjIter & other) const {
					return ptr != other.ptr;
				}
				
				const AdjIter & operator ++() const;
				const AdjIter & operator --() const;
				const AdjIter operator +(int n) const;
				const AdjIter operator -(int n) const;
				
				const AdjIter operator ++(int) const {
					const AdjIter tmp = *this;
					++*this;
					return tmp;
				}
				
				const AdjIter operator --(int) const {
					const AdjIter tmp = *this;
					--*this;
					return tmp;
				}
				
		};
		
		class Cell {
			friend class AdjIter;
			
			private:
				const Field & field;
				const int x, y;
				mutable unsigned int state;
				mutable int number, rest;
				const AdjIter endIter;
				
			public:
				enum State {
					COVERED = 0x01,
					MINE    = 0x02,
					FLAG    = 0x04,
					MARK    = 0x08
				};
				
				explicit Cell(const Field & _field, int _x, int _y) :
					field(_field), x(_x), y(_y), state(COVERED),
					number(0), rest(0),
					endIter(*this) {}
				
				virtual ~Cell() {}
				
				// Getters
				const Field & getField() const {
					return field;
				}
				
				int getX() const {
					return x;
				}
				
				int getY() const {
					return y;
				}
				
				int getNumber() const {
					return number;
				}
				
				int getRest() const {
					return rest;
				}
				
				bool isCovered() const {
					return state & COVERED;
				}
				
				bool hasMine() const {
					return state & MINE;
				}
				
				bool hasFlag() const {
					return state & FLAG;
				}
				
				bool isUnknown() const {
					return (state & (COVERED | FLAG)) == COVERED;
				}
				
				int getDist(const Cell & other) const {
					int dx = x - other.x; if (dx < 0) dx = -dx;
					int dy = y - other.y; if (dy < 0) dy = -dy;
					return dx > dy ? dx : dy;
				}
				
				// Setters
				virtual bool uncover() const;
				virtual bool cover() const;
				virtual bool setFlag() const;
				virtual bool unsetFlag() const;
				virtual bool setMine() const;
				virtual bool unsetMine() const;
				virtual bool dig() const;
				virtual bool digAround() const;
				
				// Iterators
				AdjIter begin(int dist = 1) const;
				const AdjIter & end() const;
				
		};
	}
}

#endif
