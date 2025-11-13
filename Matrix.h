#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;

// basically this sets limitations for the matrix class like what matrix functions/variables we can and cant use from our main
// and our maximum and default values for our matrix
class Matrix
{
private: // private functions and variables, basically stuff used only in/by our matrix class, cant use from our main
    int size;
    int *data;

    void allocateData(int newSize);
    void freeData();

public: // public functions/variables that we can use from our main
    Matrix();
    Matrix(int newSize);
    Matrix(const Matrix &other);
    Matrix &operator=(const Matrix &other);
    ~Matrix();

    int getSize() const;
    int getElement(int rowIndex, int columnIndex) const;
    void setElement(int rowIndex, int columnIndex, int value);

    static bool readTwoMatricesFromFile(const string &filename, Matrix &firstMatrix, Matrix &secondMatrix);

    Matrix operator+(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;

    int sumMainDiagonal() const;
    int sumSecondaryDiagonal() const;
    int sumCombinedDiagonals() const;

    void print(const string &title = "") const;
};

// functions not in our matrix class that we still want to use in main
Matrix swapRowsByValue(Matrix matrix, int rowIndex1 = 0, int rowIndex2 = 1);
Matrix swapColsByValue(Matrix matrix, int columnIndex1 = 0, int columnIndex2 = 1);
Matrix updateElementByValue(Matrix matrix, int rowIndex = 0, int columnIndex = 0, int newValue = 100);

#endif // end

