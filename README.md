## Introduction

`libminesweeper` is a C++ library to model the classic Minesweeper game, with various interfaces to manage the state of each square (flag, mine count, etc.) and the state of the whole minefield.

A notable feature of this library is to generate a "solvable" placement of mines.
Typically, Minesweeper games distribute mines randomly, which sometimes imposes the player to have no choices but to guess the next step just because there are no more squares that can be logically determined.
This library provides a new way to enjoy the Minesweeper game logically solvable from the beginning to the end.

## Algorithm

For a given state of a minefield, it is known to be an NP-complete problem to determine the next step, either flagging or uncovering some squares.
However, if the search depth is limited, it can be solved reasonably fast.

The search depth here means the number of squares examined at the same time to find a possible set of squares, which can be either flagged or uncovered.
For example, the famous "1-2-1" pattern would not require the depth of 3, because the next step can be determined by examining only two of them (i.e. depth = 2), and then the third square can be utilized for one step further.

In fact, it hardly ever happens that a search depth of 4 or more is required for any given states.
Thus, it is usually sufficient to limit the search depth to 4.

Similarly, a backward search depth is the number of squares to determine the next step where the total number of remaining mines across the entire field is also utilized.
The backward search depth of 3 would usually be sufficient.

Once such a search algorithm is repeatedly applied, one can solve the minefield until there are no more solvable squares.
This library initially places mines randomly and attempts to solve the minefield as far as possible. Whenever the field is unsolvable, it moves some mines around the "perimeter" of solved parts and repeats the process until the entire minefield becomes solvable.

## Usage

Install `libminesweeper`:

```
autoreconf -i
./configure
make
sudo make install
```

Once the library is installed, you can use it in your program:

```
#include <minesweeper.h>
#include <iostream>
int main()
{
    auto width = 15, height = 15;
    auto x = width / 2, y = height / 2;
    auto numMines = 45;
    auto forwardDepth = 4, backwardDepth = 3;
    auto field = minesweeper::generator::GeneratorField(width, height);
    const auto& initCell = field.getCell(x, y);
    field.setupSolvable(initCell, numMines, forwardDepth, backwardDepth);
    field.resetCells();
    initCell.dig();
    std::cout << field << std::endl;
}
```

And you can link it to your program:

```
g++ -lminesweeper my-program.cpp
```

## Managing git-cloned repository

| Command          | Action                             |
| ---------------- | ---------------------------------- |
| `autoreconf -i`  | Initialize autotools configuration |
| `./configure`    | Configure Makefile                 |
| `make`           | Compile sources                    |
| `make check`     | Run tests                          |
| `make distcheck` | Package .tar.gz                    |
| `make clean`     | Clean compiled code                |
| `git clean -dfX` | Clean all .gitignore-ed files      |

## Class hierarchy

The fundamental classes are `Field` and `Cell` that model the minefield and each square, respectively.

There are three levels of inheritance hierarchy as below:

* minesweeper::core::Field (and Cell)
  * minesweeper::solver::SolverField (and SolverCell)
    * minesweeper::generator::GeneratorField (and GeneratorCell)

### namepace minesweeper::core

The `core` classes provide the most common interfaces:

```
class Field
{
  public:
    Field(int width, int height);
    const Cell & getCell(int x, int y) const;
    void setupRandom(const Cell & startCell, int numMines, int dist) const;
    int getWidth() const;
    int getHeight() const;
    int getNumber() const;
    int getRest() const;
    int getPending() const;
    virtual const Cell * createCell(int x, int y) const;
    void resetCells() const;
    void clearCells() const;
  protected:
    void constructCells();
    void destructCells();
};

class Cell
{
  public:
    Cell(const Field & field, int x, int y);
    const Field & getField() const;
    int getX() const;
    int getY() const;
    int getNumber() const;
    int getRest() const;
    bool isCovered() const;
    bool hasMine() const;
    bool hasFlag() const;
    bool hasMark() const;
    bool isUnknown() const;
    int getDist(const Cell & other) const;
    virtual bool uncover() const;
    virtual bool cover() const;
    virtual bool setMine() const;
    virtual bool unsetMine() const;
    virtual bool setFlag() const;
    virtual bool unsetFlag() const;
    virtual bool setMark() const;
    virtual bool unsetMark() const;
    virtual bool dig() const;
    virtual bool digAround() const;
    virtual void handleUpdate() const;
  protected:
    virtual void clear() const;
    virtual void reset() const;
};
```

### namepace minesweeper::solver

The `solver` classes are focused on solving the minefield (or finding a next possible step).

```
class SolverField : public Field
{
  public:
    int countUnknownCells() const;
    int countFrontierCells() const;
    const CellSet & getUnknownCells() const;
    const CellSet & getFrontierCells() const;
    void solve(const Cell & startCell, int forwardDepth, int backwardDepth, bool fast = true) const;
    void solve(int forwardDepth, int backwardDepth, bool fast = true) const;
  protected:
    virtual void clearUnknowns() const;
    virtual void handleResult(const Searcher & searcher) const;
};

class SolverCell : public Cell
{
  public:
    bool isFrontier() const;
    int countUnknowns() const;
    virtual bool setFrontier() const;
    virtual bool unsetFrontier() const;
};

class Searcher
{
  public:
    Searcher(const SolverField & field);
    bool searchForward(int depth) const;
    bool searchBackward(int depth, bool fast = true) const;
    bool searchSingle() const;
    bool searchDouble() const;
    bool searchMultiple(int depth) const;
    bool searchSingle(const Cell & targetCell) const;
    bool searchDouble(const Cell & targetCell) const;
    bool searchMultiple(const Cell & targetCell, int depth) const;
    const SolverField & getField() const;
    bool hasResult() const;
    const Result & setResultFound(bool backward) const;
    const Result & getResult() const;
    const Result * detachResult() const;
    void resetResult() const;
};
```

### namepace minesweeper::generator

The `generator` classes construct a solvable minefield.

```
class GeneratorField : public SolverField
{
  public:
    void setupSolvable(const Cell & startCell, int numMines, int maxForwardDepth, int maxBackwardDepth) const;
    void makeSolvable(const Cell & startCell, int maxForwardDepth, int maxBackwardDepth) const;
};

class GeneratorCell : public SolverCell
{
};
```
