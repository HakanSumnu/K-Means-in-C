#include "matrix.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

struct Matrix
{
    double* data;
    int rowLength;
    int colLength;
    int refCount;
};

void InitializeMatrix(Matrix* matrix, int rowLength, int columnLength)
{
    matrix->data = malloc(sizeof(double) * rowLength * columnLength);
    matrix->rowLength = rowLength;
    matrix->colLength = columnLength;
    matrix->refCount = 1;
}

Matrix* AddReferenceToMatrix(Matrix* matrix)
{
    matrix->refCount += 1;
    return matrix;
}

void DeleteReferenceFromMatrix(Matrix* matrix)
{
    matrix->refCount -= 1;

    if (matrix->refCount == 0)
    {
        free(matrix->data);
        matrix->data = 0;
        matrix->rowLength = 0;
        matrix->colLength = 0;
    }
}

int GetMatrixRowLength(const Matrix* matrix)
{
    return matrix->rowLength;
}

int GetMatrixColumnLength(const Matrix* matrix)
{
    return matrix->colLength;
}

double GetMatrixElement(const Matrix* matrix, int rowIndex, int columnIndex)
{
    return matrix->data[rowIndex * matrix->colLength + columnIndex];
}

void SetMatrixElement(Matrix* matrix, int rowIndex, int columnIndex, double value)
{
    matrix->data[rowIndex * matrix->colLength + columnIndex] = value;
}

int GetMatrixSizeInBytes(const Matrix* matrix)
{
    return matrix->rowLength * matrix->colLength * sizeof(double) + sizeof(*matrix);
}

void FillMatrixWithZeros(Matrix* matrix)
{
    memset(matrix->data, 0, sizeof(double) * matrix->rowLength * matrix->colLength);
}

void CopyMatrix(Matrix* destinationMatrix, const Matrix* sourceMatrix)
{
    for (int row = 0; row < destinationMatrix->rowLength; ++row)
    {
        for (int col = 0; col < destinationMatrix->colLength; ++col)
        {
            destinationMatrix->data[row * destinationMatrix->colLength + col] = sourceMatrix->data[row * destinationMatrix->colLength + col];
        }
    }
}

void RandomizeMatrix(Matrix* matrix)
{
    for (int row = 0; row < matrix->rowLength; ++row)
    {
        for (int col = 0; col < matrix->colLength; ++col)
        {
            matrix->data[row * matrix->colLength + col] = (double)rand() / RAND_MAX;
        }
    }
}

void PrintMatrix(const Matrix* matrix)
{
    for (int row = 0; row < GetMatrixRowLength(matrix); ++row)
    {
        for (int col = 0; col < GetMatrixColumnLength(matrix); ++col)
        {
            printf("%lf ", matrix->data[row * matrix->colLength + col]);
        }
        printf("\n");
    }
}