#include "k_means.h"
#include <stdlib.h>
#include <math.h>
#include <memory.h>

void IterationKMeans(const Matrix* data, Matrix* means, int* groups, int* groupCounts)
{
    memset(groupCounts, 0, sizeof(int) * GetMatrixRowLength(means));

    for (int dataIndex = 0; dataIndex < GetMatrixRowLength(data); ++dataIndex)
    {
        double minLength = INFINITY;
        for (int groupIndex = 0; groupIndex < GetMatrixRowLength(means); ++groupIndex)
        {
            double length = 0;
            for (int elementIndex = 0; elementIndex < GetMatrixColumnLength(data); ++elementIndex)
            {
                length += (GetMatrixElement(data, dataIndex, elementIndex) - GetMatrixElement(means, groupIndex, elementIndex)) * (GetMatrixElement(data, dataIndex, elementIndex) - GetMatrixElement(means, groupIndex, elementIndex));
            }

            if (length < minLength)
            {
                minLength = length;
                groups[dataIndex] = groupIndex;
            }
        }

        groupCounts[groups[dataIndex]] += 1;
    }

    FillMatrixWithZeros(means);

    for (int dataIndex = 0; dataIndex < GetMatrixRowLength(data); ++dataIndex)
        for (int elementIndex = 0; elementIndex < GetMatrixColumnLength(data); ++elementIndex)
            SetMatrixElement(means, groups[dataIndex], elementIndex, GetMatrixElement(means, groups[dataIndex], elementIndex) + GetMatrixElement(data, dataIndex, elementIndex) / groupCounts[groups[dataIndex]]);
}

Matrix TrainKMeans(const Matrix* data, int k, int epochNumber, const Matrix* initialMeans)
{
    int* groups = malloc(sizeof(int) * GetMatrixRowLength(data));
    int* groupCounts = malloc(sizeof(int) * k);

    Matrix newMeans;
    InitializeMatrix(&newMeans, k, GetMatrixColumnLength(data));
    if (initialMeans != 0)
    {
        CopyMatrix(&newMeans, initialMeans);
    }
    else
    {
        RandomizeMatrix(&newMeans);
    }

    for (int counter = 0; counter < epochNumber; ++counter)
        IterationKMeans(data, &newMeans, groups, groupCounts);

    free(groupCounts);
    free(groups);

    return newMeans;
}