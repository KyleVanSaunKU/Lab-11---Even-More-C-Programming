#include "Matrix.h"

int main()
{
    cout << "EECS 348 - Lab 11: Matrix Operations" << endl;
    cout << endl;

    string filename;
    cout << "Enter input filename (example: sample1.txt):" << endl;
    getline(cin, filename); // get file name

    // initialize matrices
    Matrix matrixA;
    Matrix matrixB;
    
    if (filename.empty()) // handle if a file was givebn
    {
        cout << "No filename entered. Exiting." << endl;
        return 0;
    }

    bool read;
    read = Matrix::readTwoMatricesFromFile(filename, matrixA, matrixB); // read the matrices from the file

    if (!read) // handle if file cant be read
    {
        cout << "Failed to read matrices from file: " << filename << endl;
        return 1;
    }
    
    // print matrix sizes
    cout << "Loaded matrix A of size " << matrixA.getSize() << endl;
    cout << "Loaded matrix B of size " << matrixB.getSize() << endl;
    cout << endl;

    // print matrices
    matrixA.print("Matrix A:");
    matrixB.print("Matrix B:");

    // addition
    Matrix sumMatrix;
    sumMatrix = matrixA + matrixB;
    sumMatrix.print("A + B =");

    // multiplication
    Matrix productMatrix;
    productMatrix = matrixA * matrixB;
    productMatrix.print("A * B =");

    // diagonal sums for A
    cout << "- Calculating Matrix A's diagonal sums -" << endl;
    cout << "Main diagonal sum: " << matrixA.sumMainDiagonal() << endl;
    cout << "Secondary diagonal sum: " << matrixA.sumSecondaryDiagonal() << endl;
    cout << "Combined diagonals sum: " << matrixA.sumCombinedDiagonals() << endl;
    cout << endl;
    
    // diagonal sums for B
    cout << "- Calculating Matrix B's diagonal sums -" << endl;
    cout << "Main diagonal sum: " << matrixB.sumMainDiagonal() << endl;
    cout << "Secondary diagonal sum: " << matrixB.sumSecondaryDiagonal() << endl;
    cout << "Combined diagonals sum: " << matrixB.sumCombinedDiagonals() << endl;
    cout << endl;

    // swap rows, default row 0 and column 1
    Matrix AswappedRowsCopy;
    AswappedRowsCopy = swapRowsByValue(matrixA);
    AswappedRowsCopy.print("Matrix A with rows 0 and 1 swapped (copy):");

    // swap columns, default 0 and 1
    Matrix AswappedColsCopy;
    AswappedColsCopy = swapColsByValue(matrixA);
    AswappedColsCopy.print("Matrix A with cols 0 and 1 swapped (copy):");

    // update element at index, defaults at row 0, column 0, and value = 100
    Matrix AupdatedCopy;
    AupdatedCopy = updateElementByValue(matrixA);
    AupdatedCopy.print("Matrix A with element (0,0) updated to 100 (copy):");
    
        // swap rows, default row 0 and column 1
    Matrix BswappedRowsCopy;
    BswappedRowsCopy = swapRowsByValue(matrixB);
    BswappedRowsCopy.print("Matrix B with rows 0 and 1 swapped (copy):");

    // swap columns, default 0 and 1
    Matrix BswappedColsCopy;
    BswappedColsCopy = swapColsByValue(matrixB);
    BswappedColsCopy.print("Matrix B with cols 0 and 1 swapped (copy):");

    // update element at index, defaults at row 0, column 0, and value = 100
    Matrix BupdatedCopy;
    BupdatedCopy = updateElementByValue(matrixB);
    BupdatedCopy.print("Matrix B with element (0,0) updated to 100 (copy):");

    return 0; // end
}

