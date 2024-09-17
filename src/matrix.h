#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct
{
    double* data;
    int rowLength;
    int colLength;
    int refCount;
} Matrix;

void InitializeMatrix(Matrix* matrix, int rowLength, int columnLength);
Matrix* AddReferenceToMatrix(Matrix* matrix);
void DeleteReferenceFromMatrix(Matrix* matrix);
int GetMatrixRowLength(const Matrix* matrix);
int GetMatrixColumnLength(const Matrix* matrix);
double GetMatrixElement(const Matrix* matrix, int rowIndex, int columnIndex);
void SetMatrixElement(Matrix* matrix, int rowIndex, int columnIndex, double value);
int GetMatrixSizeInBytes(const Matrix* matrix);
void FillMatrixWithZeros(Matrix* matrix);
void CopyMatrix(Matrix* destinationMatrix, const Matrix* sourceMatrix);
void RandomizeMatrix(Matrix* matrix);
void PrintMatrix(const Matrix* matrix);

#endif