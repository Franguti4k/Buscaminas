//FRANCISCO JAVIER GUTIERREZ GALLEGO Y GINA ANDREA RAMIREZ GUERRERO
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"
//METODOS
//FUNCION PARA REVELAR LAS CELDAS
void Board::revealCell(Cell& cell) {
    if (!cell.isRevealed() && !cell.isFlagged()) {
        cell.setIsRevealed(true);
        if (cell.hasMine()) {
            isGameOver_ = true;
            revealAllMines();
            return;
        }
        if (countAdjacentMines(cell.getRow(), cell.getCol()) == 0) {
            for (int i = max(0, cell.getRow() - 1); i <= min(numRows_ - 1, cell.getRow() + 1); i++) {
                for (int j = max(0, cell.getCol() - 1); j <= min(numCols_ - 1, cell.getCol() + 1); j++) {
                    if (i != cell.getRow() || j != cell.getCol()) {
                        revealCell(cells_[i][j]);
                    }
                }
            }
        }
    }
}
//FUNCION PARA REVELAR TODAS LAS MINAS
void Board::revealAllMines() {
    for (int i = 0; i < numRows_; i++) {
        for (int j = 0; j < numCols_; j++) {
            if (cells_[i][j].hasMine()) {
                cells_[i][j].setIsRevealed(true);
            }
        }
    }
}
//FUNCION PARA PONER Y QUITAR LAS BANDERAS
void Board::flagCell(int row, int col) {
    if (!isValidCell(row, col)) {
        cout << "Celda no valida!" << endl;
        return;
    }
    Cell& cell = cells_[row][col];
    if (cell.isRevealed()) {
        cout << "No puedes poner una bandera en una celda revelada!" << endl;
        return;
    }
    cell.setIsFlagged(!cell.isFlagged());
}
//FUNCION PARA COMPROBAR SI ES UNA CELDA VALIDA
bool Board::isValidCell(int row, int col) const {
    return (row >= 0 && row < numRows_&& col >= 0 && col < numCols_);
}
//FUNCION PARA GENERARLAS MINAS ALEATORIAS EN EL TABLERO
void Board::generateMines(int numMines) {
    int count = 0;
    srand(time(NULL));
    while (count < numMines) {
        int row = rand() % numRows_;
        int col = rand() % numCols_;
        if (!cells_[row][col].hasMine()) {
            cells_[row][col].setHasMine(true);
            count++;
        }
    }
}
//FUNCION PARA CALCULAR LAS MINAS ADYACENTES DE UNA CELDA
void Board::calculateAdjacentMines() {
    for (int i = 0; i < numRows_; i++) {
        for (int j = 0; j < numCols_; j++) {
            if (!cells_[i][j].hasMine()) {
                int numAdjacentMines = countAdjacentMines(i, j);
                cells_[i][j].setValue(numAdjacentMines);
            }
        }
    }
}
//FUNCION CONTADOR DE MINAS ADYACENTES DE UNA CELDA
int Board::countAdjacentMines(int row, int col) const {
    int count = 0;
    for (int i = max(row - 1, 0); i <= min(row + 1, numRows_ - 1); i++) {
        for (int j = max(col - 1, 0); j <= min(col + 1, numCols_ - 1); j++) {
            if (cells_[i][j].hasMine()) {
                count++;
            }
        }
    }
    return count;
}
//FUNCION PARA REVELAR UNA CELDA
void Board::revealCell(int row, int col) {
    if (!isValidCell(row, col)) {
        cout << "Celda no valida!" << endl;
        return;
    }
    if (isValidCell(row, col) && !cells_[row][col].isRevealed()) {
        cells_[row][col].setIsRevealed(true);
        if (cells_[row][col].hasMine()) {
            isGameOver_ = true;
            revealAllMines();
            return;
        }
        if (countAdjacentMines(row, col) == 0) {
            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (isValidCell(i, j) && !(i == row && j == col)) {
                        revealCell(i, j);
                    }
                }
            }
        }
    }
}
//FUNCION PARA COMPROBAR SI HAS GANADO
bool Board::checkWin() const {
    for (int i = 0; i < numRows_; i++) {
        for (int j = 0; j < numCols_; j++) {
            const Cell& cell = cells_[i][j];
            if (!cell.hasMine() && !cell.isRevealed()) {
                return false;
            }
            if (cell.hasMine() && !cell.isFlagged()) {
                return false;
            }
        }
    }
    return true;
}
//FUNCION PARA IMPRIMIR LA MESA
void Board::print() const {
    // Imprime la primera fila con los números de columna
    cout << " ";
    for (int j = 0; j < numCols_; j++) {
        cout << "  " << j<<"  ";
    }
    cout << endl;
    // Imprime el resto de filas con los números de fila y el contenido de las celdas
    for (int i = 0; i < numRows_; i++) {
        cout << i;
        for (int j = 0; j < numCols_; j++) {
            const Cell& cell = cells_[i][j];
            if (!cell.isRevealed() && !cell.isFlagged()) {
                cout << "  -  ";
            }
            else if (cell.isFlagged()) {
                cout << "  F  ";
            }
            else if (cell.hasMine()) {
                cout << "  *  ";
            }
            else {
                int count = countAdjacentMines(i, j);
                if (count > 0) {
                    cout << "  " << count<<"  ";
                }
                else {
                    cout << "     ";
                }
            }
        }
        cout << endl;
    }
}
//FUNCIONES GENERALES
int menu() {
    int opc;
    cout << endl;
    cout << "\n\t -------BUSCAMINAS------";
    cout << "\n\t Bienvenido al juego! " << endl;
    cout << "\n\t 1. Modo facil (Tablero de 6 filas y 6 columnas con 5 minas)";
    cout << "\n\t 2. Modo experto (Tablero de 9 filas y 9 columnas con 10 minas)";
    cout << "\n\t 3. Modo personalizado";
    cout << "\n\t 0. Salir";
    cout << "\n\t Seleccione una opcion: ";
    cin >> opc;
    return opc;
}
Board jPersonalizado() {
    int numRows, numCols, numMines;
    //OPCION PERSONALIZADA
    cout << "Ingrese el numero de filas: ";
    cin >> numRows;
    cout << "Ingrese el numero de columnas: ";
    cin >> numCols;
    cout << "Ingrese el numero de minas: ";
    cin >> numMines;
    Board board(numRows, numCols, numMines);
    board.print();
    cout << endl;
    return board;
}
Board jFacil() {
    int const numRows = 6;
    int const numCols = 6;
    int const numMines = 5;
    Board board(numRows, numCols, numMines);
    board.print();
    cout << endl;
    return board;
}
Board jExperto() {
    int const numRows = 9;
    int const numCols = 9;
    int const numMines = 10;
    Board board(numRows, numCols, numMines);
    board.print();
    cout << endl;
    return board;
}
void juego(Board& b) {
    //JUEGO
    while (!b.isGameOver() && !b.checkWin()) {
        int row, col;
        string action;
        cout << "Ingrese la fila: ";
        cin >> row;
        cout << "Ingrese la columna: ";
        cin >> col;
        cout << "Ingrese la accion (r para revelar o f para poner/quitar bandera): ";
        cin >> action;
        if (action == "r") {
            b.revealCell(row, col);
        }
        else if (action == "f") {
            b.flagCell(row, col);
        }
        else {
            cout << "Letra incorrecta. Por favor ingrese r o f!" << endl;
        }
        cout << endl;
        b.print();
    }
    if (b.isGameOver()) {
        cout << "Has perdido! :( " << endl;
    }
    else {
        cout << "Has ganado! :) " << endl;
    }
}
