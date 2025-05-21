/* ----------------------------------------------------------------<Header>-
    Name: task11.cc
    Title: A program for solving puzzles.
    
    Group: TB-43
    Student: Moisiienko A.V.
    Written: 2025-05-18
    Revised: 2025-05-21

    Description: Develop an algorithm for solving the problem and implement 
                it as a program in ANSI C++.
                Arrange a flotilla of ships on the playing field in such a way
                that the ships do not touch each other even at diagonal angles. 
                The numbers below and to the right of the playing field indicate 
                the longest sequence of black cells (occupied by ships) in the 
                corresponding row/column. The numbers above and to the left of the     
                playing field indicate the longest sequence of white cells (not 
                occupied by ships) in the corresponding row/column.
------------------------------------------------------------------</Header>-*/
    
#include <iostream>

using namespace std;

#define AREA_SIZE 9
#define SHIP_COUNT 10
#define horizontal 0
#define vertical 1
#define whiteCell 0
#define blackCell 1

int shipLengths[SHIP_COUNT]{ 1, 1, 1, 1, 2, 2, 2, 3, 3, 4 };
int combinations[SHIP_COUNT]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int shipArea[AREA_SIZE][AREA_SIZE];

int checkShip(int shipIndex);
int checkShipOrientation(int shipIndex, int orientation);
void clearShipArea();
int checkAreaCell(int row, int column);
int getCellCountByRow(int row, int cellType);
int getCellCountByColumn(int column, int cellType);
int checkWhiteCellCounts();
int checkBlackCellCounts();

int main() {
    clearShipArea();
    int choice = 0;
    while (true) {
        cout << "Menu:\n";
        cout << "1. Solve the puzzle\n";
        cout << "2. Exit the program\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            int shipIndex = 0;
            cout << "Ship number: ";
            for (int i = 0; i < SHIP_COUNT; i++) {
                cout << i << "   ";
            }
            cout << "\n";
            if (checkShip(shipIndex) > 0) {
                cout << "Result found!\n";
                cout << "     -----------\n";
                for (int r = 0; r < AREA_SIZE; r++) {
                    cout << "     |";
                    for (int c = 0; c < AREA_SIZE; c++) {
                        if (shipArea[r][c] == 1) {
                            cout << "*";
                        } else {
                            cout << " ";
                        }
                        cout << "|\n";
                    }
                    cout << "     -----------\n";
                    return 0;
                }
                cout << "Result not found!\n";
            }
        } else if (choice == 2) {
            cout << "Exiting the program...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";

        }
    }
    return 0;
}
/* ---------------------------------------------------------------------[<]-
Function: checkAreaCell
Synopsis: checks whether a part of a ship can be placed in a cell (row, column).
        Takes into account the prohibition on adjacency with other ships (including diagonally).
---------------------------------------------------------------------[>]-*/
int checkAreaCell(int row, int column) {
    if (shipArea[row][column] == 1) return 0;
    if (column > 0 && shipArea[row][column-1] == 1) return 0;
    if (column < AREA_SIZE-1 && shipArea[row][column+1] == 1) return 0;
    if (row > 0 && shipArea[row-1][column] == 1) return 0;
    if (row < AREA_SIZE-1 && shipArea[row+1][column] == 1) return 0;
    if (row > 0 && column > 0 && shipArea[row-1][column-1] == 1) return 0;
    if (row > 0 && column < AREA_SIZE-1 && shipArea[row+1][column-1] == 1) return 0;
    if (row < AREA_SIZE-1 && column > 0 && shipArea[row+1][column-1] == 1) return 0;
    if (row < AREA_SIZE-1 && column < AREA_SIZE-1 && shipArea[row+1][column+1] == 1) return 0;
    return 1;
}
/* ---------------------------------------------------------------------[<]-
Function: checkBlackCellCounts
Synopsis: checks for limits on the number of black cells in certain rows and columns.
---------------------------------------------------------------------[>]-*/
int checkBlackCellCounts() {
    if (getCellCountByRow(4, blackCell) > 2) return 0;
    if (getCellCountByRow(8, blackCell) > 2) return 0;
    if (getCellCountByColumn(2, blackCell) > 3) return 0;
    if (getCellCountByColumn(6, blackCell) > 3) return 0;
    return 1;
}
/* ---------------------------------------------------------------------[<]-
Function: checkWhiteCellCounts
Synopsis: checks the limit on the number of white cells in the specified rows and columns.
---------------------------------------------------------------------[>]-*/
int checkWhiteCellCounts() {
    if (getCellCountByRow(0, whiteCell) > 3) return 0;
    if (getCellCountByRow(1, whiteCell) > 2) return 0;
    if (getCellCountByRow(2, whiteCell) > 2) return 0;
    if (getCellCountByRow(4, whiteCell) > 3) return 0;
    if (getCellCountByRow(5, whiteCell) > 8) return 0;
    if (getCellCountByRow(6, whiteCell) > 3) return 0;
    if (getCellCountByRow(7, whiteCell) > 8) return 0;
    if (getCellCountByRow(8, whiteCell) > 6) return 0;
    if (getCellCountByColumn(0, whiteCell) > 5) return 0;
    if (getCellCountByColumn(2, whiteCell) > 3) return 0;
    if (getCellCountByColumn(3, whiteCell) > 4) return 0;
    if (getCellCountByColumn(4, whiteCell) > 6) return 0;
    if (getCellCountByColumn(5, whiteCell) > 4) return 0;
    if (getCellCountByColumn(6, whiteCell) > 3) return 0;
    if (getCellCountByColumn(7, whiteCell) > 4) return 0;
    if (getCellCountByColumn(8, whiteCell) > 4) return 0;
    return 1;
}
/* ---------------------------------------------------------------------[<]-
Function: getCellCountByRow
Synopsis: returns the maximum number of consecutive cells of a given type in a row.
---------------------------------------------------------------------[>]-*/
int getCellCountByRow(int row, int cellType) {
    int cellCount = 0;
    int maxCellCount = 0;
    for (int c = 0; c < AREA_SIZE; c++) {
        if (shipArea[row][c] == cellType) {
            cellCount++;
        } else {
            if (cellCount > maxCellCount) {
                maxCellCount = cellCount;
            } cellCount = 0;
        }
    }
    if (cellCount > maxCellCount) {
        maxCellCount = cellCount;
    }
    return maxCellCount;
}
/* ---------------------------------------------------------------------[<]-
Function: getCellCountByColumn
Synopsis: returns the maximum number of consecutive cells of a given type in a column.
---------------------------------------------------------------------[>]-*/
int getCellCountByColumn(int column, int cellType) {
    int cellCount = 0;
    int maxCellCount = 0;
    for (int r = 0; r < AREA_SIZE; r++) {
        if (shipArea[r][column] == cellType) {
            cellCount++;
        } else {
            if (cellCount > maxCellCount) {
                maxCellCount = cellCount;
            } cellCount = 0;
        }
    }
    if (cellCount > maxCellCount) {
        maxCellCount = cellCount;
    }
    return maxCellCount;
}
/* ---------------------------------------------------------------------[<]-
Function: checkShipOrientation
Synopsis: checks all possible ship placements of a given length in a given 
        orientation (horizontal/vertical).
        Recursively checks subsequent ships after successful placement.
---------------------------------------------------------------------[>]-*/
int checkShipOrientation(int shipIndex, int orientation) {
    int shipLength = shipLengths[shipIndex];
    int result = 0;
    for (int index1=0; index1 < AREA_SIZE; index1++ ) {
        for (int index2=0; index2 < (AREA_SIZE + 1); index2++) {
            int correctPlace = 1;
            for (int pos = 0; pos < shipLength; pos++) {
                if (orientation == horizontal) {
                    correctPlace = checkAreaCell(index1, index2 + pos);
                } else {
                    correctPlace = checkAreaCell(index2 + pos, index1);
                }
                if (!correctPlace) break;   
            }
            if (!correctPlace) continue;
            for (int pos = 0; pos < shipLength; pos++) {
                if (orientation == horizontal) {
                    shipArea[index1][index2 + pos] = 1;
                } else {
                    shipArea[index2 + pos][index1] = 1;
                }
            }
            combinations[shipIndex]++;
            int correctCellCounts = checkBlackCellCounts();
            if (correctCellCounts) {
                if (shipIndex < SHIP_COUNT - 1) {
                    result = checkShip(shipIndex + 1);
                    if (result > 0) return result;
                } else {
                    correctCellCounts = checkWhiteCellCounts();
                    cout << "\rCombination: ";
                    for (int i = 0; i < SHIP_COUNT; i++) {
                        cout << combinations[i] << "   ";
                    }
                    if (correctCellCounts) return 1;
                }
            }
            for (int pos = 0; pos < shipLength; pos++) {
                if (orientation == horizontal) {
                    shipArea[index1][index2 + pos] = 0;
                } else {
                    shipArea[index2 + pos][index1] = 0;
                }
            }
            
        }
    }return result;
}
/* ---------------------------------------------------------------------[<]-
Function: checkShip
Synopsis: checks possible ship placements with index shipIndex.
        Tries horizontally and (if necessary) vertically.
---------------------------------------------------------------------[>]-*/
int checkShip(int shipIndex) {
    combinations[shipIndex] = 0;
    int result = checkShipOrientation(shipIndex, horizontal);
    int shipLength = shipLengths[shipIndex];
    if (result > 0 || shipLength == 1) return result;
    result = checkShipOrientation(shipIndex, vertical);
    return result;
}
/* ---------------------------------------------------------------------[<]-
Function: clearShipArea
Synopsis: clears the playing field before starting to place ships. 
---------------------------------------------------------------------[>]-*/
void clearShipArea() {
    for (int r = 0; r < AREA_SIZE; r++) {
        for (int c = 0; c < AREA_SIZE; c++) {
            shipArea[r][c] = 0;
        }
    }
}


