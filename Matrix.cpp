#include "Matrix.h"

// Here we have our matrix functions

// this function automatically allocates data for our size because we run out of Data FAST so we'll have to use this ALOT
void Matrix::allocateData(int newSize)
{
    // store the new size first
    size = newSize; // no need to call "this" since the compiler already recognizes size

    // allocate a single  block for size*size ints
    data = new int[size * size]; // new for automatic data allocation
}

// freeData function because we run out of Data FAST so we'll have to use this ALOT too
void Matrix::freeData()
{
    if (data == 0)
    {
        return;
    }

    // free a single block, we must declare [] after delete because we initialized data = new int[size * size] for automatic data allocation
    delete [] data;
    data = 0;
    size = 0;
}

// a function to delete the last amounts of data before the program ends
Matrix::~Matrix()
{
    freeData();
}

// this function counts the digits to return for the amount of spacing that is required when printing a matrices values
static int countDigitsInt(int value)
{
    if (value == 0)
    {
        return 1;
    }

    int absoluteValue;
    if (value < 0)
    {
        absoluteValue = -value;
    }
    else
    {
        absoluteValue = value;
    }

    int digits;
    digits = 0;

    while (absoluteValue > 0)
    {
        absoluteValue = absoluteValue / 10;
        ++digits;
    }

    if (value < 0)
    {
        ++digits;
    }

    return digits;
}

// a funcation to read and set our 2 matrices from the file
bool Matrix::readTwoMatricesFromFile(const string &filename, Matrix &firstMatrix, Matrix &secondMatrix)
{
    ifstream inputFile;
    inputFile.open(filename.c_str());

    if (!inputFile)
    {
        return false;
    }

    int sizeFromFile;
    if (!(inputFile >> sizeFromFile))
    {
        inputFile.close();
        return false;
    }

    if (sizeFromFile <= 0)
    {
        inputFile.close();
        return false;
    }

    // read first matrix
    firstMatrix.freeData();
    firstMatrix.allocateData(sizeFromFile);

    for (int rowIndex = 0; rowIndex < sizeFromFile; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < sizeFromFile; ++columnIndex)
        {
            firstMatrix.data[rowIndex * sizeFromFile + columnIndex] = 0;
            inputFile >> firstMatrix.data[rowIndex * sizeFromFile + columnIndex];
        }
    }

    // read second matrix
    secondMatrix.freeData();
    secondMatrix.allocateData(sizeFromFile);

    for (int rowIndex = 0; rowIndex < sizeFromFile; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < sizeFromFile; ++columnIndex)
        {
            secondMatrix.data[rowIndex * sizeFromFile + columnIndex] = 0;
            inputFile >> secondMatrix.data[rowIndex * sizeFromFile + columnIndex];
        }
    }

    inputFile.close();
    return true;
}

// initialize empty matrix
Matrix::Matrix()
{
    size = 0;
    data = 0;
}

// initialize a matrix of a given size
Matrix::Matrix(int newSize)
{
    allocateData(newSize);

    for (int rowIndex = 0; rowIndex < size; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < size; ++columnIndex)
        {
            data[rowIndex * size + columnIndex] = 0;
        }
    }
}

// copying a matrix to another matrix
Matrix::Matrix(const Matrix &other_matrix)
{
    if (other_matrix.size == 0)
    {
        size = 0;
        data = 0;
        return;
    }

    allocateData(other_matrix.size);

    for (int rowIndex = 0; rowIndex < size; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < size; ++columnIndex)
        {
            data[rowIndex * size + columnIndex] = other_matrix.data[rowIndex * size + columnIndex];
        }
    }
}

// to return the size of a matrix
int Matrix::getSize() const
{
    return size;
}

// to get the element of a matrix from a given row and column
int Matrix::getElement(int rowIndex, int columnIndex) const
{
    return data[rowIndex * size + columnIndex];
}


// to set the element of a matrix at a given row and column
void Matrix::setElement(int rowIndex, int columnIndex, int value)
{
    data[rowIndex * size + columnIndex] = value;
}

// a function to get the first diagonal for sumCombinedDiagonals
int Matrix::sumMainDiagonal() const
{
    int sum;
    sum = 0;

    for (int index = 0; index < size; ++index)
    {
        sum = sum + data[index * size + index];
    }

    return sum;
}

// a function to get the second diagonal for ssumCombinedDiagonals
int Matrix::sumSecondaryDiagonal() const
{
    int sum;
    sum = 0;

    for (int index = 0; index < size; ++index)
    {
        sum = sum + data[index * size + (size - 1 - index)];
    }

    return sum;
}

// a function that uses the 2 combined diagonals to get the Combined Diagonals Sum
int Matrix::sumCombinedDiagonals() const
{
    int mainSum;
    mainSum = sumMainDiagonal();

    int secondarySum;
    secondarySum = sumSecondaryDiagonal();

    int combinedSum;
    combinedSum = mainSum + secondarySum;

    if (size % 2 == 1)
    {
        int centerValue;
        centerValue = data[(size / 2) * size + (size / 2)];
        combinedSum = combinedSum - centerValue;
    }

    return combinedSum;
}

// "=" operator function so we can compare matrices by ='s
Matrix &Matrix::operator=(const Matrix &other_matrix) { 
  
    if (this == &other_matrix) { 
        return *this; 
    } 
    
    freeData(); 
    
    if (other_matrix.size == 0) { 
        size = 0; 
        data = 0; 
        return *this; 
    } 
    
    allocateData(other_matrix.size); 
    
    for (int rowIndex = 0; rowIndex < size; ++rowIndex) { 
        for (int columnIndex = 0; columnIndex < size; ++columnIndex) { 
            data[rowIndex * size + columnIndex] = other_matrix.data[rowIndex * size + columnIndex]; 
        } 
    } 
    
    return *this; 
}

// "+" operator function so we can add matrices values by +'s
Matrix Matrix::operator+(const Matrix &other_matrix) const
{
    Matrix result;

    if (size != other_matrix.size)
    {
        return result;
    }

    result.allocateData(size);

    for (int rowIndex = 0; rowIndex < size; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < size; ++columnIndex)
        {
            result.data[rowIndex * size + columnIndex] =
                data[rowIndex * size + columnIndex] + other_matrix.data[rowIndex * size + columnIndex];
        }
    }

    return result;
}

// "*" operator function so we can multiply matrices values by *'s
Matrix Matrix::operator*(const Matrix &other_matrix) const
{
    Matrix result;

    if (size != other_matrix.size)
    {
        return result;
    }

    result.allocateData(size);

    for (int rowIndex = 0; rowIndex < size; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < size; ++columnIndex)
        {
            result.data[rowIndex * size + columnIndex] = 0;
        }
    }

    for (int rowIndex = 0; rowIndex < size; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < size; ++columnIndex)
        {
            int sumValue;
            sumValue = 0;

            for (int innerIndex = 0; innerIndex < size; ++innerIndex)
            {
                sumValue = sumValue + data[rowIndex * size + innerIndex] * other_matrix.data[innerIndex * size + columnIndex];
            }

            result.data[rowIndex * size + columnIndex] = sumValue;
        }
    }

    return result;
}

// a function to print the matrix
void Matrix::print(const string &title) const
{
    if (!title.empty())
    {
        cout << title << endl;
    }

    if (size == 0)
    {
        cout << "(empty matrix)" << endl;
        return;
    }

    int maxWidth;
    maxWidth = 0;

    for (int rowIndex = 0; rowIndex < size; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < size; ++columnIndex)
        {
            int digits;
            digits = countDigitsInt(data[rowIndex * size + columnIndex]);

            if (digits > maxWidth)
            {
                maxWidth = digits;
            }
        }
    }

    if (maxWidth < 1)
    {
        maxWidth = 1;
    }

    int columnWidth;
    columnWidth = maxWidth + 2;

    for (int rowIndex = 0; rowIndex < size; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < size; ++columnIndex)
        {
            int digits;
            digits = countDigitsInt(data[rowIndex * size + columnIndex]);

            int numberOfSpaces;
            numberOfSpaces = columnWidth - digits;

            for (int spaceIndex = 0; spaceIndex < numberOfSpaces; ++spaceIndex)
            {
                cout << ' ';
            }

            cout << data[rowIndex * size + columnIndex];
        }

        cout << endl;
    }

    cout << endl;
}

// a function to swap the rows of a matrix
Matrix swapRowsByValue(Matrix matrix, int rowIndex1, int rowIndex2)
{
    int matrixSize;
    matrixSize = matrix.getSize();

    if (rowIndex1 < 0 || rowIndex1 >= matrixSize || rowIndex2 < 0 || rowIndex2 >= matrixSize)
    {
        return matrix;
    }

    for (int columnIndex = 0; columnIndex < matrixSize; ++columnIndex)
    {
        int tempValue;
        tempValue = matrix.getElement(rowIndex1, columnIndex);

        matrix.setElement(rowIndex1, columnIndex, matrix.getElement(rowIndex2, columnIndex));
        matrix.setElement(rowIndex2, columnIndex, tempValue);
    }

    return matrix;
}

// a function to swap the columns of a matrix
Matrix swapColsByValue(Matrix matrix, int columnIndex1, int columnIndex2)
{
    int matrixSize;
    matrixSize = matrix.getSize();

    if (columnIndex1 < 0 || columnIndex1 >= matrixSize || columnIndex2 < 0 || columnIndex2 >= matrixSize)
    {
        return matrix;
    }

    for (int rowIndex = 0; rowIndex < matrixSize; ++rowIndex)
    {
        int tempValue;
        tempValue = matrix.getElement(rowIndex, columnIndex1);

        matrix.setElement(rowIndex, columnIndex1, matrix.getElement(rowIndex, columnIndex2));
        matrix.setElement(rowIndex, columnIndex2, tempValue);
    }

    return matrix;
}

// a function to update the value of a matrix at a given row and column
Matrix updateElementByValue(Matrix matrix, int rowIndex, int columnIndex, int newValue)
{
    int matrixSize;
    matrixSize = matrix.getSize();

    if (rowIndex < 0 || rowIndex >= matrixSize || columnIndex < 0 || columnIndex >= matrixSize)
    {
        return matrix;
    }

    matrix.setElement(rowIndex, columnIndex, newValue);

    return matrix;

}
