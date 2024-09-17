#ifndef SCALERS_H_
#define SCALERS_H_

#include "matrix.h"

typedef struct
{
    double* minValues;
    double* maxValues;
    int featureNum;
    int refCount;
} MinMaxScaler;

void InitializeMinMaxScaler(MinMaxScaler* minMaxScaler);
void AddReferenceToMinMaxScaler(MinMaxScaler* minMaxScaler);
void MinMaxScalerFit(MinMaxScaler* minMaxScaler, const Matrix* matrix);
Matrix MinMaxScalerTransform(const MinMaxScaler* minMaxScaler, const Matrix* matrix);
Matrix MinMaxScalerFitTransform(MinMaxScaler* minMaxScaler, const Matrix* matrix);
Matrix MinMaxScalerDetransform(const MinMaxScaler* minMaxScaler, const Matrix* matrix);
void DeleteReferenceFromMinMaxScaler(MinMaxScaler* minMaxScaler);

#endif