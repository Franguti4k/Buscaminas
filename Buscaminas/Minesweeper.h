//FRANCISCO JAVIER GUTIERREZ GALLEGO Y GINA ANDREA RAMIREZ GUERRERO
#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
//CLASE CELDA
class Cell {
private:
 int row_;
 int col_;
 bool hasMine_;
 bool isRevealed_;
 bool isFlagged_;
 int value_;
public:
 Cell(int row = 0, int col = 0, bool hasMine = false, bool isRevealed = false, bool isFlagged = false, int value = 0)
 : row_(row), col_(col), hasMine_(hasMine), isRevealed_(isRevealed), isFlagged_(isFlagged), value_(value) {}
 int getRow() const { return row_; }
 int getCol() const { return col_; }
 bool hasMine() const { return hasMine_; }
 bool isRevealed() const { return isRevealed_; }
 bool isFlagged() const { return isFlagged_; }
 int getValue() const { return value_; }
 void setHasMine(bool hasMine) { hasMine_ = hasMine; }
 void setIsRevealed(bool isRevealed) { isRevealed_ = isRevealed; }
 void setIsFlagged(bool isFlagged) { isFlagged_ = isFlagged; }
 void setValue(int value) { value_ = value; }
 friend ostream& operator<<(ostream& os, const Cell& cell) {
 os << "(" << cell.row_ << ", " << cell.col_ << ")";
 return os;
 }
};
//CLASE BOARD
class Board {
private:
 int numRows_;
 int numCols_;
 int numMines_;
 vector<vector<Cell>> cells_;
 bool isGameOver_;
 void revealCell(Cell& cell);
 void revealAllMines();
 bool isValidCell(int row, int col) const;
 void generateMines(int numMines);
 void calculateAdjacentMines();
 int countAdjacentMines(int row, int col) const;
public:
 Board() : numRows_{ 0 }, numCols_{ 0 }, numMines_{ 0 }, isGameOver_{ false } {};
 Board(int numRows, int numCols, int numMines)
 : numRows_(numRows), numCols_(numCols), numMines_(numMines), isGameOver_(false) {
 cells_ = vector<vector<Cell>>(numRows_, vector<Cell>(numCols_));
 for (int i = 0; i < numRows_; i++) {
 for (int j = 0; j < numCols_; j++) {
 cells_[i][j] = Cell(i, j);
 }
 }
 generateMines(numMines_);
 calculateAdjacentMines();
 }
 int getNumRows() const { return numRows_; }
 int getNumCols() const { return numCols_; }
 int getNumMines() const { return numMines_; }
 const vector<vector<Cell>>& getCells() const { return cells_; }
 bool isGameOver() const { return isGameOver_; }
 void revealCell(int row, int col);
 void flagCell(int row, int col);
 bool checkWin() const;
 void print() const;
};
#endif //MINESWEEPER_H
