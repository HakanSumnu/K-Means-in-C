#include "scalers.h"
#include <stdlib.h>
#include <math.h>

struct MinMaxScaler
{
    double* minValues;
    double* maxValues;
    int featureNum;
    int refCount;
};

void InitializeMinMaxScaler(MinMaxScaler* minMaxScaler)
{
    minMaxScaler->minValues = 0;
    minMaxScaler->maxValues = 0;
    minMaxScaler->featureNum = 0;
    minMaxScaler->refCount = 1;
}

void AddReferenceToMinMaxScaler(MinMaxScaler* minMaxScaler)
{
    minMaxScaler->refCount += 1;
}

void MinMaxScalerFit(MinMaxScaler* minMaxScaler, const Matrix* matrix)
{
    if (minMaxScaler->featureNum != GetMatrixColumnLength(matrix))
    {
        free(minMaxScaler->minValues);
        free(minMaxScaler->maxValues);
        minMaxScaler->minValues = malloc(sizeof(double) * GetMatrixColumnLength(matrix));
        minMaxScaler->maxValues = malloc(sizeof(double) * GetMatrixColumnLength(matrix));
        minMaxScaler->featureNum = GetMatrixColumnLength(matrix);
    }

    for (int col = 0; col < GetMatrixColumnLength(matrix); ++col)
        minMaxScaler->minValues[col] = INFINITY;

    for (int col = 0; col < GetMatrixColumnLength(matrix); ++col)
        minMaxScaler->maxValues[col] = -INFINITY;

    for (int row = 0; row < GetMatrixRowLength(matrix); ++row)
    {
        for (int col = 0; col < GetMatrixColumnLength(matrix); ++col)
        {
            if (minMaxScaler->minValues[col] > GetMatrixElement(matrix, row, col))
            {
                minMaxScaler->minValues[col] = GetMatrixElement(matrix, row, col);
            }

            if (minMaxScaler->maxValues[col] < GetMatrixElement(matrix, row, col))
            {
                minMaxScaler->maxValues[col] = GetMatrixElement(matrix, row, col);
            }
        }
    }
}

Matrix MinMaxScalerTransform(const MinMaxScaler* minMaxScaler, const Matrix* matrix)
{
    Matrix newMatrix;
    InitializeMatrix(&newMatrix, GetMatrixRowLength(matrix), GetMatrixColumnLength(matrix));

    for (int row = 0; row < GetMatrixRowLength(matrix); ++row)
    {
        for (int col = 0; col < GetMatrixColumnLength(matrix); ++col)
        {
            SetMatrixElement(&newMatrix, row, col, (GetMatrixElement(matrix, row, col) - minMaxScaler->minValues[col]) / (minMaxScaler->maxValues[col] - minMaxScaler->minValues[col]));
        }
    }

    return newMatrix;
}

Matrix MinMaxScalerFitTransform(MinMaxScaler* minMaxScaler, const Matrix* matrix)
{
    MinMaxScalerFit(minMaxScaler, matrix);
    return MinMaxScalerTransform(minMaxScaler, matrix);
}

Matrix MinMaxScalerDetransform(const MinMaxScaler* minMaxScaler, const Matrix* matrix)
{
    Matrix newMatrix;
    InitializeMatrix(&newMatrix, GetMatrixRowLength(matrix), GetMatrixColumnLength(matrix));

    for (int row = 0; row < GetMatrixRowLength(matrix); ++row)
    {
        for (int col = 0; col < GetMatrixColumnLength(matrix); ++col)
        {
            SetMatrixElement(&newMatrix, row, col, GetMatrixElement(matrix, row, col) * (minMaxScaler->maxValues[col] - minMaxScaler->minValues[col]) + minMaxScaler->minValues[col]);
        }
    }

    return newMatrix;
}

void DeleteReferenceFromMinMaxScaler(MinMaxScaler* minMaxScaler)
{
    minMaxScaler->refCount -= 1;

    if (minMaxScaler->refCount == 0)
    {
        free(minMaxScaler->minValues);
        minMaxScaler->minValues = 0;
        free(minMaxScaler->maxValues);
        minMaxScaler->maxValues = 0;
        minMaxScaler->featureNum = 0;
    }
}