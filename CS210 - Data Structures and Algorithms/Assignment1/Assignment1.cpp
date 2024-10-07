// Name: Zana Osman
// Student Number: 200489300
// Date: February 6th, 2024

#include <iostream>
using namespace std;

// Given constraints to only have a max size of 10 by 10 or 100 individuals values
const int MAX_ROWS = 10;
const int MAX_COLS = 10;

// Provided from assignment notes, this is the definitions of all classes used in the class MatrixType
class MatrixType {
public:
    MatrixType();
    void SetSize(int rowSize, int colSize);
    void StoreItem(int item, int row, int col);
    void Add(MatrixType otherOperand, MatrixType& result);
    void Sub(MatrixType otherOperand, MatrixType& result);
    void Mult(MatrixType otherOperand, MatrixType& result);
    void Print();
    bool AddSubCompatible(MatrixType otherOperand);
    bool MultCompatible(MatrixType otherOperand);
private:
    int values[MAX_ROWS][MAX_COLS];
    int numRows;
    int numCols;
};

// Set both rows and columns to be zero as a standard
MatrixType::MatrixType() {
    numRows = 0;
    numCols = 0;
}

// Sets the size equal to the number of rows, columns
void MatrixType::SetSize(int rowSize, int colSize){
    numRows = rowSize;
    numCols = colSize;
}

// Stores the matrix in an item, this sets the matrix from 0 - 10
void MatrixType::StoreItem(int item, int row, int col){
    values[row][col] = item;
}

// Function to add two matrices, first checks if the two matrices are equal,
// if it is then the function will then add the two
void MatrixType::Add(MatrixType otherOperand, MatrixType& result){
    if (AddSubCompatible(otherOperand)){
        result.SetSize(numRows, numCols);
        for (int i = 0; i < numRows; ++i){
            for (int j = 0; j < numCols; ++j)
                result.values[i][j] = values[i][j] + otherOperand.values[i][j];
        }
    } else
        cout << "The operation is not compatible." << endl;
}

// This function subtracts matrix a from matrix b,
// this is only possbile if the matrix dimensions of both are exactly the same
void MatrixType::Sub(MatrixType otherOperand, MatrixType& result){
    if (AddSubCompatible(otherOperand)){
        result.SetSize(numRows, numCols);
        for (int i = 0; i < numRows; ++i){
            for (int j = 0; j < numCols; ++j)
                result.values[i][j] = values[i][j] - otherOperand.values[i][j];
        }
    } else
        cout << "The operation is not compatible." << endl;
}

// This function is responsible for multiplying the matrices,
// it checks by using elementary matrix rules to ensure
// matrix a and matrix b can be compatible to multiply
void MatrixType::Mult(MatrixType otherOperand, MatrixType& result){
    if (MultCompatible(otherOperand)){
        result.SetSize(numRows, numCols);
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < otherOperand.numCols; ++j) {
                int sum = 0;
                for (int k = 0; k < numCols; ++k) {
                    sum += values[i][k] * otherOperand.values[k][j];
                }
                result.values[i][j] = sum;
            }
        }
    } else {
        cout << "The operation is not compatible." << endl;
    }
}

// Function to print the matrices, this entire code is based on using a 2-D array approach
// as this is the simplest way to create, print and do operations for matrices
void MatrixType::Print(){
    for (int i = 0; i < numRows; ++i){
        for (int j = 0; j < numCols; ++j)
            cout << values[i][j] << " ";
    }
        cout << endl;
}

// Checks to see if the rows and colums of matrix a is equal to matrix b,
// if it is then addition and subtraction is possible
bool MatrixType::AddSubCompatible(MatrixType otherOperand){
    return numRows == otherOperand.numRows && numCols == otherOperand.numCols;
}

// Checks to see if multuplication can be done, if the columns are not equal to rows the operation is not possible
bool MatrixType::MultCompatible(MatrixType otherOperand){
    return numCols == otherOperand.numRows;
}

int main() {
    MatrixType matrices[10];
    int matrixnum = 1;

    while (true) {
        // Asks the user what operation they will do
        int operation;
        cout << "Enter operation (1: new matrix, 2: add, 3: subtract, 4: multiply, 5: print, 6: end): ";
        cin >> operation;

        // Used switch case as this was easiest to take 6 user functions
        // and split them up for different operations, like adding, subtraction, multiply
        switch (operation) {
            // This case will make a new matrix, provided it is under the 
            // limit of 10 and under the max rows and columns of 10
            case 1: {
                // 
                if (matrixnum >= 10) {
                    cout << "Maximum number of matrices reached." << endl;
                    continue;
                }
                // User will then be asked to choose the number of rows and columns
                int rows, cols;
                cout << "Enter number of rows and columns: ";
                cin >> rows >> cols;

                // Checks if the desired rows and cols is not passed the max of 10
                if (rows > MAX_ROWS || cols > MAX_COLS) {
                    cout << "Matrix size exceeds maximum dimensions." << endl;
                    continue;
                }

                // Stores matrix in indexs 0 - 10
                matrices[matrixnum].SetSize(rows, cols);

                // Takes in matrix values to store
                cout << "Enter matrix values:" << endl;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        int value;
                        cin >> value;
                        matrices[matrixnum].StoreItem(value, i, j);
                    }
                }

                // Adds a new matrix and increases max number of possible matrices
                cout << "Matrix " << matrixnum << " added." << endl;
                matrixnum++;
                break;
            }
            // Adding, subtracting and multiplication case
            case 2:
            case 3:
            case 4: {
                // Checks to see if there are two matrices, if not function will not be possible
                if (matrixnum < 2) {
                    cout << "You need at least two matrices to perform this operation." << endl;
                    continue;
                }

                // Takes matrix 1 and 2 and which matrix the user wants the result to go to
                int f1, f2, f3;
                cout << "Enter first matrix and second matrix number along with target matrix numbers ";
                cin >> f1 >> f2 >> f3;

                // If any of the two matrices or the target matrix number is above 10 and below 0,
                // it will show as invalid as this cannot exist in the range
                if (f1 < 0 || f1 >= matrixnum || f2 < 0 || f2 >= matrixnum || f3 < 0 || f3 >= matrixnum) {
                    cout << "Invalid matrix indices." << endl;
                    continue;
                }

                // Seperates the 3 functions add, subtract and multiply then does each function individually
                MatrixType resultMatrix;
                if (operation == 2) {
                    matrices[f1].Add(matrices[f2], resultMatrix);
                } else if (operation == 3) {
                    matrices[f1].Sub(matrices[f2], resultMatrix);
                } else if (operation == 4) {
                    matrices[f1].Mult(matrices[f2], resultMatrix);
                }

                // Checks to see if multiplication is compatible, if it is, 
                // it will base the result on what operation was used
                if (resultMatrix.MultCompatible(matrices[f3])) {
                    matrices[f3] = resultMatrix;
                    cout << "Matrices " << f1 << " and " << f2 << " ";
                    if (operation == 2) cout << "added";
                    if (operation == 3) cout << "subtracted";
                    if (operation == 4) cout << "multiplied";
                    cout << ", and the result is stored in matrix " << f3 << "." << endl;
                } else {
                    cout << "Matrix " << f3 << " is not compatible with the result." << endl;
                }
                break;
            }
            // Print the matrix with the Print() function
            case 5: {
                int matrixIndex;
                cout << "Enter matrix index to print: ";
                cin >> matrixIndex;

                // If a negative value or a value above the current matrix count 
                // it will print an error
                if (matrixIndex < 0 || matrixIndex >= matrixnum) {
                    cout << "Invalid matrix index." << endl;
                    continue;
                }

                // 
                cout << "Matrix " << matrixIndex << ":" << endl;
                matrices[matrixIndex].Print();
                break;
            }
            // Last case ends the program
            case 6:
                return false; 
            default:
                cout << "Invalid operation." << endl;
                break;
        }
    }

    return 0;
}