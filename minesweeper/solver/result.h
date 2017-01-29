#ifndef _MINESWEEPER_SOLVER_RESULT_H_
#define _MINESWEEPER_SOLVER_RESULT_H_

namespace minesweeper {
    namespace solver {
        using namespace minesweeper::core;
        
        class Result {
            private:
                const SolverField & field;
                const BipartiteCells input;
                const BipartiteCells output;
                const bool backward;
                
            public:
                explicit Result(const SolverField & _field, bool _backward) :
                        field(_field), backward(_backward) {}
                
                const SolverField & getField() const {
                    return field;
                }
                
                const BipartiteCells & getInput() const {
                    return input;
                }
                
                const BipartiteCells & getOutput() const {
                    return output;
                }
                
                CellSet & getInputRedCells() const {
                    return input.getRedCells();
                }
                
                CellSet & getInputBlueCells() const {
                    return input.getBlueCells();
                }
                
                CellSet & getOutputRedCells() const {
                    return output.getRedCells();
                }
                
                CellSet & getOutputBlueCells() const {
                    return output.getBlueCells();
                }
                
                bool isBackward() const {
                    return backward;
                }
                
        };
    }
}

#endif
