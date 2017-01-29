#ifndef _MINESWEEPER_GENERATOR_RECORD_STATE_H_
#define _MINESWEEPER_GENERATOR_RECORD_STATE_H_

#include "common.h"

namespace minesweeper {
    namespace generator {
        using namespace minesweeper::core;
        using namespace minesweeper::solver;
        
        const int UNRECORDED = -1;
        
        class RecordState {
            private:
                mutable int number;
                
            public:
                explicit RecordState() : number(UNRECORDED) {}
                
                bool isRecorded() const {
                    return number != UNRECORDED;
                }
                
                int getNumber() const {
                    return number;
                }
                
                void record(int num) const {
                    if (num != UNRECORDED && (number == UNRECORDED || number > num)) {
                        number = num;
                    }
                }
                
                void unrecord(int num) const {
                    if (number >= num) {
                        number = UNRECORDED;
                    }
                }
                
                void clear() const {
                    number = UNRECORDED;
                }
                
        };
    }
}

#endif
