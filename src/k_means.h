#ifndef K_MEANS_H_
#define K_MEANS_H_
#include "matrix.h"

Matrix TrainKMeans(const Matrix* data, int k, int epochNumber, const Matrix* initialMeans);

#endif