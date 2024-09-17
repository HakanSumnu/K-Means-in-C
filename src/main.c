#include "k_means.h"
#include "scalers.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    srand(time(0));
    Matrix data;
    InitializeMatrix(&data, 6, 3);
    RandomizeMatrix(&data);
    MinMaxScaler minMaxScaler;
    InitializeMinMaxScaler(&minMaxScaler);
    Matrix transformedData = MinMaxScalerFitTransform(&minMaxScaler, &data);
    Matrix result = TrainKMeans(&transformedData, 3, 100, 0);
    Matrix transformedResult = MinMaxScalerDetransform(&minMaxScaler, &result);

    printf("Data\n");
    PrintMatrix(&data);
    printf("\nTransformed Data\n");
    PrintMatrix(&transformedData);
    printf("\nResult\n");
    PrintMatrix(&result);
    printf("\nTransformed Result\n");
    PrintMatrix(&transformedResult);

    DeleteReferenceFromMatrix(&data);
    DeleteReferenceFromMatrix(&transformedData);
    DeleteReferenceFromMatrix(&result);
    DeleteReferenceFromMatrix(&transformedResult);

    DeleteReferenceFromMinMaxScaler(&minMaxScaler);

    return 0;
}