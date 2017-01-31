#include "cell.h"
#include "field.h"
#include <queue>

namespace minesweeper {
    namespace core {
        /**********************************************************************
         * Cell
         **********************************************************************/
        bool Cell::uncover() const {
            if (!isCovered() || hasFlag()) {
                return false;
            }
            
            state &= ~COVERED;
            
            if (!hasMine()) {
                field.pending--;
            }
            
            handleUpdate();
            return true;
        }
        
        bool Cell::cover() const {
            if (isCovered() || hasFlag()) {
                return false;
            }
            
            state |= COVERED;
            
            if (!hasMine()) {
                field.pending++;
            }
            
            handleUpdate();
            return true;
        }
        
        bool Cell::setMine() const {
            if (hasMine()) {
                return false;
            }
            
            state |= MINE;
            field.number++;
            field.rest++;
            
            if (isCovered()) {
                field.pending--;
            }
            
            for (AdjIter adj = begin(); adj != end(); adj++) {
                (*adj)->number++;
                (*adj)->rest++;
            }
            
            handleUpdate();
            return true;
        }
        
        bool Cell::unsetMine() const {
            if (!hasMine()) {
                return false;
            }
            
            state &= ~MINE;
            field.number--;
            field.rest--;
            
            if (isCovered()) {
                field.pending++;
            }
            
            for (AdjIter adj = begin(); adj != end(); adj++) {
                (*adj)->number--;
                (*adj)->rest--;
            }
            
            handleUpdate();
            return true;
        }
        
        bool Cell::setFlag() const {
            if (hasFlag() || !isCovered()) {
                return false;
            }
            
            state |= FLAG;
            field.rest--;
            
            for (AdjIter adj = begin(); adj != end(); adj++) {
                (*adj)->rest--;
            }
            
            handleUpdate();
            return true;
        }
        
        bool Cell::unsetFlag() const {
            if (!hasFlag() || !isCovered()) {
                return false;
            }
            
            state &= ~FLAG;
            field.rest++;
            
            for (AdjIter adj = begin(); adj != end(); adj++) {
                (*adj)->rest++;
            }
            
            handleUpdate();
            return true;
        }
        
        bool Cell::setMark() const {
            if (hasMark()) {
                return false;
            }
            
            state |= MARK;
            
            handleUpdate();
            return true;
        }
        
        bool Cell::unsetMark() const {
            if (!hasMark()) {
                return false;
            }
            
            state &= ~MARK;
            
            handleUpdate();
            return true;
        }
        
        bool Cell::dig() const {
            bool ret = false;
            
            if (!hasFlag() && uncover()) {
                ret = true;
                
                if (number == 0 && !hasMine()) {
                    std::queue<const Cell *> q;
                    q.push(this);
                    
                    for (const Cell * ptr = q.front(); !q.empty(); ptr = q.front()) {
                        q.pop();
                        
                        for (AdjIter adj = ptr->begin(); adj != ptr->end(); adj++) {
                            if (!(*adj)->hasFlag() && (*adj)->uncover()) {
                                if ((*adj)->number == 0 && !(*adj)->hasMine()) {
                                    q.push(*adj);
                                }
                            }
                        }
                    }
                }
            }
            
            return ret;
        }
        
        bool Cell::digAround() const {
            bool ret = false;
            
            if (rest == 0) {
                for (AdjIter adj = begin(); adj != end(); adj++) {
                    if ((*adj)->dig()) {
                        ret = true;
                    }
                }
            }
            
            return ret;
        }
        
        AdjIter Cell::begin(int dist) const {
            return ++AdjIter(*this, dist);
        }
        
        const AdjIter & Cell::end() const {
            return endIter;
        }
        
        /**********************************************************************
         * AdjIter
         **********************************************************************/
        AdjIter::AdjIter(const Cell & c, int dist) : cell(c), ptr(&c) {
            int xmax = c.getField().getWidth() - 1;
            int ymax = c.getField().getHeight() - 1;
            
            x1 = (c.x > dist ? c.x - dist : 0);
            x2 = (c.x < xmax - dist ? c.x + dist : xmax);
            y1 = (c.y > dist ? c.y - dist : 0);
            y2 = (c.y < ymax - dist ? c.y + dist : ymax);
        }
        
        // Only needed for endIter
        AdjIter::AdjIter(const Cell & c) : cell(c), ptr(&c),
                x1(c.x), x2(c.x), y1(c.y), y2(c.y) {}
        
        const AdjIter & AdjIter::operator ++() const {
            if (ptr == &cell) {
                ptr = &cell.getField().getCell(x1, y1);
                
                if (ptr != &cell) {
                    return *this;
                }
            }
            
            int x = ptr->x;
            int y = ptr->y;
            
            do {
                if (++x > x2) {
                    x = x1;
                    
                    if (++y > y2) {
                        ptr = &cell;
                        return *this;
                    }
                }
                
                ptr = &cell.getField().getCell(x, y);
                
            } while (ptr == &cell);
            
            return *this;
        }
        
        const AdjIter & AdjIter::operator --() const {
            if (ptr == &cell) {
                ptr = &cell.getField().getCell(x2, y2);
                
                if (ptr != &cell) {
                    return *this;
                }
            }
            
            int x = ptr->x;
            int y = ptr->y;
            
            do {
                if (--x < x1) {
                    x = x2;
                    
                    if (--y < y1) {
                        ptr = &cell;
                        return *this;
                    }
                }
                
                ptr = &cell.getField().getCell(x, y);
                
            } while (ptr == &cell);
            
            return *this;
        }
        
        const AdjIter AdjIter::operator +(int n) const {
            if (n < 0) {
                return *this - (-n);
            }
            
            const AdjIter tmp = *this;
            
            while (n--) {
                ++tmp;
            }
            
            return tmp;
        }
        
        const AdjIter AdjIter::operator -(int n) const {
            if (n < 0) {
                return *this + (-n);
            }
            
            const AdjIter tmp = *this;
            
            while (n--) {
                --tmp;
            }
            
            return tmp;
        }
    }
}
